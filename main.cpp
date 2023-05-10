///////////// includes /////////////////////
#include "mbed.h"
#include "Joystick.h"
#include "N5110.h"  
#include "PongEngine.h"
#include "Utils.h"
#include "numbers.h"

///////////// defines /////////////////////
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 10

///////////// objects ///////////////////
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
Joystick joystick(PC_1, PC_0);
DigitalIn buttonA(PC_3); //onboard user button
DigitalIn buttonB(PC_2); //button on the board
PwmOut buzzer(PA_15);
PongEngine pong;
DigitalOut led1(PC_12);
DigitalOut led2(PC_10);
DigitalOut led3(PC_11);

///////////// prototypes ///////////////
void init();
void render();
void welcome();
void story();
void tutorial();
void game_over();
////////////////////////////////////////

/////////// Musical Notes ///////////
#define NOTE_E3  165
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_AS3 233
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_E5  659
#define NOTE_D5  587
#define NOTE_G5  784
#define NOTE_F5  698
#define NOTE_AS4 466
#define NOTE_A5  880

////////////  Song ///////////////
int spaceMelody[] = {
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4,
  NOTE_C5, NOTE_B4, NOTE_C5, NOTE_D5,
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4,
  NOTE_C5, NOTE_B4, NOTE_C5, NOTE_D5,
  NOTE_E5, NOTE_C5, NOTE_E5, NOTE_G5,
  NOTE_G4
};

int gameOverTheme[] = {
  NOTE_E3, NOTE_G3, NOTE_C4, NOTE_GS3,
  NOTE_DS4, NOTE_AS3, NOTE_GS3, NOTE_G4,
  NOTE_FS4, NOTE_C5
};
//////////////////////////////////

void play_note(int frequency);

