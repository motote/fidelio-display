#include "FidelioDisplay.h"


 word FidelioDisplay::numbers[] = {0x3F00, 0x0600, 0x5B00, 0x4F00, 0x6600, 0x6D00, 0x7D00, 0x0700, 0x7F00, 0x6F00}; //0..9
 byte FidelioDisplay::daddr[]   = {0xC6, 0xC4, 0xC2, 0xC0};

FidelioDisplay::FidelioDisplay(int dioPin, int clkPin, int stbPin)
{
  _dioPin = dioPin;
  _clkPin = clkPin;
  _stbPin = stbPin;
  _tLastTime = 0;
  _dots = false;
  _pm = false;
  _alarm = false;
  _level = 7;
}

void FidelioDisplay::init() 
{
  pinMode(_dioPin, OUTPUT);
  pinMode(_clkPin, OUTPUT);
  pinMode(_stbPin, OUTPUT);

  digitalWrite(_dioPin, HIGH);
  digitalWrite(_clkPin, HIGH);
  digitalWrite(_stbPin, HIGH);

  delay(200);

  //sendByte(0b10001111);   //Intensidad
  setBright(7);
  sendByte(0b00000011);   //Configuracion 7Dig 10Seg
  sendByte(0b01000000);
}

void FidelioDisplay::setBright(int level)
{
  if (level < 0 || level > 7) return;
  _level = level;
  byte bCommand = 0b10001000 | _level;
  sendByte(bCommand);
}

void FidelioDisplay::cycleBright()
{
  _level+=3;
  if (_level > 7) _level = 1;
}

void FidelioDisplay::sendByte(byte data)
{
    digitalWrite(_stbPin, LOW); 
    for (byte x=0; x<8; x++) {
      digitalWrite(_dioPin, (data & 01));
      data >>= 1;
      digitalWrite(_clkPin, LOW);
      delayMicroseconds(1); 
      digitalWrite(_clkPin, HIGH);
    }
  digitalWrite(_dioPin,HIGH);  
  digitalWrite(_stbPin, HIGH); 
}

void FidelioDisplay::sendWord(word data)
{
    digitalWrite(_stbPin, LOW); 
    for (byte x=0; x<16; x++) {
      digitalWrite(_dioPin, (data & 01));
      data >>= 1;
      digitalWrite(_clkPin, LOW);
      delayMicroseconds(1); 
      digitalWrite(_clkPin, HIGH);
    }
  digitalWrite(_dioPin,HIGH);
  digitalWrite(_stbPin, HIGH); 
}

 void FidelioDisplay::dots(bool value)
 {
  _dots = value;
 }
 
 void FidelioDisplay::pm(bool value)
 {
  _pm = value;
 }
 
 void FidelioDisplay::alarm(bool value)
 {
  _alarm = value;
 }

 void FidelioDisplay::toogleDots()
 {
  _dots = !_dots;
 }
 
 void FidelioDisplay::tooglePm()
 {
  _pm = !_pm;
 }
 
 void FidelioDisplay::toogleAlarm()
 {
  _alarm = !_alarm;
 }

void FidelioDisplay::write(char *cad)
{
  if (strlen(cad) != 4) return;
  
  setBright(_level);
  for (int i = 0; i < 4; i++) 
  {
    word data = numbers[cad[i] - '0'] + daddr[i];
    if (_dots  && i == 1) data |= 0x8000;
    if (_alarm && i == 2) data |= 0x8000;
    if (_pm    && i == 3) data |= 0x8000;
    sendWord(data);
  }
}
