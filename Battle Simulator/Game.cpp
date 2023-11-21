#include "Game.h"
#include <iostream>

DelayedText::DelayedText(const std::string& gstring, const sf::Font& gfont, unsigned int gsize) :
    sf::Text("", gfont, gsize),
    current(0),
    m_string(gstring)
{

}
void DelayedText::setString(const std::string& gstring)
{
    m_buffer.clear();
    m_string = gstring;
    current = 0;
}
void DelayedText::setDelay(sf::Time gtime)
{
    m_delay = gtime;
}
const DelayedText& DelayedText::update(float x, float y)
{
    m_time += m_Clock.restart();
    while (m_time >= m_delay)
    {
        m_time -= m_delay;
        if (current < m_string.length())
        {
            m_buffer += m_string[current];
            ++current;
        }
    }
    sf::Text::setString(m_buffer);
    sf::Text::setPosition(x, y);
    return *this;
}
//OUR PLAYER MODELS

 Game::Game(Player pl1, Player pl2) : mState(State::HOME),mPlayer1(pl1), mPlayer2(pl2), mWindow(sf::VideoMode(853, 640), "Battle", sf::Style::Close)
 {
 	 //Sets up the background
     mBgTexture.loadFromFile("background.jpg");
 	 mBackground.setTexture(mBgTexture);
 	 mBackground.setPosition(0, 0);

     mSPTexture.loadFromFile("spbg.jpg");
     mSPSprite.setTexture(mSPTexture);
     mSPSprite.setPosition(0.0f, 0.0f);

     //sets up the hp bar background for player1
     hpbarbackpl1.setPosition(mPlayer1.getPosX() + 25, mPlayer1.getPosY() - 25);
     hpbarbackpl1.setFillColor(sf::Color::Red);
     hpbarbackpl1.setSize(sf::Vector2f(200, 15));

     //sets up the hp bar background for player2
     hpbarbackpl2.setPosition(mPlayer2.getPosX() + 25, mPlayer2.getPosY() - 25);
     hpbarbackpl2.setFillColor(sf::Color::Red);
     hpbarbackpl2.setSize(sf::Vector2f(200, 15));

     //sets up the hp bar for player1
     hpbarpl1.setPosition(mPlayer1.getPosX() + 25, mPlayer1.getPosY() - 25);
     hpbarpl1.setFillColor(sf::Color::Cyan);

     //sets up the hp bar for player2
     hpbarpl2.setFillColor(sf::Color::Cyan);
     hpbarpl2.setPosition(mPlayer2.getPosX() + 25, mPlayer2.getPosY() - 25);
    
     HomeScreentext.setFont(font);
     HomeScreentext.setPosition(853 / 2.0f, 640 / 2.0f);
     HomeScreentext.setString("HOME SCREEN!\nPRESS ENTER TO CONTINUE");
     HomeScreentext.setCharacterSize(30);
     
     font.loadFromFile("ARCADECLASSIC.TTF");
     
     infoBarText.setFont(font);
     infoBarText.setPosition(sf::Vector2f(InfoBar.getPosition().x + 5, InfoBar.getPosition().y + 5));
     infoBarText.setCharacterSize(20);
     infoBarText.setFillColor(sf::Color::Black);
    
     pl1BarText.setFont(font);
     pl1BarText.setFillColor(sf::Color::Black);
     pl1BarText.setCharacterSize(45);
     pl1BarText.setString(mPlayer1.getName());
     pl1BarText.setPosition(sf::Vector2f(pl1Bar.getPosition().x + 5, pl1Bar.getPosition().y + 5));
     
     pl2BarText.setFont(font);
     pl2BarText.setFillColor(sf::Color::Black);
     pl2BarText.setCharacterSize(45);
     pl2BarText.setString(mPlayer2.getName());
     pl2BarText.setPosition(sf::Vector2f(pl2Bar.getPosition().x + 5, pl2Bar.getPosition().y + 5));

     srand(time(0));
     if (mPlayer1.getRoll() >= mPlayer2.getRoll())
     {
         std::cout << mPlayer1.getName() << " gets the first turn!";
         mTurn = Turn::PLAYER1;
     }
     else
     {
         std::cout << mPlayer2.getName() << " gets the first turn!";
         mTurn = Turn::PLAYER2;
     }

 }

 Textbox tbox3(35, sf::Color::Red, true);
 Textbox tbox4(35, sf::Color::Red, false);
 int skillpointsleft;

