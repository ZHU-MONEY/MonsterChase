#include "Monster.h"
#include <stdlib.h>

Monster::Monster()
{

}

Monster::Monster(const Vector2D& pos, char* name, const int time)
{
	setName(name);
	setPosition(pos);
	setTimeToLive(time);
}

Monster::~Monster()
{
	free(name_);
	name_ = NULL;
}

void Monster::move(Player& targetPlayer)
{
	Vector2D targetPlayerPosition = targetPlayer.getPosition();
	//if the monster didn't catch the player, move randomly
	if (position_ != targetPlayerPosition) {
		int randomDirection = rand() % 4;
		Player::move((direction)randomDirection);
		decreaseTimeToLive();
	}
	else {
		//game over
	}
}

void Monster::setTimeToLive(int time)
{
	timeToLive_ = time;
}

int Monster::getTimeToLive() const
{
	return timeToLive_ +1;
}

void Monster::decreaseTimeToLive()
{
	timeToLive_ -= 1;
}

