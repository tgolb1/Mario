#include "Level.h"
#include "Game.h"

Level::Level(){
    settings = new Settings();
    settings->setPreferences("preferences.txt");
    N = settings->N;
    L = settings->L;
    V = settings->V;
    cPct = settings->coinPct;
    bPct = settings->coinPct;
    gPct = settings->coinPct;
    kPct = settings->coinPct;
    mPct = settings->coinPct;
    delete settings;
}

Level::~Level(){}

void Level::setLevel(){
    int randNum;
    grid = new char*[N];

    for(int i=0; i<N; ++i){
        grid[i] = new char[N];
        for(int j=0; j<N; ++j){
            randNum = rand()%100;
            if (randNum < cPct) {
                grid[i][j] = 'c';
            } else if (randNum < cPct+bPct) {
                grid[i][j] = 'x';
            } else if (randNum < cPct+bPct+gPct) {
                grid[i][j] = 'g';
            } else if (randNum < cPct+bPct+gPct+kPct) {
                grid[i][j] = 'k';
            } else {
                grid[i][j] = 'm';
            }
        }
    }
    //grid is now full of coins, blanks, goombas, koopas, and mushrooms
    //Hero, warp pipe, and level boss will overwrite 3 of these squares

}