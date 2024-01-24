#ifndef FIRE_H
#define FIRE_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

/* 
 */
class fire_ws2812b
{
  public:

  fire_ws2812b (int num_pixels, int data_pin);

  /* Turn all LEDs off. will update all LEDs */
  void turn_leds_off ();

  /* Turn indivdual LED to a color, no update is trigger.
   * If zou want the LED to show the color, call update () afterwards */
  void turn_led_color_no_update (int led, uint8_t red, uint8_t green, uint8_t blue);

  /* Turn all LEDs to the same color. Will update all LEDs */
  void turn_leds_color (uint8_t red, uint8_t green, uint8_t blue);

  /* Update the LED strip, thus show all set colors. */
  void update ();

  protected:

  // Number of pixels that this strip controls
  int num_pixels;
  // data pin of this strip
  int data_pin;
  // The actual LEDs
  Adafruit_NeoPixel pixels;
};


#endif // FIRE_H
