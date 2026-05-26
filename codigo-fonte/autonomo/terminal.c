#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <unistd.h>
#include <pty.h>
#include <utmp.h>
#include <fcntl.h>
#include <signal.h>
#include <wait.h>

#define TAM_FONT 12
typedef enum {
    TAM_X = 1000,
    TAM_Y = 500
} TAM_TERMINAL;

extern char *environ[];
char *letra; 

int main(void)
{
    int slave;
    int master;
    int linha = 0;
    openpty(&master, &slave, NULL, NULL, NULL);
    pid_t pid = fork();
    if (pid == 0)
    {
        login_tty(slave);
        char *path = "/usr/bin/bash";
        char *argv[] = { path, NULL};
        
        int resul = execve(path,argv,environ);
        printf("resul\n");
        return 0;
    }
    else
    {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        SDL_Window *win = SDL_CreateWindow("terminal do leu :)",TAM_X, TAM_Y, 0);
        SDL_Renderer* rend = SDL_CreateRenderer(win, NULL);
        TTF_Init();
        
        SDL_Event event;
        
        
        TTF_Font* font = TTF_OpenFont("/usr/share/fonts/TTF/NotoSansNerdFont-ExtraCondensedMediumItalic.ttf",TAM_FONT);
        TTF_TextEngine* engine = TTF_CreateRendererTextEngine(rend);
        
        SDL_StartTextInput(win);
        
        for(;;){
            int status;
            pid_t pid_pai = waitpid(pid, &status, WNOHANG);
            if(pid_pai == pid) break;
            char buffer[1024 * 1024];
            while (SDL_PollEvent(&event))
            {
                if(event.type == SDL_EVENT_QUIT)
                { 
                    printf("%d\n", pid);
                    kill(pid , SIGKILL);
                    waitpid(pid, NULL, 0);
                    return 0;
                };
                if(event.type == SDL_EVENT_KEY_DOWN){
                    if(event.key.key == SDLK_ESCAPE)
                    {
                        kill(pid , SIGKILL);
                        waitpid(pid, NULL, 0);
                        return 0;
                    };
                    if(event.key.key == SDLK_RETURN)
                    {
                        linha += TAM_FONT;
                        write(master,"\n", 1);
                    };
                    if(event.key.key == SDLK_BACKSPACE) buffer[strlen(buffer) - 1] = '\0';
                }
                if(event.type == SDL_EVENT_TEXT_INPUT) 
                write(master, event.text.text, strlen(event.text.text));
            }
            fcntl(master, F_SETFL, O_NONBLOCK);
            int n = read(master, buffer, 1024 * 1024);
            
            SDL_RenderClear(rend);
            
            TTF_Text* text = TTF_CreateText(engine, font, buffer, 0);
            TTF_SetTextColor(text, 255, 255, 255, 255);
            SDL_SetRenderDrawColor(rend, 0, 0 ,0 ,255);
            TTF_DrawRendererText(text, TAM_Y/TAM_Y,linha);
            SDL_RenderPresent(rend);
            SDL_Delay(16);
            
            /*
            if(n > 0){
                FILE *file = fopen("terminal.txt", "a");
                fwrite(buffer, 1, n, file);
                fclose(file);
            
            }
            */
        }

        printf("%d\n", pid);
        TTF_DestroyGPUTextEngine(engine);
        TTF_CloseFont(font);
        SDL_DestroyWindow(win);
        SDL_DestroyRenderer(rend);
        SDL_Quit();
               
        }
            return 0;
        }
        