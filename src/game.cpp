#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include "../include/game.h"

using namespace std;

Game::Game() {
    srand(time(0));
    attempts = 0;
    score = 0;
    loadHighScore();
}

// 🔹 Load high score from file
void Game::loadHighScore() {
    ifstream file("highscore.txt");

    if (file.is_open()) {
        file >> highScore;
        file.close();
    } else {
        highScore = 0;
    }
}

// 🔹 Save high score to file
void Game::saveHighScore() {
    ofstream file("highscore.txt");

    if (file.is_open()) {
        file << highScore;
        file.close();
    }
}

// 🔹 Setup difficulty
void Game::setup() {
    int choice;

    cout << "==============================\n";
    cout << "   NUMBER GUESSING GAME\n";
    cout << "==============================\n";

    cout << "Current High Score: " << highScore << "\n\n";

    cout << "Select Difficulty:\n";
    cout << "1. Easy (1-50, 10 attempts)\n";
    cout << "2. Medium (1-100, 7 attempts)\n";
    cout << "3. Hard (1-200, 5 attempts)\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        range = 50;
        maxAttempts = 10;
    } else if (choice == 2) {
        range = 100;
        maxAttempts = 7;
    } else {
        range = 200;
        maxAttempts = 5;
    }

    number = rand() % range + 1;
    attempts = 0;
}

// 🔹 Main game logic
void Game::play() {
    int guess;

    setup();

    auto start = chrono::high_resolution_clock::now();

    while (attempts < maxAttempts) {
        cout << "\nEnter your guess: ";

        // ✅ Input validation
        if (!(cin >> guess)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Enter a number.\n";
            continue;
        }

        attempts++;

        if (guess < number) {
            cout << "Too low!";
        } else if (guess > number) {
            cout << "Too high!";
        } else {
            cout << "\nCorrect! You guessed in " << attempts << " attempts.\n";

            score = 100 - (attempts * 10);
            if (score < 0) score = 0;

            cout << "Score: " << score << endl;

            // 🔥 High score update
            if (score > highScore) {
                cout << "New High Score!\n";
                highScore = score;
                saveHighScore();
            }

            break;
        }

        cout << " | Attempts left: " << (maxAttempts - attempts) << endl;
    }

    if (attempts == maxAttempts && guess != number) {
        cout << "\nGame Over! The number was: " << number << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Time taken: " << duration.count() << " seconds\n";
}