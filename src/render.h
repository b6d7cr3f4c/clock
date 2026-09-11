#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

typedef struct {
  struct termios orig_termios;
  int rows;
  int cols;
} RenderState;

int render_init(RenderState* render);
void render_fini(RenderState* render);
void render_draw(RenderState* render);

#endif // !RENDER_H




