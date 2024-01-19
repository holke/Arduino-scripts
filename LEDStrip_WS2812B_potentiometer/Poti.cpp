#include "Poti.h"


void
Poti::print ()
{
  Serial.print("This is Poti at Pin: ");
  Serial.print(get_pin());
  Serial.print(", min: ");
  Serial.print(get_min());
  Serial.print(", max: ");
  Serial.print(get_max());
  Serial.print(", current: ");
  Serial.print(get_current());
}

int Poti::read_value() 
{
  current_value = analogRead(pin);
  Poti::update_min_max ();
}

void 
Poti::update_min_max ()
{
  if (current_value < min_value) {
    min_value = current_value;
  }
  if (current_value > max_value) {
    max_value = current_value;
  }
}