#pragma once
#include "Vector2D.h"
#include <string.h>


enum class direction { Up, Down, Left, Right };
class Player
{
public:
	const static int MAX_NAME_LENGTH = 10;

	//constructor and destructor
	Player();
	Player(const Vector2D& pos,const char* name);
	~Player();

	virtual void move(direction dir);

	//getters and setters
	Vector2D getPosition() const;
	void setPosition(const Vector2D& position);
	const char* getName();
	void setName(const char* name);

protected:
	Vector2D position_;
	char name_[MAX_NAME_LENGTH+1];
};

