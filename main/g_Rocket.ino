struct object rocketObj = {0, 0, "3=>", true};

void rocketLoop(){
  if(rotatedEncoder || pressedButton || change) drawPlayerObject(rocketObj);
}