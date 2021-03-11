///
/// activate/inactivate IME by both shift press simultaneously.
///

// Required fcitx
// use Input SubSytem
// usage:
// $ ./test < /dev/input/event3

#ifdef DEBUG
#define debug(...) printf(...)
#else
#define debug(...) 
#endif

// #define DEBUG 

#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define KEY_PRESSED 1
// ime is en -> 1 : true
// ime is jp -> 0 : false
int isEn;

void toIme_jp() {
  isEn = 0;
  debug("change to jp\n");
  system("fcitx-remote -o");
  // system("ibus engine 'mozc-jp'");
}
void toIme_en() {
  isEn = 1;
  debug("change to en\n");
  system("fcitx-remote -c");
  // system("ibus engine 'xkb:us::eng'");
}
void imeChange() {
  if(isEn)
    toIme_jp();
  else
    toIme_en();
}
int main(void)
{
  toIme_en();

  int flag = 0;

  debug("%s\n", "run");

  while(1) {
    // read event3 file from stdin(fd = 0)
    struct input_event event;
    
    if (read(0, &event, sizeof(event)) != sizeof(event)) {
      perror("Error");
      exit(EXIT_FAILURE);
    }

    // Pressed key check
    if(event.type == EV_KEY) {
      switch(event.code) {
        case 42: // Shift_L
        case 54: // Shift_R
          event.value == KEY_PRESSED ? flag++ : flag--;

          if(flag == 2) {
            debug("Both of shift down\n");
            debug("change IME\n");
            imeChange();
          }
          break;
        default:
          debug("%d\n", event.code);
          break;
      }
    }
  }
}
