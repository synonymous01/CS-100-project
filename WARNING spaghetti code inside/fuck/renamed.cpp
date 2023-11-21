#include <iostream>
#include "Game.h"


using namespace std;


int main()
{
    Player mainPlayer("Player");
    Player enemy1("Enemy 1", 1, 2);
    Player enemy2("Enemy 2", 5, 8);
    Player enemy3("Enemy 3", 9, 4);
    fight(mainPlayer, enemy1);
    fight(mainPlayer, enemy2);
    fight(mainPlayer, enemy3);
}

void fight(Player player1, Player player2)
{
    if (isPlayer1First(player1, player2))
    {
        runBattle(player1, player2);
    } else
    {
        runBattle(player2, player1);
    }
    
}

void runBattle(Player p1, Player p2)
{
    bool isGameOver = false;
    do 
    {
        cout << "It's " << p1.getName() << "'s turn! What will you do?" << endl;
        turn(p1, p2, isGameOver);
        cout << "It's " << p2.getName() << "'s turn! What will they do?" << endl;
        turn(p2, p1, isGameOver);
    } while (!isGameOver);

    //below code to declare the winner of the battle!
    if (p1.dealDamage(0))
    {
        cout << p2.getName() << " is the winner of the battle!!!";
    } else 
    {
        cout << p1.getName() << " is the winner of the battle!!!";
    }
}

void turn(Player attacker, Player defender, bool &gameStatus)
{
    cout << "0 for Strong Attack" << endl;
    cout << "1 for Light Attack" << endl;
    cout << "2 for Defending this turn" << endl;
    cout << "Press any other key to skip this turn" << endl;
    int choice;
    //modifier is a % which is multiplied by difficulty to determine if attack fails or not 
    double miss_modifier = 0;
    defender.defending ? miss_modifier += 0.25 : miss_modifier; 
    if (attacker.getBot())
    {
        choice = attacker.decideTurn();
    }
    else 
    {
        cin >> choice;
    }
    int roll = attacker.getRoll();
    switch(choice)
    {
        case STRONG_ATTACK:
            attacker.defending = false;
            miss_modifier += 0.6;
            double difference = (miss_modifier * 20) - roll;
            attacker.recordOutcome(difference);
            if (difference > 0)
            {
                printPhrase(0, attacker.getName());
                gameStatus = attacker.dealDamage(attacker.getUnarmedAttack());
            } else 
            {
                printPhrase(2, attacker.getName());
                gameStatus = defender.dealDamage(attacker.getUnarmedAttack());
            }
            break;
        case LIGHT_ATTACK:
            attacker.defending = false;
            miss_modifier += 0.2;
            double difference = (miss_modifier * 20) - roll;
            attacker.recordOutcome(difference);
            if (difference > 0)
            {
                printPhrase(0, attacker.getName());
                gameStatus = attacker.dealDamage(attacker.getUnarmedAttack() * 0.5);
            } else
            {
                printPhrase(1, attacker.getName());
                gameStatus = defender.dealDamage(attacker.getUnarmedAttack() * 0.5);
            }
            break;
        case DEFEND:
            attacker.defending = true;
            break;
    }
}


void printPhrase(int attackType, string attackerName)
{
    cout << attackerName << phrases[attackType][rand() % 3] << endl;

}

bool isPlayer1First(Player p1, Player p2)
{
    cout << "Which player attacks first? Lets decide with a dice roll!" << endl;
    // player1 has an advantage; if roll is equal player1 gets first turn
    if (p1.getRoll() >= p2.getRoll())
    {
        cout << p1.getName() << " gets the first turn!";
        return true;
    } else 
    {
        cout << p2.getName() << " gets the first turn!";
        return false;
    }
}