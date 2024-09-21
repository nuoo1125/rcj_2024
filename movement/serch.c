while(gin>0 && black>0){
  if(gin>0){
    angle();
    camera();
    if(found_gin==true){
        catch();
        go_rescue();
    }
    else(){
      angle();
    }
  }
}
