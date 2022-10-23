#include <DS3231.h>
#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#include <Keypad.h>
#include <string.h>

const int buzzerLED = 7;
const int offButton = 6;
const int photoResistor = A0;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int hour;
int minute;
int second;

int alarmHour;
int alarmMinute;

int set = 1;

DS3231 clock;
RTCDateTime dt;

U8X8_SSD1309_128X64_NONAME0_4W_SW_SPI u8x8(/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8); 

void setup()
{
  Serial.begin(9600);

  //Serial.println("Initialize RTC module");
  // Initialize DS3231
  clock.begin();
  // Manual (YYYY, MM, DD, HH, II, SS
  // clock.setDateTime(2016, 12, 9, 11, 46, 00);
  
  // Send sketch compiling time to Arduino
  clock.setDateTime(__DATE__, __TIME__);    
  /*
  Tips:This command will be executed every time when Arduino restarts. 
       Comment this line out to store the memory of DS3231 module
  */

  u8x8.begin();

  pinMode(buzzerLED, OUTPUT);
  pinMode(offButton, INPUT);
  pinMode(photoResistor, INPUT);
}

void loop() {

  dt = clock.getDateTime();

  hour = dt.hour;
  minute = dt.minute;

  String sHour = String(hour);
  String sMinute = String(minute);

  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,0,sHour.c_str());
  u8x8.drawString(1,0,":");
  u8x8.drawString(2,0,sMinute.c_str());

  //char customKey = customKeypad.getKey();

  alarmHour = hour;
  alarmMinute = minute;

  //set_alarm(customKey);

  if(alarmHour == hour && alarmMinute == minute)
  {
    while(set == 1)
    {
      digitalWrite(buzzerLED, HIGH);

      Serial.println(analogRead(photoResistor));
      Serial.println(digitalRead(offButton));

      delay(1000);

      if (digitalRead(offButton) == 0 && analogRead(photoResistor) < 200)
      {
        set = 0;
        digitalWrite(buzzerLED, LOW);
      }
    }
    delay(1000);
  }
  
}

// void set_alarm(char customKey)
// {
//   if(customKey = 'A')
//   {
//     while(set == 1)
//     {
//       if(customKeypad.getKey() == '1')
//       {
//         alarmHour = 1;
//         set = 0;
//       }
//       if(customKeypad.getKey() == '2')
//       {
//         alarmHour = 2;
//         set = 0;
//       }
//       if(customKeypad.getKey() == '3')
//       {
//         alarmHour = 3;
//         set = 0;
//       }
//       if(customKeypad.getKey() == '4')
//       {
//         alarmHour = 4;
//         set = 0;
//       }
//       if(customKeypad.getKey() == '5')
//       {
//         alarmHour = 5;
//         set = 0;
//       }
//       if(customKeypad.getKey() == '6')
//       {
//         alarmHour = 6;
//         set = 0;
//       }
//       if(customKeypad.getKey() == '7')
//       {
//         alarmHour = 7;
//         set = 0;
//       }
//       if(customKeypad.getKey() == '8')
//       {
//         alarmHour = 8;
//         set = 0;
//       }
//       if(customKeypad.getKey() == '9')
//       {
//         alarmHour = 9;
//         set = 0;
//       }
//       if(customKeypad.getKey() == '*')
//       {
//         alarmHour = 10;
//         set = 0;
//       }
//       if(customKeypad.getKey() == '0')
//       {
//         alarmHour = 11;
//         set = 0;
//       }
//       if(customKeypad.getKey() == '#')
//       {
//         alarmHour = 12;
//         set = 0;
//       }

//       set = 1;

//       while(set == 1)
//       {
//         if(customKeypad.getKey() == '*')
//         {
//           alarmMinute -= 1;
//         }
//         if(customKeypad.getKey() == '#')
//         {
//           alarmMinute += 1;
//         }
//         if(customKeypad.getKey() == '0')
//         {
//           if(alarmMinute < 0 || alarmMinute > 59)
//           {
//             alarmMinute = 0;
//           }
//           set = 0;
//         }
//       }
//     }
//   }
//}
