#include <GLFW/glfw3.h>
#include <math.h>

#include <stdlib.h>

#include <iostream>
#include <vector>
#include <random>


const int ROWS = 200; // Количество строк
const int COLS = 200; // Количество столбцов

struct Coord {
    int x;
    int y;
    bool alive;
    std::vector<int> gen;
};



int updateGrid(std::vector<Coord>& cords) {
    std::vector<Coord> tempCords = cords;

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            
        }
    }
    //1111
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int liveNeighbors = 0;
            // Перевіряємо всіх сусідів клітки
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0) continue; // Пропускаємо поточну клітинку

                    int ni = (i + di + ROWS) % ROWS;
                    int nj = (j + dj + COLS) % COLS;

                    if (cords[ni * COLS + nj].alive)
                        liveNeighbors++;
                }
            }

            // Застосовуємо правила гри
            int index = i * COLS + j;
            if (cords[index].alive && (liveNeighbors < 2 || liveNeighbors > 3)) {
                tempCords[index].alive = false;
            }
            else if (!cords[index].alive && liveNeighbors == 3) {
                tempCords[index].alive = true;
            }
            // Якщо жодне правило не застосовується, стан клітинки не змінюється,
            // тому немає потреби оновлювати tempCords[index].alive
        }
    }
    //1111

    cords = tempCords;
    return 0;
}


int drawKvad(GLFWwindow* window, int cordX, int cordY, int size, bool live) {
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

    float x = (cordX / (float)windowWidth) * 2.0f - 1.0f;
    float y = (cordY / (float)windowHeight) * 2.0f - 1.0f;

    
    if (live) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + 0.05f / size, y);
        glVertex2f(x + 0.05f / size, y - 0.05f / size);
        glVertex2f(x, y - 0.05f / size);
        glEnd();
    }

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



    

    //for (int i = 0; i < ROWS; ++i)
    //{
    //    for (int j = 0; j < COLS; ++j)
    //    {
    //        
    //    }
    //    
    //}
    /* Loop until the user closes the window */
    std::vector<Coord> cords;

    std::vector<int> myList(1);
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cords.push_back({ i, j, false, myList });
        }
    }
    for (int i = 1; i < ROWS - 1; i++) {
        for (int j = 1; j < ROWS - 1; j++) {
            if (rand() % 2 == 1) {
                int index = i * COLS + j;
                cords[index].alive = true;
            }
        }
    }

    while (!glfwWindowShouldClose(window))
    {
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        

        
        updateGrid(cords);
        int size = 4;
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                int index = i * COLS + j;
                Coord info = cords[index];
                drawKvad( window, i * 25 / size, j * 25 / size, size, info.alive);
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

