/*  
 *  b-grove-OLED.ino
 *
 *
 * GNU GENERAL PUBLIC LICENSE
 * Use at your own risk.
 ************************************************ Important stuff if needed ****************************************
 *
 * Purchase here https://wiki.seeedstudio.com/Grove-OLED_Display_0.96inch/ about $20 USD
 *
 * Note u8g2 is an arduino search caplble library, easy to install
 *
 *  using 128 x 64 seeeduino OLED
 *  black GND 
 *  red 3v3      so do not need the protective resistors below
 *  white SDA    D11 // on portenta
 *  yellow SCL   D12 // on portenta
 *
 * another reference here 
 * https://github.com/olikraus/u8g2/wiki/u8g2reference#setfont
 *
 * For platformio you need the following at the bottom of the platformio.ini file
   lib_deps = olikraus/U8g2@^2.32.10
 *
 *
 ********************************************************** end ****************************************************
 *
 * 
 *  By Jeremy Ellis twitter @rocksetta
 *  Webpage http://rocksetta.com
 *  Arduino High School Robotics Course at
 *  https://github.com/hpssjellis/arduino-high-school-robotics-course
 * 
 *  Update March 28, 2021
 *
 * MbedI2C  myI2C0(PH_8,  PH_7);  //MbedI2C(int sda, int scl);
 * MbedI2C  myI2C1(PB_7,  PB_6); 
 * MbedI2C  myI2C2(PH_12, PH_11); 
 * 
 */

#include <Arduino.h>  // only needed for https://platformio.org/

#include <U8g2lib.h>


// works
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   //(rotation, clock, data [, reset])

// makes it 128 x 32 if you want that
//U8G2_SSD1306_128X64_ALT0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // SSD1306 and SSD1308Z are compatible
//
// Not yet tested, for Portenta Breakout Board
// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, PH_7, PH_8,    /* reset=*/ U8X8_PIN_NONE);   // I2C0 default //(rotation, clock, data [, reset])
// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, PB_6, PB_7,    /* reset=*/ U8X8_PIN_NONE);   // I2C1
// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,  PH_11, PH_12, /* reset=*/ U8X8_PIN_NONE);   // I2C2

int myDelay = 1000;   // non-block delay in milliseconds
unsigned long myStart;



void setup(void) {
  myStart = millis();   // set delay

  // Don't declare DAC A0 if you want jit to work.
  pinMode(1, OUTPUT);  // no D2 so use 2
  pinMode(2, OUTPUT);  // no D2 so use 2
  //pinMode(A3, INPUT_PULLDOWN);  // no D2 so use 2
  pinMode(A3, INPUT);  // no D2 so use 2
  u8g2.begin();
  Serial.begin(115200);

  // wait for the serial monitor or 10 seconds
  while (!Serial && millis() < 10000 ){
    // do nothing for a bit to connect the monitor if you want
  };  
  Serial.println();
  Serial.println("Hello PCB testing");

  // For DAC pin A0  
  // analogWriteResolution(10); // Set analog out resolution to max, 8bits, 10-bits, 12 bits
  // analogReadResolution(10); // Set analog input resolution to max

}
 
void loop(void) {
  if ( (millis() - myStart ) >= myDelay) {       
     myStart = millis();      //  reset the delay time
 
    analogWrite(A0, random(524)+500 );  // DAC pin max 1023 

    analogWrite(A1, random(200)+56 );  // PWM pin max 255

    digitalWrite(2,!digitalRead(2)); // either on or off 1 or 0


    String myA2 = "A2: "+String(digitalRead(2));
    int myA2Length = myA2.length() + 1; 
    char myA2Char[myA2Length];
    myA2.toCharArray(myA2Char, myA2Length);
  
    String myA3 = "A3: "+String(analogRead(A3));
    int myA3Length = myA3.length() + 1; 
    char myA3Char[myA3Length];
    myA3.toCharArray(myA3Char, myA3Length);
  
    Serial.println("-----");
    Serial.println(myA2);
    Serial.println(myA3);
  
    
  
   
    u8g2.clearBuffer();                   // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr); 
    // FONTS to try    
    // u8g2_font_ncenB08_tr           // normal
    // u8g2_font_u8glib_4_tf          // small
    // u8g2_font_ncenB18_tr           // bigger
    // u8g2_font_pieceofcake_mel_tr   // weird
    // u8g2_font_ncenB08_tr           // skinny
    // u8g2_font_unifont_t_symbols    // stretched
    // FONT LIST at 
    //https://github.com/olikraus/u8g2/wiki/fntlistall
    
    // u8g2.setFontDirection(random(3)); // 0, normal, 1,2,3 rotate by 90 degrees
    u8g2.drawPixel(random(128), random(64));
    
    u8g2.drawLine(  0,0,  127,0);        // horizontal top
    u8g2.drawLine(  0,63, 127,63);        // horizontal bottom
    u8g2.drawLine(127,0,  127,63);        // vertical right
    u8g2.drawLine(  1,0,    1,63);            // vertical left
  
    u8g2.drawCircle(90,20, random(15)); // Circle center x,y,  random radius
    u8g2.drawStr(5,10, "Hello" );  // write something to the internal memory
  

    u8g2.drawStr(5,20, myA2Char);  
    u8g2.drawStr(5,30, myA3Char);  
      
    u8g2.sendBuffer();                  // transfer internal memory to the display
  } // end timer  
}
