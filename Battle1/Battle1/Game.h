#pragma once
#include "Player.h"

//Enumeration for keeping track of the Turn
enum Turn
{
	PLAYER1,
	PLAYER2
};

//Enumeration for keeping track of the screen
enum State
{
	HOME,
	SHOP,
	TOSS,
	ACTION
};


//class for displaying text character by character
class DelayedText : public sf::Text
{
private:
	sf::Clock m_Clock;
	sf::Time m_time, m_delay;
	std::string m_string, m_buffer;
	unsigned int current;
public:
	DelayedText(const std::string& gstring, const sf::Font& gfont, unsigned int gsize);
	void setString(const std::string& string);//covering text's setter
	void setDelay(sf::Time gtime);
	const DelayedText& update(float, float);
};

//MAIN GAME CLASS
class Game
{
	sf::RenderWindow mWindow;                                                 //Game window
	sf::Texture mBgTexture;													  //This variable holds the texture or the art for the background
	sf::Sprite mBackground;                                                   //Sprite for the background
	Turn mTurn;                                                               //Value is whoever's turn it is
	State mState;															  //Keeps track of which screen our game is on
	std::string mInfoText;													  //Text that'll be shown in the infobox inside the game, changes according to the turn or attacks

	Player mPlayer1;														  //An object of Player class and Our Player number 1
	Player mPlayer2;														  //An object of Player class and Our Player number 2
	sf::Time delayTime;														  //Variable for changing delay times between two different things

	sf::Font font;															  //Holds our Font
	sf::RectangleShape pl1Bar = getBox(mPlayer1, 0, -80, 250, 80, false);	  //This creates a box above the player 1's head for hp and name
	sf::RectangleShape pl2Bar = getBox(mPlayer2, 0, -80, 250, 80, false);	  //This creates a box above the player 2's head for hp and name
	sf::RectangleShape InfoBar = getBox(mPlayer1, -185, -395, 440, 230, true);//A box for showing info and prompts in the top left of the screen, (being drawn with reference of position of player1)
	sf::RectangleShape hpbarbackpl1;										  //Red background for the hp bar of player 1
	sf::RectangleShape hpbarbackpl2;										  //Red Background for the hp bar of player 2
	sf::RectangleShape hpbarpl1;											  //Actual dynamic hp bar of player 1
	sf::RectangleShape hpbarpl2;											  //Actual dynamic hp bar of player 1

	sf::Text HomeScreentext;                                                  //Text to display at the homescreen
	sf::Text infoBarText;													  //Text to display inside the mInfoBar
	sf::Text pl1BarText;													  //Text to display inside the bar above Player 1
	sf::Text pl2BarText;													  //Text to display inside the bar above Player 2

	void processEvents();													  //Member function that'll handle all the EVENTS happening (Events as in the windows events) 
	void update();															  //Member function that'll update the value of different variables as the game progresses
	void render(DelayedText);												  //Member function that'll be rendering all the screens and objects, param is DelayedText object, to display at the homescreen
	void handleInput(sf::Keyboard::Key key, bool pressed);					  //Member function that'll recieve player's input and takes actions accordingly

	public:
 	Game(Player Player1, Player Player2);                                     //Constructor, that'll be taking two Player objects 
 	void run();																  //it is what it is

	//Getters and Setters for mState
	State getState() { return mState; }										  	
	void setState(State st) { mState = st; }								  

	//Getter and Setter for mTurn
	Turn getTurn() { return mTurn; }										 
	void setTurn(Turn t) { mTurn = t; }
};