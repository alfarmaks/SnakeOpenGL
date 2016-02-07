#include <GL\glut.h>
#include <random>
#ifndef APPLE_INCLUDED
#define APPLE_INCLUDED
#define N 30
#define M 20
#define Scale 25
class Apple
{
private:
	int x, y;
public:
	Apple(int _x = 0, int _y = 0){
		this->x = _x;
		this->y = _y;
	}

	int getX()const {
		return this->x;
	}
	int getY() const{
		return this->y;
	}

	void New(){
		x = std::rand() % N;
		y = std::rand() % M;
	}
	void DrawApple(){
		glColor3f(1.0, 0.0, 0.0);
		glRectf(x * Scale + 1, y * Scale + 1, (x + 1) * Scale - 1, (y + 1) * Scale - 1);
	}
};
#endif