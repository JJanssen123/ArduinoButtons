
// config
const int NR_OF_BUTTONS = 4;
const int BUTTON_PINS[] = {4, 5, 6, 7};

int debounceDelay = 10;


// globals
int buttons_reading[NR_OF_BUTTONS];
unsigned long buttons_lastDebounceTime[NR_OF_BUTTONS];
int buttons_lastState[NR_OF_BUTTONS];
int buttons_State[NR_OF_BUTTONS];

// declare callbacks
void (*button_on_callback)(int);
void (*button_off_callback)(int);

void buttons_setup() {
  for (int button_nr = 0; button_nr < NR_OF_BUTTONS; button_nr++) {
    pinMode(BUTTON_PINS[button_nr], INPUT_PULLUP);
    buttons_lastDebounceTime[button_nr] = 0;
    buttons_State[button_nr] = 0;
  }
}

void set_button_on_callback(void *function_pointer) {
  button_on_callback = function_pointer;
}

void set_button_off_callback(void *function_pointer) {
  button_off_callback = function_pointer;
}

int get_nr_of_buttons() {
  return NR_OF_BUTTONS;
}

void buttons_loop() {
  // debounce
  for (int button_nr = 0; button_nr < NR_OF_BUTTONS; button_nr++) {
    unsigned long current_millis = millis();
    if (current_millis - buttons_lastDebounceTime[button_nr] >= debounceDelay) {
      int this_button = digitalRead(BUTTON_PINS[button_nr]);
      if (buttons_State[button_nr] == 0 && this_button ) {
        buttons_State[button_nr] = 1;
        buttons_lastDebounceTime[button_nr] = current_millis;
        if (button_on_callback != NULL) button_on_callback(button_nr);
      }
      else if (buttons_State[button_nr] == 1 && !this_button) {
        buttons_State[button_nr] = 0;
        buttons_lastDebounceTime[button_nr] = current_millis;
        if (button_off_callback != NULL) button_off_callback(button_nr);
      }
    }
  }
}
