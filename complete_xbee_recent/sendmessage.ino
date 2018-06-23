
void send_data(char address_64[], char msg[])
{
  unsigned char address_16[2] = {0xFF,0xFE};
  short len = 0x0E;
  char p1[3]={0},p2[3]={0},p3[3]={0},p4[3]={0},p5[3]={0},p6[3]={0},p7[3]={0},p8[3]={0};
  unsigned checksum = 0x10+0x01;
  
  for(byte i=0;i<2;i++)
  {
    p1[i]=address_64[i];
    p2[i]=address_64[i+2];
    p3[i]=address_64[i+4];
    p4[i]=address_64[i+6];
    p5[i]=address_64[i+8];
    p6[i]=address_64[i+10];
    p7[i]=address_64[i+12];
    p8[i]=address_64[i+14];
  }
  
  Serial.write(0x7E);

  len += strlen(msg);
  Serial.write((len&0xff00)>>8);
  Serial.write(len&0xff);
  
  Serial.write(0x10);
  Serial.write(0x01);

  checksum += strtol(p1,NULL,16);
  Serial.write(strtol(p1,NULL,16));
  checksum += strtol(p2,NULL,16);
  Serial.write(strtol(p2,NULL,16));
  checksum += strtol(p3,NULL,16);
  Serial.write(strtol(p3,NULL,16));
  checksum += strtol(p4,NULL,16);
  Serial.write(strtol(p4,NULL,16));
  checksum += strtol(p5,NULL,16);
  Serial.write(strtol(p5,NULL,16));
  checksum += strtol(p6,NULL,16);
  Serial.write(strtol(p6,NULL,16));
  checksum += strtol(p7,NULL,16);
  Serial.write(strtol(p7,NULL,16));
  checksum += strtol(p8,NULL,16);
  Serial.write(strtol(p8,NULL,16));
//  for(char i=0;i<8;i++)
//    Serial.write(address_64[i]);
  
  for(char i=0;i<2;i++)
  {
    Serial.write(address_16[i]);
    checksum += address_16[i];
  }
  
  Serial.write(byte(0x00)); //broadcast_radius = 0
  Serial.write(byte(0x00)); //options = 0

  for(int i=0;i<strlen(msg);i++)
  {
    Serial.write(msg[i]);
    checksum += msg[i];
  }

  checksum &= 0xff;
  checksum = 0xff - checksum;
  Serial.write(checksum);
}

