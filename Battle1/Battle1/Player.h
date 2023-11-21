#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <time.h>

enum PlayerState
{
	BEFOREATTACK,
	AFTERATTACK
};

class Player
{
private:
	/* 0: Unarmed combat, 1: Melee Combat
	   2: Defense, 3: Thievery
	*/
	std::string mName;
	int mUnarmedAttack, mMeleeAttack, mDefense, mThievery;
	int mBaseAttr;
	float mHP;
	float positionX;
	float positionY;
	PlayerState mPlState;
	sf::Sprite mPlayerSprite;
	sf::Texture mPlayerTexture;


	int getBaseAttr()
	{
		srand(time(NULL));
		return rand() % 16 + 3;
	}
public:
	Player(std::string name, int uA, int mC, int cD, int sT);
	Player(std::string name);


	int getUnarmedAttack() const;
	int getMeleeAttack() const;
	int getDefense() const;
	int getThievery() const;
	float getHP() { return mHP; }
	float getPosX() { return positionX; }
	float getPosY() { return positionY; }
	PlayerState getPlState() { return mPlState; }
	sf::Sprite getSprite() { return mPlayerSprite; }
	std::string getName() const;

	void setSkill(int& skillType, int value);
	void setHP(float hp) { mHP = hp; }
	void setPos(float x, float y) { positionX = x; positionY = y; }
	void setAllSkills();
	void setSprite(std::string path);
	void setPlState(PlayerState st) { mPlState = st; }

	int getRoll();
	//below method are for non player fighters
	void setAllSkills(int spUnarmed, int spMelee, int spDefense, int spThievery);
	friend sf::RectangleShape getBox(Player, float, float, float, float, bool);
};