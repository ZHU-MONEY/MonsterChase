#pragma once
#include "Player.h"
#include "Monster.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <conio.h>
class MonsterChase
{
private:
	Monster** monsters_;
	Player* player_;

	int startMonsterAmount_;
	int currentMonsterAmount_;
	int maxMonsterAmount_;

	bool gameStatus_= true;

	static const int MAX_MONSTER_TIME_TO_LIVE = 1;

	static constexpr const char* DEFAULT_MONSTER_NAME = "default";
	static const char* defaultNamePointer;
	//static const char defaultName[256];
	static const int MAX_INPUT_SIZE = 256;
	static const int MAX_MONSTER_AMOUNT = 10;
	static const int MAX_X = 50;
	static const int MAX_Y = 50;

public:

	MonsterChase();
	~MonsterChase();
	void askForStartingMonsterAmount();
	void askForMaxMonsterAmount();
	void askForMonsterName();
	void askForCommand();
	void createMonster(char* name);
	void createMonsterAtIndex(char* name, int& i);
	void askForPlayerName();
	void createPlayer(char* name);
	Vector2D createRandomLocation();
	void printGameData();
	bool getGameStatus();
	void revertGameStatus();
	void update();
	char defaultMonsterName[8] = "default";
	char* ptr = defaultMonsterName;

};

