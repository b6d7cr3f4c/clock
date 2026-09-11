#include "render.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

const char *digits[10][5] = {
    { " ### ", "#   #", "#   #", "#   #", " ### " }, // 0
    { "  #  ", " ##  ", "  #  ", "  #  ", " ### " }, // 1
    { " ### ", "#   #", "   # ", "  #  ", "#####"}, // 2
    { " ### ", "    #", "  ## ", "    #", " ### " }, // 3
    { "#  # ", "#  # ", "#####", "   # ", "   # " }, // 4
    { "#####", "#    ", "#### ", "    #", "#### " }, // 5
    { " ### ", "#    ", "#### ", "#   #", " ### " }, // 6
    { "#####", "    #", "   # ", "  #  ", " #   " }, // 7
    { " ### ", "#   #", " ### ", "#   #", " ### " }, // 8
    { " ### ", "#   #", " ####", "    #", " ### " }  // 9
};

const char *colon[5] = {
    "     ",
    "  #  ",
    "     ",
    "  #  ",
    "     "
};

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

void render_draw(RenderState *render, char input[])
{
    (void)render;

    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    int term_width = ws.ws_col;
    int term_height = ws.ws_row;

    int height = 5;
    int width = 0;

    /* Calculate rendered width */
    for (int i = 0; input[i] != '\0'; i++) {
        width += 5;

        /* One space between characters */
        if (input[i + 1] != '\0')
            width++;
    }

    /*
     * Slant adds up to height - 1 characters
     * to the left side.
     */
    int slant_width = height - 1;

    int total_width = width + slant_width;

    int start_x = (term_width - total_width) / 2;
    int start_y = (term_height - height) / 2;

    /* Don't allow negative positions */
    if (start_x < 0)
        start_x = 0;

    if (start_y < 0)
        start_y = 0;

    /* Draw each row */
    for (int row = 0; row < height; row++) {

        /* Move cursor to beginning of this row */
        printf("\033[%d;%dH",
               start_y + row + 1,
               start_x + row + 1);

        /* Draw every character */
        for (int i = 0; input[i] != '\0'; i++) {

            if (input[i] == ':') {
                printf("%s", colon[row]);
            } else if (input[i] >= '0' && input[i] <= '9') {
                int digit = input[i] - '0';
                printf("%s", digits[digit][row]);
            }

            /* Space between glyphs */
            if (input[i + 1] != '\0')
                putchar(' ');
        }
    }

    fflush(stdout);
}
