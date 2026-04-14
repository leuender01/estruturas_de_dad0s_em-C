#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

// Shader que calcula a raiz quadrada (sqrt) na GPU
const char* shaderSource = 
    "#version 330 core\n"
    "out vec4 color;\n"
    "void main() {\n"
    "    float x = gl_FragCoord.x * gl_FragCoord.y;\n" // Pega um número baseado na posição do pixel
    "    float res = sqrt(x);\n"                     // O CÁLCULO pesado
    "    color = vec4(res, 0.0, 0.0, 1.0);\n"         // Guarda o resultado na cor
    "}\n";

int main() {
    if (!glfwInit()) return -1;
    
    // Criamos uma janela invisível (offscreen) só para usar a GPU
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(2000, 2000, "GPU Bench", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    // Compilação rápida do Shader
    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &shaderSource, NULL);
    glCompileShader(fs);
    unsigned int program = glCreateProgram();
    glAttachShader(program, fs);
    glLinkProgram(program);

    // Medição de tempo
    double startTime = glfwGetTime();

    // Executa o desenho (isso dispara os 4 milhões de cálculos de uma vez)
    glUseProgram(program);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 1.0f,  1.0f);
        glVertex2f(-1.0f,  1.0f);
    glEnd();
    glFinish(); // Força a GPU a terminar tudo antes de medir o tempo

    double endTime = glfwGetTime();
    printf("GPU processou 4 milhoes de raizes quadradas em: %f segundos\n", endTime - startTime);

    glfwTerminate();
    return 0;
}