void Game::handleInput(sf::Keyboard::Key key, bool pressed)
{
    int input;
    double miss_modifier = 0;
    bool OnePlayerDied;
    if (key == sf::Keyboard::Return && pressed)
    {
        if (mState == State::HOME)
        {
            mState = State::SHOP;
        }
        else if (mState == State::SHOP)
        {
            //mState = State::ACTION;
            if (tbox3.getSelectedStatus())
            {
                input = std::stoi(tbox3.getText());
                if (input < 13 && input >= 0)
                {
                    mPlayer1.setAttack(input);
                    tbox3.setSelected(false);
                    tbox4.setSelected(true);
                    skillpointsleft = input;
                }
            }
            else if (tbox4.getSelectedStatus())
            {
                input = std::stoi(tbox4.getText());
                if ((input + skillpointsleft == 13) && (input >= 0))
                {
                    mPlayer1.setDefense(input);
                    tbox3.setSelected(false);
                    tbox4.setSelected(false);
                    mPlayer1.setAllSkills();
                    mState = State::ACTION;
                }
            }
        }
        else if (mState == State::ACTION)
        {
            if (mTurn == Turn::PLAYER1)
            {
                mTurn = Turn::PLAYER2;
            }
            else if (mTurn == Turn::PLAYER2)
            {
                mTurn = Turn::PLAYER1;
            }
        }
        else if (mState == State::WINNER && winner == PLAYER1)
        {
            mState = ACTION;
        }

    }
    else if (key == sf::Keyboard::S && pressed)
    {
        if (mTurn == Turn::PLAYER1)
        {
            mPlayer2.defending ? miss_modifier += 0.25 : miss_modifier;
            mPlayer1.defending = false;
            miss_modifier += 0.6;
            double difference = (miss_modifier * 20) - (mPlayer1.getRoll());
            mPlayer1.recordOutcome(difference);
            if (difference > 0)
            {
                OnePlayerDied = mPlayer1.dealdamage(mPlayer1.getUnarmedAttack());
                mInfoText = mPlayer1.getAPhrase(0);
                if (OnePlayerDied)
                {
                    winner = PLAYER2;
                    mState = State::WINNER;
                }
            }
            else
            {
                OnePlayerDied = mPlayer2.dealdamage(mPlayer1.getUnarmedAttack());
                mInfoText = mPlayer1.getAPhrase(2);
                if (OnePlayerDied)
                {
                    winner = PLAYER1;
                    mState = State::WINNER;
                }
            }

            mPlayer1.setPlState(PlayerState::AFTERATTACK);
            mPlayer2.setPlState(PlayerState::BEFOREATTACK);
        }
        else if (mTurn == Turn::PLAYER2)
        {
            mPlayer1.defending ? miss_modifier += 0.25 : miss_modifier;
            mPlayer2.defending = false;
            miss_modifier += 0.6;
            double difference = (miss_modifier * 20) - (mPlayer2.getRoll());
            mPlayer2.recordOutcome(difference);
            if (difference > 0)
            {
                OnePlayerDied = mPlayer2.dealdamage(mPlayer1.getUnarmedAttack());
                mInfoText = mPlayer2.getAPhrase(0);
                if (OnePlayerDied)
                {
                    winner = PLAYER1;
                    mState = State::WINNER;
                }
            }
            else
            {
                OnePlayerDied = mPlayer1.dealdamage(mPlayer1.getUnarmedAttack());
                mInfoText = mPlayer2.getAPhrase(2);
                if (OnePlayerDied)
                {
                    winner = PLAYER2;
                    mState = State::WINNER;
                }
            }
            mPlayer2.setPlState(PlayerState::AFTERATTACK);
            mPlayer1.setPlState(PlayerState::BEFOREATTACK);
        }
    }
    else if (key == sf::Keyboard::L && pressed)
    {
        if (mTurn == Turn::PLAYER1)
        {
            mPlayer1.defending = false;
            miss_modifier += 0.2;
            double difference = (miss_modifier * 20) - (mPlayer1.getRoll());
            mPlayer1.recordOutcome(difference);
            if (difference > 0)
            {
                OnePlayerDied = mPlayer1.dealdamage(mPlayer1.getUnarmedAttack() * 0.5);
                mInfoText = mPlayer1.getAPhrase(0);
                if (OnePlayerDied)
                {
                    winner = PLAYER2;
                    mState = State::WINNER;
                }
            }
            else
            {
                OnePlayerDied = mPlayer2.dealdamage(mPlayer1.getUnarmedAttack() * 0.5);
                mInfoText = mPlayer1.getAPhrase(1);
                if (OnePlayerDied)
                {
                    winner = PLAYER1;
                    mState = State::WINNER;
                }
            }
            mPlayer1.setPlState(PlayerState::AFTERATTACK);
            mPlayer2.setPlState(PlayerState::BEFOREATTACK);
        }
        else if (mTurn == Turn::PLAYER2)
        {
            mPlayer2.defending = false;
            miss_modifier += 0.2;
            double difference = (miss_modifier * 20) - (mPlayer2.getRoll());
            mPlayer2.recordOutcome(difference);
            if (difference > 0)
            {
                OnePlayerDied = mPlayer2.dealdamage(mPlayer2.getUnarmedAttack() * 0.5);
                mInfoText = mPlayer2.getAPhrase(0);
                if (OnePlayerDied)
                {
                    winner = PLAYER1;
                    mState = State::WINNER;
                }
            }
            else
            {
                OnePlayerDied = mPlayer1.dealdamage(mPlayer2.getUnarmedAttack() * 0.5);
                mInfoText = mPlayer2.getAPhrase(0);
                if (OnePlayerDied)
                {
                    winner = PLAYER2;
                    mState = State::WINNER;
                }
            }
            mPlayer2.setPlState(PlayerState::AFTERATTACK);
            mPlayer1.setPlState(PlayerState::BEFOREATTACK);
        }
    }
    else if (key == sf::Keyboard::D && pressed)
    {
        
        if (mTurn == Turn::PLAYER1)
        {
            mInfoText = mPlayer1.getName() + " DECIDED TO DEFEND";
            mPlayer1.defending = true;
            mPlayer1.setPlState(PlayerState::AFTERATTACK);
            mPlayer2.setPlState(PlayerState::BEFOREATTACK);
        }
        else if (mTurn == Turn::PLAYER2)
        {
            mInfoText = mPlayer2.getName() + " DECIDED TO DEFEND";
            mPlayer2.defending = true;
            mPlayer2.setPlState(PlayerState::AFTERATTACK);
            mPlayer1.setPlState(PlayerState::BEFOREATTACK);
        }
    }
}

 void Game::processEvents()
 {
 	sf::Event event;
 	while (mWindow.pollEvent(event))
 	{
 		switch (event.type)
 		{
        case sf::Event::TextEntered:
            if (mState == State::SHOP)
            {
                if (tbox3.getSelectedStatus())
                {
                    tbox3.typedOn(event);
                }
                else if (tbox4.getSelectedStatus())
                {
                    tbox4.typedOn(event);
                }
            }
 		case sf::Event::KeyPressed:
 			handleInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handleInput(event.key.code, false);
            break;
 		case sf::Event::Closed:
 			mWindow.close();
 			break;
 		}
 	}
 }

