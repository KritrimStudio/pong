#include <iostream>
using namespace std;

enum eDirection {STOP=0, LEFT=1, UPLEFT=2, DOWNLEFT=3, RIGHT=4, UPRIGHT=5, DOWNRIGHT=6};

// this class will define the ball location, direction, movement
class PongBall{
    private:
        int x, y;
        int originalX, originalY;
        eDirection direction;
    public:
        // constructor
        PongBall(int posX, int posY){
            originalX = posX;
            originalY = posY;
            x = posX;
            y = posY;
            direction = STOP;
        }
        // called to reset the position & Direction of the ball
        void reset(){
            x = originalX;
            y = originalY;
            direction = STOP;
        }
        // changes direction of the ball to the user given input
        void changeDirection(eDirection dir){
            direction = dir;
        }
        void randomDirection(){
            // rand() generates random numbers
            // rand() % 6 generates numbers from 0 - 5
            // ((rand() % 6) +1) generates numbers from 1-6, since we don't need 0, coz 0 is used only for stopping the ball
            direction = (eDirection)((rand() % 6) +1);
        }
        // for moving the ball in different directions
        void move(){
            // enums are extremely useful for sWITCh staements, coz it'll accpet only predefined values, therefore we can be sure that we have writtent switch for all the cases in enum
            switch(direction){
                case STOP:
                    break;
                case LEFT:
                    x--;
                    break;
                case RIGHT:
                    x++;
                    break;
                case UPLEFT:
                    x--;
                    y--;
                    break;
                case UPRIGHT:
                    x++;
                    y--;
                    break;
                case DOWNLEFT:
                    x--;
                    y++;
                    break;
                case DOWNRIGHT:
                    x++;
                    y++;
                    break;
                default:
                    break;
            }
        }
        // creating a friend function, this function overloads the "<<" operator from oStream class
        friend ostream & operator<<(ostream &out, PongBall pBall){
            // "<<" symbol acts like string concatenation
            out << "Ball [x:" << pBall.x << " , y:" << pBall.y << "] dir:" << pBall.direction;
            return out;
        }
        // inline functions are required to reduce method call overhead, for example if calling method takes 3 sec, and executing method takes just 1 sec, use inline 
        // simple getter methods
        inline int getX(){
            return x;
        }
        inline int getY(){
            return y;
        }
        inline int getDirection(){
            return direction;
        }

};