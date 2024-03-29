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
    float rot;
};


int drawLine(GLFWwindow* window, int StartX, int StartY, int EndX, int EndY) {
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

    float x = (StartX / (float)windowWidth) * 2.0f - 1.0f;
    float y = (StartY / (float)windowHeight) * 2.0f - 1.0f;

    float x2 = (EndX / (float)windowWidth) * 2.0f - 1.0f;
    float y2 = (EndY / (float)windowHeight) * 2.0f - 1.0f;
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x2, y2);
    glEnd();



    return 0;
}

int calculate(GLFWwindow* window, std::vector<Coord>& cords, int StartX, int StartY, float rotate, int curentnum) {

    int windowWidth = 1000, windowHeight = 1000;
    float x = (StartX / (float)windowWidth) * 2.0f - 1.0f;
    float y = (StartY / (float)windowHeight) * 2.0f - 1.0f;

    float EndX = 0;
    float EndY = 0;
    float size = 5;
    float radians = rotate * PI / 180.0;

    if (curentnum % 2 == 0) {
        curentnum = curentnum / 2;

        rotate -= 11;
        EndX = StartX + size * cos(radians);
        EndY = StartY + size * sin(radians);


    }

    else
    {
        curentnum = curentnum * 3 + 1;

        rotate += 18;

        EndX = StartX + size * cos(radians);
        EndY = StartY + size * sin(radians);

    }

    cords.push_back({ EndX, EndY, rotate });


    /*if (curentnum != 2) {
        calculate(window, cords, EndX, EndY, rotate, curentnum, step);
    }*/

    return curentnum;


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



    for (int i = 0; i < 100000; i++)
    {
        cords.push_back({ 500, 200 , 90 });
        int curnum = rand() % 10000000;
        while (true)
        {
            Coord lastCoord = cords.back();
            float lastX = lastCoord.x;
            float lastY = lastCoord.y;
            float lastrot = lastCoord.rot;
            if (curnum < 4) {
                break;
            }
            else
            {
                curnum = calculate(window, cords, lastX, lastY, lastrot, curnum);
            }
        }

    }


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);



        for (size_t i = 0; i < cords.size() - 1; ++i) { // Итерируем до предпоследнего элемента
            Coord currentCoord = cords[i]; // Текущая пара координат
            Coord nextCoord = cords[i + 1]; // Следующая пара координат
            if (nextCoord.x != 500)
            {
                drawLine(window, currentCoord.x, currentCoord.y, nextCoord.x, nextCoord.y);
            }
            // Ваш код здесь: работа с currentCoord и nextCoord
        }



        glfwSwapBuffers(window);
        glfwPollEvents();
        /* Swap front and back buffers */


        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

