struct object chaserObj = {0, 0, "X", true};
struct object chasedObj = {0, 0, "O", true};

void chaseLoop(){
  if(rotatedEncoder || pressedButton || change){
    if(chasedObj.flag == 1) drawRandomMovingObject(chasedObj);
    else if(chasedObj.flag == 0){
      drawRandomStaticObject(chasedObj);
      chasedObj.flag = 1;
    }

    drawPlayerObject(chaserObj);

    if(isCollision(chaserObj, chasedObj)) chasedObj.flag = 0;
  }
}