void clearCustom(int col, int row, int len){
  oLcd.setCursor(col, row);
  for (int i = 0; i < len; i++) oLcd.print(" ");
}

void clearObj(struct object &obj){
  clearCustom(obj.x.value, obj.y.value, strlen(obj.text));
}

void updateObjectAxis(struct object &obj,  struct axis &ax, int move){
  int next = ax.value + move;

  if(obj.teleport){
    if(next < ax.min) ax.value = ax.max - 1;
    else ax.value = next % ax.max;
  }
  else{
    if(next >= ax.min && next < ax.max) ax.value = next;
  }
}

void updateObjectPosition(struct object &obj, int move_x, int move_y){
  if(move_x != 0) updateObjectAxis(obj, obj.x, move_x);
  if(move_y != 0) updateObjectAxis(obj, obj.y, move_y);
}

void drawStaticObject(struct object &obj){
  oLcd.setCursor(obj.x.value, obj.y.value);
  oLcd.print(obj.text);
}

void drawMovingObject(struct object &obj){
  clearObj(obj);

  updateObjectAxis(obj, obj.x, obj.flag);

  drawStaticObject(obj);
}

void drawRandomStaticObject(struct object &obj){
  clearObj(obj);

  obj.x.value = random(obj.x.min, obj.x.max);
  obj.y.value = random(obj.y.min, obj.y.max);

  drawStaticObject(obj);
}

void drawRandomMovingObject(struct object &obj){
  clearObj(obj);

  updateObjectPosition(obj, random(-1, 1), random(-1, 1));

  drawStaticObject(obj);
}

void drawPlayerObject(struct object &obj){
  clearObj(obj);

  if(rotatedEncoder){
    updateObjectAxis(obj, obj.x, direction);

    rotatedEncoder = false;
  }

  if(pressedButton){
    updateObjectAxis(obj, obj.y, 1);
    pressedButton = false;
  }

  if(change) change = false;

  drawStaticObject(obj);
}

bool isCollision(struct object &obj_a, struct object &obj_b){
  return obj_a.x.value == obj_b.x.value && obj_a.y.value == obj_b.y.value;
}