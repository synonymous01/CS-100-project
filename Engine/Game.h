#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <time.h>

// class Game
// {
// 	sf::RenderWindow mWindow;
// 	sf::Texture mBgTexture;
// 	sf::Sprite mBackground;
// 	sf::Texture mPTexture;
// 	sf::Sprite mPlayer;

// 	enum State
// 	{
// 		PAUSED,
// 		NOT_PAUSED
// 	};

// 	void processEvents();
// 	void update();
// 	void render();
// 	void handleInput(sf::Keyboard::Key);

// public:
// 	Game();
// 	Game(int x, int y, std::string title, std::string path);

// 	void run();
// };

class Player
{
private:
	/* 0: Unarmed combat, 1: Melee Combat
	   2: Defense, 3: Thievery
	*/
	std::string mName;
	int mUnarmedAttack, mMeleeAttack, mDefense, mThievery;
	int mBaseAttr;
	int mHP;


	int getBaseAttr()
	{
		srand(time(NULL));
		return rand() % 16 + 3;
	}
public:
	Player(std::string name, int uA, int mC, int cD, int sT);
	Player(std::string name);
	void setSkill(int& skillType, int value);
	int getUnarmedAttack() const;
	std::string getName() const;
	int getMeleeAttack() const;
	int getDefense() const;
	int getThievery() const;
	void setAllSkills();
	int getRoll();
	//below method are for non player fighters
	void setAllSkills(int spUnarmed, int spMelee, int spDefense, int spThievery);
};

//console prototypes
bool isPlayer1First(Player p1, Player p2);
void runBattle(Player player1, Player player2);

