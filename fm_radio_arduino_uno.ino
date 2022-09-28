#include <Wire.h> // this lets you use I2C
#include <TEA5767Radio.h>// radio chip
#include <TM1637Display.h>//7segment display
//******global*****
double station= 104.3; //the radio station the unit is tuned into
double fm_max=108.0;//the last fm station
double fm_min=88.0;// the fist fm station

//******7segment display*****
#define CLK 2//clock pin
#define DIO 3//data pin
TM1637Display display(CLK, DIO);//setting the clock and data pins to the display

//******TEA5767******
TEA5767Radio radio = TEA5767Radio();// able to call it as radio

//******rotary encoder*****
int encoderA=8;//pin conected to encoder
int encoderB=9;//pin conected to encoder
int Alast;// the last state of the encoder
int Anow;// the curent state of the encoder




void setup() {
  Wire.begin();//able to use I2C for the radio which are pins 18 & 19 marked SDA & SCL 
  Serial.begin(9600);
  display.setBrightness(0x02);//setting the brightness of the display
  display.showNumberDec(station*10, false);//display the station number. need to add *10 to display whole number
  radio.setFrequency(station);//setting the radio stataion

  pinMode(encoderA,INPUT);//able to read data from encoder
  pinMode(encoderB,INPUT);//able to read data from encoder
  digitalWrite(encoderA,HIGH);//needs to be set high 
  digitalWrite(encoderB,HIGH);//needs to be set high
  Serial.begin(9600);
  Alast=digitalRead(encoderA);//sets Alast to the current state
}

void loop() {
  Anow= digitalRead(encoderA);//reads in the curent state of pin a
  if((Alast==HIGH)&&(Anow==LOW)){//while it twist it pulls encoderA low & when it stop twisting it will stay high
    if(digitalRead(encoderB) == LOW){//will be LOW while it is twisting to the left  
      station-=.1;//subtract .1
    }
    else{//if incoderB is HIGH that it is twisting to the right
      station+=.1;  
    }
    Serial.println(station);//prints the curent value
    radio.setFrequency(station);//setting the radio stataion
    display.showNumberDec(station*10, false);//display the station number. need to add *10 to display whole number
  }
  Alast=Anow;//resets Alast to the curent state
}
