#include <iostream>
#include "../include/game.h"

using namespace std;

int main() {
    char choice;

    do {
        Game game;
        game.play();

        cout << "\nDo you want to play again? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}