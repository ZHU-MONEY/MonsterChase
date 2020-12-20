#include "Vector2D.h"

Vector2D::Vector2D()
{
	x_ = 0;
	y_ = 0;
}

Vector2D::Vector2D(float x, float y)
{
	x_ = x;
	y_ = y;
}

Vector2D::Vector2D(const Vector2D& copy)
{
	x_ = copy.getX();
	y_ = copy.getY();
}

Vector2D::~Vector2D()
{
}

void Vector2D::setX(float x)
{
	x_ = x;
}

void Vector2D::setY(float y)
{
	y_ = y;
}

void Vector2D::setXY(float x, float y)
{
	x_ = x;
	y_ = y;
}


float Vector2D::getX() const
{
	return x_;
}

float Vector2D::getY() const
{
	return y_;
}

Vector2D Vector2D::operator=(const Vector2D& vec)
{
	setXY(vec.getX(), vec.getY());
	return *this;
}

Vector2D Vector2D::operator+(const Vector2D& vec) const
{
	Vector2D* v = new Vector2D(x_ + vec.getX(), y_ + vec.getY());
	return *v;
}

Vector2D Vector2D::operator+=(const Vector2D& vec)
{
	setXY(x_ + vec.getX(), y_ + vec.getY());
	return *this;
}

Vector2D Vector2D::operator-(const Vector2D& vec) const
{
	Vector2D* v = new Vector2D(x_ - vec.getX(), y_ - vec.getY());
	return *v;
}

Vector2D Vector2D::operator-=(const Vector2D& vec)
{
	setXY(x_ - vec.getX(), y_ - vec.getY());
	return *this;
}

Vector2D Vector2D::operator*=(float scale)
{
	setXY(x_ * scale, y_ * scale);
	return *this;
}

bool Vector2D::operator==(const Vector2D& vec) const
{
	return(x_ == vec.getX() && y_ == vec.getY());
}

bool Vector2D::operator!=(const Vector2D& vec) const
{
	return (x_ != vec.getX() && y_ != vec.getY());
}

Vector2D Vector2D::operator-() const
{
	Vector2D *v = new Vector2D(-x_, -y_);
	return *v;
}

