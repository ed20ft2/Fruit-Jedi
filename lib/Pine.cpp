#include "Pine.h"

Pine::Pine() {}

const int Pineapple[13][11]= {
    { 0,0,0,1,1,0,1,1,0,0,0, },
    { 0,1,1,1,1,1,1,1,1,1,0, },
    { 1,1,1,1,1,1,1,1,1,1,1, },
    { 0,1,0,1,1,1,1,1,0,1,0, },
    { 0,0,1,1,1,1,1,1,1,0,0, },
    { 0,1,0,1,0,1,0,1,0,1,0, },
    { 0,1,1,0,1,1,1,0,1,1,0, },
    { 0,1,0,1,0,1,0,1,0,1,0, },
    { 0,1,1,0,1,0,1,0,1,1,0, },
    { 0,1,0,1,0,1,0,1,0,1,0, },
    { 0,0,1,1,1,0,1,1,1,1,0, },
    { 0,0,0,1,0,1,0,1,0,0,0, },
    { 0,0,0,0,1,1,1,0,0,0,0, },
};

void Pine::init(int speed) {
    //printf("Pine: Init\n");
    _x = 190;
    _y = rand() % 35; // 48 - height, should stop it from clipping at the bottom
    _velocity.x = speed;
}

void Pine::draw(N5110 &lcd) {
    //printf("Pine: Draw\n");
    lcd.drawSprite(_x, _y, 13, 11, (int*)Pineapple);
}

void Pine::update(){
    //printf("Pine: Update\n");     
    _x += -_velocity.x; //made it negative so it moves towards the player
}

void Pine::set_velocity(Position2D v){
    printf("Pine: Velocity\n");
    _velocity.x = v.x;
}

void Pine::set_pos(Position2D p) {
    printf("Pine: Set Position\n");
    _x = p.x;
    _y = p.y;
}

Position2D Pine::get_velocity(){ return {_velocity.x,_velocity.y}; }

Position2D Pine::get_pos() { return {_x,_y}; }

