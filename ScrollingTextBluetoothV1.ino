#define FONT_5x8_FIXED_MEDIUM
#define FONT_CHARSET_SMALL
#include <StripDisplay.h>
XBMFont * fontP = &fixedMedium_5x8;

#define STRIPLED_GPIO 5
#define STRIPLED_W  8
#define STRIPLED_H  8

CRGB leds[STRIPLED_W * STRIPLED_H];

StripDisplay strip(STRIPLED_GPIO, STRIPLED_W, STRIPLED_H, WRAP_COLUMNS, ORIGIN_TOP_RIGHT, leds);

// message board globals
String message = "Boaz";
#define START_OFFSET -10
int offset = START_OFFSET;
// time managemet globals
#define SCROLL_MS 150;
int update_ms = 0;


// initial FastLED and StripDisplay setup
void setup() {
  FastLED.addLeds<NEOPIXEL, STRIPLED_GPIO>(leds, STRIPLED_W * STRIPLED_H);
  strip.setup(fontP);
  Serial.begin(9600);
  Serial.println(String(STRIPLED_W * STRIPLED_H) + String(" leds on gpio ") + String(strip.getGpio()));
  // initial message setup
  strip.setBgColor(CRGB::Blue);
  strip.setFgColor(CRGB::Yellow);
  updateMessageText("Hello");
}

// setup new message text
void updateMessageText(String text1) { //so basically the text comes in from bluetooth and = text1 instantly I just gotta make it stay = to something else like text
  //message = text;
  offset = START_OFFSET;
  Serial.println((text1) + " text1");
  Serial.println((message) + " message");
  String text;

  // strip.setText(text);

  if (text1.substring(0) == "bg red") { // test the received buffer for "on"
    FastLED.clear();
    strip.setBgColor(CRGB::Red);
    FastLED.show();
 //   message = text;
  }

  if (text1.substring(0) == "bg green") { // test the received buffer for "on"
    FastLED.clear();
    strip.setBgColor(CRGB::Green);
    FastLED.show();
   // message = text;

  }

  if (text1.substring(0) == "bg blue") { // test the received buffer for "on"
    FastLED.clear();
    strip.setBgColor(CRGB::Blue);
    FastLED.show();
   // message = text;
  }

  if (text1.substring(0) == "bg white") { // test the received buffer for "on"
    FastLED.clear();
    strip.setBgColor(CRGB::White);
    FastLED.show();
  //  message = text;
  }

  if (text1.substring(0) == "bg clear") { // test the received buffer for "on"
    FastLED.clear();
    strip.setBgColor(CRGB::Black);
    FastLED.show();
  //  message = text;
  }

  if (text1.substring(0) == "fg red") { // test the received buffer for "on"
    FastLED.clear();
    strip.setFgColor(CRGB::Red);
    FastLED.show();
   // message = text;
  }

  if (text1.substring(0) == "fg green") { // test the received buffer for "on"
    FastLED.clear();
    strip.setFgColor(CRGB::Green);
    FastLED.show();
  //  message = text;
  }

  if (text1.substring(0) == "fg blue") { // test the received buffer for "on"
    FastLED.clear();
    strip.setFgColor(CRGB::Blue);
    FastLED.show();
  //  message = text;
  }

  if (text1.substring(0) == "fg white") { // test the received buffer for "on"
    FastLED.clear();
    strip.setFgColor(CRGB::White);
    FastLED.show();
   // message = text;
  }

  if (text1.substring(0) == "fg clear") { // test the received buffer for "on"
    FastLED.clear();
    strip.setFgColor(CRGB::Black);
    FastLED.show();
   // message = text; //message = stored data
  }

  if (text1.substring(0) != "fg clear" && text1.substring(0) != "fg white" && text1.substring(0) != "fg blue" && text1.substring(0) != "fg green" && text1.substring(0) != "fg red" && text1.substring(0) != "bg clear" &&
  text1.substring(0) != "bg white" && text1.substring(0) != "bg red" && text1.substring(0) != "bg green" && text1.substring(0) != "bg blue") {

message = text1; //message just equals whatever just came in over bluetooth
     text1 = text; //storing text1 to the global variable
    strip.setText(message);//printing whatever is held in text
     Serial.println((text) + " text in else");
          Serial.println((text1) + " text1 in else");

  Serial.println((message) + " message in else");
  }
  

  //else {
  //  message = text1; //message just equals whatever just came in over bluetooth
 //   text1 = text; //storing text1 to the global variable
  //  strip.setText(message);//printing whatever is held in text
  //   Serial.println((text) + " text in else");
   //       Serial.println((text1) + " text1 in else");

 // Serial.println((message) + " message in else");
 // }


}

// display and scroll message
void displayMessageText() {
  if (offset > strip.getTextWidth())
    offset = START_OFFSET;
  strip.displayText(offset);
  offset++;
}

// get message from serial if any
void getMessageSerial() {
  if (Serial.available())
    updateMessageText(Serial.readString());
}



void loop() {
  FastLED.setBrightness(32);
  // mesure current time
  int current_ms = millis();
  // poll for message on serial port
  getMessageSerial();
  // scroll and display message at a fixed time rate
  if (update_ms <= current_ms) {
    displayMessageText();
    update_ms = current_ms + SCROLL_MS;
  }
  else {
    FastLED.delay(update_ms - current_ms);
  }

}
