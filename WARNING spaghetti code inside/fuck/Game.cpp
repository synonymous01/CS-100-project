#include "Game.h"
#include <iostream>

// Game::Game() : mWindow(sf::VideoMode(640, 480), "SFML Application")
// {
// 	mBgTexture.loadFromFile("./Resources/Desert.png");
// 	mBackground.setTexture(mBgTexture);
// 	mBackground.setPosition(0, 0);
// }

// Game::Game(int x, int y, std::string title, std::string path) : mWindow(sf::VideoMode(x, y), title)
// {
// 	mPTexture.loadFromFile(path);
// 	mPlayer.setTexture(mPTexture);
// 	mPlayer.setPosition(10.0f, 10.0f);
// 	mBgTexture.loadFromFile("./Resources/Desert.png");
// 	mBackground.setTexture(mBgTexture);
// 	mBackground.setPosition(0, 0);
// }

// void Game::handleInput(sf::Keyboard::Key)
// {

// }

// void Game::processEvents()
// {
// 	sf::Event event;
// 	while (mWindow.pollEvent(event))
// 	{
// 		switch (event.type)
// 		{
// 		case sf::Event::KeyPressed:
// 			handleInput(event.key.code);
// 			break;
// 		case sf::Event::Closed:
// 			mWindow.close();
// 			break;
// 		}
// 	}
// }

// void Game::update()
// {

// }

// void Game::render()
// {
// 	mWindow.clear();
// 	mWindow.draw(mBackground);
// 	mWindow.draw(mPlayer);
// 	mWindow.display();
// }

// void Game::run()
// {
// 	while (mWindow.isOpen())
// 	{
// 		processEvents();
// 		update();
// 		render();
// 	}
// }

Player::Player(std::string name, int uA, int cD)
{
	srand(time(NULL));
	mBaseAttr = (rand() % 16) + 3;
	mName = name;
	mCounter = 0;
	setAllSkills(uA, cD);
}

Player::Player(std::string name)
{
	mCounter = 0;
	srand(time(NULL));
	mBaseAttr = (rand() % 16) + 3;
	mName = name;
	setAllSkills();
}

std::string Player::getName() const
{
	return mName;
}

int Player::getUnarmedAttack() const
{
	return mUnarmedAttack;
}

int Player::getDefense() const
{
	return mDefense;
}

void Player::setAllSkills()
{
	using namespace std;
	int skillPointsLeft = 13;
	int spUnarmed, spDefense, spThievery;
	cout << "You have a total of 13 Skill points\nUse them wisely." << endl;
	do {
	if(skillPointsLeft < 0) 
	{
		cout << "try again, too many points allocated";
		skillPointsLeft = 13;
	}
	cout << "Give points for unarmed attack: ";
	cin >> spUnarmed;
	skillPointsLeft -= spUnarmed;
	cout << "Give points for defense: ";
	cin >> spDefense;
	skillPointsLeft -= spDefense;
	} while(skillPointsLeft < 0);

	mUnarmedAttack = (mBaseAttr - 10) + spUnarmed;
	mUnarmedAttack < 0 ? mUnarmedAttack * -1 : mUnarmedAttack;
	mDefense = mBaseAttr + spDefense;
	mHP = mDefense;
	isBot = false;
}


void Player::setAllSkills(int spUnarmed, int spDefense)
{
	mUnarmedAttack = (mBaseAttr - 10) + spUnarmed;
	mUnarmedAttack < 0 ? mUnarmedAttack * -1 : mUnarmedAttack;
	mDefense = mBaseAttr + spDefense;
	mHP = mDefense;
	isBot = true;
}


int Player::getRoll()
{
	srand(time(NULL));
	mLuckFactor = findLuckFactor() * 1.5;
	int value = ((rand() % 20) + 1) + int(mLuckFactor);
	std::cout << mName << " rolls a " << value << "!" << std::endl;
	return value;
}

bool Player::dealDamage(int damageDealt)
{
	mHP -= damageDealt;
	if(mHP > 0)
	{
		return false;
	} else
	{
		return true; // game over scenario
	}
	
}

//below two methods are only for computer fighters
bool Player::getBot() const
{
	return isBot;
}

turnChoice Player::decideTurn()
{
	if (mHP < 5)
	{
		if (mUnarmedAttack < 7)
		{
			return DEFEND; 
		} else
		{
			return LIGHT_ATTACK; 
		}
	} else
	{
		if (mLuckFactor < 0)
		{
			return DEFEND;
		} else
		{
			return STRONG_ATTACK; 
		}
		
	}
	
}

double Player::findLuckFactor()
{
	double outcomesSum = 0;
	for (int i = 0; i < 3; i++) outcomesSum += mLastThreeOutcomes[i];
	return outcomesSum;
}

void Player::recordOutcome(double result)
{
	mLastThreeOutcomes[mCounter++ % 3] = result; // look how many lines of code i saved here :-)
}