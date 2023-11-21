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

Player::Player(std::string name, int uA, int mC, int cD, int sT)
{
	mBaseAttr = getBaseAttr();
	mName = name;
	setAllSkills(uA, mC, cD, sT);
}

Player::Player(std::string name)
{
	mBaseAttr = getBaseAttr();
	mName = name;
	setAllSkills();
}

void Player::setSkill(int& skillType, int value)
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

int Player::getMeleeAttack() const
{
	return mMeleeAttack;
}

int Player::getDefense() const
{
	return mDefense;
}

int Player::getThievery() const
{
	return mThievery;
}

void Player::setAllSkills()
{
	using namespace std;
	int skillPointsLeft = 20;
	int spUnarmed, spMelee, spDefense, spThievery;
	cout << "You have a total of 20 Skill points\nUse them wisely." << endl;
	do {
	if(skillPointsLeft < 0)
	{
		cout << "try again, too many points allocated";
		skillPointsLeft = 20;
	}
	cout << "Give points for unarmed attack: ";
	cin >> spUnarmed;
	skillPointsLeft -= spUnarmed;
	cout << "Give points for melee attack: ";
	cin >> spMelee;
	skillPointsLeft -= spMelee;
	cout << "Give points for melee attack: ";
	cin >> spDefense;
	skillPointsLeft -= spDefense;
	cout << "Give points for melee attack: ";
	cin >> spThievery;
	skillPointsLeft -= spThievery;
	} while(skillPointsLeft < 0);

	mUnarmedAttack = mBaseAttr - 10 + spUnarmed;
	mMeleeAttack = mBaseAttr - 10 + spMelee;
	mDefense = mBaseAttr - 10 + spDefense;
	mThievery = mBaseAttr - 10 + spThievery;
	mHP = 10 + mDefense;
}


void Player::setAllSkills(int spUnarmed, int spMelee, int spDefense, int spThievery)
{
	mUnarmedAttack = mBaseAttr - 10 + spUnarmed;
	mMeleeAttack = mBaseAttr - 10 + spMelee;
	mDefense = mBaseAttr - 10 + spDefense;
	mThievery = mBaseAttr - 10 + spThievery;
	mHP = 10 + mDefense;
}


int Player::getRoll()
{
	srand(time(NULL));
	int value = (rand() % 21) + 1;
	std::cout << mName << " rolls a " << value << "!" << std::endl;
	return value;

}
