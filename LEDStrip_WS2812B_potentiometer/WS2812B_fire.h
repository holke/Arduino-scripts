#ifndef FIRE_H
#define FIRE_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


/* 
 */
template <int NUM_PIXELS>
class fire_ws2812b
{
  public:

  fire_ws2812b (int data_pin) : num_pixels (NUM_PIXELS), data_pin (data_pin) 
  {
  }

  void init () 
  {
    Serial.println ("Init");
    delay (100);
    pixels = Adafruit_NeoPixel(num_pixels, data_pin, NEO_GRB + NEO_KHZ800);
    pixels.begin();
    // Turn all pixels off before starting
    turn_leds_off ();
  }

  /* Turn all LEDs off. will update all LEDs */
  void turn_leds_off ()
  {
    Serial.println("Turn Off");
    delay (100);
    turn_leds_color (0, 0, 0);
  }

  /* Turn indivdual LED to a color, no update is trigger.
   * If zou want the LED to show the color, call update () afterwards */
  void turn_led_color_no_update (int led, uint8_t red, uint8_t green, uint8_t blue)
  {
    colors[led][0] = red;
    colors[led][1] = green;
    colors[led][2] = blue;
  }

  /* Turn all LEDs to the same color. Will update all LEDs */
  void turn_leds_color (uint8_t red, uint8_t green, uint8_t blue)
  {
    Serial.print ("Turn color: ");
    Serial.print (red);
    Serial.print (" ");
    Serial.print (blue);
    Serial.print (" ");
    Serial.println (green);
    delay (100);
    for(int i = 0; i < num_pixels;i++){
      turn_led_color_no_update (i, red, green, blue); 
    }
    update ();
  }

  /* Update the LED strip, thus show all set colors. */
  void update ()
  {
    for(int led = 0; led < num_pixels;led++){
      pixels.setPixelColor (led, pixels.Color(colors[led][0], colors[led][1], colors[led][2]));
    }
    pixels.show(); // This sends the updated pixel color to the hardware.  
  }

  protected:

  // Number of pixels that this strip controls
  int num_pixels;
  // data pin of this strip
  int data_pin;
  // The actual LEDs
  Adafruit_NeoPixel pixels;
  // Array buffering the current color
  uint8_t colors[NUM_PIXELS][3];
};


#endif // FIRE_H
