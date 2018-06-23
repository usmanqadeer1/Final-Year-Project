String check="";
String raw_message;
String message_again="";
String hex_to_ascii_string(String st);
int hex_to_ascii(char c, char d);
int hex_to_int(char c);
String getMessage(){
  
 
  while(Serial.available()>0){
    //detachInterrupt(2);
      sprintf(value,"%02X",Serial.read());
      if(x!=0 && value[0] == '7' && value[1] == 'E'){
        raw_message="7E";
        x=1;
        return raw_message;
      } 
      raw_message=raw_message+value;
      x++;
  }
  if(message_again!=raw_message)
  {
    message_again=raw_message;
 //   attachInterrupt(0, zero_crosss_int, RISING);
    return raw_message;
  }
  else{
 //   attachInterrupt(0, zero_crosss_int, RISING);
    return "";
  }
   
}

String getResultMessage(){
  
  String s=getMessage();
  if(s.length() > 30)
    {String message = s.substring(MESSAGE_START,s.length()-2);
    String result_message = hex_to_ascii_string(message);  


    return result_message;
    }
    else 
    return "";
}
  
String hex_to_ascii_string(String st){
  String result="";
  char character;
  int len = st.length();
  char buf = 0;
  for(int i = 0; i < len; i++){
      if(i % 2 != 0){
          character =(char) hex_to_ascii(buf, st[i]);
          result=result+character;
      }else{
           buf = st[i];
      }
   }
   return result;
}

int hex_to_ascii(char c, char d){
        int high = hex_to_int(c) * 16;
        int low = hex_to_int(d);
        return high+low;
}
int hex_to_int(char c){
        int first = c / 16 - 3;
        int second = c % 16;
        int result = first*10 + second;
        if(result > 9) result--;
        return result;
}
