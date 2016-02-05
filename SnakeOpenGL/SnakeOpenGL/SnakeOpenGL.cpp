// SnakeOpenGL.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Direction.h"
#include <random>
#include <time.h>
#include <GL\glut.h>
#define N 30
#define M 20
#define Scale 25
#define width Scale*N
#define height Scale*M


Direction dir = Direction::RIGHT;
int num = 2;

class Apple
{
public:
	int x, y;

	void New(){
		x = std::rand() % N;
		y = std::rand() % M;
	}
	void DrawApple(){
		glColor3f(1.0, 0.0, 0.0);
		glRectf(x * Scale + 1, y * Scale + 1, (x + 1) * Scale - 1, (y + 1) * Scale - 1);
	}
} apple;

struct Point
{
	int x;
	int y;
} snake[100];

void DrawField(){
	
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);

	for (int i = 0; i < width; i += Scale){
		glVertex2f(i, 0);
		glVertex2f(i, height);
	}
	for (int j = 0; j < height; j += Scale){
		glVertex2f(0, j);
		glVertex2f(width, j);
	}
	glEnd();
}

void Tick(){
	for (int i = num; i > 0; --i){
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}

	if (dir == Direction::DOWN){
		snake[0].y += 1;
	}
	else if (dir == Direction::UP){
		snake[0].y -= 1;
	}
	else if (dir == Direction::LEFT){
		snake[0].x -= 1;
	}
	else if (dir == Direction::RIGHT){
		snake[0].x += 1;
	}
}

void DrawSnake(){
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < num; i++){
		glRectf(snake[i].x * Scale + 1, snake[i].y * Scale + 1, (snake[i].x + 1)*Scale - 1, (snake[i].y + 1)*Scale - 1);
	}
}

void handleKey(int key, int a, int b){
	switch (key)
	{
		case 100: dir = Direction::LEFT; break;
		case 103: dir = Direction::UP; break;
		case 102: dir = Direction::RIGHT; break;
		case 101: dir = Direction::DOWN; break;
		default:
			break;
	}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	apple.DrawApple();
	DrawField();
	DrawSnake();
	glFlush();
}

void timer(int = 0){
	display();
	Tick();

	glutTimerFunc(250, timer, 0);
}

int main(int argc, char **argv)
{
	srand((unsigned)time(NULL));//randomize random
	
	apple.New();
	snake[0].x = 10;
	snake[0].y = 10;
	snake[1].x = 9;
	snake[1].y = 10;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("Snake");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	
	glutDisplayFunc(display);
	glutTimerFunc(250, timer, 0);
	glutSpecialFunc(handleKey);

	glutMainLoop();
}