#pragma once

#include <stdio.h>
class Vector2D
{

private:
	float x_;
	float y_;

public:

	//const static Vector2D UNIT_X;

	//constructor
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D& copy);
	//Vector2D(const Vector2D& copy);

	//destructor
	~Vector2D();

	//setters and getters
	void setX(float x);
	void setY(float y);
	void setXY(float x, float y);
	float getX() const;
	float getY() const;

	Vector2D operator=(const Vector2D& vec);

	Vector2D operator+(const Vector2D& vec) const;
	Vector2D operator+=(const Vector2D& vec);
	Vector2D operator-(const Vector2D& vec) const;
	Vector2D operator-=(const Vector2D& vec);
	Vector2D operator*=(float scale);

	bool operator==(const Vector2D& vec) const;
	bool operator!=(const Vector2D& vec) const;

	Vector2D operator-() const;

};

