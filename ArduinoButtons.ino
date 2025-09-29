/* 
    This file is to demonstrate how to use clicks.ino

    1. Register your functions as callback functions in setup()
       if you dont need a double click or long click, don't register a function for that
    2. Write your functions
    3. call clicks_loop() in the main loop()

*/


void setup() {
  Serial.begin(115200);

  // register callback functions
  set_single_click_callback(my_single_click); // when a single click is detected by clicks.ino, my_single_click is called
  set_double_click_callback(my_double_click);
  set_long_click_callback(my_long_click);
}

void loop() {
  clicks_loop();
}

// when a single click is detected by clicks.ino, this function is called
void my_single_click(int button_nr) {
  Serial.print("Single click on button ");
  Serial.println(button_nr);
}

void my_double_click(int button_nr) {
  Serial.print("Double click on button ");
  Serial.println(button_nr);
}

void my_long_click(int button_nr) {
  Serial.print("Long click on button ");
  Serial.println(button_nr);
}
