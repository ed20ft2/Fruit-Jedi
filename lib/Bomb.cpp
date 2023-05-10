#include "Bomb.h"

Bomb::Bomb() {}

const int Mine[13][12]= {
    { 0,0,0,0,0,1,1,0,0,0,1,0 },
    { 0,0,0,0,1,0,0,1,0,0,0,0 },
    { 0,0,0,1,1,1,0,0,0,1,0,0 },
    { 0,0,1,0,0,0,1,0,0,0,0,1 },
    { 0,1,0,0,0,0,0,1,0,0,0,0 },
    { 1,0,0,1,0,1,0,0,1,0,0,0 },
    { 1,0,0,0,1,0,0,0,1,0,0,0 },
    { 1,0,0,1,0,1,0,0,1,0,0,0 },
    { 1,0,0,0,0,0,0,0,1,0,0,0 },
    { 0,1,0,0,0,0,0,1,0,0,0,0 },
    { 0,0,1,0,0,0,1,0,0,0,0,0 },
    { 0,0,0,1,1,1,0,0,0,0,0,0 },
};

void Bomb::init(int speed) {
    //printf("Bomb: Init\n"); //testing if actually initialises
    _x = 120;
    _y = rand() % 35;

    _velocity.x = speed;
}

void Bomb::draw(N5110 &lcd) {
    lcd.drawSprite(_x, _y, 13, 12, (int*)Mine);
}

void Bomb::update(){
    _x += -_velocity.x; //made it negative so it moves towards the player
}

void Bomb::set_velocity(Position2D v){
    printf("Bomb: Velocity\n");
    _velocity.x = v.x;
}

void Bomb::set_pos(Position2D p) {
    printf("Bomb: Set Position\n");
    _x = p.x;
    _y = p.y;
}

Position2D Bomb::get_velocity(){ return {_velocity.x,_velocity.y}; }

Position2D Bomb::get_pos() { return {_x,_y}; }

