#include <iostream>
#include "GameManager.cpp"

using namespace std;

int main(){
    GameManager newgame = GameManager(40,20);
    newgame.run();
    return 0;
}