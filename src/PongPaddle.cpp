#include <iostream>
using namespace std;
// this class will define the attributes of paddle (player) and how it moves

class PongPaddle{
    private:
        int x, y;
        int originalX, originalY;
    public:
        PongPaddle(){
            x = y = 0;
        }
        PongPaddle(int posX, int posY) : PongPaddle(){
            x = originalX = posX;
            y = originalY = posY;
        }
        void reset(){
            x = originalX;
            y = originalY;
        }
        // inline functions are required to reduce method call overhead, for example if calling method takes 3 sec, and executing method takes just 1 sec, use inline 
        // move the paddle up and down Y axis, paddle shouldn't move in X axis
        inline void moveUp(){
            y--;
        }
        inline void moveDown(){
            y++;
        }
        // simple getter methods
        inline int getX(){
            return x;
        }
        inline int getY(){
            return y;
        }
        friend ostream & operator<<(ostream &out, PongPaddle paddle){
            out << "Paddle [x:" << paddle.x << ", y:" << paddle.y << "]";
            return out;
        }
};