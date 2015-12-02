#pragma once
#include <cmath>

enum Direction
{
	FRONT,BACK,LEFT,RIGHT,CLOCKWISE,COUNTERCLOCKWISE
};

class Vec3
{
private:
	float x;
	float y;
	float z;
	float length;
	void updateLength(){ length = sqrt(powf(x, 2.0f) + powf(y, 2.0f) + powf(z, 2.0f)); }
public:
	Vec3(float x, float y, float z){ setValue(x,y,z); }
	~Vec3(){}
	void setValue(float x, float y, float z){ this->x = x; this->y = y; this->z = z; updateLength(); }
	float getX(){ return x; }
	float getY(){ return y; }
	float getZ(){ return z; }
	void increX(float i){ this->x += i; }
	void increY(float i){ this->y += i; }
	void increZ(float i){ this->z += i; }
	float getNormalizedX(){ return x / length; }
	float getNormalizedY(){ return y / length; }
	float getNormalizedZ(){ return z / length; }
	void increVec(Vec3 &v, Direction direction){
		switch (direction)
		{
		case FRONT:
			x += v.getNormalizedX();
			y += v.getNormalizedY();
			z += v.getNormalizedZ();
			break;
		case BACK:
			x -= v.getNormalizedX();
			y -= v.getNormalizedY();
			z -= v.getNormalizedZ();
			break;
		default:
			break;
		}
		updateLength();
	}
};

