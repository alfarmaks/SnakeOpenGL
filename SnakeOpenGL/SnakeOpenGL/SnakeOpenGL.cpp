// SnakeOpenGL.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Direction.h"
#include "Apple.h"
#include <vector>
#include <time.h>
#define N 30
#define M 20
#define Scale 25
#define width Scale*N
#define height Scale*M


Direction dir = Direction::RIGHT;
int num = 2;
Apple *apple = new Apple();

//Parts of snake
struct Point
{
	int x;
	int y;
} snake[600];

//Draw field
void DrawField(){
	
	glColor3f(0.0, 0.7, 0.0);
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

//Change position of snake in every tick. Сheck if snake eats an apple or itself. 
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

	if (apple->getX() == snake[0].x && apple->getY() == snake[0].y){
		num++;
		apple->New();
	}
	for (int i = 1; i < num; i++){
		if (snake[i].x == snake[0].x && snake[i].y == snake[0].y){
			num = i;
		}
	}
	if (snake[0].x >= N){
		snake[0].x = 0;
	}
	if (snake[0].x < 0){
		snake[0].x = N - 1;
	}
	if (snake[0].y < 0){
		snake[0].y = M - 1;
	}
	if (snake[0].y >= M){
		snake[0].y = 0;
	}
}

//draw all parts of snake
void DrawSnake(){
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < num; i++){
		glRectf(snake[i].x * Scale + 1, snake[i].y * Scale + 1, (snake[i].x + 1)*Scale - 1, (snake[i].y + 1)*Scale - 1);
	}
}

//catch which key was press by user
void handleKey(int key, int a, int b){
	switch (key)
	{
		case 100: 
			if (dir != Direction::RIGHT)
				dir = Direction::LEFT; 
			break;
		case 103: 
			if (dir != Direction::DOWN)
				dir = Direction::UP; 
			break;
		case 102: 
			if (dir != Direction::LEFT)
				dir = Direction::RIGHT; 
			break;
		case 101: 
			if (dir != Direction::UP)
				dir = Direction::DOWN; 
			break;
		default:
			break;
	}
}

//Draw apples, Field and snake
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	apple->DrawApple();
	DrawField();
	DrawSnake();
	
	glFlush();
	
	glutSwapBuffers();
}

//timer which change information on display(calls function display and Tick)
void timer(int = 0){
	display();
	Tick();

	glutTimerFunc(250, timer, 0);
}

int main(int argc, char **argv)
{
	srand((unsigned)time(NULL));//randomize random
	apple->New();
	snake[0].x = 10;
	snake[0].y = 10;
	snake[1].x = 9;
	snake[1].y = 10;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("Snake");
	glClearColor(1.0, 1.0, 0.6, 1.0);//set bachground's color 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	
	glutDisplayFunc(display);
	glutTimerFunc(250, timer, 0);
	glutSpecialFunc(handleKey);

	glutMainLoop();
}