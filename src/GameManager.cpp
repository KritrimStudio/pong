#include <iostream>
#include <time.h>
#include <conio.h>
#include "PongPaddle.cpp"
#include "PongBall.cpp"
using namespace std;

// this class will manage all the aspects of game, like scores, no of players, their movement keys, new game etc.
class GameManager{
    private:
        // defines the widht and height of the play area (map area)
        int width, height;
        // defines scores for player 1 and 2
        int score1, score2;
        // defines up and down buttons (keys) for each player
        char up1, down1, up2, down2;
        // if TRUE, then game will quit
        bool quit;
        // using pointers for ball and player objects, this wil help us with garbage collection and deconstruction of the unused objects
        // we need one pong ball to play
        PongBall *ball;
        // we need two paddle players
        PongPaddle *player1;
        PongPaddle *player2;
    public:
        // this constructor will define initial state of the game
        GameManager(int w, int h){
            width = w;
            height = h;
            // game should not quit at the begining
            quit = false;
            // time(NULL) will get current time in unicode format
            srand(time(NULL));
            // assign input keys for player movement
            up1 ='w';
            down1 ='s';
            up2 = 'i';
            down2 = 'k';
            // initial score for both players will be zero
            score1 = score2 = 0;
            // place the ball at the center of the map (positioned half of height and half of width)
            ball = new PongBall(w/2, h/2);
            // player 1 will be postioned at the center of far left
            player1 = new PongPaddle(1, (h/2)-3);
            // player 2 will be placed at far right but at the same height as player 1
            player2 = new PongPaddle(w-2, (h/2)-3);
        }
        // we need a destructor coz c++ doesn't have an inbuild garbage collector, so to avoid memory leaks we will maually remove objects for memory i.e, destruct them
        // destructor will same syntax as constructor but will have "~" symbol prefix
        ~GameManager(){
            // remove below pointer objects from memory
            delete (ball, player1, player2);
        }
        // method to increment scores of players
        void incrementScore(PongPaddle *player){
            if(player == player1) {
                score1++;
            }
            if(player == player2) {
                score2++;
            }
            // reset ball and player postions
            ball -> reset();
            player1 -> reset();
            player2 -> reset();
        }
        // draw the map for the game , we will be using command line, instead of fancy graphics
        void drawmap(){
            // clear terminal screen
            system("cls");
            // draw the top wall, '0xB2' will be our wall character, you can use a different charcter if u fancy
            for (int i=0; i<width+2; i++){
                cout << "\xB2";
            }
            cout << endl;

            // draw rest of the items between top and bottom wall
            // Y-axis
            for(int i = 0; i<height; i++){
                // X-axis
                for(int j = 0; j<width; j++){
                    // get x,y cordinates of the ball and both players using the pointers
                    int ballX = ball -> getX();
                    int ballY = ball -> getY();
                    int player1X = player1 -> getX();
                    int player1Y = player1 -> getY();
                    int player2X = player2 -> getX();
                    int player2Y = player2 -> getY();
                    // draw right wall, 0xB2 is the unicode for sidewall char
                    if(j == 0){
                        cout << "\xB2";
                    }

                    // draw rest of the things between right and left wall
                    // draw ball
                    if(ballX == j && ballY == i){
                        cout << "O";
                    }
                    // players will be 4 char in height, draw player1, 0xDB is the unicode for a solid wall char
                    else if(player1X == j && player1Y == i){
                        cout << "\xDB";
                    }
                    else if(player1X == j && player1Y +1 == i){
                        cout << "\xDB";
                    }
                    else if(player1X == j && player1Y +2 == i){
                        cout << "\xDB";
                    }
                    else if(player1X == j && player1Y +3 == i){
                        cout << "\xDB";
                    }
                    // draw player2
                    else if(player2X == j && player2Y == i){
                        cout << "\xDB";
                    }
                    else if(player2X == j && player2Y +1 == i){
                        cout << "\xDB";
                    }
                    else if(player2X == j && player2Y +2 == i){
                        cout << "\xDB";
                    }
                    else if(player2X == j && player2Y +3== i){
                        cout << "\xDB";
                    }
                    // if nothing, then print empty space
                    else{
                        cout << " ";
                    }

                    // draw left wall
                    if(j == width - 1){
                        cout << "\xB2";
                    }
                }// end of j loop
                cout << endl;
            }// end of i loop

            // draw bottom wall
            for (int i=0; i<width+2; i++){
                cout << "\xB2";
            }
            cout << endl;
            // print scores
            cout << "Player 1: " << score1 << endl <<"Player 2: " << score2 << endl;
        }// end of drwaMap()

        // function to move the ball and the player based keyboard input
        void userInput(){
            // move the ball
            ball -> move();
            
            // get x,y cordinates of the ball and both players using the pointers
            int ballX = ball -> getX();
            int ballY = ball -> getY();
            int player1X = player1 -> getX();
            int player1Y = player1 -> getY();
            int player2X = player2 -> getX();
            int player2Y = player2 -> getY();           

            // move Players (if keyboard is hit = _kbhit)
            if(_kbhit){
                // get current typed character
                char currentKey = _getch();
                // quit game if user types 'q'
                if(currentKey == 'q'){
                    quit = true;
                }
                // for up and down keys pressed by user
                if(currentKey == up1 && player1Y > 0){
                    player1 -> moveUp();
                }
                if(currentKey == up2 && player2Y > 0){
                    player2 -> moveUp();
                }
                if(currentKey == down1 && player1Y + 4 < height){
                    player1 -> moveDown();
                }
                if(currentKey == down2 && player2Y + 4 < height){
                    player2 -> moveDown();
                }
                // when ball is stopped, pressing any key will move the ball in random direction
                if(ball -> getDirection() == STOP){
                    ball->randomDirection();
                }
            }
        }// end of userInput

        // this method detects collision between ball and the player paddle
        void collisionDetectLogic(){
            // get x,y cordinates of the ball and both players using the pointers
            int ballX = ball -> getX();
            int ballY = ball -> getY();
            int player1X = player1 -> getX();
            int player1Y = player1 -> getY();
            int player2X = player2 -> getX();
            int player2Y = player2 -> getY();

            // ball hits player 1 paddle (paddle size 4)
            for(int i = 0; i < 4; i++){
                if(ballX == player1X + 1 && ballY == player1Y + i){
                    ball -> changeDirection((eDirection)(rand() % 3 + 4));
                }
            }
            // ball hits player 2 paddle (paddle size 4)
            for(int i = 0; i < 4; i++){
                if(ballX == player2X - 1 && ballY == player2Y + i){
                    ball -> changeDirection((eDirection)(rand() % 3 + 1));
                }
            }
            // ball hits top wall
            if(ballY == 0){
                ball -> changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
            }
            // ball hits bottom wall
            if(ballY == height -1){
                ball -> changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : DOWNLEFT);
            }
            // ball hits left wall (score up player 2)
            if(ballX == 0){
                incrementScore(player2);
            }
            // ball hits right wall (score up player 1)
            if(ballX == width -1){
                incrementScore(player1);
            }
        }// end of collisionDetectLogic

        // run the whole game manager logic
        void run(){
            // until user quits
            while(!quit){
                drawmap();
                userInput();
                collisionDetectLogic();
            }
        }
};