#include <string.h>

#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04

Dynamixel Dxl(DXL_BUS_SERIAL1);
char strRemain[2000] = "";
const int numJoint = 16;
const int numData = numJoint*2;

void setup(){
  pinMode(BOARD_LED_PIN, OUTPUT);
  Dxl.begin(3);
  for(int i = 1; i<17 ; i++)
  {
    Dxl.goalSpeed(i, 1023);
    Dxl.jointMode(i);
  }
  SerialUSB.attachInterrupt(usbInterrupt);
  for(int i = 1; i<17 ; i++)
  {
    Dxl.goalPosition(i, 512);
  }
}

void usbInterrupt(byte* buffer, byte nCount){  
  char strBuffer[2000] = "";
  strncpy(strBuffer, (char*)buffer, nCount);
  //SerialUSB.print("buffer : ");
  //SerialUSB.println(strBuffer);
  char strSum[2000] = "";
  strncpy(strSum, strRemain, sizeof(strSum));
  strcat(strSum, strBuffer);
  
  boolean bSearch = true;
  
  while(bSearch)
  {
    char* chsSchr = strchr(strSum,'s');
    char* cheSchr = strchr(strSum,'e');
    if(chsSchr>=strSum && cheSchr>=strSum)
    {
      int sIndex = (int)(chsSchr)-(int)(strSum);
      int eIndex = (int)(cheSchr)-(int)(strSum);
      
      if (eIndex-sIndex-1 == numData)
      {
        char strMatch[numData+1] = "";
        boolean isOver199 = true;
        for(int i=0;i<numData;i++)
        {
          strMatch[i] = strSum[sIndex+1+i];
          isOver199 = isOver199 && (int)strMatch[i]>199;
        } 
        //SerialUSB.print("Mathed String :: ");
        //SerialUSB.println(strMatch);
         
        if(isOver199) {
          //SerialUSB.println("good");
          for (int i=0;i<numJoint;i++)
          {
            int high = ((int)strMatch[i*2]-200);
            int low = ((int)strMatch[i*2+1]-200);
            int jointAngle = high*32+low;
            Dxl.goalPosition(i+1, jointAngle);
            //SerialUSB.print("Joint ");
            //SerialUSB.print(i+1);
            //SerialUSB.print(" :: ");
            //SerialUSB.println(jointAngle);
          }
         digitalWrite(BOARD_LED_PIN, HIGH); // set to as HIGH LED is turn-off
          delay(50);          // Wait for 0.1 second
          digitalWrite(BOARD_LED_PIN, LOW);  // set to as LOW LED is turn-on
          delay(50);          // Wait for 0.1 second   
        }
      }
      
      char tmpStr[2000] = "";
      strncpy(tmpStr, strSum,sizeof(tmpStr));
      
      strSum = {};
      for(int i=0;i<strlen(tmpStr)-eIndex-1;i++)
      {
        strSum[i] = tmpStr[i+eIndex+1];
      }      
    }
    else bSearch = false;
  }
  strRemain = {};
  strncpy(strRemain, strSum, sizeof(strRemain));
  //SerialUSB.print("remain strings :: ");
  //SerialUSB.println(strRemain);
  
//  char tmpChar[nCount-2]; 
//  for(int i= 0; i<nCount; i++)
//  {
//    unsigned int moveit = buffer[i]*4;
//    if(moveit>1023) moveit = 1023;
//    Dxl.goalPosition(ID_NUM, moveit);
//    break;
//  }
}

void loop(){
}


