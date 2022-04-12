#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "util.h"
#include <math.h>

#define _USE_MATH_DEFINES
#define  M_PI 3.14159265358979323846

unsigned int program;
GLint color1Loc, color2Loc,color3Loc,color4Loc,color5Loc,color6Loc,color7Loc,color8Loc,scaleLoc;
GLint titik1Loc,titik2Loc;
float titik1,titik2;
float color1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float color2[] = { 1.0f, 0.5f, 0.2f, 1.0f };
float color3[] = { 1.0f, 1.0f, 0.4f, 1.0f };
float color4[] = { 1.0f, 0.1f, 1.0f, 1.0f };
float color5[] = { 0.9f, 1.0f, 0.5f, 1.0f };
float color6[] = { 0.6f, 0.8f, 1.0f, 1.0f };
float color7[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float color8[] = { 0.4f, 0.5f, 0.5f, 1.0f };

float xp=0, yp=0, r = 1, n = 8, a=0.5f , x, y;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_K && action == GLFW_PRESS)
    {
        for (int i = 0; i < 4; i++) {
            color1[i] = (rand() * 1.0f) / RAND_MAX;
            color2[i] = (rand() * 1.0f) / RAND_MAX;
            color3[i] = (rand() * 1.0f) / RAND_MAX;
            color4[i] = (rand() * 1.0f) / RAND_MAX;
            color5[i] = (rand() * 1.0f) / RAND_MAX;
            color6[i] = (rand() * 1.0f) / RAND_MAX;
            color7[i] = (rand() * 1.0f) / RAND_MAX;
            color8[i] = (rand() * 1.0f) / RAND_MAX;
        }

        std::cout << color1[0] << " " << color1[1] << " " << color1[2] << " " << color1[3] << std::endl;
        std::cout << color2[0] << " " << color2[1] << " " << color2[2] << " " << color2[3] << std::endl;
        glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);
        glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);
        glUniform4f(color3Loc, color3[0], color3[1], color3[2], color3[3]);
        glUniform4f(color4Loc, color4[0], color4[1], color4[2], color4[3]);
        glUniform4f(color5Loc, color5[0], color5[1], color5[2], color5[3]);
        glUniform4f(color6Loc, color6[0], color6[1], color6[2], color6[3]);
        glUniform4f(color7Loc, color7[0], color7[1], color7[2], color7[3]);
        glUniform4f(color8Loc, color8[0], color8[1], color8[2], color8[3]);
    }
    else if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {   
        a +=0.1f;
        glUniform1f(scaleLoc, a);
    }
    else if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        a -=0.1f;
        glUniform1f(scaleLoc, a);
    }
}



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);
    GLenum err = glewInit();

    float vertices[18] = {

    };
    int u = 0;
    a = (2 * 3.14) / n; //a = nilai 6.28 dibagi banyak segi
    for (int i = 0; i < n; i++) {
        x = xp + r * cos(i * a);
        y = yp + r * sin(i * a);
        vertices[u] = x;
        std::cout << vertices[u]; std::cout << endl;
        u = u + 1;
        vertices[u] = y;
        std::cout << vertices[u]; std::cout << endl;
        u = u + 1;
    }
    vertices[16] = xp;
    vertices[17] = yp;


    unsigned int indexArr[] = { 
        0,1,8,
        1,2,8,
        2,3,8,
        3,4,8,
        4,5,8,
        5,6,8,
        6,7,8,
        7,0,8
    };

    unsigned int vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);

    std::cout << vertexBuffer << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);


    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 24, indexArr, GL_STATIC_DRAW);

    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


    glShaderSource(vertexShader, 1, &vertexChar, NULL);

    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);


    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);



    glUseProgram(program);
    scaleLoc = glGetUniformLocation(program, "scale");
    glUniform1f(scaleLoc, a);

    color1Loc = glGetUniformLocation(program, "color1");
    glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);

    //membuat titik 1
    titik1Loc = glGetUniformLocation(program, "titik1");
    glUniform1f(titik1Loc,indexArr[0]);

    //membuat titik 2
    titik2Loc = glGetUniformLocation(program, "titik2");
    glUniform1f(titik2Loc, indexArr[1]);

    float z = 0.0f;
    float increment = 0.05f;
    color2Loc = glGetUniformLocation(program, "color2");
    glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);

    color3Loc = glGetUniformLocation(program, "color3");
    glUniform4f(color3Loc, color3[0], color3[1], color3[2], color3[3]);
    
    color4Loc = glGetUniformLocation(program, "color4");
    glUniform4f(color4Loc, color4[0], color4[1], color4[2], color4[3]);
    
    color5Loc = glGetUniformLocation(program, "color5");
    glUniform4f(color5Loc, color5[0], color5[1], color5[2], color5[3]);
    
    color6Loc = glGetUniformLocation(program, "color6");
    glUniform4f(color6Loc, color6[0], color6[1], color6[2], color6[3]);
    
    color7Loc = glGetUniformLocation(program, "color7");
    glUniform4f(color7Loc, color7[1], color7[1], color7[2], color7[3]);
    
    color8Loc = glGetUniformLocation(program, "color8");
    glUniform4f(color8Loc, color2[1], color8[1], color8[2], color8[3]);



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform4f(color1Loc, z, color1[1], color1[2], color1[3]);
        glUniform4f(color2Loc, z, color2[1], color2[2], color2[3]);
        glUniform4f(color3Loc, z, color3[1], color3[2], color3[3]);
        glUniform4f(color4Loc, z, color4[1], color4[2], color4[3]);
        glUniform4f(color5Loc, z, color5[1], color5[2], color5[3]);
        glUniform4f(color6Loc, z, color6[1], color6[2], color6[3]);
        glUniform4f(color7Loc, z, color7[1], color7[2], color7[3]);
        glUniform4f(color8Loc, z, color8[1], color8[2], color8[3]);

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr);

        if (z > 1.0f)
            increment = -0.005f;
        else if (z < 0.0f)
            increment = 0.005f;

        z += increment;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

}
