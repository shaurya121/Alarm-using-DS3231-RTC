#include "Wire.h"
#define DS3232_I2C_ADDRESS 0x68

// convert normal decimal to BCD
byte DectoBCD(byte val){
  return ((val/10*16)+(val%10));
}

// BCD back to decimal
byte BCDtoDec(byte val){
  return ((val/16*10)+(val%16));
}

int vdd=7;  // buzzer 
int gnd=4;  // buzzer

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(vdd, OUTPUT);
  pinMode(gnd, OUTPUT);
  digitalWrite(vdd, HIGH);
  digitalWrite(gnd, HIGH);
  // to set the time for first time
  // format- seconds, minutes, hours, day, date, month, year
  //setDS3232time(0, 35, 20, 5, 24, 03, 22);
}

// function to set time and date
void setDS3232time(byte second, byte minute, byte hour, byte day, byte date, byte month, byte year){
  Wire.beginTransmission(DS3232_I2C_ADDRESS);
  Wire.write(0);
  Wire.write(DectoBCD(second));
  Wire.write(DectoBCD(minute));
  Wire.write(DectoBCD(hour));
  Wire.write(DectoBCD(day));    // set day of week (1=sunday, 7=saturday)
  Wire.write(DectoBCD(date));   
  Wire.write(DectoBCD(month));      
  Wire.write(DectoBCD(year));   // set year (0 to 99)
  Wire.endTransmission();
}

void read3232time(byte *second, byte *minute, byte *hour, byte *day, byte *date, byte *month, byte *year){
  Wire.beginTransmission(DS3232_I2C_ADDRESS);
  Wire.write(0);  // set DS3232 register pointer to 00H
  Wire.endTransmission();
  Wire.requestFrom(DS3232_I2C_ADDRESS, 7);

  // request seven bytes of data from DS3232 starting from register 00H
  *second=BCDtoDec(Wire.read() & 0x7f);
  *minute=BCDtoDec(Wire.read());
  *hour=BCDtoDec(Wire.read() & 0x3f);
  *day=BCDtoDec(Wire.read());
  *date=BCDtoDec(Wire.read());
  *month=BCDtoDec(Wire.read());
  *year=BCDtoDec(Wire.read());
}

void checkTime(){
  byte second, minute, hour, day, date, month, year;
  // retrieve data  from DS3232
  read3232time(&second, &minute, &hour, &day, &date, &month, &year);

  // check whether time is 07:30AM to turn on the alarm
  if (hour==07 && minute==30){
    digitalWrite(gnd, LOW);
  }
  else{
    digitalWrite(gnd, HIGH);
  }
}


void loop() {
  checkTime();
  delay(1000);
  // put your main code here, to run repeatedly:
}
