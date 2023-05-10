#include "Melon.h"

Melon::Melon() {}

const int Vader[13][13]= {
    { 0,0,0,0,0,0,0,0,0,1,1,0,0 },
    { 0,0,0,0,0,0,0,0,1,0,1,1,0 },
    { 0,0,0,0,0,0,0,1,1,0,0,1,1 },
    { 0,0,0,0,0,0,1,1,0,1,0,1,1 },
    { 0,0,0,0,0,1,1,1,1,1,0,1,1 },
    { 0,0,0,0,1,1,1,1,1,1,0,1,1 },
    { 0,0,0,1,1,1,1,0,1,1,0,1,1 },
    { 0,0,1,1,1,0,1,1,1,1,0,1,1 },
    { 0,1,1,0,1,1,1,1,1,0,1,1,0 },
    { 1,0,0,1,1,1,1,0,0,1,1,1,0 },
    { 1,1,0,0,0,0,0,0,1,1,1,0,0 },
    { 0,1,1,1,1,1,1,1,1,1,0,0,0 },
    { 0,0,0,1,1,1,1,1,0,0,0,0,0 },
};

void Melon::init(int speed) {
    //printf("Melon: Init\n"); // Testing purposes to see if Melon.h works accordingly
    _x = 200;
    _y = rand() % 35; // 48 - height, should stop it from clipping at the bottom

    _velocity.x = speed;
}

void Melon::draw(N5110 &lcd) {
    //printf("Melon: Draw\n");
    lcd.drawSprite(_x, _y, 13, 13, (int*)Vader);
}

void Melon::update(){
    //printf("Melon: Update\n");     
    _x += -_velocity.x; //made it negative so it moves towards the player
}

void Melon::set_velocity(Position2D v){
    printf("Melon: Velocity\n");
    _velocity.x = v.x;
}

void Melon::set_pos(Position2D p) {
    printf("Melon: Set Position\n");
    _x = p.x;
    _y = p.y;
}

Position2D Melon::get_velocity(){ return {_velocity.x,_velocity.y}; }

Position2D Melon::get_pos() { return {_x,_y}; }
