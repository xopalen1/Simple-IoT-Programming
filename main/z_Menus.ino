struct object chooseObj = {2, 0, "Choose Game"};

void chooseLoop(){
  if(change){
    oLcd.clear();
    drawStaticObject(chooseObj);
    change = false;
  }

  if(rotatedEncoder){
    clearObj(chooseOpt[currOpt]);
    currOpt = (currOpt + direction + GAME_COUNT) % GAME_COUNT;
    drawStaticObject(chooseOpt[currOpt]);
    rotatedEncoder = false;
  }

  if(pressedButton){
    switchMenu();
    currState = STATE_GAMING;
    oLcd.clear();
  }
}

struct object pausedObj = {5, 0, "PAUSED"};
struct object statsObj = {5, 1, "Stats"};
struct object continueObj = {4, 1, "Continue"};
struct object exitObj = {6, 1, "Exit"};

struct object pausedOpt[3] = {statsObj, continueObj, exitObj};

void pausedSetup(){
  if(currState != STATE_GAMING) return;
  oLcd.clear();
  drawStaticObject(pausedObj);
  currState = STATE_PAUSED;
}

void pausedLoop(){
  if(rotatedEncoder){
    clearObj(pausedOpt[currOpt]);
    currOpt = (currOpt + direction + (STATE_COUNT - 1)) % (STATE_COUNT - 1);
    drawStaticObject(pausedOpt[currOpt]);
    rotatedEncoder = false;
  }

  if(pressedButton){
    switchMenu();
    oLcd.clear();
  }
}