#include "PongEngine.h"

PongEngine::PongEngine(){ 
    _lives = 3; 
    _score = 0;
}    

void PongEngine::init(int paddle_position, int paddle_height, int paddle_width, int speed){
    //printf("Pong Engine: Init\n");
    _pine.init(speed);
    _bomb.init(speed);
    _peach.init(speed);
    _melon.init(speed);
    _paddle.init(paddle_position, paddle_height, paddle_width);
}

int PongEngine::update(UserInput input) {   
    //printf("Pong Engine: Update\n"); //testing purposes
    _pine.update();
    _bomb.update();
    _peach.update();
    _melon.update();
    _paddle.update(input);
    // important to update paddles and pine before checking collisions so can
    // correct for it before updating the display
    check_paddle_collision();
    
    check_goal();  // checking if the object passes the LHS

    return _lives;
}

int PongEngine::add_score() { 
    return _score;
}

void PongEngine::draw(N5110 &lcd) {
    //printf("Pong Engine: Draw\n");
    // draw the elements in the LCD buffer
    lcd.setPixel(10, 3, 1);
    lcd.setPixel(6, 11, 1);
    lcd.setPixel(17, 18, 1);
    lcd.setPixel(9, 30, 1);
    lcd.setPixel(5, 39, 1);
    lcd.setPixel(19, 8, 1);
    lcd.setPixel(30, 15, 1);
    lcd.setPixel(33, 30, 1);
    lcd.setPixel(21, 37, 1);
    lcd.setPixel(33, 43, 1);
    lcd.setPixel(34, 4, 1);
    lcd.setPixel(46, 14, 1);
    lcd.setPixel(47, 22, 1);
    lcd.setPixel(45, 33, 1);
    lcd.setPixel(48, 43, 1);
    lcd.setPixel(58, 15, 1);
    lcd.setPixel(58, 4, 1);
    lcd.setPixel(71, 13, 1);
    lcd.setPixel(72, 4, 1);
    lcd.setPixel(81, 10, 1);
    lcd.setPixel(76, 31, 1);
    lcd.setPixel(66, 45, 1);
    
    lcd.drawLine(0,0,WIDTH-1,0,1);  // top
    lcd.drawLine(WIDTH-1,0,WIDTH-1,HEIGHT-1,1);  // back wall
    lcd.drawLine(0,HEIGHT-1,WIDTH-1,HEIGHT-1,1); // bottom
    _paddle.draw(lcd);
    _bomb.draw(lcd);
    _pine.draw(lcd);
    _peach.draw(lcd);
    _melon.draw(lcd);
}

void PongEngine::check_paddle_collision() {
    //printf("Pong Engine: Check Paddle Collision\n");
    // read current attributes of the elements

    // pine position and velocity
    Position2D pine_pos = _pine.get_pos();
    Position2D pine_velocity = _pine.get_velocity();

    // bomb position and velocity
    Position2D bomb_pos = _bomb.get_pos();
    Position2D bomb_velocity = _bomb.get_velocity();

    // peach position and velocity
    Position2D peach_pos = _peach.get_pos();
    Position2D peach_velocity = _peach.get_velocity();

    // melon position and velocity
    Position2D melon_pos = _melon.get_pos();
    Position2D melon_velocity = _melon.get_velocity();

    // paddle position
    Position2D paddle_pos = _paddle.get_pos();  // paddle

    // see if pine has hit the paddle by checking for overlaps
    if (
        (pine_pos.y >= paddle_pos.y) && //top
        (pine_pos.y <= paddle_pos.y + _paddle.get_height() ) && //bottom
        (pine_pos.x >= paddle_pos.x) && //left  
        (pine_pos.x <= paddle_pos.x + _paddle.get_width() )  //right
    ) {
        _pine.init(2);
        _score += 3;
    }
    else if (
        (peach_pos.y >= paddle_pos.y) && //top
        (peach_pos.y <= paddle_pos.y + _paddle.get_height() ) && //bottom 
        (peach_pos.x >= paddle_pos.x) &&
        (peach_pos.x <= paddle_pos.x + _paddle.get_width() )  //right
    ) {
        _peach.init(2);
        _score  += 1;
    }
    else if (
        (melon_pos.y >= paddle_pos.y) && //top
        (melon_pos.y <= paddle_pos.y + _paddle.get_height() ) && //bottom 
        (melon_pos.x >= paddle_pos.x) &&
        (melon_pos.x <= paddle_pos.x + _paddle.get_width() )  //right
    ) {
        _melon.init(3);
        _score += 5;
    }
    else if (
        (bomb_pos.y >= paddle_pos.y) && //top
        (bomb_pos.y <= paddle_pos.y + _paddle.get_height() ) && //bottom 
        (bomb_pos.x >= paddle_pos.x) &&
        (bomb_pos.x <= paddle_pos.x + _paddle.get_width() )  //right
    ) {
        _bomb.init(3);
        _lives--;
    }
}

void PongEngine::check_goal() { // instead of Check goal it works to check if it goes to the left handside

    //printf("Pong Engine: Check Goal\n");
    Position2D pine_pos = _pine.get_pos();
    Position2D pine_velocity = _pine.get_velocity();

    Position2D bomb_pos = _bomb.get_pos();
    Position2D bomb_velocity = _bomb.get_velocity();

    Position2D peach_pos = _peach.get_pos();
    Position2D peach_velocity = _peach.get_velocity();

    Position2D melon_pos = _melon.get_pos();
    Position2D melon_velocity = _melon.get_velocity();

    Position2D paddle_pos = _paddle.get_pos();  // paddle

    // check if pine position has gone off the left
    if (pine_pos.x + 13 < 0) { // + 13 so the sprite disappears outside of the 
        // reset the pine
        _pine.init(4); // when it hits the paddle, it should reset
    }    
    // check if bomb position has gone off the left
    else if (bomb_pos.x + 13 < 0) { // + 13 so the sprite disappears outside of the 
        // reset the bomb
        _bomb.init(4); // when it hits the paddle, it should reset
    }   
    else if (peach_pos.x + 13 < 0) { // + 13 so the sprite disappears into the LHS
        // reset the peach
        _peach.init(4); // when it hits the paddle, it should reset
    }   
    else if (melon_pos.x + 13 < 0) { // + 13 so the sprite disappears into the LHS
        // reset the melon
        _melon.init(4); // when it hits the paddle, it should reset
    }   
}



