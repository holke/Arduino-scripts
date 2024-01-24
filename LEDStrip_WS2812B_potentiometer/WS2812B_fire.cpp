#include "WS2812B_fire.h"


fire_ws2812b::fire_ws2812b (int num_pixels, int data_pin) : num_pixels (num_pixels), data_pin (data_pin) {
  pixels = Adafruit_NeoPixel(num_pixels, data_pin, NEO_GRB + NEO_KHZ800);
  Serial.begin(9600);
  pixels.begin();
  // Turn all pixels off before starting
  turn_leds_off ();
}


void 
fire_ws2812b::turn_leds_off ()
{
  turn_leds_color (0, 0, 0);
}

void
fire_ws2812b::turn_led_color_no_update (int led, uint8_t red, uint8_t green, uint8_t blue)
{
  pixels.setPixelColor (led, pixels.Color(red, green, blue)); 
}

void 
fire_ws2812b::turn_leds_color (uint8_t red, uint8_t green, uint8_t blue)
{
  for(int i = 0; i < num_pixels;i++){
    turn_led_color_no_update (i, red, green, blue); 
  }
  update ();
}


void
fire_ws2812b::update ()
{
  pixels.show(); // This sends the updated pixel color to the hardware.  
}