#include <Bounce2.h>
#include <Keyboard.h>

#define PIN_UP     11
#define PIN_DOWN   9
#define PIN_LEFT   10
#define PIN_RIGHT  12
#define PIN_A      8
#define PIN_B      13
#define PIN_SELECT 6
#define PIN_START  7

#define KEY_A      'z'
#define KEY_B      'x'
#define KEY_SELECT KEY_ESC
#define KEY_START  KEY_RETURN

Bounce up     = Bounce(); 
Bounce down   = Bounce();
Bounce left   = Bounce();
Bounce right  = Bounce();
Bounce a      = Bounce();
Bounce b      = Bounce();
Bounce select = Bounce();
Bounce start  = Bounce();

bool s_up     = false;
bool s_down   = false;
bool s_left   = false;
bool s_right  = false;
bool s_a      = false;
bool s_b      = false;
bool s_select = false;
bool s_start  = false;

void attachBtnToPin(Bounce &btn, int pin, int interval = 2)
{
  pinMode(pin, INPUT_PULLUP);
  btn.attach(pin);
  btn.interval(interval);
}

bool readBtn(Bounce &btn)
{
  btn.update();
  
  return !btn.read();
}

void simulateKey(Bounce &btn, char key, bool &btn_state)
{
  if (readBtn(btn)) {
    if (!btn_state) {
      Keyboard.press(key);
      btn_state = true;
    }
  } else {
    if (btn_state) {
      Keyboard.release(key);
      btn_state = false;
    }
  }
}

void setup()
{
  attachBtnToPin(up,    PIN_UP);
  attachBtnToPin(down,  PIN_DOWN);
  attachBtnToPin(left,  PIN_LEFT);
  attachBtnToPin(right, PIN_RIGHT);

  attachBtnToPin(a, PIN_A);
  attachBtnToPin(b, PIN_B);

  attachBtnToPin(select, PIN_SELECT);
  attachBtnToPin(start,  PIN_START);

  Keyboard.begin();
}

void loop()
{
  simulateKey(up,    KEY_UP_ARROW,    s_up);
  simulateKey(down,  KEY_DOWN_ARROW,  s_down);
  simulateKey(left,  KEY_LEFT_ARROW,  s_left);
  simulateKey(right, KEY_RIGHT_ARROW, s_right);

  simulateKey(a, KEY_A, s_a);
  simulateKey(b, KEY_B, s_b);

  simulateKey(select, KEY_SELECT, s_select);
  simulateKey(start,  KEY_START,  s_start);
}
