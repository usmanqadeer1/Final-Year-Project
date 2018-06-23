#include <EEPROM.h>

#define  fullOn    10
#define  fullOff   80
#define  FQ_50      1 // in case of 50Hz
#define  FQ_60      0 // in case of 50Hz


#define MESSAGE_START 30
//String frame[50];
char value[2];

int x=0;
float difference1;
float difference2;
float propTime = 10.0;

//String raw_message;

int switch1 = 8;         // the number of the input pin
int bulb1 = 11;

int switch2 = 9;         
int bulb2 = 12;

int switch3=10;
int bulb3=13;

int switch4=6;
int bulb4=7;


int fan2_switch=5;
int fan2=4;
int fan2_led=A5;

int fan1_switch=A0;
int fan1=3;
int fan1_led=A4;


int flag1,flag2;
int dimmer1=A2;
int dimmer2=A3;


int dimtime1 = 0;
int dimtime2 = 0;

int portvalue1=fullOff;
int portvalue2=fullOff;

int portvalue11=fullOff;
int portvalue21=fullOff;
int portvalue12=fullOff;
int portvalue22=fullOff;
int backUpVoltage;

int previous[6] = {LOW,LOW,LOW,LOW,LOW,LOW};// the previous reading from the input pin

int reading[6];
//int eeAddress=0;

int switches[6] = {switch1,switch2,switch3,switch4,fan1_switch,fan2_switch};
int state[6] = {LOW,LOW,LOW,LOW,LOW,LOW};//to be saved
  
String received;  
int leds[6] = {bulb1, bulb2, bulb3, bulb4, fan1_led, fan2_led};
String commands_off[6] = {"b10","b20","b30","b40","f1of","f2of"};
String commands_on[6]  = {"b11","b21","b31","b41","f1on","f2on"};

long times[6] ={0,0,0,0,0,0}; 
long timef1,timef2;
long debounce = 100;   // the debounce time, increase if the output flickers

void zero_crosss_int() ;
void hardware_set(void);
String getResultMessage();

String portvalue1_send;
String portvalue2_send;
char buf[15];
void setup()
{
  Serial.begin(9600);
  attachInterrupt(0, zero_crosss_int, RISING);
  
  pinMode(switch1, INPUT);
  pinMode(bulb1, OUTPUT);
  
  pinMode(switch2, INPUT);
  pinMode(bulb2, OUTPUT);
  
  pinMode(switch3, INPUT);
  pinMode(bulb3, OUTPUT);
  
  pinMode(switch4, INPUT);
  pinMode(bulb4, OUTPUT);
  
  
  pinMode(fan2_switch,INPUT);
  pinMode(fan2, OUTPUT);
  pinMode(fan2_led,OUTPUT); 
  
  pinMode(fan1_switch,INPUT);
  pinMode(fan1, OUTPUT); 
  pinMode(fan1_led,OUTPUT);
 
 
  pinMode(dimmer1, INPUT);
  pinMode(dimmer2, INPUT); 

  int eeAddress=0;
  for(int i=0;i<6;i++){
    state[i]=EEPROM.read(eeAddress);
    eeAddress+=sizeof(int);
  }
} 

void loop()
{
  for(int i=0;i<6;i++){
     reading[i] = digitalRead(switches[i]);
  }
  
  portvalue22=analogRead(dimmer2)/8;  
  portvalue12=analogRead(dimmer1)/8;
   if(abs(portvalue11-portvalue12)>=5){
          portvalue11=portvalue12;
          portvalue1=portvalue12;
          portvalue1=constrain(portvalue1,fullOn,fullOff);            
   }

   if(abs(portvalue21-portvalue22)>=5){
          portvalue21=portvalue22;
          portvalue2=portvalue22;
          portvalue2=constrain(portvalue2,fullOn,fullOff);       
   }
 
   backUpVoltage=analogRead(A1);
     backUp(); 
   if(backUpVoltage<1000){
   
    }
  hardware_set();
  xbee_state_change();
}

  
void xbee_state_change(){
  received=getResultMessage();
   String checkfan=received.substring(0,4);
  
          
   if(received.equals("b10")) {
     state[0]=LOW;
     received.toCharArray(buf,10);
     send_data("0013A20040F7BCC1",buf);
    
   }
   if(received.equals("b11")) {
     state[0]=HIGH;
     received.toCharArray(buf,10);
     send_data("0013A20040F7BCC1",buf);
   }
   if(received.equals("b20")){
     state[1]=LOW;
     received.toCharArray(buf,10);
     send_data("0013A20040F7BCC1",buf);
   }
   if(received.equals("b21") ){
     state[1]=HIGH;
     received.toCharArray(buf,10);
     send_data("0013A20040F7BCC1",buf);
   }  
   if(received.equals("b30")){
     state[2]=LOW;
     received.toCharArray(buf,10);
     send_data("0013A20040F7BCC1",buf);
   }
   if(received.equals("b31")){
     state[2]=HIGH;
     received.toCharArray(buf,10);
     send_data("0013A20040F7BCC1",buf);
   }
      
   if(received.equals("b40")){
     state[3]=LOW;
     received.toCharArray(buf,10);
     send_data("0013A20040F7BCC1",buf);
   }
  if(received.equals("b41")){
     state[3]=HIGH;
     received.toCharArray(buf,10);
     send_data("0013A20040F7BCC1",buf);
   }  

    if(received.equals("f1of")){
     state[4]=LOW;  
     received.toCharArray(buf,10);
     send_data("0013A20040F7BCC1",buf);
      
   }

   if(checkfan.equals("f1on")){
     state[4]=HIGH;
    
    String analogf1=received.substring(4,7);

    if(analogf1.length()==3){

     portvalue1=analogf1.toInt();
     portvalue1=constrain(portvalue1,fullOn,fullOff);
      
      }
     
    received.toCharArray(buf,10);
    send_data("0013A20040F7BCC1",buf);  
    
   }
     
   if(received.equals("f2of") ){
     state[5]=LOW;
     
     received.toCharArray(buf,10);
     send_data("0013A20040F7BCC1",buf);
   
   }
   if(checkfan.equals("f2on")){
     state[5]=HIGH; 
     received.toCharArray(buf,10);
     send_data("0013A20040F7BCC1",buf);
     String analogf2=received.substring(4,7);
     if(analogf2.length()==3){

       portvalue2=analogf2.toInt();
       portvalue2=constrain(portvalue2,fullOn,fullOff);
      }
       
}
  if(received.equals("check_status")){

    String a="";
    for(int i=0;i<6;i++){
      a = a + digitalRead(leds[i]);
      
    }
    a=a+"s"+portvalue1;
    a=a+"s"+portvalue2;
    a.toCharArray(buf,15);
    send_data("0013A20040F7BCC1",buf);
  }

  if(received.equals("onAll")){
    for(int i=0;i<6;i++){
      state[i]=HIGH;
    }
  }
  if(received.equals("offAll")){
    for(int i=0;i<6;i++){
       state[i]=LOW;
    }
  }
}


void backUp(){
  int eeAddress=0;
  for(int e=0;e<6;e++){
      EEPROM.update(eeAddress, state[e]);
      eeAddress+=sizeof(int); 
  }
}

