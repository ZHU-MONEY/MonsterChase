#include "Player.h"

Player::Player()
{
	char as[] = "dftName_";
	setName(as);
}

Player::Player(const Vector2D& pos, char* name)
{
	setName(name);
	setPosition(pos);
}

Player::~Player()
{
	free(name_);
	name_ = NULL;
}

void Player::move(direction dir)
{
	switch (dir)
	{
	case direction::Up:
		position_.setY(position_.getY() + 1);
		break;
	case direction::Down:
		position_.setY(position_.getY() - 1);
		break;
	case direction::Left:
		position_.setX(position_.getX() - 1);
		break;
	case direction::Right:
		position_.setX(position_.getX() + 1);
		break;
	default:
		break;
	}
}

Vector2D Player::getPosition() const
{
	return position_;
}

void Player::setPosition(const Vector2D& position)
{
	position_ = position;
}

const char* Player::getName()
{
	return name_;
}

void Player::setName(char* name)
{
	name_ = name;
	//strcpy_s(name_, name);
}
