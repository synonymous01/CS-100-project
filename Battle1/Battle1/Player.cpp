#include "Player.h"


Player::Player(std::string name, int uA, int mC, int cD, int sT)
{
	mBaseAttr = getBaseAttr();
	mName = name;
	setAllSkills(uA, mC, cD, sT);
}

Player::Player(std::string name) : mName(name), mHP(100.0f), mPlState(PlayerState::BEFOREATTACK)
{
	mBaseAttr = getBaseAttr();
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
	/*using namespace std;
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
	mHP = 10 + mDefense;*/
}


void Player::setAllSkills(int spUnarmed, int spMelee, int spDefense, int spThievery)
{
	mUnarmedAttack = mBaseAttr - 10 + spUnarmed;
	mMeleeAttack = mBaseAttr - 10 + spMelee;
	mDefense = mBaseAttr - 10 + spDefense;
	mThievery = mBaseAttr - 10 + spThievery;
	mHP = 10 + mDefense;
}


//int Player::getRoll()
//{
//	srand(time(NULL));
//	int value = (rand() % 21) + 1;
//	std::cout << mName << " rolls a " << value << "!" << std::endl;
//	return value;
//
//}

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
