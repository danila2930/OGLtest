#include <GLFW/glfw3.h>
#include <math.h>
#include <cmath>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <random>


const int ROWS = 400; // Количество строк
const int COLS = 400; // Количество столбцов


void updateGrid(int current[ROWS][COLS], int next[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int liveNeighbors = 0;
            // Перевіряємо всіх сусідів клітки
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0) continue; // Пропускаємо поточну клітинку

                    // Використовуємо модульну арифметику для обчислення індексів
                    int ni = (i + di + ROWS) % ROWS;
                    int nj = (j + dj + COLS) % COLS;

                    liveNeighbors += current[ni][nj];
                }
            }
            // Застосовуємо правила гри
            if (current[i][j] == 1 && (liveNeighbors < 2 || liveNeighbors > 3)) {
                next[i][j] = 0;
            }
            else if (current[i][j] == 0 && liveNeighbors == 3) {
                next[i][j] = 1;
            }
            else {
                next[i][j] = current[i][j];
            }
        }
    }
}


int drawKvad(GLFWwindow* window, int cordX, int cordY, int size) {
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

    float x = (cordX / (float)windowWidth) * 2.0f - 1.0f;
    float y = (cordY / (float)windowHeight) * 2.0f - 1.0f;

    

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x , y - 0.0020f * size);
    glVertex2f(x + 0.0020f * size, y- 0.0020f * size);
    glVertex2f(x+ 0.0020f * size, y);
    glEnd();
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

    int currentGrid[ROWS][COLS] = { {0} };
    int nextGrid[ROWS][COLS] = { {0} };

    

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            std::random_device rd; // Генератор випадкових чисел
            std::mt19937 gen(rd()); // Використання Mersenne Twister для генерації чисел
            std::uniform_int_distribution<> dis(1, 2); // Рівномірний розподіл від 1 до 2

            int random_number = dis(gen);
            if (random_number == 1) {
                currentGrid[i][j] = 1;
            }
        }
        
    }
    int size = 3;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
        glClear(GL_COLOR_BUFFER_BIT);
        


        updateGrid(currentGrid, nextGrid);
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                currentGrid[i][j] = nextGrid[i][j];
                if (currentGrid[i][j] == 1) {
                    
                    drawKvad(window, i * size + 50, j * size + 50, size);

                }
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
        /* Swap front and back buffers */
        

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

