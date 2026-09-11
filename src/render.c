#include "render.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void enable_raw_mode(struct termios *orig) {
  struct termios raw;
  tcgetattr(STDIN_FILENO, orig);
  raw = *orig;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int render_init(RenderState *render) {
  enable_raw_mode(&render->orig_termios);
  fputs("\x1b[?25l\x1b[H\x1b[2J\x1b[3J", stdout); // hide cursor, home, clear screen + scrollback
  fflush(stdout);

  return 0;
}

void render_fini(RenderState *render) {
  fputs("\x1b[2J\x1b[H\x1b[?25h", stdout); // clear, home, show cursor
  fflush(stdout);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &render->orig_termios);
}

