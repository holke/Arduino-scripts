#ifndef POTI_H
#define POTI_H

#include <Arduino.h>

/* A potentiometer class to manage read values from a poti.
 * The poti must be connected to 5V, a PIN, GND.
 * The poti stores the minimum and maximum read values and the currently read value.
 */
class Poti
{
  public:

  // Constructor 
  // Pin - The Arduino Pin that the middle of the poti is connected to
  Poti (int Pin) : Poti(Pin, INT16_MAX, 0) {}

  // Constructor
  // Pin - The Arduino Pin that the middle of the poti is connected to
  // min - Known minimum value of the Poti
  // max - Knwon maximum value of the Poti
  Poti (int Pin, int min, int max) : pin(Pin), min_value(min), max_value (max) {}

  inline int get_min () {return min_value;}
  inline int get_max () {return max_value;}
  inline int get_current () {return current_value;}
  inline int get_pin () {return pin;}
  
  // Read the current value of the Poti.
  // Also updates min and max
  int read_value ();

  // Print information of the Poti
  // Pin, min, max, current
  void print ();

  private:

  void update_min_max ();
  int min_value;
  int max_value;
  int current_value;
  int pin; // The Arduino pin to which the middle pin of the poti is connected to.
};


#endif // POTI_H
