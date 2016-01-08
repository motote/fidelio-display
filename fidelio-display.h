#ifndef FIDELIODISPLAY_h
#define FIDELIODISPLAY_h

#include <Arduino.h>
typedef uint8_t byte;
typedef uint16_t word;

class FidelioDisplay
{
public:
  FidelioDisplay(int dioPin, int clkPin, int stbPin);
  int readKey();
  void init();
  void write(char *cad);
  void setBright(int level);
  void cycleBright();
  void dots(bool value);
  void pm(bool value);
  void alarm(bool value);
  void toogleDots();
  void tooglePm();
  void toogleAlarm();
private:
  void sendByte(byte data);
  void sendWord(word data);

  int  _dioPin;
  int  _clkPin;
  int  _stbPin;
  byte _level;
  bool _pm;
  bool _alarm;
  bool _dots;
  long _tLastTime;
  static word numbers[];
  static byte daddr[];

};

#endif
