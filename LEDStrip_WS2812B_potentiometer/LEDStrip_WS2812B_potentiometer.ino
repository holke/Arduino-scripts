/* This is modified example code from https://starthardware.org/viele-leds-mit-arduino-steuern-ws2812/ 
 * Using an WS2812B LED strip and a potentiometer.
 * The potentiometer controls how many LEDs are turned on.
 *
 * Connect Potentiometer to 5V, PIN A0, GND
 * Connect WS2812B to 5V, GND. Connect data via 300-500Ohm resistor to PIN 3
 */

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include "Poti.h"
#include "WS2812B_fire.h"

#define PIN            3  // Data pin of LED strip
#define MAX_NUM_PIXELS 8 // Max number of pixels to turn on
#define STRIP_PIXEL_COUNT 10 // The number of pixels of the LED srip

fire_ws2812b<STRIP_PIXEL_COUNT> Strip(PIN);


int delayval = 500;


int PotiPin = A0;   // select the input pin for the potentiometer
int ledPin = 9;      // select the pin for the LED
int counter = 0;
int output_value;

Poti poti (PotiPin, 10, 1000);

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin (9600);
  Serial.println ("Starting");
  Strip.init ();
}


// Map the sensor value from the interval [min, max] to [0, 255].
// Thus, subtract min, to map to [0, max-min],
// then multiply with 255 / (max-min )
void set_output_value ()
{
  // Adjust for fluctuations, so that we can actually get values that turn
  // the LED of.
  int adjusted_min = poti.get_min() + 10;
  int adjusted_max = poti.get_max();
  float temp = poti.get_current()- adjusted_min;
  temp = temp * MAX_NUM_PIXELS;
  temp = temp / (adjusted_max - adjusted_min);
  output_value = temp;
  if (output_value < 0) output_value = 0;
  if (output_value > MAX_NUM_PIXELS) output_value = MAX_NUM_PIXELS;
}

void loop() {
#if 1
  // read the value from the sensor:
  poti.read_value ();
  set_output_value ();
  
  int num_pixels = output_value;
  
  const float brightness_base = 0.1;

  // turn the ledPin on
  for(int i = 0; i < num_pixels;i++){
    const float brightness = (float)(num_pixels - i)/num_pixels * brightness_base;
    Strip.turn_led_color_no_update (i, 255*brightness, 0, 255*brightness);
  }
  // turn the remaining pixels off
  for (int i = num_pixels; i < MAX_NUM_PIXELS;i++) {
    Strip.turn_led_color_no_update(i, 0,0,0); // OFF
  }

  // Show all pixels
  Strip.update ();

  delay (100);
  if (counter % 10 == 0) {
    poti.print ();
    Serial.print(", output: ");
    Serial.println(output_value);
  }
  counter++;
#endif
}