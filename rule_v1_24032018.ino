/*
  LBE Rule
  Designed in Ausralia 
  By Nick Owen
  For Little Bird Electronics, 2018 
*/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            10

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



// setSegments
/******************************************************************************/
// Sets the 'digitCodes' that are required to display the desired segments.
// Using this function, one can display any arbitrary set of segments (like
// letters, symbols or animated cursors). See setDigitCodes() for common
// numeric examples.
//
// Bit-segment mapping:  0bHGFEDCBA
//      Visual mapping:
//                        AAAA          6666
//                       F    B        7    5
//                       F    B        7    5
//                        GGGG          8888
//                       E    C        1    3
//                       E    C        1    3        (Segment H is often called
//                        DDDD  H       2222        DP, for Decimal Point)



static const byte PinCodeMap[] = {6, 5, 3, 2, 1, 7, 8, 4};

static const byte digitCodeMap[] = {
  // Segments:    [see setSegments() for bit/segment mapping]
  // HGFEDCBA  // Char:
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111, // 9
  B00000000, // BLANK
  B01000000, // DASH
  B00111000, // L
  B01111001, // E
  B10000000, // DP
};




// constants won't change. They're used here to set pin numbers:
const int buttonPin = 9;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

// the setup function runs once when you press reset or power the board
void setup() {

  // Serial.begin(115200);
  // initialize digital pin 13 as an output.
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(buttonPin, INPUT);


  digitalWrite(8, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(7, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(6, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(4, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)

  delay(500);


  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.

  // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Moderately bright green color.

  pixels.show(); // This sends the updated pixel color to the hardware.

  rainbow(5);


}

// the loop function runs over and over again forever
void loop() {

  segnum(10);
  segnum(12);
  delay(1000);
  segnum(10);
  segnum(8);
  delay(1000);
  segnum(10);
  segnum(13);
  delay(1000);
  segnum(14);
  delay(1000);



  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  while (buttonState == LOW) {
    buttonState = digitalRead(buttonPin);

    // turn LED on:
    rainbow(5);
  }

  // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Moderately bright green color.

  pixels.show(); // This sends the updated pixel color to the hardware.


}

void segnum(int x) {
  // Serial.println("start");
  for (int i = 0; i < 8; i++) {

    //Serial.print((digitCodeMap[x]>>i)& 0x01);
    //Serial.println(!((digitCodeMap[x]>>i)& 0x01));

    digitalWrite(PinCodeMap[i], !((digitCodeMap[x] >> i) & 0x01)); // turn the LED on (HIGH is the voltage level)

  }
  // Serial.println("end");

}


void neooff() {
  strip.setPixelColor(0, pixels.Color(0, 0, 0)); // Moderately bright green color.

  strip.show(); // This sends the updated pixel color to the hardware.
  delay(1);


}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 255; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


uint32_t Wheel(byte WheelPos) {
  WheelPos = 64 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}




