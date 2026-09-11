#ifndef RENDER_H
#define RENDER_H

#include <termios.h>

typedef struct {
  struct termios orig_termios;
  int rows;
  int cols;
} RenderState;

int render_init(RenderState* render);
void render_fini(RenderState* render);
void render_draw(RenderState* render, char input[]);

#endif // !RENDER_H




