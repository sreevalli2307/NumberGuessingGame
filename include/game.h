#ifndef GAME_H
#define GAME_H

class Game {
private:
    int number;
    int attempts;
    int maxAttempts;
    int range;
    int score;
    int highScore;

public:
    Game();
    void setup();
    void play();

    void loadHighScore();
    void saveHighScore();
};

#endif