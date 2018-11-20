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
#define BRIGHTNESS  255
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define DATA_PIN 1

CRGB leds[NUM_LEDS];

// GUItool: begin automatically generated code

AudioInputI2S            adc1;           //xy=606,191

AudioFilterBiquad    biquad1;           // Filtros A
AudioFilterBiquad    biquad2;
AudioFilterBiquad    biquad3;
AudioMixer4          mixer1;  
AudioAnalyzeRMS       peak1;          //xy=317,123
AudioAnalyzeFFT1024    myFFT;

AudioConnection c2(adc1, 1, biquad1, 0);
AudioConnection c4(biquad1, 0, biquad2, 0);
AudioConnection c5(biquad2, 0, biquad3, 0); 
AudioConnection c3(biquad3, 0, mixer1, 0);  

AudioConnection          patchCord1(mixer1, 0, peak1, 0);
AudioConnection          patchCord2(adc1,  1,myFFT, 0);







void setup() {

  double bi_one[5]={1,2,1,-0.140934181433268,0.00496561087406639};
  double bi_two[5]={1,-2,1,-1.88494521627714,0.88646428967279};
  double bi_three[5]={1,-2,1,-1.99414122228007,0.994149803599171};
  biquad1.setCoefficients(0, bi_one);
  biquad2.setCoefficients(0, bi_two);
  biquad3.setCoefficients(0, bi_three);
  mixer1.gain(0, 0.255637816298686);
  myFFT.windowFunction(AudioWindowHanning1024);
  AudioMemory(128);
  Serial.begin(57600);
       FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
      FastLED.setBrightness(BRIGHTNESS);


       

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

int n3_0[]={};
int n2_0[]={41,40,39,30,32,23,21,12,14,5,4,3};
int n1_0[]={38,37,36,33,35,20,18,15,17,2,1,0};

int n3_1[]={44,27,26,9,8};
int n2_1[]={30,40,31,22,13,4};
int n1_1[]={33,37,34,19,16,1};

int n3_2[]={44,43,42,29,26,25,24,9,8,7,6};
int n2_2[]={42,41,40,31,22,23,24,11,6,5,4};
int n1_2[]={38,37,36,35,20,19,18,15,2,1,0};

int n3_3[]={44,43,42,29,26,25,24,11,8,7,6};
int n2_3[]={42,41,40,31,22,23,24,13,6,5,4};
int n1_3[]={38,37,36,35,20,19,18,17,2,1,0};

int n3_4[]={44,43,42,27,28,29,26,25,24,9,10,11,8,7,6};
int n2_4[]={42,40,29,31,24,23,22,13,4};
int n1_4[]={38,36,33,35,20,19,18,17,0};

int n3_5[]={44,43,42,27,26,25,24,11,8,7,6};
int n2_5[]={42,41,40,29,24,23,22,13,4,5,6};
int n1_5[]={38,37,36,33,20,19,18,17,2,1,0};

int n3_6[]={44,43,42,27,26,25,24,9,11,8,7,6};
int n2_6[]={42,41,40,29,24,23,22,11,13,6,5,4};
int n1_6[]={38,37,36,33,20,19,18,15,17,2,1,0};

int n3_7[]={44,43,42,29,25,24,11,6};
int n2_7[]={42,41,40,31,23,22,13,4};
int n1_7[]={38,37,36,35,19,18,17,0};

int n3_8[]={44,43,42,27,29,26,25,24,9,11,8,7,6};
int n2_8[]={42,41,40,29,31,24,23,22,11,13,6,5,4};
int n1_8[]={38,37,36,33,35,20,19,18,15,17,2,1,0};

int n3_9[]={44,43,42,27,29,26,25,24,11,6};
int n2_9[]={42,41,40,29,31,24,23,22,13,4};
int n1_9[]={38,37,36,33,35,20,19,18,17,0};

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(20); } }



elapsedMillis fps;
elapsedMillis fps2;
double cal=0.7; 
double RMS=0;
double RMS_=0;
double pascales=0;
int dB=0;
int i=0;
int val2=2;

