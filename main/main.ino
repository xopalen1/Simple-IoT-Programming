#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

int lcdWidth = 16, lcdHeight = 2;

LiquidCrystal_I2C oLcd(0x3F, lcdWidth, lcdHeight);

#define CLK 35
#define DT 27
#define BTN 25

struct axis{
  int value,
      min, max;

  axis(int v, int mi, int ma) : value(v), min(mi), max(ma) {}
};

struct object{
  struct axis x, y;

  const char* text;

  bool teleport;
  int flag;

  object(int x_val, int y_val,
         const char* txt,
         bool tp = false, int flg = 0):
      x(x_val, 0, lcdWidth),
      y(y_val, 0, lcdHeight),
      text(txt),
      teleport(tp),
      flag(flg)
      {}
};

/*Define your [game]TitleObj here ↓↓↓*/
struct object rocketTitleObj = {5, 1, "Rocket"};
struct object chaseTitleObj = {5, 1, "Chase"};
/*Define your [game]TitleObj here ↑↑↑*/

/*!!!MAKE SURE THAT YOU HAVE THE SAME INDEX IN chooseOpt and Game IN THE NEXT TWO STEPS!!!*/

struct object chooseOpt[] = {rocketTitleObj, chaseTitleObj}; /*<-- Add your [game]TitleObj here*/
enum Game {GAME_ROCKET, GAME_CHASE, GAME_COUNT}; /*<-- Add your GAME_[GAME] here !!!GAME_COUNT must be last!!!*/

/*!!!MAKE SURE THAT YOU HAVE THE SAME INDEX IN chooseOpt and Game IN THE PREVIOUS TWO STEPS!!!*/

Game currGame = GAME_COUNT;

/*Add your main [game]Loop here ↓↓↓*/
void switchGameLoop(){
  switch(currGame){
    case GAME_ROCKET: rocketLoop(); break;
    case GAME_CHASE: chaseLoop(); break;
  }
}
/*Add your main [game]Loop here ↑↑↑*/

/*You are all set :)*/

/*You can ignore the rest*/

volatile int direction = 0;  
volatile bool rotatedEncoder = false;
int lastStateCLK;

unsigned long lastButtonPress = 0;
const unsigned long buttonHeld = 1000;
const unsigned long debounceDelay = 150;
bool holdingButton = false;
bool pressedButton = false;

bool change = true;
int currOpt = 0;

enum State {STATE_STATS, STATE_GAMING, STATE_CHOOSE, STATE_PAUSED, STATE_COUNT};
State currState = STATE_CHOOSE;

void IRAM_ATTR handleEncoder() {
  int stateCLK = digitalRead(CLK);
  if(stateCLK != lastStateCLK && stateCLK == HIGH) {
    if(digitalRead(DT) != stateCLK) direction = -1; // CCW
    else direction = 1; // CW
    rotatedEncoder = true;
  }
  lastStateCLK = stateCLK;
}

void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(BTN, INPUT_PULLUP);

  lastStateCLK = digitalRead(CLK);

  attachInterrupt(digitalPinToInterrupt(CLK), handleEncoder, CHANGE);

  oLcd.init();
  oLcd.backlight();
}

void loop() {
  if(digitalRead(BTN) == LOW && millis() - lastButtonPress > debounceDelay) {
    lastButtonPress = millis();

    while(digitalRead(BTN) == LOW){
      if(!holdingButton && millis() - lastButtonPress > buttonHeld){
        pausedSetup();
        holdingButton = true;
      }
    }

    if(!holdingButton) pressedButton = true;
    holdingButton = false;
    lastButtonPress = millis();
  }

  switchLoop();
}
