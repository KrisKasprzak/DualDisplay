/*

  The purpose of this program is to test and demonstrate dual displays

  2 x 128 x 64 display


  This could tested should work with any Arduino
  
  Pin connections
  Arduino   device
  A0    
  A1
  A2
  A3
  A4    SDA (if no SDA pin)
  A5    SCL (if not SCL pin)
  1
  2
  3
  4
  5
  6
  7
  8
  9
  10
  11
  12
  13
  SDA   SDA
  SLC   SLC

  Display
  http://www.amazon.com/Diymall%C2%AE-Yellow-Serial-Arduino-Display/dp/B00O2LLT30?ie=UTF8&psc=1&redirect=true&ref_=oh_aui_detailpage_o00_s01
  

*/

#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 Display1(OLED_RESET);
Adafruit_SSD1306 Display2(OLED_RESET);

int i, j;

void setup()   {

  //Serial.begin(9600);

  Display1.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  Display1.clearDisplay();
  Display1.display();

  Display2.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Display2.clearDisplay();
  Display2.display();

}


void loop() {


  for (i = 0; i < 270; i+=10) {

    Display1.setTextSize(2);
    Display1.setTextColor(WHITE, BLACK);
    Display1.setCursor(0, 0 );
    Display1.println("Display 1");
    Display1.fillCircle(i, 30,  10, 1);
    Display1.display();
    Display1.clearDisplay();

    Display2.setTextSize(2);
    Display2.setTextColor(WHITE, BLACK);
    Display2.setCursor(0, 0);
    Display2.println("Display 2");
    Display1.fillCircle(i - 127, 30,  10, 1);
    Display2.display();
    Display2.clearDisplay();


  }

}



// the following code is another sketch for a dual trace oscilloscope
// just copy / paste it into another .ino file

/*

  The purpose of this program is create a simple oscilloscope using an Arduino UNO and an LCD 128 x 64 display

  Code will create a PWM signal for display on the graph
  The display is a Balance world Inc 0.96" Inch Yellow and Blue I2c IIC Serial 128x64 Oled LCD Oled LED Module for Arduino


  Pin connections
  Arduino   device
  Ground    LCD ground
  +5VDC     Vcc
  A0    input voltage to adjust PWM (optional used here for demo purposes)
  A1    input for data read trace A1 (5 VDC limit)
  A2    input for data read trace A2 (5 VDC limit)
  A3
  A4    SDA (if no SDA pin)
  A5    SCL (if not SCL pin)
  1
  2
  3
  4
  5
  6
  7
  8
  9
  10
  11    PWM output (optional used here for demo purposes, connect to A0)
  12
  13
  SDA   SDA
  SLC   SLC

  Graphics Libraries
  https://github.com/adafruit/Adafruit-GFX-Library
  https://github.com/adafruit/Adafruit_SSD1306

  display
  http://www.amazon.com/Balance-world-Yellow-Arduino-Display/dp/B00ZI01RO0/ref=sr_1_1?ie=UTF8&qid=1448860339&sr=8-1&keywords=balance+world+.96


*/


 /*

#include <Adafruit_SSD1306.h>

#define READ_PIN1      A1
#define READ_PIN2      A2
#define PWM_PIN2       9
#define PWM_PIN       11
#define ADJ_PIN       A0
#define OLED_RESET    4


Adafruit_SSD1306 display1(OLED_RESET);
Adafruit_SSD1306 display2(OLED_RESET);

byte data1[128];
byte data2[128];
int x, i;
int scnt, pos, ecnt;
double y, pwmVolts;
unsigned long time1, time2, times, timee, timex;
double distance;

void setup() {
  Serial.begin(9600);

  display1.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display2.begin(SSD1306_SWITCHCAPVCC, 0x3D);

  display1.clearDisplay();
  display1.display();

  display2.clearDisplay();
  display2.display();

  //---------------------------------------------- Set PWM frequency for D3 & D11 ------------------------------
  //TCCR2B = TCCR2B & B11111000 | B00000001;    // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000011;    // set timer 2 divisor to    32 for PWM frequency of   980.39 Hz
  TCCR2B = TCCR2B & B11111000 | B00000100;    // set timer 2 divisor to    64 for PWM frequency of   490.20 Hz (The DEFAULT)
  //TCCR2B = TCCR2B & B11111000 | B00000101;    // set timer 2 divisor to   128 for PWM frequency of   245.10 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000110;    // set timer 2 divisor to   256 for PWM frequency of   122.55 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000111;    // set timer 2 divisor to  1024 for PWM frequency of    30.64 Hz

  pinMode(READ_PIN1, INPUT);
  pinMode(READ_PIN2, INPUT);
  pinMode(ADJ_PIN, INPUT);
  pinMode(PWM_PIN, OUTPUT);
  pinMode(PWM_PIN2, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  // pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  // pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

}

void loop() {

  analogRead(ADJ_PIN) / 4 ;
  // if no adjustment pot, just hard code the voltage to control the PWM
  pwmVolts = 128;

  analogWrite(PWM_PIN, pwmVolts);
  analogWrite(PWM_PIN2, pwmVolts);

  times = GetRiseTime(READ_PIN1);
  timex = micros() - times;
  timee = GetRiseTime(READ_PIN1);
  time1 = GetTime();

  // since we are at rise get the data
  // you may think to just draw the data as we get it but it's way too slow
  for (x = 10; x <= 127; x++) {
    data1[x] = (analogRead(READ_PIN1) / 21.7659);
  }

  times = GetRiseTime(READ_PIN2);
  timex = micros() - times;
  timee = GetRiseTime(READ_PIN2);
  time2 = GetTime();

  // since we are at rise get the data
  // you may think to just draw the data as we get it but it's way too slow
  for (x = 10; x <= 127; x++) {
    data2[x] = (analogRead(READ_PIN2) / 21.7659);
  }

  DrawGraph(display1, data1, time1, "A1 Trace");
  DrawGraph(display2, data2, time2, "A2 Trace");

}

void DrawGraph(Adafruit_SSD1306 & display, byte * data, unsigned long t, char * n) {

  display.clearDisplay();
  for (int x = 10; x <= 127; x++) {
    display.drawLine(x , 63 - (data[x - 1]), x , 63 - (data[x]), 1);
  }


  // draw the axis, lables and tick marks
  for (int y = 0; y < 6; y++) {
    display.drawFastHLine(7, y * (48) / 5 + 16, 3, 1);
  }
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.setCursor(0, 57);
  display.println("0");
  display.setCursor(0, 16);
  display.println("5");
  display.fillRect(0, 0,  127 , 14, 1);
  display.setTextColor(BLACK, WHITE);
  display.drawFastHLine(10, 63,  128 - 10, 1);
  display.drawFastVLine(10, 16,  63, 1);
  display.setTextSize(1);
  display.setCursor(2, 3);
  display.print(n);
  display.setCursor(85, 3);
  t = 1000000 / t;
  display.print(t);
  display.setCursor(105, 3);
  display.println("Hz");
  display.display();
  display.clearDisplay();

}

long GetTime() {
  long thetime;

  if (timee == 0 | times == 0) {
    thetime = -1000000;
  }
  else {
    thetime = timee - times - timex;
  }

  return thetime;
}

long GetRiseTime(int PIN) {

  // find the first rise time
  scnt = 0;
  ecnt = 0;
  long stime = 0;
  while (scnt++ < 400) {
    pos = analogRead(PIN);
    if (pos == 0) {
      while (ecnt++ < 400) {
        pos = analogRead(PIN);
        if (pos != 0) {
          stime = micros();
          break;
        }
      }
      break;
    }
  }
  return stime;
}

*/




