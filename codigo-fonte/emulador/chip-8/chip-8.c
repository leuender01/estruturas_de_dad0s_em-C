#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const uint8_t fontset[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

typedef struct{
    uint8_t V[16];
    uint16_t pc;
    uint16_t i;
    uint8_t sp;
    uint16_t stack[16];
    bool display[64][32];
    uint8_t ram[4096];
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t keypad[16];
} Chip8;

void chip8_cyrcle(Chip8 *cpu, FILE *fd);
void init_chipt0(Chip8 *cpu);
uint8_t chip8_load_rom(Chip8 *cpu, const char *filename);
uint8_t map_sdl_key(SDL_Keycode key);

int draw = 0;

int main(int argc, char *argv[]){

    for(int i = 0; i < argc; i++){
        printf("%s\n", argv[i]);

    }
    if(argc > 2 || argc < 2) return 0;
    FILE *fd = fopen("opcodes.txt","ab");
    Chip8 cpu;
    init_chipt0(&cpu);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao inicializar o SDL! Erro: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* janela = SDL_CreateWindow("CHip-8",640, 320,SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderizador = SDL_CreateRenderer(janela, NULL);
                                            
    if(!chip8_load_rom(&cpu, argv[1])){
        printf("Erro ao carregar arquivo\n");
        return -1;
    };
    bool rodando = true;
    SDL_Event evento;
    uint64_t tempo_anterior_cpu = SDL_GetTicks();
    uint64_t tempo_anterior_timers = SDL_GetTicks();

    const uint64_t MS_POR_CICLO_CPU = 2;
    const uint64_t MS_POR_DECREMENTO_TIMER = 16;

    while(rodando)
    {
        uint64_t tempo_atual = SDL_GetTicks();
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_EVENT_QUIT) {
                rodando = false;
            }
            if (evento.type == SDL_EVENT_KEY_DOWN) {
                uint8_t chip8_key = map_sdl_key(evento.key.key);
                if (chip8_key != 0xFF) {
                    cpu.keypad[chip8_key] = 1;
                }
            }
            if (evento.type == SDL_EVENT_KEY_UP) {
                uint8_t chip8_key = map_sdl_key(evento.key.key);
                if (chip8_key != 0xFF) {
                    cpu.keypad[chip8_key] = 0;
                }
            }
        }
        if (tempo_atual - tempo_anterior_cpu >= MS_POR_CICLO_CPU) {
            chip8_cyrcle(&cpu, fd);
            tempo_anterior_cpu = tempo_atual;
        }

        if (tempo_atual - tempo_anterior_timers >= MS_POR_DECREMENTO_TIMER) {
            if (cpu.delay_timer > 0) cpu.delay_timer--;
            if (cpu.sound_timer > 0) cpu.sound_timer--;
            tempo_anterior_timers = tempo_atual;
        }


        if(draw == 1)
        {
            SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
            SDL_RenderClear(renderizador);

            SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255);
            for(int line = 0 ;line < 32; line++){
                for(int collumn = 0; collumn < 64; collumn++)
                {
                    if(cpu.display[collumn][line] == true){
                        SDL_FRect pixel;
                        pixel.x = collumn * 10.0f;
                        pixel.y = line * 10.0f;
                        pixel.w = 10.0f;
                        pixel.h = 10.0f;

                        SDL_RenderFillRect(renderizador, &pixel);
                    }
                }
            }
            SDL_RenderPresent(renderizador);
            draw = 0;
        }
        SDL_Delay(2);
    }
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    SDL_Quit();
    fclose(fd);
    return 0;
}

void init_chipt0(Chip8 *cpu)
{
    memset(cpu, 0, sizeof(Chip8));
    cpu->pc = 0x200;

    
    for(int i = 0; i < 80; i++)
    {
       cpu->ram[i] = fontset[i];

    }
   
}

uint8_t chip8_load_rom(Chip8 *cpu, const char *filename)
{
    FILE *fd = fopen(filename, "rb");
    if( fd == NULL) return 0;
    fread(&cpu->ram[0x200], 1, sizeof(cpu->ram) - 0x200, fd);
    fclose(fd);
    return 1;
}

