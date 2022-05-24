
# Alarm Clock using DS3232 Module

Use Arduino UNO as a alarm clock using DS3232 Module.


## Screenshots
![App Screenshot](https://raw.githubusercontent.com/shaurya121/Alarm-using-DS3231-RTC/main/Screenshots/device.gif)
![App Screenshot](https://raw.githubusercontent.com/shaurya121/Alarm-using-DS3231-RTC/main/Screenshots/serial_monitor.jpg)
                Serial Monitor



## Usage/Examples
Assign '0x68' I2C address to the DS3232 module:
```c
#define DS3232_I2C_ADDRESS 0x68

```

Number system converter functions:
```c
byte DectoBCD(byte val){
    ...
}

byte BCDtoDec(byte val){
    ...
}
```

Assign +ve and -ve pins to buzzer:
```c
int vdd=7;
int gnd=4;
```
Set time on DS3232 module:
```c
void setDS3232time(byte second, byte...year){
    ...
}
```

Read time from DS3232 module:
```c
void read3232time(byte *second, byte *minute...*year){
    ...
}
```

If time is 7:30 AM, then buzzer starts beeping-
```c
if (hour==07 && minute==30){
    digitalWrite(gnd, LOW);
  }
```
