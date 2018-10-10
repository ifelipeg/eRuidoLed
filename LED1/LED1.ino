/* Mono Peak Meter

   Scrolling peak audio level meter in the Arduino Serial Monitor

   Audio input needs to connect to pin 16 (A2).  The signal range is 0 to 1.2V.
   See the documentation in the Audio System Design Tool for the recommended
   circuit to connect an analog signal.

   This example code is in the public domain
*/
#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>
#define NUM_LEDS 60
#define DATA_PIN 1
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define DATA_PIN 1

CRGB leds[NUM_LEDS];

// GUItool: begin automatically generated code
AudioInputI2S            adc1;           //xy=164,95
AudioAnalyzeRMS         peak1;          //xy=317,123
AudioConnection          patchCord1(adc1,1, peak1,0);
// GUItool: end automatically generated code


void setup() {
  
  AudioMemory(4);
  Serial.begin(57600);
  LEDS.addLeds<WS2812SERIAL,DATA_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(10);
}

// for best effect make your terminal/monitor a minimum of 31 chars wide and as high as you can.
int f1[9]={8, 7, 6, 5, 4, 3, 2, 1, 0};
int f2[9]={9, 10, 11,  12,  13,  14 , 15,  16 , 17 };
int f3[9]={ 26,  25 , 24 , 23 , 22 , 21 , 20,19 , 18};
int f4[9]={27, 28, 29 , 30, 31,  32,  33,  34,35};
int f5[9]={44,  43, 42,  41,40,39,38,37,  36};
int f6[9]={45, 46, 47, 48, 49, 50, 51,  52,  53};



int n3_[]={44,43,42,27,28,29,26,25,24,9,10,11,8,7,6};
int n2_[]={41,40,39,30,31,32,23,22,21,12,13,14,5,4,3};
int n1_[]={38,37,36,33,34,35,20,19,18,15,16,17,2,1,0};

int n3_0[]={44,43,42,27,29,26,24,9,11,8,7,6};
int n2_0[]={41,40,39,30,32,23,21,12,14,5,4,3};
int n1_0[]={38,37,36,33,35,20,18,15,17,2,1,0};

int n3_1[]={43,42,29,24,11,6};
int n2_1[]={40,39,32,21,14,3};
int n1_1[]={37,36,35,18,17,0};

int n3_2[]={44,43,42,29,26,25,24,9,8,7,6};
int n2_2[]={41,40,39,32,23,22,21,12,5,4,3};
int n1_2[]={38,37,36,35,20,19,18,15,2,1,0};

int n3_3[]={44,43,42,29,26,25,24,11,8,7,6};
int n2_3[]={41,40,39,32,23,22,21,14,5,4,3};
int n1_3[]={38,37,36,35,20,19,18,17,2,1,0};

int n3_4[]={44,43,42,27,28,29,26,25,24,9,10,11,8,7,6};
int n2_4[]={41,39,30,32,23,22,21,14,3};
int n1_4[]={38,36,33,35,20,19,18,17,0};

int n3_5[]={44,43,42,27,26,25,24,11,8,7,6};
int n2_5[]={41,40,39,30,23,22,21,14,5,4,3};
int n1_5[]={38,37,36,33,20,19,18,17,2,1,0};

int n3_6[]={44,43,42,27,26,25,24,9,11,8,7,6};
int n2_6[]={41,40,39,30,23,22,21,12,14,5,4,3};
int n1_6[]={38,37,36,33,20,19,18,15,17,2,1,0};

int n3_7[]={44,43,42,29,25,24,11,6};
int n2_7[]={41,40,39,32,22,21,14,3};
int n1_7[]={38,37,36,35,19,18,17,0};

int n3_8[]={44,43,42,27,29,26,25,24,9,11,8,7,6};
int n2_8[]={41,40,39,30,32,23,22,21,12,14,5,4,3};
int n1_8[]={38,37,36,33,35,20,19,18,15,17,2,1,0};

int n3_9[]={44,43,42,27,29,26,25,24,11,6};
int n2_9[]={41,40,39,30,32,23,22,21,14,3};
int n1_9[]={38,37,36,33,35,20,19,18,17,0};

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(150); } }



elapsedMillis fps;
double cal=0.08; 
double RMS=0;
double RMS_=0;
double pascales=0;
int i=0;
int val2=2;
int uno[45];
int dos[45];
int tres[45];
int s_uno;
int s_dos;
int s_tres;
void loop() {

if (peak1.available()) {
      
      RMS = peak1.read();   
      RMS=RMS*RMS;
      RMS_=RMS_+RMS;
      i++;      
    }
  
  if (fps > 100) {
    fps=0;
    RMS_=RMS_/i;
    RMS_=sqrt(RMS_);
    pascales=RMS_/cal;
    
      Serial.print(20*log10(pascales/0.00002));
      
      Serial.println();

      
int x = (val2/ 1U) % 10;
unsigned y = (val2 / 10U) % 10;
unsigned z = (val2 / 100U) % 10;
char buf [64]; 
sprintf (buf, "The voltage is currently %3d volts DC\r\n", x);


if (x==0){
  uno=n1_0;
}
if (x==1){
  uno=n1_1;
}
if (x==2){
  uno=n1_2;
}
if (x==3){
  uno=n1_3;
}
if (x==4){
  uno=n1_4;
}
if (x==5){
  uno=n1_5;
}
if (x==6){
  uno=n1_6;
}
if (x==7){
  uno=n1_7;
}
if (x==8){
  uno=n1_8;
}
if (x==9){
  uno=n1_9;
}

if (y==0){
  dos=n2_0;
}
if (y==1){
  dos=n2_1;
}
if (y==2){
  dos=n2_2;
}
if (y==3){
  dos=n2_3;
}
if (y==4){
  dos=n2_4;
}
if (y==5){
  dos=n2_5;
}
if (y==6){
  dos=n2_6;
}
if (y==7){
  dos=n2_7;
}
if (y==8){
  dos=n2_8;
}
if (y==9){
  dos=n2_9;
}

if (z==0){
  tres=n3_0;
}
if (z==1){
  tres=n3_1;
}
if (z==2){
  tres=n3_2;
}
if (z==3){
  tres=n3_3;
}
if (z==4){
  tres=n3_4;
}
if (z==5){
  tres=n3_5;
}
if (z==6){
  tres=n3_6;
}
if (z==7){
  tres=n3_7;
}
if (z==8){
  tres=n3_8;
}
if (z==9){
  tres=n3_9;
}

s_uno=(sizeof(uno)/sizeof(int));

for(int i=0; i < s_uno; i++){
    leds[n3_1[i]] = CHSV(hue++, 255, 255);
    FastLED.show();    
  delay(20);
}

s_dos=(sizeof(dos)/sizeof(int));

for(int i=0; i < s_dos; i++){
    leds[n3_1[i]] = CHSV(hue++, 255, 255);
    FastLED.show();    
  delay(20);
}

s_tres=(sizeof(tres)/sizeof(int));

for(int i=0; i < s_tres; i++){
    leds[n3_1[i]] = CHSV(hue++, 255, 255);
    FastLED.show();    
  delay(20);
}


  
  delay(500);
  fadeall();
  FastLED.show();



















      
      i=0;
      RMS=0;
      RMS_=0;
  }






  
}