int uno [15];
int dos [15];
int tres [15];
int nada []={50,50,50,50,50,50,50,50,50,50,50,50,50,50,50};

int s_uno;
int s_dos;
int s_tres;
int x=-1;
void loop() {
static uint8_t hue = 0;
float n;
  int o;
  int ii=3;




if (peak1.available() && myFFT.available()) {
      
      RMS = peak1.read();   
      RMS=RMS*RMS;
      RMS_=RMS_+RMS;
      i++; 



Serial.print("FFT: ");
    for (o=0; o<9; o++) {
      
      ii=(pow(2,o)+ii);
     Serial.print(ii-1-(pow(2,o)-1));
        Serial.print("  ");

        Serial.print(ii-1);
        Serial.print("  ");


        
      n = myFFT.read((ii-1-(pow(2,o)-1)),(ii-1));
     //n=n/((ii-1)-(pow(2,o)-1));


        Serial.print(20*log10((n/cal)/0.00002));
        Serial.print("      ");


      
if (o==0){
  
if (20*log10((n/cal)/0.00002)>40){  
 
    leds[8] = CRGB(295, 193, 0);
}

else {
    leds[8] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>50){  
 
    leds[9] = CRGB(295, 193, 0);
}

else {
    leds[9] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>55){  
 
    leds[26] = CRGB(212, 232, 12);
}

else {
    leds[26] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>60){  
 
    leds[27] = CRGB(232, 109, 12);
}

else {
    leds[27] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>65){  
 
    leds[44] = CRGB(255, 0, 0);
}

else {
    leds[44] = CHSV(0, 0, 0);
}


}

if (o==1){
  
if (20*log10((n/cal)/0.00002)>40){  
 
    leds[7] = CRGB(295, 193, 0);
}

else {
    leds[7] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>50){  
 
    leds[10] = CRGB(295, 193, 0);
}

else {
    leds[10] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>55){  
 
    leds[25] = CRGB(212, 232, 12);
}

else {
    leds[25] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>60){  
 
    leds[28] = CRGB(232, 109, 12);
}

else {
    leds[28] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>65){  
 
    leds[43] = CRGB(255, 0, 0);
}

else {
    leds[43] = CHSV(0, 0, 0);
}


}

if (o==2){
  
if (20*log10((n/cal)/0.00002)>40){  
 
    leds[6] =CRGB(295, 193, 0);
}

else {
    leds[6] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>50){  
 
    leds[11] = CRGB(295, 193, 0);
}

else {
    leds[11] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>55){  
 
    leds[24] = CRGB(212, 232, 12);
}

else {
    leds[24] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>60){  
 
    leds[29] = CRGB(232, 109, 12);
}

else {
    leds[29] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>65){  
     
      
    leds[42] = CRGB(255, 0, 0);
}

else {
    leds[42] = CHSV(0, 0, 0);
}


}

if (o==3){
  
if (20*log10((n/cal)/0.00002)>40){  
 
    leds[5] =CRGB(295, 193, 0);
}

else {
    leds[5] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>50){  
 
    leds[12] = CRGB(295, 193, 0);
}

else {
    leds[12] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>55){  
 
    leds[23] = CRGB(212, 232, 12);
}

else {
    leds[23] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>60){  
 
    leds[30] = CRGB(232, 109, 12);
}

else {
    leds[30] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>65){  
 
    leds[41] = CRGB(255, 0, 0);
}

else {
    leds[41] = CHSV(0, 0, 0);
}


}

if (o==4){
  
if (20*log10((n/cal)/0.00002)>40){  
 
    leds[4] = CRGB(295, 193, 0);
}

else {
    leds[4] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>50){  
 
    leds[13] = CRGB(295, 193, 0);
}

else {
    leds[13] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>55){  
 
    leds[22] = CRGB(212, 232, 12);
}

else {
    leds[22] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>60){  
 
    leds[31] = CRGB(232, 109, 12);
}

else {
    leds[31] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>65){  
 
    leds[40] = CRGB(255, 0, 0);
}

else {
    leds[40] = CHSV(0, 0, 0);
}


}

if (o==5){
  
if (20*log10((n/cal)/0.00002)>40){  
 
    leds[3] = CRGB(295, 193, 0);
}

else {
    leds[3] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>50){  
 
    leds[14] = CRGB(295, 193, 0);
}

else {
    leds[14] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>55){  
 
    leds[21] = CRGB(212, 232, 12);
}

else {
    leds[21] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>60){  
 
    leds[32] = CRGB(232, 109, 12);
}

else {
    leds[32] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>65){  
      hue++;
      hue++;
      hue++;
    leds[39] = CRGB(255, 0, 0);
}

else {
    leds[39] = CHSV(0, 0, 0);
}


}

if (o==6){
  
if (20*log10((n/cal)/0.00002)>40){  
 
    leds[2] =CRGB(295, 193, 0);
}

else {
    leds[2] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>50){  
 
    leds[15] = CRGB(295, 193, 0);
}

else {
    leds[15] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>55){  
 
    leds[20] = CRGB(212, 232, 12);
}

else {
    leds[20] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>60){  
 
    leds[33] = CRGB(232, 109, 12);
}

else {
    leds[33] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>65){  
 
    leds[38] = CRGB(255, 0, 0);
}

else {
    leds[38] = CHSV(0, 0, 0);
}


}

if (o==7){
  
if (20*log10((n/cal)/0.00002)>40){  
 
    leds[1] = CRGB(295, 193, 0);
}

else {
    leds[1] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>50){  
 
    leds[16] = CRGB(295, 193, 0);
}

else {
    leds[16] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>55){  
 
    leds[19] = CRGB(212, 232, 12);
}

else {
    leds[19] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>60){  
 
    leds[34] = CRGB(232, 109, 12);
}

else {
    leds[34] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>65){  
 
    leds[37] = CRGB(255, 0, 0);
}

else {
    leds[37] = CHSV(0, 0, 0);
}


}

if (o==8){
  
if (20*log10((n/cal)/0.00002)>40){  
 
    leds[0] = CRGB(295, 193, 0);
}

else {
    leds[0] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>50){  
 
    leds[17] = CRGB(295, 193, 0);
}

else {
    leds[17] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>55){  
 
    leds[18] = CRGB(212, 232, 12);
}

else {
    leds[18] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>60){  
 
    leds[35] = CRGB(232, 109, 12);
}

else {
    leds[35] = CHSV(0, 0, 0);
}

if (20*log10((n/cal)/0.00002)>65){  
 
    leds[36] = CRGB(255, 0, 0);
}

else {
    leds[36] = CHSV(0, 0, 0);
}


}



    }
    Serial.println();



}
  
  if (fps > 100) {
    fps=0;
    RMS_=RMS_/i;
    RMS_=sqrt(RMS_);
    pascales=RMS_/cal;
dB=20*log10(pascales/0.00002);
     
FastLED.setBrightness(((dB-15)*255)/83 );





//
//
//if (dB>40){  
//  for(int i=0; i < 9; i++){
//    leds[f1[i]] = CRGB(58, 255, 0);
//    }
//}
//
//else {
//  for(int i=0; i < 9; i++){
//    leds[f1[i]] = CHSV(0, 0, 0);
//  }    
//}
//
//
//
//if (dB>55){  
//  for(int i=0; i < 9; i++){
//    leds[f2[i]] = CRGB(163, 246, 0);
//    }
//}
//
//else {
//  for(int i=0; i < 9; i++){
//    leds[f2[i]] = CHSV(0, 0, 0);
//  }    
//}
//
//  
//
//if (dB>60){  
//  for(int i=0; i < 9; i++){
//    leds[f3[i]] = CRGB(238, 215, 0);
//    }
//}
//
//else {
//  for(int i=0; i < 9; i++){
//    leds[f3[i]] = CHSV(0, 0, 0);
//  }    
//}
//
//
//
//if (dB>65){  
//  for(int i=0; i < 9; i++){
//    leds[f4[i]] = CRGB(230,109,0);
//    }
//}
//
//else {
//
//  for(int i=0; i < 9; i++){
//    leds[f4[i]] = CHSV(0, 0, 0);
//  }    
//}
//
//
//
//if (dB>70){  
//  for(int i=0; i < 9; i++){
//    leds[f5[i]] = CRGB(255, 0, 0);
//    }
//}
//
//else {
//
//  for(int i=0; i < 9; i++){
//  
//    leds[f5[i]] = CHSV(222, 9, 2);
//  }    
//}

FastLED.show();  







if (fps2>8000){



int x = (dB / 1U) % 10;   



int y = (dB / 10U) % 10;

int z = (dB / 100U) % 10;
memcpy(uno, nada,15*sizeof(int));
memcpy(dos, nada,15*sizeof(int));
memcpy(tres, nada,15*sizeof(int));


if (x==0){
  
memcpy(uno, n1_0, sizeof(n1_0));
 
}

if (x==1){

memcpy(uno, n1_1, sizeof(n1_1));
}
if (x==2){
  
memcpy(uno, n1_2, sizeof(n1_2));
}
if (x==3){
 
memcpy(uno, n1_3, sizeof(n1_3));
}
if (x==4){
 
memcpy(uno, n1_4, sizeof(n1_4));
}
if (x==5){

memcpy(uno, n1_5, sizeof(n1_5));
}
if (x==6){

memcpy(uno, n1_6, sizeof(n1_6));
}
if (x==7){

memcpy(uno, n1_7, sizeof(n1_7));
}
if (x==8){

memcpy(uno, n1_8, sizeof(n1_8));
}
if (x==9){

memcpy(uno, n1_9, sizeof(n1_9));
}


if (y==0){
 
memcpy(dos, n2_0, sizeof(n2_0));
}
if (y==1){
  
memcpy(dos, n2_1, sizeof(n2_1));
}
if (y==2){
 
memcpy(dos, n2_2, sizeof(n2_2));
}
if (y==3){

memcpy(dos, n2_3, sizeof(n2_3));
}
if (y==4){

memcpy(dos, n2_4, sizeof(n2_4));
}
if (y==5){

memcpy(dos, n2_5, sizeof(n2_5));

}
if (y==6){

memcpy(dos, n2_6, sizeof(n2_6));
}
if (y==7){

memcpy(dos, n2_7, sizeof(n2_7));
}
if (y==8){

memcpy(dos, n2_8, sizeof(n2_8));
}
if (y==9){

memcpy(dos, n2_9, sizeof(n2_9));
}



if (z==0){

memcpy(tres, n3_0, sizeof(n3_0));
}
if (z==1){
 
memcpy(tres, n3_1, sizeof(n3_1));
}
if (z==2){
 
memcpy(tres, n3_2, sizeof(n3_2));
}
if (z==3){
 
memcpy(tres, n3_3, sizeof(n3_3));
}
if (z==4){

memcpy(tres, n3_4, sizeof(n3_4));
}
if (z==5){
 
memcpy(tres, n3_5, sizeof(n3_5));

}
if (z==6){

memcpy(tres, n3_6, sizeof(n3_6));
}
if (z==7){

memcpy(tres, n3_7, sizeof(n3_7));
}
if (z==8){

memcpy(tres, n3_8, sizeof(n3_8));
}
if (z==9){

memcpy(tres, n3_9, sizeof(n3_9));
}


fadeall();
FastLED.show(); 
//for(int i=0; i < 49; i++){
//    leds[i] = CHSV(0, 0, 0);
//    
//FastLED.show(); 
//}

s_tres=(sizeof(dos)/sizeof(int));

for(int i=0; i < s_tres; i++){
    leds[tres[i]] = CHSV(hue++, 255, 255);
delay(20);
 FastLED.show();   
}

s_dos=(sizeof(dos)/sizeof(int));

for(int i=0; i < s_dos; i++){
    leds[dos[i]] = CHSV(hue++, 255, 255);
delay(20);
 FastLED.show();   
}



s_uno=(sizeof(uno)/sizeof(int));

for(int i=0; i < s_uno; i++){
    leds[uno[i]] = CHSV(hue++, 255, 255);
    delay(20);
FastLED.show();   

}

delay(750);
fps2=0;
}


















      
      i=0;
      RMS=0;
      RMS_=0;
  }






  
}
