// Code designed to read the data from an MIT id card using a Teensy 3.2.
// These cards recieve power at 125khz and transmit back at 62.5khz and 187.5khz
// More information available at ramoyer.com/2018/08/Card-Reader.html

#include <FrequencyTimer2.h>

#define numSamples 20000
uint8_t data[numSamples];
long lastMillis = 0;
bool on = true;
int j = 0;// sample counter

IntervalTimer myTimer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(14,INPUT);
  pinMode(5,OUTPUT);
  pinMode(13,OUTPUT);
  FrequencyTimer2::setPeriod(8);
  FrequencyTimer2::enable();

  // delay so samples are taken on correct part of waveform
  delayMicroseconds(4);//f(1) = 64, f(2) = 0 leads with 255,64,0, f(3) = 64, f(4) = 128, f(5) = 194, f(6) = 255, f(7) = 192, f(8) = 128, f(9) = 64 + weird stuff for some reason, 
  myTimer.begin(sample,16);// calls sample() at 16µs (62.5khz)
  
}

void loop() {
  // delay while interrupts gather some data. 
  // 3 seconds is to keep from overwhelming user with data. 
  // Only needs time of numsamples/freq for reading
  delay(3000);
  
  //Print the data
  noInterrupts();
  for(int i=0; i <numSamples;i++){
    Serial.print(data[i]);
    Serial.print("\n");
  }
  Serial.println("");

  // blink status light
  if(on == true){
    digitalWrite(13,HIGH);
    on = false;
  }
  else if(on == false){
    digitalWrite(13,LOW);
    on = true;
  }
  j = 0;// reset sample counter
  interrupts();
}

void sample(){
  if(j<numSamples){
    data[j] = analogRead(14);
  }
  j++;
}
