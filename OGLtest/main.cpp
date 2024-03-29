#include <GLFW/glfw3.h>
#include <math.h>
#include <cmath>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <random>

//3d

const double PI = 3.14159265358979323846;

struct Coord {
    float x;
    float y;
    float z;
};


int drawLine(GLFWwindow* window, int StartX, int StartY, int EndX, int EndY) {
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

    float x = (StartX / (float)windowWidth) * 2.0f - 1.0f;
    float y = (StartY / (float)windowHeight) * 2.0f - 1.0f;

    float x2 = (EndX / (float)windowWidth) * 2.0f - 1.0f;
    float y2 = (EndY / (float)windowHeight) * 2.0f - 1.0f;




    return 0;
}






int main(void)
{

    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(1000, 1000, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    std::vector<Coord> cords;


    cords.push_back({ 500, 200 , 90 });
    


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);



      /*for (size_t i = 0; i < cords.size() - 1; ++i) { 
            Coord currentCoord = cords[i];
            Coord nextCoord = cords[i + 1];
            if (nextCoord.x != 500)
            {
                drawLine(window, currentCoord.x, currentCoord.y, nextCoord.x, nextCoord.y);
            }
        }*/



        glfwSwapBuffers(window);
        glfwPollEvents();
        /* Swap front and back buffers */


        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

