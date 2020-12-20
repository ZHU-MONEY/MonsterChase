#include "MonsterChase.h"



MonsterChase::MonsterChase()
{
	askForMaxMonsterAmount();
	askForStartingMonsterAmount();
	currentMonsterAmount_ = 0;
	askForMonsterName();
	askForPlayerName();
}

void MonsterChase::askForStartingMonsterAmount()
{
	std::cout << "Enter starting Monster amount: " << std::endl;
	std::cin >> startMonsterAmount_;

	//check if input is integer
	while (std::cin.fail()) {
		std::cout << "Please input integer" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> startMonsterAmount_;
	}

	std::cin.ignore();
	if (startMonsterAmount_ < maxMonsterAmount_ + 1)
		std::cout << "Starting Monster amount is set to: " << startMonsterAmount_ << std::endl;
	else
	{
		std::cout << "Starting Monster amount CAN'T be larger than MAX Monster amount" << startMonsterAmount_ << std::endl;
		askForStartingMonsterAmount();
	}

}

void MonsterChase::askForMaxMonsterAmount()
{
	std::cout << "Enter maximum Monster amount that is less than 10: " << std::endl;
	std::cin >> maxMonsterAmount_;
	//check if input is integer
	while (std::cin.fail()) {
		std::cout << "Please input integer" << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> maxMonsterAmount_;
	}
	std::cin.ignore();
	if (maxMonsterAmount_ > 0 && maxMonsterAmount_ < MAX_MONSTER_AMOUNT + 1)
	{
		std::cout << "Maximum Monster amount is set to: " << maxMonsterAmount_ << std::endl;
		monsters_ = new Monster * [maxMonsterAmount_];
	}
	else
	{
		std::cout << "Maximum Monster amount CAN'T be more than 10 or less than 0!! Please enter a number between 0 and 10" << maxMonsterAmount_ << std::endl;
		askForMaxMonsterAmount();
	}
}

void MonsterChase::askForMonsterName()
{
	while (currentMonsterAmount_ < startMonsterAmount_) {
		char monsterNameBuffer[MAX_INPUT_SIZE + 1];

		//char* ptr = monsterNameBuffer;
		std::cout << "Enter monster name" << std::endl;

		std::cin.getline(monsterNameBuffer, MAX_INPUT_SIZE + 1);

		//assign default name if user doesn't input name for the monster
		if (strlen(monsterNameBuffer) ==0)
		{
			std::cout << "Monster's name is set to: --- defMon ---" << std::endl;
			createMonster("defMon");
		}
		//otherwise use user input name
		else {
			char* monsterName = (char*)malloc(strlen(monsterNameBuffer));

			for (int i = 0; i < strlen(monsterNameBuffer) + 1;i++) {
				monsterName[i] = monsterNameBuffer[i];
			}

			//strcpy_s(monsterName, ptr);
			std::cout << "Monster's name is set to: --- " << monsterName << " ---" << std::endl;
			createMonster(monsterName);
		}
	}
	//fill the remainning array elements that are not pointed to Monster to NULL
	for (int i = currentMonsterAmount_; i < maxMonsterAmount_;i++) {
		monsters_[i] = NULL;
	}

}

void MonsterChase::askForCommand()
{
	char moveDir;
	std::cout << "Where do you want to move" << std::endl;
	moveDir = _getch();
	switch (moveDir) {
	case 'w':
		player_->move(direction::Up);
		break;
	case 'a':
		player_->move(direction::Left);
		break;
	case 's':
		player_->move(direction::Down);
		break;
	case 'd':
		player_->move(direction::Left);
		break;
	case 'q':
		revertGameStatus();
		break;
	default:
		std::cout << "Please enter w-a-s-d to move or q to quit" << std::endl;
		askForCommand();
		break;
	}
}

void MonsterChase::createMonster(const char* name)
{
	Vector2D initialMonsterPos = createRandomLocation();
	monsters_[currentMonsterAmount_] = new Monster(initialMonsterPos, name, MAX_MONSTER_TIME_TO_LIVE);
	currentMonsterAmount_++;
}

void MonsterChase::createMonsterAtIndex(const char* name, int& i)
{
	Vector2D initialMonsterPos = createRandomLocation();
	monsters_[i] = new Monster(initialMonsterPos, name, MAX_MONSTER_TIME_TO_LIVE);
	currentMonsterAmount_++;
}

void MonsterChase::askForPlayerName()
{
	char playerName[MAX_INPUT_SIZE + 1];
	std::cout << "enter player name" << std::endl;

	std::cin.getline(playerName, MAX_INPUT_SIZE + 1);
	std::cout << "player name is: *** " << playerName << " ***" << std::endl;
	createPlayer(playerName);
}

void MonsterChase::createPlayer(const char* name)
{
	//player always start at the middle, this is hard coded
	Vector2D initialPlayerPos = Vector2D(25.0f, 25.0f);
	player_ = new Player(initialPlayerPos, name);
}

Vector2D MonsterChase::createRandomLocation()
{
	float randomX = rand() % MAX_X;
	float randomY = rand() % MAX_Y;
	return Vector2D(randomX, randomY);
}

void MonsterChase::printGameData()
{
	//print player
	std::cout << "Player " << player_->getName() << " is at " << player_->getPosition().getX() << "---" << player_->getPosition().getY() << std::endl;

	//print monster
	for (int i = 0; i < maxMonsterAmount_;i++) {
		if (monsters_[i] != NULL) {
			std::cout << "Monster " << monsters_[i]->getName() << " is at " << monsters_[i]->getPosition().getX() << "---" << monsters_[i]->getPosition().getY() << " time left to live " << monsters_[i]->getTimeToLive() << std::endl;
		}
	}

	std::cout << std::endl;
}

bool MonsterChase::getGameStatus()
{
	return gameStatus_;
}

void MonsterChase::revertGameStatus()
{
	gameStatus_ = !gameStatus_;
}

void MonsterChase::update()
{
	askForCommand();

	//update each monster
	//delete dead monsters
	for (int i = 0; i < maxMonsterAmount_;i++) {
		if (monsters_[i] != NULL)
		{
			if (monsters_[i]->getTimeToLive() <= 0) {
				delete monsters_[i];
				monsters_[i] = NULL;
				std::cout << "A monster died!" << std::endl;
				currentMonsterAmount_--;
			}
		}
	}
	//move each monsters
	for (int i = 0; i < maxMonsterAmount_;i++) {
		if (monsters_[i] != NULL)
		{
			monsters_[i]->move(*player_);
		}
	}

	//insert monster if not maxed out
	if (currentMonsterAmount_ < maxMonsterAmount_) {
		int randomNum = rand() % 10;
		// 10% of chance to add a new one
		if (randomNum < 2) {
			for (int i = 0; i < maxMonsterAmount_;i++) {
				if (monsters_[i] == NULL) {
					createMonsterAtIndex(DEFAULT_MONSTER_NAME, i);
					break;
				}
			}
		}
	}
	printGameData();
}

int main() {
	MonsterChase* MC = new MonsterChase();
	while (MC->getGameStatus()) {
		MC->update();
	}
	std::cout << "end of program" << std::endl;
}