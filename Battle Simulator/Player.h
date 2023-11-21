#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <time.h>

enum PlayerState
{
	BEFOREATTACK,
	AFTERATTACK
};

enum turnChoice
{
	LIGHT_ATTACK = 1,
	DEFEND = 2,
	STRONG_ATTACK = 0
};

class Player
{
private:
	/* 0: Unarmed combat, 1: Melee Combat
	   2: Defense, 3: Thievery
	*/
	std::string mName;
	int mUnarmedAttack, mDefense;
	int spAttack, spDefense;
	int mBaseAttr;
	float mHP;
	bool isBot = false;
	int mLastThreeOutcomes[3] = { 0, 0, 0 };
	int mCounter; // tracks index to avoid overwriting outcomes array
	double mLuckFactor;
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
	bool defending = false;
	Player(std::string name, int uA, int cD);
	Player(std::string name);

	int getUnarmedAttack() const;
	int getDefense() const;
	std::string getName() const;

	float getHP() { return mHP; }
	float getPosX() { return positionX; }
	float getPosY() { return positionY; }

	PlayerState getPlState() { return mPlState; }
	sf::Sprite getSprite() { return mPlayerSprite; }

	void setSkill(int skillType, int value);
	void setHP(float hp) { mHP = hp; }
	void setPos(float x, float y) { positionX = x; positionY = y; }
	void setAttack(int val) { spAttack = val; }
	void setDefense(int val) { spDefense = val; }
	void setAllSkills();
	const std::string phrases[3][3] = {
{
	" got confused and hit\n themself!",
	" forgot who they were\n punching so they punched themselves!",
	" wrote Cpp code and went\n crazy enough to hit themselves!"
},
{
	" said something rude and\n did minimal damage!",
	" reminded their opponent of\n a forgotten assignment and did\n minimal damage!",
	" called their opponent an SSE\n student and did minimal damage!"
},
{
	" gave a strong upper-cut which\n did maximum damage!",
	" gave a strong jab to the head\n for maximum damage!",
	" punched their opponent hard\n enough for maximum damage!"
}
	};
	std::string getAPhrase(int att)
	{
		return mName + phrases[att][rand() % 3];
	}


	void setSprite(std::string path);
	void setPlState(PlayerState st) { mPlState = st; }
	//void dealdamage(int damage) { mHP -= damage; }
	bool dealdamage(int damageDealt)
	{
		mHP -= damageDealt;
		if (mHP > 0)
		{
			return false;
		}
		else
		{
			return true; // game over scenario
		}

	}

	double findLuckFactor();
	void recordOutcome(double result);
	int getRoll();
	//below method are for non player fighters
	void setAllSkills(int spMelee, int spDefense);
	bool getbot() const { return isBot; }
	turnChoice decideTurn();


	friend sf::RectangleShape getBox(Player, float, float, float, float, bool);
};