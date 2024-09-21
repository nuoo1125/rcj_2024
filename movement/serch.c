if(silver == true){
  angle(-90);//serchの一番最初の角度
  while(ball_silver>0){
    camera_silver();
    if(car == found_car){
      angle_set();
      dis = infinity;
      while(dis<定数){
        tof();
        go_forward();
        sleep_ms(100);//必要かはわからない
      }
      ball_get();
      go_rescue();
      ball_throw();
      go_position();
    }
    else{
      angle(30);
    }
  }
  angle(-90);//serchの一番最初の角度
  while(ball_silver <= 0 && ball_black>0){
    camera_black();
    if(car == found_car){
      angle_set();
      dis = infinity;
      while(dis<定数){
        tof();
        go_forward();
        sleep_ms(100);//必要かはわからない
      }
      ball_get();
      go_rescue();
      ball_throw();
      go_position();
    }
    else{
      angle(30);
    }
  }
}