int main() {
    init();      // initialise devices and objects
    buttonA.mode(PullUp);
    buttonB.mode(PullDown);
    welcome();   // waiting for the user to start 
    story();
    render();    // first draw the initial frame 
    int fps = 15;
    thread_sleep_for(1000/fps);  // and wait for one frame period - millseconds
    
    int lives = 3;   // display lives on LEDs
    
    while (lives > 0) {  // keep looping while lives remain

        led1 = (lives >= 1);
        led2 = (lives >= 2);
        led3 = (lives >= 3);

        // read the joystick input and store in a struct
        UserInput input = {joystick.get_direction(),joystick.get_mag()};
        lives = pong.update(input);   // update the game engine based on input    
        render();                     // draw frame on screen
        thread_sleep_for(1000/fps);   // and wait for one frame period - ms

        int counter = pong.add_score();
    }
    game_over();

    int score = pong.add_score();

    //score = score + 750; //for testing purposes to test the hundreds digit + test the achievement system

    //for testing purposes
    //printf("Your final score is: %d\n", score); 

    // SCORE-BOARD
    lcd.drawSprite(19, 5, 9, 8, (int*)letter_s);
    lcd.drawSprite(29, 5, 9, 8, (int*)letter_c);
    lcd.drawSprite(39, 5, 9, 8, (int*)letter_o);
    lcd.drawSprite(49, 5, 9, 8, (int*)letter_r);
    lcd.drawSprite(59, 5, 9, 8, (int*)letter_e);
    lcd.refresh();

    int hundreds = score / 100;   // get the hundreds digit
    int tens = (score / 10) % 10; // get the tens digit
    int ones = score % 10;        // get the ones digit

    // displays tens digit
    if (hundreds >= 0) {
        //lcd.printString(0, 2, 1); /// test purposes
        lcd.drawSprite(27, 20, 9, 8, (int*)zero);
        if (hundreds == 1) {
            lcd.drawSprite(27, 20, 9, 8, (int*)one);
        } else if (hundreds == 2) {
            lcd.drawSprite(27, 20, 9, 8, (int*)two);
        } else if (hundreds == 3) {
            lcd.drawSprite(27, 20, 9, 8, (int*)three);
        } else if (hundreds == 4) {
            lcd.drawSprite(27, 20, 9, 8, (int*)four);
        } else if (hundreds == 5) {
            lcd.drawSprite(27, 20, 9, 8, (int*)five);
        } else if (hundreds == 6) {
            lcd.drawSprite(27, 20, 9, 8, (int*)six);
        } else if (hundreds == 7) {
            lcd.drawSprite(27, 20, 9, 8, (int*)seven);
        } else if (hundreds == 8) {
            lcd.drawSprite(27, 20, 9, 8, (int*)eight);
        } else if (hundreds == 9) {
            lcd.drawSprite(27, 20, 9, 8, (int*)nine);
        }
    }

    // displays tens digit
    if (tens >= 0) {
        //lcd.printString(0, 2, 1); /// test purposes
        lcd.drawSprite(39, 20, 9, 8, (int*)zero);
        if (tens == 1) {
            lcd.drawSprite(39, 20, 9, 8, (int*)one);
        } else if (tens == 2) {
            lcd.drawSprite(39, 20, 9, 8, (int*)two);
        } else if (tens == 3) {
            lcd.drawSprite(39, 20, 9, 8, (int*)three);
        } else if (tens == 4) {
            lcd.drawSprite(39, 20, 9, 8, (int*)four);
        } else if (tens == 5) {
            lcd.drawSprite(39, 20, 9, 8, (int*)five);
        } else if (tens == 6) {
            lcd.drawSprite(39, 20, 9, 8, (int*)six);
        } else if (tens == 7) {
            lcd.drawSprite(39, 20, 9, 8, (int*)seven);
        } else if (tens == 8) {
            lcd.drawSprite(39, 20, 9, 8, (int*)eight);
        } else if (tens == 9) {
            lcd.drawSprite(39, 20, 9, 8, (int*)nine);
        }
    }
    // display the ones digit
    if (ones == 0) {
            lcd.drawSprite(51, 20, 9, 8, (int*)zero);
        } else if (ones == 1) {
            lcd.drawSprite(51, 20, 9, 8, (int*)one);
        } else if (ones == 2) {
            lcd.drawSprite(51, 20, 9, 8, (int*)two);
        } else if (ones == 3) {
            lcd.drawSprite(51, 20, 9, 8, (int*)three);
        } else if (ones == 4) {
            lcd.drawSprite(51, 20, 9, 8, (int*)four);
        } else if (ones == 5) {
            lcd.drawSprite(51, 20, 9, 8, (int*)five);
        } else if (ones == 6) {
            lcd.drawSprite(51, 20, 9, 8, (int*)six);
        } else if (ones == 7) {
            lcd.drawSprite(51, 20, 9, 8, (int*)seven);
        } else if (ones == 8) {
            lcd.drawSprite(51, 20, 9, 8, (int*)eight);
        } else if (ones == 9) {
            lcd.drawSprite(51, 20, 9, 8, (int*)nine);
    }   

    // Milestones Achievement 
    if (score < 100) {
        // do nothing
        }else if (score > 100 && score < 250 ) {
            lcd.drawSprite(19, 33, 11, 11, (int*)stars);
        }else if (score > 250 && score < 500 ) {
            lcd.drawSprite(19, 33, 11, 11, (int*)stars);
            lcd.drawSprite(31, 33, 11, 11, (int*)stars);
        }else if (score > 500 && score < 750 ) {
            lcd.drawSprite(19, 33, 11, 11, (int*)stars);
            lcd.drawSprite(31, 33, 11, 11, (int*)stars);
            lcd.drawSprite(44, 33, 11, 11, (int*)stars);
        }else if (score > 750 ) {
            lcd.drawSprite(19, 33, 11, 11, (int*)stars);
            lcd.drawSprite(31, 33, 11, 11, (int*)stars);
            lcd.drawSprite(44, 33, 11, 11, (int*)stars);
            lcd.drawSprite(56, 33, 11, 11, (int*)stars);
        }

    lcd.setPixel(9, 10, 1);
    lcd.setPixel(21, 23, 1);
    lcd.setPixel(7, 25, 1);
    lcd.setPixel(18, 32, 1);
    lcd.setPixel(13, 41, 1);
    lcd.setPixel(41, 45, 1);
    lcd.setPixel(33, 43, 1);
    lcd.setPixel(45, 44, 1);
    lcd.setPixel(58, 38, 1);
    lcd.setPixel(64, 30, 1);
    lcd.setPixel(75, 25, 1);
    lcd.setPixel(70, 13, 1);
    lcd.setPixel(80, 6, 1);
    lcd.setPixel(73, 43, 1);
    lcd.refresh();
}

void init() {
    lcd.init(LPH7366_1);
    lcd.setContrast(0.55);
    joystick.init();
    pong.init(0,10,10,2);     // paddle x position, paddle_height,paddle_width,speed

    // initialize the DigitalOut objects for the LEDs
    led1 = DigitalOut(PC_12);
    led2 = DigitalOut(PC_10);
    led3 = DigitalOut(PC_11);
}

void render() {  // clear screen, re-draw and refresh
    lcd.clear();  
    pong.draw(lcd);
    lcd.refresh();
}

