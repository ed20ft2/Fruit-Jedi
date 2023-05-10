#ifndef PONGENGINE_H
#define PONGENGINE_H

#include "mbed.h"
#include "N5110.h"
#include "Pine.h"
#include "Utils.h"
#include "Paddle.h"
#include "Bomb.h"
#include "Peach.h"
#include "Melon.h"

class PongEngine {
    public:
        PongEngine();  // pass in the lcd object from the main file
        void init(int paddle_position,int paddle_height,int paddle_width,int speed);
        int update(UserInput input); 
        int add_score(); ////
        void draw(N5110 &lcd);
    private:
        void check_wall_collision();
        void check_paddle_collision();
        void check_goal();
        Pine _pine;
        Bomb _bomb;
        Peach _peach;
        Melon _melon;
        Paddle _paddle;
        int _lives;
        int _score;
};

#endif