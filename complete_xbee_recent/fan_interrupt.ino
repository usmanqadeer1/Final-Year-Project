void zero_crosss_int()  // function to be fired at the zero crossing to dim the light
{

  interrupts();
  dimtime1 = (77*portvalue1);
  dimtime2 = (77*portvalue2);
 
  
   if(state[5]==HIGH && state[4]==LOW)
     {
        
        delayMicroseconds(dimtime2);
        digitalWrite(fan2, HIGH);
        delayMicroseconds(propTime);         
        digitalWrite(fan2, LOW);
       
     }
     
     if(state[5]==LOW && state[4]==HIGH)
     {
        
        delayMicroseconds(dimtime1);
        digitalWrite(fan1, HIGH);
        delayMicroseconds(propTime);         
        digitalWrite(fan1, LOW);
        
     }
     
     if(state[4]==HIGH && state[5]==HIGH)
     {
        if(dimtime1>dimtime2){
        
         delayMicroseconds(dimtime2);
         digitalWrite(fan2, HIGH);
         difference1=dimtime1-dimtime2;
         delayMicroseconds( difference1);
         digitalWrite(fan1, HIGH);
         delayMicroseconds(propTime);
         digitalWrite(fan2, LOW);
         digitalWrite(fan1, LOW);
                    
        }       
        if(dimtime2>dimtime1){
         delayMicroseconds(dimtime1);
         digitalWrite(fan1, HIGH);
         difference2=dimtime2-dimtime1;
         delayMicroseconds( difference2);
         digitalWrite(fan2, HIGH);
         delayMicroseconds(propTime);
         digitalWrite(fan1, LOW);
         digitalWrite(fan2, LOW);
                    
        }
        
         if(dimtime2==dimtime1){
         
         delayMicroseconds(dimtime1);
         digitalWrite(fan1, HIGH);
         digitalWrite(fan2, HIGH);
         delayMicroseconds(propTime);
         digitalWrite(fan1, LOW);
         digitalWrite(fan2, LOW); 
        }
                
     }

 
      
}
