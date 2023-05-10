#ifndef PEACH_H
#define PEACH_H

#include "mbed.h"
#include "N5110.h"
#include "Utils.h"  // for Position


class Peach
{

public:
    Peach();
    void init(int speed);
    void draw(N5110 &lcd);
    void update();
    /// accessors and mutators
    void set_velocity(Position2D v);
    Position2D get_velocity();
    Position2D get_pos();
    void set_pos(Position2D p);
    
private:

    Position2D _velocity;
    int _x;
    int _y;
};
#endif