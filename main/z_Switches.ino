void switchLoop(){
  switch(currState){
    case STATE_CHOOSE: chooseLoop(); break;
    case STATE_PAUSED: pausedLoop(); break;
    case STATE_GAMING: switchGameLoop(); break;
  }
}

void switchState(){
  currState = (State)currOpt;
}

void switchGame(){
  currGame = (Game)currOpt;
}

void switchMenu(){
  switch(currState){
    case STATE_STATS: break;
    case STATE_GAMING: break;
    case STATE_CHOOSE: switchGame(); break;
    case STATE_PAUSED: switchState(); break;
  }

  currOpt = 0;
  pressedButton = false;
  change = true;
}