void welcome() { // splash screen

    const int letter_fruit[9][41]= {
    { 0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1, },
    { 1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1, },
    { 0,0,0,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,1,0, },
    { 0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0, },
    { 0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0, },
    { 0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0, },
    { 0,0,1,1,1,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0, },
    { 0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,1,0,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0, },
    { 0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,1,1,0,0,1,1,0,0,0,0,1,0,0,0,0, },
    };

    const int letter_jedi[12][30]= {
    { 0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,1,1, },
    { 0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,1,1, },
    { 0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1, },
    { 0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1, },
    { 0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1, },
    { 0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1, },
    { 0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,1,1,1,0,0,1,1, },
    { 0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,1,0,1,1,1,1,1,1,0,0,0,0,1,1, },
    { 0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,1,1, },
    { 1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,1,1, },
    { 0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
    { 0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, },
    };

    lcd.printString(" Fruit ",0,1);  
    lcd.printString(" Jedi ",0,2);
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
    lcd.clear();
    lcd.printString("Created by:",0,1);  
    lcd.printString("Farhan",0,2);
    lcd.printString("201528357",0,4);
    lcd.refresh();
    ThisThread::sleep_for(1000ms);
    lcd.clear();
    lcd.refresh();

    int a = 1;
    while (a == 1){
        for(int i = 0; i < sizeof(spaceMelody) / sizeof(int); i++){         //iterate through the C_major_scale array
        play_note(spaceMelody[i]);    //pass the note at position C_major_scale[i] to function
        lcd.drawSprite(10, 28-i, 9, 41, (int*)letter_fruit);
        lcd.drawSprite(38, 42-i, 12, 30, (int*)letter_jedi);
        lcd.setPixel(10, 3, 1);
        lcd.setPixel(34, 4, 1);
        lcd.setPixel(6, 11, 1);
        lcd.setPixel(24, 23, 1);
        lcd.setPixel(21, 37, 1);
        lcd.setPixel(77, 40, 1);
        lcd.setPixel(9, 30, 1);
        lcd.setPixel(5, 39, 1);
        lcd.setPixel(58, 4, 1);
        lcd.setPixel(72, 4, 1);
        lcd.setPixel(81, 10, 1);
        lcd.setPixel(58, 15, 1);
        lcd.setPixel(48, 43, 1);
        lcd.setPixel(67, 15, 1);
        lcd.inverseMode();
        lcd.refresh();
        ThisThread::sleep_for(25ms);  // slows down the pace of the melody
        lcd.clear();
        }
        a = 0;
        lcd.refresh();
        buzzer.pulsewidth_us(0);
        lcd.clear();
    }
    lcd.normalMode();
    lcd.setPixel(4, 7, 1);
    lcd.setPixel(25, 21, 1);
    lcd.setPixel(12, 25, 1);
    lcd.setPixel(17, 37, 1);
    lcd.setPixel(3, 42, 1);
    lcd.setPixel(39, 26, 1);
    lcd.setPixel(72, 36, 1);
    lcd.setPixel(61, 11, 1);
    lcd.setPixel(80, 5, 1);
    lcd.drawSprite(6, 7, 9, 41, (int*)letter_fruit);
    lcd.drawSprite(45, 15, 12, 30, (int*)letter_jedi);
    lcd.printString("A - Start",14,4); 
    lcd.printString("B - Tutorial",9,5);   
    lcd.refresh();

    while (buttonA.read() == 1){
        ThisThread::sleep_for(100ms);
        if (buttonB.read() == 1){
        tutorial();
        }
    }
}

void story() {
    lcd.clear();
    lcd.printString(" As a young ",0,1);  
    lcd.printString(" Jedi in ",0,2);
    lcd.printString(" training ",0,3);
    lcd.printString(" you must ",0,4);  
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
    lcd.clear();
    lcd.printString(" test your ",0,1);
    lcd.printString(" skills by ",0,2);
    lcd.printString(" by cutting ",0,3);  
    lcd.printString(" FRUIT... ",0,4);
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
    lcd.clear();
    lcd.printString(" Jabba the ",0,1);  
    lcd.printString(" Hut secretly ",0,2);
    lcd.printString(" wants to ",0,3);
    lcd.printString(" sabotage ",0,4);
    lcd.printString(" your progress",0,5);
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
    lcd.clear();
    lcd.printString(" Will you ",0,2);  
    lcd.printString(" overcome his ",0,3);
    lcd.printString(" treachery ?",0,4);
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
    lcd.clear();
    lcd.printString("  and become ",0,2);  
    lcd.printString("    a true ",0,3);
    lcd.printString("    JEDI! ",0,4);
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
}

void game_over() { // splash screen 
    const int melodyLength = sizeof(gameOverTheme) / sizeof(int);
    const int melodyDuration = 200; // Duration of each note in milliseconds

    for (int i = 0; i < melodyLength; i++)
    {
        play_note(gameOverTheme[i]);
        buzzer.pulsewidth_us(0);
        lcd.clear();
        lcd.inverseMode();
        lcd.printString("|            |", 0, 0);
        lcd.printString("|            |", 0, 1);
        lcd.printString("| ========== |", 0, 2);
        lcd.printString("| Game Over! |", 0, 3);
        lcd.printString("| ========== |", 0, 4);
        lcd.printString("|            |", 0, 5);
        lcd.refresh();
        ThisThread::sleep_for(300ms);
        lcd.clear();
        lcd.normalMode();
        lcd.refresh();
        ThisThread::sleep_for(50ms); // Short pause between notes
    }

    for (int volume = 100; volume >= 0; volume -= 5)
    {
        buzzer.pulsewidth_us(static_cast<int>(volume / 100.0 * 1000));
        ThisThread::sleep_for(50ms);
    }
    lcd.inverseMode();
    lcd.clear();
    lcd.refresh();
    ThisThread::sleep_for(50ms);
}

void play_note(int frequency){
    buzzer.period_us((float) 1000000.0f/ (float) frequency);    //set the period of the pwm signal (in us)
    buzzer.pulsewidth_us(buzzer.read_period_us()/2);            //set pulse width of the pwm to 1/2 the period
    ThisThread::sleep_for(500ms);                               //play sound for 500ms
}

void tutorial() {

    const int Lightsaber[10][10]= {
    { 1,1,0,0,0,0,0,0,0,0, },
    { 1,1,1,1,0,0,0,0,0,0, },
    { 0,1,1,0,1,0,0,0,0,0, },
    { 0,1,0,1,1,0,0,0,0,0, },
    { 0,0,1,1,0,1,0,0,0,0, },
    { 0,0,0,0,1,0,1,0,0,0, },
    { 0,0,0,0,0,1,0,1,0,0, },
    { 0,0,0,0,0,0,1,0,1,0, },
    { 0,0,0,0,0,0,0,1,0,1, },
    { 0,0,0,0,0,0,0,0,1,1, },
    };

    lcd.clear();
    lcd.printString(" Cut the Fruit",0,1);
    lcd.printString("  with the ",0,2);
    lcd.printString(" light-saber ",0,3);
    lcd.printString("    edge!   ",0,4);
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
    lcd.clear();
    lcd.printString("  Using the ",0,1);
    lcd.printString("  Joystick ",0,2);
    lcd.printString("    'Up' ",0,3);
    lcd.printString("   'Down' ",0,4);
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
    lcd.clear();
    lcd.printString("  Avoid the",0,2);
    lcd.printString("    bombs! ",0,3);
    lcd.printString("     and ",0,4);
    lcd.refresh();
    ThisThread::sleep_for(2000ms);
    lcd.clear();
    lcd.printString("   Get the ",0,2);
    lcd.printString("   highest ",0,3);
    lcd.printString("   score! ",0,4);
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
    lcd.clear();
    lcd.printString(" ----------- ",0,1);  
    lcd.printString("   Fruit   ",0,2);  
    lcd.printString("   Jedi   ",0,3);
    lcd.printString("   Handbook   ",0,4);
    lcd.printString(" ----------- ",0,5);  
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
    lcd.clear();
    lcd.printString("Princess Leia",0,1);  
    lcd.printString("   Peach  ",0,2);
    lcd.printString("  --------- ",0,3);
    lcd.printString("  Points +1 ",0,4);
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
    lcd.clear();
    lcd.printString("  Chewbecca ",0,1);  
    lcd.printString("  PineApple ",0,2);
    lcd.printString(" ----------- ",0,3);
    lcd.printString("  Points +3 ",0,4);
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
    lcd.clear();
    lcd.printString(" ---Vader--- ",0,1);  
    lcd.printString("  Watermelon ",0,2);
    lcd.printString(" ----------- ",0,3);
    lcd.printString("  Points +5",0,4);
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
    lcd.clear();
    lcd.printString(" ----------- ",0,1);  
    lcd.printString("    Bomb   ",0,2);
    lcd.printString(" ----------- ",0,3);
    lcd.printString("   Lives -1 ",0,4);
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
    lcd.clear();
    lcd.printString(" ----------- ",0,1);  
    lcd.printString("  ! PRESS !  ",0,2);
    lcd.printString(" ----TO---- ",0,3);
    lcd.printString("  ! PLAY !   ",0,4);
    lcd.printString(" ----------- ",0,5); 
    lcd.refresh();
    ThisThread::sleep_for(2500ms);
}