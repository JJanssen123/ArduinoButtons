
// this code is used to transform button presses to clicks, doubleclicks and long clicks

// config
const int NR_OF_BUTTONS_IN_USE = 4;


// globals
unsigned int last_click_time[NR_OF_BUTTONS_IN_USE];
int clicked[NR_OF_BUTTONS_IN_USE];
int hold[NR_OF_BUTTONS_IN_USE];
int double_click_interval = 500;
int long_click_interval = 550;

// declare callbacks
void (*single_click_callback)(int);
void (*double_click_callback)(int);
void (*long_click_callback)(int);

void set_single_click_callback(void *function_pointer) {
  single_click_callback = function_pointer;
}

void set_double_click_callback(void *function_pointer) {
  double_click_callback = function_pointer;
}

void set_long_click_callback(void *function_pointer) {
  long_click_callback = function_pointer;
}

void clicks_setup() {
  buttons_setup();
  set_button_on_callback(clicks_button_on);
  set_button_off_callback(clicks_button_off);
}

void clicks_loop() {
  buttons_loop();
  for (int button_nr = 0; button_nr < NR_OF_BUTTONS; button_nr++) {
    unsigned long current_millis = millis();
    if (current_millis - last_click_time[button_nr] > double_click_interval && clicked[button_nr]) {
      clicked[button_nr] = 0;
    }
    if (current_millis - last_click_time[button_nr] >= long_click_interval && hold[button_nr]) {
    if (long_click_callback != NULL) long_click_callback(button_nr);      
      hold[button_nr] = 0;
    }
  }
}

void clicks_button_on(int button_nr) {
  unsigned long current_millis = millis();
  if (!clicked[button_nr]) {
    if (single_click_callback != NULL) single_click_callback(button_nr);
    clicked[button_nr] = 1;
    hold[button_nr] = 1;
    last_click_time[button_nr] = current_millis;
  }
  else if (clicked[button_nr] && current_millis - last_click_time[button_nr] <= double_click_interval) {
    if (double_click_callback != NULL) double_click_callback(button_nr);
    clicked[button_nr] = 0;
  }
}

void clicks_button_off(int button_nr) {
  hold[button_nr] = 0;
}
