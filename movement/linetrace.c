//いったん日本語で書く
//割り込みを設定するやつ参考俺のタクトスイッチ
int main(){
  gpio_set_irq_enabled_with_callback(sw, GPIO_IRQ_EDGE_FALL, true, &sw_do);//sw_do関数を呼び出すみたいなやつ
  car_state car = carhold
  while(gin=false){
    checkline();
    if (green = true){
      // 車の状態を管理するやつをtypedef enumで実装するからよろ できた
      if(state=left)move_left();
      if(state=right)move_right();
      if(state=turn)move_turn();
  }
    else{
    linetrace();
    }
}
