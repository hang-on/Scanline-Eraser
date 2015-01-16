
// Test circuit for quad video buffer for scanline eraser
// Buffer inverted control input is connected to a push button and pulled to ground
// Buffer input is pulled to ground
// Buffer output is connected to Arduino pin 7, and pulled to ground by R1
// See schematic


#define PROBE_PIN 7
#define LED_PIN 6

boolean state;

void setup(){
  pinMode(PROBE_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(PROBE_PIN, HIGH); // Activate internal pull-up resistor on probe pin

}

void loop(){
  // probe the buffer output
  if(digitalRead(PROBE_PIN)) {
    // the line is HIGH, which must mean that:
    // 1) Internal pull-up is defeated by R1,
    // 2) Buffer output is HI-Z (disconnected), so line is not grounded
    // 3) = Current flows through the internal pull-up resistor to +5V
    state = HIGH;
  }
  else {
    // the line is LOW, which must mean that:
    // 1) Internal pull-up is (again) defeated by R1,
    // 2) Buffer output is LOW, and the buffer is defeated by both
    //    R1 and the internal pull-up resistors, thus pulling the line to ground
    // 3) = current flows through the buffer to GND
    state = LOW;
  }  

  
  // toggle LED according to state
  // LED on = buffer output is HI-Z (tristate, electrically disconnected)
  // LED off = buffer output is GND
  digitalWrite(LED_PIN, state);
  
  // insert small delay
  delay(10);
}


