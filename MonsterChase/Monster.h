#pragma once
#include "Player.h"
class Monster : public Player
{
public:
	Monster();
	Monster(const Vector2D& pos, const char* name, const int time);
	~Monster();
	void move(Player& targetPlayer);
	void setTimeToLive(int time);
	int getTimeToLive() const;
	void decreaseTimeToLive();
private:
	int timeToLive_;
};

