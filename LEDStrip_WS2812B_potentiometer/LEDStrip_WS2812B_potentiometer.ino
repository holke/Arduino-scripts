/* This is modified example code from https://starthardware.org/viele-leds-mit-arduino-steuern-ws2812/ 
 * Using an WS2812B LED strip and a potentiometer.
 * The potentiometer controls how many LEDs are turned on.
 *
 * Connect Potentiometer to 5V, PIN A0, GND
 * Connect WS2812B to 5V, GND. Connect data via 300-500Ohm resistor to PIN 3
 */

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN            3
#define MAX_NUM_PIXELS 60

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(MAX_NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500;


int sensorPin = A0;   // select the input pin for the potentiometer
int ledPin = 9;      // select the pin for the LED
int sensor_value = 0;  // variable to store the value coming from the sensor
int counter = 0;
int min_sensor_value = INT16_MAX;
int max_sensor_value = 0;
int output_value;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  pixels.begin();
}

void update_min_max ()
{
  if (sensor_value < min_sensor_value) {
    min_sensor_value = sensor_value;
  }
  if (sensor_value > max_sensor_value) {
    max_sensor_value = sensor_value;
  }
}

// Map the sensor value from the interval [min, max] to [0, 255].
// Thus, subtract min, to map to [0, max-min],
// then multiply with 255 / (max-min )
void set_output_value ()
{
  // Adjust for fluctuations, so that we can actually get values that turn
  // the LED of.
  int adjusted_min = min_sensor_value + 10;
  int adjusted_max = max_sensor_value;
  float temp = sensor_value - adjusted_min;
  temp = temp * MAX_NUM_PIXELS;
  temp = temp / (adjusted_max - adjusted_min);
  output_value = temp;
  if (output_value < 0) output_value = 0;
  if (output_value > MAX_NUM_PIXELS) output_value = MAX_NUM_PIXELS;
}

void loop() {
  // read the value from the sensor:
  sensor_value = analogRead(sensorPin);
  update_min_max ();
  set_output_value ();
  
  int num_pixels = output_value;
  
  float brightness = 0.1;
  
  // turn the ledPin on
  for(int i = 0; i < num_pixels;i++){
    pixels.setPixelColor(i, pixels.Color(255*brightness, 0, 255*brightness)); // PINK!
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  // turn the remaining pixels off
  for (int i = num_pixels; i < MAX_NUM_PIXELS;i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // OFF
    pixels.show(); // This sends the updated pixel color to the hardware.
  }

  delay (100);
  if (counter % 10 == 0) {
    Serial.print("Sensor: ");
    Serial.print(sensor_value);
    Serial.print(", min: ");
    Serial.print(min_sensor_value);
    Serial.print(", max: ");
    Serial.print(max_sensor_value);
    Serial.print(", output: ");
    Serial.println(output_value);
  }
  counter++;
}