void Game::update()
{
    if (mTurn == Turn::PLAYER1 && mState == ACTION)
    {
        if (mPlayer1.getPlState() == PlayerState::BEFOREATTACK)
        {
            mInfoText = "What does " + mPlayer1.getName() + " want to do!\n\nS  For Strong attack\nL  for light attack\nD  for defense\nEnter  to skip this turn";
            delayTime = sf::seconds(0);
        }
        else if (mPlayer1.getPlState() == PlayerState::AFTERATTACK)
        {
            delayTime = sf::seconds(2.0f);
            mTurn = Turn::PLAYER2;
            mPlayer1.setPlState(PlayerState::BEFOREATTACK);
            mPlayer2.setPlState(PlayerState::BEFOREATTACK);
        }
    }
    else if (mTurn == Turn::PLAYER2 && mState == State::ACTION)
    {
        if (mPlayer2.getPlState() == PlayerState::BEFOREATTACK)
        {
            mInfoText = "What does " + mPlayer2.getName() + " want to do!\n\nS  For Strong attack\nL  for light attack\nD  for defense\nEnter  to skip this turn";
            delayTime = sf::seconds(1);
            int choice = -1;
            if (mPlayer2.getbot())
            {
                choice = mPlayer2.decideTurn();
            }
            switch (choice)
            {
            case STRONG_ATTACK:
                handleInput(sf::Keyboard::S, true);
                break;
            case LIGHT_ATTACK:
                handleInput(sf::Keyboard::L, true);
                break;
            case DEFEND:
                handleInput(sf::Keyboard::D, true);
                break;
            default:
                break;
            }
        }
        else if (mPlayer2.getPlState() == PlayerState::AFTERATTACK)
        {
            delayTime = sf::seconds(2.0f);
            mTurn = Turn::PLAYER1;
            mPlayer2.setPlState(PlayerState::BEFOREATTACK);
            mPlayer1.setPlState(PlayerState::BEFOREATTACK);
        }
    }
    else if (mState == WINNER)
    {
        std::string winnert, loser;
        if (winner == PLAYER1)
        {
            winnert = mPlayer1.getName();
            loser = mPlayer2.getName();
        }
        else if (winner == PLAYER2)
        {
            winnert = mPlayer2.getName();
            loser = mPlayer1.getName();
        }
        mInfoText = winnert + "  completely\n obliterated  " + loser;
    }
    hpbarpl1.setSize(sf::Vector2f((mPlayer1.getHP()/mPlayer1.getDefense() * 100) * 2, 15));
    hpbarpl2.setSize(sf::Vector2f((mPlayer2.getHP()/mPlayer2.getDefense() * 100) * 2, 15));
    infoBarText.setString(mInfoText);
}

 void Game::render(DelayedText txt)
 {
     if (mState == State::ACTION)
     {
         mWindow.clear();
         mWindow.draw(mBackground);
         mWindow.draw(mPlayer1.getSprite());
         mWindow.draw(mPlayer2.getSprite());
         mWindow.draw(pl1Bar);
         mWindow.draw(pl1BarText);
         mWindow.draw(pl2Bar);
         mWindow.draw(pl2BarText);
         mWindow.draw(hpbarbackpl1);
         mWindow.draw(hpbarpl1);
         mWindow.draw(hpbarbackpl2);
         mWindow.draw(hpbarpl2);
         mWindow.draw(InfoBar);
         mWindow.draw(infoBarText);
         mWindow.display();
         sf::sleep(delayTime);
     }

     else if (mState == State::HOME)
     {
         mWindow.clear();
         mWindow.draw(txt.update(853/3.0f, 640/3.0f));
         mWindow.display();
     }

     else if (mState == State::SHOP)
     {
         sf::Text text;
         text.setFont(font);
         text.setPosition(40, 30);
         text.setString("You have got 13 skillpoints to allocate!\n\n\nEnter the amount you want to allocate\ntowards the attack\n\n\n\n\nEnter the amount for Defense");
         text.setCharacterSize(40);
         text.setFillColor(sf::Color::Black);
         tbox3.setFont(font);
         tbox3.setPosition(sf::Vector2f(40.0f, 235.0f));
         tbox4.setFont(font);
         tbox4.setPosition(sf::Vector2f(40.0f, 500.0f));
         mWindow.clear();
         mWindow.draw(mSPSprite);
         mWindow.draw(text);
         tbox3.drawTo(mWindow);
         tbox4.drawTo(mWindow);
         mWindow.display();
     }
     else if (mState == State::WINNER)
     {
         mWindow.clear();
         mWindow.draw(mBackground);
         mWindow.draw(InfoBar);
         mWindow.draw(infoBarText);
         mWindow.display();
     }
 }

 void Game::run()
 {
    DelayedText txt("WELCOME! LETS PLAY\nPress ENTER TO CONTINUE", font, 30);
    txt.setDelay(sf::seconds(0.1f));
 	while (mWindow.isOpen())
 	{
 		processEvents();
 		update();
 		render(txt);
 	}
 }