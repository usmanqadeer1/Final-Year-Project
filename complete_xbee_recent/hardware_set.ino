void hardware_set(void){

 for(int i=0;i<6;i++){
  if ((reading[i] == HIGH) && ((previous[i]) == LOW) && (millis() - (times[i])) > debounce) {
    if (state[i] == HIGH){
      state[i] = LOW;
      commands_off[i].toCharArray(buf,10);
      send_data("0013A20040F7BCC1",buf);  
    }
      
    else{
      state[i] = HIGH;
     commands_on[i].toCharArray(buf,10);
     send_data("0013A20040F7BCC1",buf);  
    }
      

    times[i] = millis();    
  }

  digitalWrite(leds[i], state[i]);
  previous[i] = reading[i];
}



}
