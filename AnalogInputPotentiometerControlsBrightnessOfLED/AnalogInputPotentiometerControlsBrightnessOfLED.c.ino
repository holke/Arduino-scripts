/*
  Analog Input

  A potentiometer at analo input 0 controls the brightness of on LED
  at pin 9.
  In order to calibrate the brightness, you must turn the potentiometer
  fully left and fully right after starting the program.
  (Recalibrations happens constantly)

  TODO: Sometimes the calibration breaks due to missreadings of the potentiometer.
        Add a button to reset the calibration.
  TODO: Can we store the calibration values in internal ROM?

  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 9 through 220 ohm resistor
    cathode (short leg) attached to ground

  created by Johannes Holke
  January 11 2024

  Modified from the Analog input example:

  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInput
*/

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
  int adjusted_min = min_sensor_value + 100;
  int adjusted_max = max_sensor_value - 25;
  float temp = sensor_value - adjusted_min;
  temp = temp * 255;
  temp = temp / (adjusted_max - adjusted_min);
  output_value = temp;
  if (output_value < 0) output_value = 0;
  if (output_value > 255) output_value = 255;
}

void loop() {
  // read the value from the sensor:
  sensor_value = analogRead(sensorPin);
  update_min_max ();
  set_output_value ();
  
  // turn the ledPin on
  analogWrite(ledPin, output_value);
  delay (10);
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
