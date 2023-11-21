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

 Game::Game(Player Player1, Player Player2) : mState(State::HOME),mPlayer1(Player1), mPlayer2(Player2), mWindow(sf::VideoMode(853, 640), "Battle", sf::Style::Close)
 {
    mTurn = Turn::PLAYER1;
 	mBgTexture.loadFromFile("background.jpg");
 	mBackground.setTexture(mBgTexture);
 	mBackground.setPosition(0, 0);
    hpbarbackpl1.setPosition(mPlayer1.getPosX() + 25, mPlayer1.getPosY() - 25);
    hpbarbackpl1.setFillColor(sf::Color::Red);
    hpbarbackpl1.setSize(sf::Vector2f(200, 15));
    hpbarbackpl2.setPosition(mPlayer2.getPosX() + 25, mPlayer2.getPosY() - 25);
    hpbarbackpl2.setFillColor(sf::Color::Red);
    hpbarbackpl2.setSize(sf::Vector2f(200, 15));
    hpbarpl1.setPosition(mPlayer1.getPosX() + 25, mPlayer1.getPosY() - 25);
    hpbarpl1.setFillColor(sf::Color::Cyan);
    hpbarpl2.setPosition(mPlayer2.getPosX() + 25, mPlayer2.getPosY() - 25);
    hpbarpl2.setFillColor(sf::Color::Cyan);
    HomeScreentext.setFont(font);
    HomeScreentext.setPosition(853 / 2.0f, 640 / 2.0f);
    HomeScreentext.setString("HOME SCREEN!\nPRESS ENTER TO CONTINUE");
    HomeScreentext.setCharacterSize(30);
    font.loadFromFile("ARCADECLASSIC.TTF");
    infoBarText.setFont(font);
    infoBarText.setPosition(sf::Vector2f(InfoBar.getPosition().x + 5, InfoBar.getPosition().y + 5));
    infoBarText.setCharacterSize(30);
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
 }

void Game::handleInput(sf::Keyboard::Key key, bool pressed)
{
    if (key == sf::Keyboard::Enter && pressed)
    {
        if (mState == State::HOME)
        {
            mState = State::SHOP;
        }
        else if (mState == State::SHOP)
        {
            mState = State::ACTION;
        }
        else if (mState == State::ACTION)
        {
            if (mTurn == Turn::PLAYER1)
            {
                mTurn = Turn::PLAYER2;
            }
            else if (mTurn == Turn::PLAYER2)
            {
                mTurn = Turn::PLAYER2;
            }
        }

    }
    else if (key == sf::Keyboard::S && pressed)
    {
        if (mTurn == Turn::PLAYER1)
        {
            mPlayer1.setPlState(PlayerState::AFTERATTACK);
            mPlayer2.setPlState(PlayerState::BEFOREATTACK);
        }
        else if (mTurn == Turn::PLAYER2)
        {
            mPlayer2.setPlState(PlayerState::AFTERATTACK);
            mPlayer1.setPlState(PlayerState::BEFOREATTACK);
        }
    }
    else if (key == sf::Keyboard::L && pressed)
    {
        if (mTurn == Turn::PLAYER1)
        {
            mPlayer1.setPlState(PlayerState::AFTERATTACK);
            mPlayer2.setPlState(PlayerState::BEFOREATTACK);
        }
        else if (mTurn == Turn::PLAYER2)
        {
            mPlayer2.setPlState(PlayerState::AFTERATTACK);
            mPlayer1.setPlState(PlayerState::BEFOREATTACK);
        }
    }
    else if (key == sf::Keyboard::D && pressed)
    {
        if (mTurn == Turn::PLAYER1)
        {
            mPlayer1.setPlState(PlayerState::AFTERATTACK);
            mPlayer2.setPlState(PlayerState::BEFOREATTACK);
        }
        else if (mTurn == Turn::PLAYER2)
        {
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
    if (mTurn == Turn::PLAYER1)
    {
        if (mPlayer1.getPlState() == PlayerState::BEFOREATTACK)
        {
            mInfoText = "What does " + mPlayer1.getName() + " want to do!\n\nS  For Strong attack\nL  for light attack\nD  for defense\nEnter  to skip this turn";
            delayTime = sf::seconds(0);
        }
        else if (mPlayer1.getPlState() == PlayerState::AFTERATTACK)
        {
            mInfoText = "Did a full 180 crazy";
            delayTime = sf::seconds(1.3);
            mTurn = Turn::PLAYER2;
            mPlayer1.setPlState(PlayerState::BEFOREATTACK);
        }
    }
    else if (mTurn == Turn::PLAYER2)
    {
        if (mPlayer2.getPlState() == PlayerState::BEFOREATTACK)
        {
            mInfoText = "What does " + mPlayer2.getName() + " want to do!\n\nS  For Strong attack\nL  for light attack\nD  for defense\nEnter  to skip this turn";
            delayTime = sf::seconds(0);
        }
        else if (mPlayer2.getPlState() == PlayerState::AFTERATTACK)
        {
            mInfoText = "Did not do a full 180 crazy";
            delayTime = sf::seconds(1.3);
            mTurn = Turn::PLAYER1;
            mPlayer2.setPlState(PlayerState::BEFOREATTACK);
        }
    }
    hpbarpl1.setSize(sf::Vector2f(mPlayer1.getHP() * 2, 15));
    hpbarpl2.setSize(sf::Vector2f(mPlayer2.getHP() * 2, 15));
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
         text.setPosition(853 / 3.0f, 640 / 3.0f);
         text.setString("SHOPESCREEN!\nPRESS ENTER TO CONTINUE");
         text.setCharacterSize(30);
         mWindow.clear();
         mWindow.draw(text);
         mWindow.display();
     }
 }

 void Game::run()
 {
    DelayedText txt("WELCOME! LETS PLAY\nPress ENTER TO CONTINUE", font, 30);
    txt.setDelay(sf::seconds(1.f / 10.f));
 	while (mWindow.isOpen())
 	{
 		processEvents();
 		update();
 		render(txt);
 	}
 }