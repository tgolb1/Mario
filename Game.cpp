#include "Game.h"

using namespace std;

Game::Game(){
    srand(time(0)); //set random seed for RNG
    l = new Level();
    log = "\0";
    lives = l->V;
    coins = 0;
    powLev = 0;
    killCount = 0;

    for(int i = 0; i < l->L; ++i){
        level = i+1;
        l->setLevel();
        setSpecialObjects();
        playLevel();
    }

    delete l;
    
}

Game::~Game(){}

void Game::setSpecialObjects(){
    heroX = randNum(l->N); //set hero coordinates
    heroY = randNum(l->N);
    occObj = l->grid[heroX][heroY];
    l->grid[heroX][heroY] = 'H'; //place hero

    l->grid[randNum(l->N)][randNum(l->N)] = 'w'; //place warp pipe 
    l->grid[randNum(l->N)][randNum(l->N)] = 'b'; //place boss

}


void Game::playLevel(){
    bool isAlive = true;

    while(isAlive){
        log += "\n\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~";
        log += "\n\nLevel: " + to_string(level);
        log += "\nMario is at position (" + to_string(heroX) + ", " + to_string(heroY) + ")";
        log += "\nLives remaining: " + to_string(lives);
        log += "\nCoins in wallet: " + to_string(coins);
        log += "\nPower Level: " + to_string(powLev);
        printGrid(l->N);

        move();

        if (killCount == 7) {
            killCount = 0;
            lives++;
            log += "\n\nEXTRA LIFE (7 consecutive kills)";
        }

        switch(occObj){
            case 'x':
                log += "\nMario moves on.";
            break;

            case 'c':
                coins++;
                log += "\nMario picked up a coin! (" + to_string(coins) + ")";
            break;

            case 'g':
                while (isAlive){
                    if((randNum(100))<80){
                        log += "\nMario fought a goomba and won!";
                        killCount++;
                        break;
                    } else {
                        if (powLev >=1){
                            log += "\nMario fought a goomba and lost.";
                            log += "\nMario will STAY PUT.";
                            powLev--;
                        } else if (lives > 0){
                            lives--;
                            powLev = 0;
                            killCount = 0;
                        } else {
                            isAlive = false;
                            //break;
                        }
                    }
                }
            break;

            case 'k':
                while (isAlive){
                    if((randNum(100))<65){
                        log += "\nMario fought a koopa and won!";
                        killCount++;
                        break;
                    } else {
                        if (powLev > 0){
                            log += "\nMario fought a koopa and lost.";
                            log += "\nMario will STAY PUT.";
                            powLev -= 1;
                        } else if (lives > 0){
                            lives--;
                            powLev = 0;
                            killCount = 0;    
                        } else {
                            log += "\nMario DIED."; //todo delete
                            isAlive = false;
                            //break;
                        }
                    }
                }
            break;

            case 'm':
                powLev++;
                log += "\nMario ate a mushroom! (PL:" + to_string(powLev) + ")";
            break;

            case 'b':
                while (isAlive){
                    if((randNum(100))<50){
                        log += "\nMario fought the level boss and won!";
                        return;
                    } else {
                        if (powLev >=2){
                            log += "\nMario fought the level boss and lost.";
                            log += "\nMario will STAY PUT.";
                            powLev -= 2;
                        } else if (lives > 0) {
                            lives--;
                            powLev = 0;
                            killCount = 0;    
                            log += "\nMario fought the level boss and lost.";
                            log += "\n" + to_string(lives) + " lives remaining.";
                            log += "\nMario will STAY PUT.";
                        } else {
                            isAlive = false;
                            //break;
                        }
                    }
                }
            break;

            case 'w':
                log += "\nMario warped to next level!";
                return;
            break;

            default:
                log += "\n\n\n~~~~~ error occured ~~~~~\n\n\n";
            return;
        }
    }
    //log += "\n\n\nMario died and the game ended :(\n\n";

    cout << log << endl;
}

void Game::move(){
    int direction = randNum(4);
    l->grid[heroX][heroY] = 'x';

    log += "\n\nMario will move ";
    switch(direction){
        case 0: //up
            log += "UP.";
            if(heroX == 0){
                heroX = l->N;
            } else {
                heroX--;
            }
        break;
        case 1: //down
            log += "DOWN.";
            if(heroX == l->N){
                heroX = 0;
            } else {
                heroX++;
            }
        break;
        case 2: //left
            log += "LEFT.";
            if(heroY == 0){
                heroY = l->N;
            } else {
                heroY--;
            }
        break;
        case 3: //right
            log += "RIGHT";
            if(heroY == l->N){
                heroY = 0;
            } else {
                heroY++;
            }
        break;
    }
    occObj = l->grid[heroX][heroY];
    l->grid[heroX][heroY] = 'H';
}


int Game::randNum(int bound){
    return rand()%(bound);
}

void Game::printGrid(int n) {
    log += "\n";
    for (int i = 0; i < n; ++i){
        log += "\n";
        for (int j = 0; j < n; ++j){
            log += l->grid[i][j];
            log += " ";
        }
    }
}
