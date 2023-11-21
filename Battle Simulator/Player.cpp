#include "Player.h"
#include <iostream>


Player::Player(std::string name, int uA, int cD) :  mPlState(PlayerState::BEFOREATTACK)
{
	srand(time(NULL));
	mBaseAttr = (rand() % 16) + 3;
	mName = name;
	mCounter = 0;
	setAllSkills(uA, cD);
}

Player::Player(std::string name) : mName(name), mPlState(PlayerState::BEFOREATTACK)
{
	mCounter = 0;
	srand(time(NULL));
	mBaseAttr = (rand() % 16) + 3;
	mName = name;
	setAllSkills();
	isBot = false;
}

void Player::setSkill(int skillType, int value)
{
	skillType = value;
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
	mUnarmedAttack = (mBaseAttr - 10) + spAttack;
	if (mUnarmedAttack < 0)
	{
		mUnarmedAttack *= -1;
	}
	mDefense = mBaseAttr + spDefense;
	mHP = mDefense;
	std::cout << "mHP : " << mHP;
	isBot = false;
}


void Player::setAllSkills(int spUnarmed, int spDefense)
{
	mUnarmedAttack = (mBaseAttr - 10) + spUnarmed;
	if (mUnarmedAttack < 0)
	{
		mUnarmedAttack *= -1;
	}
	mDefense = mBaseAttr + spDefense;
	mHP = mDefense;
	isBot = true;
}

int Player::getRoll()
{
	mLuckFactor = findLuckFactor() * 1.5;
	int value = ((rand() % 20) + 1) + int(mLuckFactor);
	std::cout << mName << " rolls a " << value << "! mHP of " << mName << " is " << mHP << std::endl;
	return value;
}

turnChoice Player::decideTurn()
{
	std::cout << "mHP " << mName << " " << mHP << std::endl;
	std::cout << "mUnarmedAttack : " << mUnarmedAttack << std::endl;
	if (mHP < 5)
	{
		if (mUnarmedAttack < 7)
		{
			return DEFEND;
		}
		else
		{
			return LIGHT_ATTACK;
		}
	}
	else
	{
		if (mLuckFactor < 0)
		{
			return DEFEND;
		}
		else
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

void Player::setSprite(std::string path)
{
	mPlayerTexture.loadFromFile(path);
	mPlayerSprite.setTexture(mPlayerTexture);
	mPlayerSprite.setPosition(positionX, positionY);
}

sf::RectangleShape getBox(Player pl, float x, float y, float W, float H, bool opaque)
{
	sf::RectangleShape box;
	box.setSize(sf::Vector2f(W, H));
	box.setPosition(sf::Vector2f(pl.positionX + x, pl.positionY + y));
	if (opaque)
		box.setFillColor(sf::Color::Green);
	else
		box.setFillColor(sf::Color::Transparent);

	box.setOutlineThickness(4);
	box.setOutlineColor(sf::Color::Black);

	return box;
}
