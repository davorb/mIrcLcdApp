/*
  USBLCD project. 
  (c) 2009 Davor Babic <davorATdavor.se>
*/
#include <LiquidCrystal.h>
#include <string.h>

#define CLEARTIME  500
#define STARTUPBANNERTIME  1000

#include "WProgram.h"
void setup();
void clr();
void clr(int delayTime);
void loop();
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
char text[255];
int size=0;
char oldText[255];
int textPointer;
char timeOutText[255];
long timeoutCounter;

void setup() {
  
  /* Setup timeouttext */
    char textRow0[21];
  char textRow1[21];
  char textRow2[21];
  char textRow3[21];
  textRow0[20]='\0';
  textRow1[20]='\0';
  textRow2[20]='\0';
  textRow3[20]='\0';

  /////////////0
  textRow0[0]=255;
  textRow0[1]=255;
  textRow0[2]=' ';
  textRow0[3]=' ';
  textRow0[4]=' ';
  textRow0[5]=255;
  textRow0[6]=' ';
  textRow0[7]=' ';
  textRow0[8]=255;
  textRow0[9]=' ';
  textRow0[10]=255;
  textRow0[11]=' ';
  textRow0[12]=' ';
  textRow0[13]=255;
  textRow0[14]=255;
  textRow0[15]=' ';
  textRow0[16]=' ';
  textRow0[17]=255;
  textRow0[18]=255;
  textRow0[19]=' ';
  /////////////
  
  /////////////1
  textRow1[0]=255;
  textRow1[1]=' ';
  textRow1[2]=255;
  textRow1[3]=' ';
  textRow1[4]=255;
  textRow1[5]=' ';
  textRow1[6]=255;
  textRow1[7]=' ';
  textRow1[8]=255;
  textRow1[9]=' ';
  textRow1[10]=255;
  textRow1[11]=' ';
  textRow1[12]=255;
  textRow1[13]=' ';
  textRow1[14]=' ';
  textRow1[15]=255;
  textRow1[16]=' ';
  textRow1[17]=255;
  textRow1[18]=' ';
  textRow1[19]=255;
  /////////////

  /////////////2
  textRow2[0]=255;
  textRow2[1]=' ';
  textRow2[2]=255;
  textRow2[3]=' ';
  textRow2[4]=255;
  textRow2[5]=255;
  textRow2[6]=255;
  textRow2[7]=' ';
  textRow2[8]=255;
  textRow2[9]=' ';
  textRow2[10]=255;
  textRow2[11]=' ';
  textRow2[12]=255;
  textRow2[13]=' ';
  textRow2[14]=' ';
  textRow2[15]=255;
  textRow2[16]=' ';
  textRow2[17]=255;
  textRow2[18]=255;
  textRow2[19]=' ';
  /////////////
  
  /////////////3
  textRow3[0]=255;
  textRow3[1]=255;
  textRow3[2]=' ';
  textRow3[3]=' ';
  textRow3[4]=255;
  textRow3[5]=' ';
  textRow3[6]=255;
  textRow3[7]=' ';
  textRow3[8]=' ';
  textRow3[9]=255;
  textRow3[10]=' ';
  textRow3[11]=' ';
  textRow3[12]=' ';
  textRow3[13]=255;
  textRow3[14]=255;
  textRow3[15]=' ';
  textRow3[16]=' ';
  textRow3[17]=255;
  textRow3[18]=' ';
  textRow3[19]=255;
  /////////////
  
  timeOutText[0]='\0';
  strcat(timeOutText, textRow0);
  strcat(timeOutText, textRow2);
  strcat(timeOutText, textRow1);
  strcat(timeOutText, textRow3);
  /* End setup timeouttext */
  
  
  // 1: 0,0
  // 2: 0,1
  // 3: 0,2
  // 4: 0,3
  // must have delay after clear. around 20ms.  
  lcd.begin(4, 20);
  lcd.clear();
  Serial.begin(9600);
  
  clr(STARTUPBANNERTIME);
}

void clr() {
  clr(CLEARTIME);
}

void clr(int delayTime) {
  lcd.clear();
  delay(20);
  lcd.print(timeOutText);
  delay(delayTime);  
  //lcd.print(".");
  //delay(1000);
}

void loop() {
  while(Serial.available() > 0 && size<10) {
    char tmp[2];
    tmp[1]='\0';
    tmp[0]=Serial.read();
    if(tmp[0] != ']') {
      //strcat(text, tmp);
      text[textPointer]=tmp[0];
      textPointer++;
    } else {
      Serial.read();
      Serial.read();
      text[0]='\0';
      textPointer=0;
      for (int i=1; i < 255; i++) {
        text[i]=' ';
      }
      clr();
    }
  }
  char textRow0[21];
  char textRow1[21];
  char textRow2[21];
  char textRow3[225];
  
  for (int i=0; i<20; i++) {
    textRow0[i]=' ';
    textRow1[i]=' ';
    textRow2[i]=' ';
    textRow3[i]=' ';
  }
  
  for(int i=0; i<20; i++){
    textRow0[i]=text[i];
    textRow1[i]=text[i+20];
    textRow2[i]=text[i+40];
    textRow3[i]=text[i+60];
  }
  textRow0[20]='\0';
  textRow1[20]='\0';
  textRow2[20]='\0';
  textRow3[20]='\0';
  
  textRow3[19]='.';
  
  char outText[255];
  outText[0]='\0';
  strcat(outText, textRow0);
  strcat(outText, textRow2);
  strcat(outText, textRow1);
  strcat(outText, textRow3);
  //strcat(outText, ".");
  
  if (strcmp(oldText, outText) != 0) {
    lcd.clear();
    delay(20);
    lcd.print(outText);
    delay(20);
  
    strcpy(oldText, outText);
    timeoutCounter = 0;
  }
  delay(500);
  timeoutCounter++;
  
  if (timeoutCounter == 5400) { // 5400=45min
    lcd.clear();
    delay(20);
    
    /* The line below this comment displays
     * the banner and turns on the light. If
     * it is crossed out, the LCD will turn
     * itself off until another message is
     * received.
     */
    //lcd.print(timeOutText);
    delay(20);
  }
}


int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

