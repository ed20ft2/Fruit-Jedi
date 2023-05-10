#include "Peach.h"

Peach::Peach() {}

const int Princess[13][14]= {
    { 0,0,1,1,1,1,0,0,0,0,0,0,0,0 },
    { 0,0,0,1,0,0,1,0,0,0,0,0,0,0 },
    { 0,0,0,0,1,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,0,1,1,0,1,0,1,1,1,1,0 },
    { 0,0,1,1,0,0,1,1,1,0,0,0,0,1 },
    { 0,1,0,0,0,0,0,1,0,0,0,1,1,0 },
    { 1,0,0,0,1,1,0,1,1,0,1,0,0,0 },
    { 1,0,0,1,0,0,0,1,0,1,0,0,0,0 },
    { 1,0,0,0,0,0,0,0,0,1,0,0,0,0 },
    { 1,0,0,0,0,0,0,0,0,1,0,0,0,0 },
    { 0,1,0,0,0,0,0,0,1,0,0,0,0,0 },
    { 0,0,1,0,0,0,0,1,0,0,0,0,0,0 },
    { 0,0,0,1,1,1,1,0,0,0,0,0,0,0 },
};

void Peach::init(int speed) {
    //printf("Peach: Init\n"); // Testing purposes to see if Peach.h works accordingly
    _x = 140;
    _y = rand() % 35; // 48 - height, should stop it from clipping at the bottom

    _velocity.x = speed;
}

void Peach::draw(N5110 &lcd) {
    //printf("Peach: Draw\n");
    lcd.drawSprite(_x, _y, 13, 14, (int*)Princess);
}

void Peach::update(){
    //printf("Peach: Update\n");     
    _x += -_velocity.x; //made it negative so it moves towards the player
}

void Peach::set_velocity(Position2D v){
    printf("Peach: Velocity\n");
    _velocity.x = v.x;
}

void Peach::set_pos(Position2D p) {
    printf("Peach: Set Position\n");
    _x = p.x;
    _y = p.y;
}

Position2D Peach::get_velocity(){ return {_velocity.x,_velocity.y}; }

Position2D Peach::get_pos() { return {_x,_y}; }
