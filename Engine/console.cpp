#include <iostream>
#include "Game.h"
using namespace std;

int main()
{
    Player mainPlayer("Player");
    Player enemy1("Enemy 1", 1, 2, 12, 5);
    Player enemy2("Enemy 2", 5, 5, 5, 5);
    Player enemy3("Enemy 3", 9, 4, 2, 5);
    isPlayer1First(mainPlayer, enemy1);

}

// void runBattle(Player player1, Player player2)
// {
//     if (isPlayer1First(player1, player2))
//     {

//     } else
//     {

//     }

// }

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
