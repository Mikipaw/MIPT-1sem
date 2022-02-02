#include "CPU.h"

const int       WIDTH     = 800;
const int       HEIGHT    = 600;
const int       ROWS      = 30;
const int       COLUMNS   = 40;

int number_of_cmds = 0;
FILE* noc = fopen (_number_of_commands, "rb");

CREATE_CPU(cpu, number_of_cmds, 1);

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    float color = 0;
    glBegin(GL_QUADS);
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            color = (float) cpu.ram(COLUMNS * i + j);
            if(color != 0)
            glColor3f((float)((int) (color + i + j) % 9) / 10 ,
                      (float)((int) (color + i - j) % 8) / 10,
                      (float)((int) (color - i + j) % 7) / 10);
            else glColor3f(0, 0, 0);
            glVertex2f(i *     HEIGHT / ROWS, j      * WIDTH / COLUMNS);
            glVertex2f((i + 1) * HEIGHT / ROWS, j      * WIDTH / COLUMNS);
            glVertex2f((i + 1) * HEIGHT / ROWS, (j + 1)  * WIDTH / COLUMNS);
            glVertex2f(i     * HEIGHT / ROWS, (j + 1)  * WIDTH / COLUMNS);

        }
    } glEnd();
    glFlush();
}


int main(int argc, char** argv) {
    fclose(noc);
    //CPU_info(cpu);


    int check = cpu.Work();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Video memory");
    glOrtho (0, WIDTH, HEIGHT, 0, -1, 1);
    glutDisplayFunc(Display);
    CPU_info(cpu);
    glutMainLoop();


    if(check != 0) {
        CPU_info(cpu);
        return check;
    }

    return 0;
}