void chip8_cyrcle(Chip8 *cpu, FILE *fd)
{
    uint16_t opcode = (cpu->ram[cpu->pc] << 8) | cpu->ram[cpu->pc + 1];
    cpu->pc += 2;
    uint16_t nnn = opcode & 0x0FFF;
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    uint8_t kk = opcode & 0x00FF;
    /*
    printf("opcode [binario: %0b hexadecimal: %0x numero inteiro: %u]\n\r \
nnn 12-bits endereço[[binario: %0b hexadecimal: %0x numero inteiro: %u]]\n\r \
x registrador VX [binario: %0b hexadecimal: %0x numero inteiro: %u]\n\r \
y registrador VY [binario: %0b hexadecimal: %0x numero inteiro: %u]\n\r \
kk constante de 8-bits [binario: %0b hexadecimal: %0x numero inteiro: %u]\n\r",
        opcode,
            opcode,
            opcode,
            nnn,
            nnn,
            nnn,
            x,
            x,
            x,
            y,
            y,
            y,
            kk,
            kk,
            kk
        );
        */
    switch(opcode & 0xF000)
    {
        case 0x0000:
            if(opcode == 0x00E0)
            {
                memset(cpu->display, 0, sizeof(cpu->display));
                fprintf(fd,"instrução: %0x limapr tela \033[32mexecultada\033[0m\n", opcode);


            }else if( opcode == 0x00EE)
            {
                cpu->sp--;
                fprintf(fd,"instrução: %0x Retornando uma sub-rotina\033[32mexecultada\033[0m\n", opcode);
                cpu->pc = cpu->stack[cpu->sp];
            }
            break;
        case 0x1000:
            cpu->pc = nnn;
            fprintf(fd,"instrução: %0x saltando para o enderço %i \033[32mexecultada\033[0m\n", opcode, nnn);
            break;
        case 0x2000:
            fprintf(fd,"instrução: %0x chamando uma sub-rotina no enderço %i \033[32mexecultada\033[0m\n", opcode, nnn);
            cpu->stack[cpu->sp] = cpu->pc;
            cpu->sp++;
            cpu->pc = nnn;
            break;
        case 0x3000:
            fprintf(fd,"instrução: %0x iginorando a proxima instrução se V[%d] == %i\033[32mexecultada\033[0m\n", opcode, x,kk);
            if(cpu->V[x] == kk) cpu->pc += 2;
            break;
        case 0x4000:
            fprintf(fd,"instrução: %0x iginorando a proxima instrução se V[%d] != %i \033[32mexecultada\033[0m\n", opcode, x,kk);
            if(cpu->V[x] != kk) cpu->pc += 2;
            break;
        case 0x5000:
            fprintf(fd,"instrução: %0x iginorando a proxima instrução se V[%d] == V[%d] \033[32mexecultada\033[0m\n", opcode, x,y);
            if(cpu->V[x] == cpu->V[y]) cpu->pc += 2;
            break;
        case 0x6000:
            cpu->V[x] = kk;
            fprintf(fd,"instrução: %0x Define V[%d] = %i \033[32mexecultada\033[0m\n", opcode, x, kk);
            break;
        case 0x7000:
            cpu->V[x] += kk;
            fprintf(fd,"instrução: %0x Define V[%d] += %i \033[32mexecultada\033[0m\n", opcode, x, kk);
            break;
        case 0x8000:
            uint8_t arg = opcode & 0x000F;
            uint8_t carry = 0;
            switch(arg){
                case 0x0:
                    fprintf(fd,"instrução: %0x  Define V[%i] = V[%i] \033[32mexecultada\033[0m\n", opcode, x, y);
                    cpu->V[x] =  cpu->V[y];
                    break;
                case 0x1:
                    fprintf(fd,"instrução: %0x  Define V[%i] |= V[%i] \033[32mexecultada\033[0m\n", opcode, x, y);
                    cpu->V[x] |= cpu->V[y];
                    break;
                case 0x2:
                    fprintf(fd,"instrução: %0x  Define V[%i] &= V[%i] \033[32mexecultada\033[0m\n", opcode, x, y);
                    cpu->V[x] &= cpu->V[y];
                    break;
                case 0x3:
                    fprintf(fd,"instrução: %0x  Define V[%i] ^= V[%i] \033[32mexecultada\033[0m\n", opcode, x, y);
                    cpu->V[x] ^= cpu->V[y];
                    break;
                case 0x4:
                    fprintf(fd,"instrução: %0x  Define V[%i] += V[%i] \033[32mexecultada\033[0m\n", opcode, x, y);
                    uint16_t sum = cpu->V[x] + cpu->V[y];
                    cpu->V[x] = sum & 0xFF;
                    cpu->V[0xF] = (sum > 255) ? 1 : 0;
                    break;
                case 0x5:
                    fprintf(fd,"instrução: %0x  Define V[%i] -= V[%i] \033[32mexecultada\033[0m\n", opcode, x, y);
                    carry = (uint8_t)((cpu->V[x] >= cpu->V[y]) ? 1 : 0);
                    cpu->V[x] -= cpu->V[y];
                    cpu->V[0xF] = carry;
                    break;
                case 0x6:
                    fprintf(fd,"instrução: %0x  Define V[%i] >>= 1 \033[32mexecultada\033[0m\n", opcode, x);
                    cpu->V[0xF] = cpu->V[x] & 0x1;
                    cpu->V[x] >>= 1;
                    break;
                case 0x7:
                    fprintf(fd,"instrução: %0x  Define V[%i] = V[%i] -  V[%i] \033[32mexecultada\033[0m\n", opcode, x, y, x);
                    carry = (uint8_t)((cpu->V[y] >= cpu->V[x]) ? 1 : 0);
                    cpu->V[x] = cpu->V[y] - cpu->V[x];
                    cpu->V[0xF] = carry;
                    break;
                case 0xE:
                    fprintf(fd,"instrução: %0x  Define V[%i] <<= 1 \033[32mexecultada\033[0m\n", opcode, x);
                    cpu->V[0xF] = (cpu->V[x] & 0x80) >> 7;
                    cpu->V[x] <<= 1;
                    break;
            }
            break;
        case 0x9000:
            fprintf(fd,"instrução: %0x iginorando a proxima instrução se V[%d] != V[%d] \033[32mexecultada\033[0m\n", opcode, x, kk);
            if(cpu->V[x] != cpu->V[y]) cpu->pc += 2;
            break;
        case 0xA000:
            cpu->i = nnn;
            fprintf(fd,"instrução: %0x Denifine I(index) = para o enderço %i\033[32mexecultada\033[0m\n", opcode, nnn);
            break;
        case 0xB000:
            cpu->pc = cpu->V[0] + nnn;
            fprintf(fd,"instrução: %0x pc = V[0] + %i\033[32mexecultada\033[0m\n", opcode, nnn);
            break;
        case 0xC000:
            fprintf(fd,"instrução: %0x Define um numero aleatorio V[%i] = rand() & %i\033[32mexecultada\033[0m\n", opcode);
            cpu->V[x] = rand() & kk;
            break;
        case 0xD000:
            uint8_t N = opcode & 0x000F;
            uint8_t codx = cpu->V[x];
            uint8_t cody = cpu->V[y];
            fprintf(fd,"instrução: %0x nas cordenadas (V[%i], V[%i]) desenha uma sprite com 8 pixels de largura e %i de altura a partir do endereço I = %i\033[32mexecultada\033[0m\n", opcode,x, y, N, cpu->i);
            cpu->V[0xF] = 0;
            for(int rline = 0; rline < N; rline++)
            {
                uint8_t sprite_byte = cpu->ram[cpu->i + rline];
                
                for(int bcol = 0; bcol < 8 ; bcol++)
                {
                    if((sprite_byte & (0x80 >> bcol)) != 0)
                    {
                        int screen_x = codx + bcol;
                        int screen_y = cody + rline;
                        if(cpu->display[screen_x][screen_y] == 1){
                            cpu->V[0xF] = 1;
                        }
                        cpu->display[screen_x][screen_y] ^= 1;
                    }

                }
            }
            draw = 1;
            break;
        case 0xE000:
            if(kk == 0x9E){
                fprintf(fd,"instrução: %0x pula a proxim se key == V[%i]\033[33mexecultada\033[0m\n", opcode, x);
                
                if(cpu->keypad[cpu->V[x]] == 1){
                    cpu->pc += 2;
                }
            }else if(kk == 0xA1){
                fprintf(fd,"instrução: %0x pula a proxim se key != V[%i]\033[33mexecultada\033[0m\n", opcode, x);
                
                if(cpu->keypad[cpu->V[x]] != 1){
                    cpu->pc += 2;
                }
            }
            break;
        case 0xF000:
            if(kk == 0x07){
                cpu->V[x] = cpu->delay_timer;
                fprintf(fd,"instrução: %0x \033[33mexecultado\033[0m\n", opcode);
            }else if(kk == 0x0A){
                bool tecla_precionada = false;
                for(int i = 0; i < 16; i++){
                    if(cpu->keypad[i] == 1){
                        cpu->V[x] = i;
                        tecla_precionada = true;
                    }
                }
                if(!tecla_precionada){
                    cpu->pc -= 2;
                }
                fprintf(fd,"instrução: %0x \033[33mexecultado\033[0m\n", opcode);
            
            }else if(kk == 0x15){
                fprintf(fd,"instrução: %0x \033[33mexecultado\033[0m\n", opcode);
                cpu->delay_timer = cpu->V[x];
            }else if(kk == 0x18){
                fprintf(fd,"instrução: %0x \033[33mexecultado\033[0m\n", opcode);
                cpu->sound_timer = cpu->V[x];
            }else if(kk == 0x1E){
                fprintf(fd,"instrução: %0x \033[33mexecultado\033[0m\n", opcode);
                cpu->i += cpu->V[x];
            }else if(kk == 0x29){
                fprintf(fd,"instrução: %0x \033[33mexecultado\033[0m\n", opcode);
                cpu->i = cpu->V[x] * 5;
            }else if(kk == 0x33){
                fprintf(fd,"instrução: %0x \033[33mexecultado\033[0m\n", opcode);
                uint8_t value = cpu->V[x];
                cpu->ram[cpu->i]     = value / 100;
                cpu->ram[cpu->i + 1] = (value / 10 ) % 10;
                cpu->ram[cpu->i + 2] = value % 10;
            }else if(kk == 0x55){
                fprintf(fd,"instrução: %0x \033[33mexecultado\033[0m\n", opcode);
                for(int i = 0; i <= x; i++){
                    cpu->ram[cpu->i + i] = cpu->V[i];
                }
            }else if(kk == 0x65){
                fprintf(fd,"instrução: %0x \033[33mexecultado\033[0m\n", opcode);
                for(int i = 0; i <= x; i++){
                    cpu->V[i] = cpu->ram[cpu->i + i];
                }
            }
            break;
        default:
            fprintf(fd,"instrução: %0x nao\033[33mexecultada\033[0m\n", opcode);
            break;
    }
}

uint8_t map_sdl_key(SDL_Keycode key) {
    switch (key) {
        case SDLK_X: return 0x0;
        case SDLK_1: return 0x1;
        case SDLK_2: return 0x2;
        case SDLK_3: return 0x3;
        case SDLK_Q: return 0x4;
        case SDLK_W: return 0x5;
        case SDLK_E: return 0x6;
        case SDLK_A: return 0x7;
        case SDLK_S: return 0x8;
        case SDLK_D: return 0x9;
        case SDLK_Z: return 0xA;
        case SDLK_C: return 0xB;
        case SDLK_4: return 0xC;
        case SDLK_R: return 0xD;
        case SDLK_F: return 0xE;
        case SDLK_V: return 0xF;
        default:     return 0xFF; // Tecla inválida
    }
}
