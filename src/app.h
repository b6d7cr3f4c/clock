#ifndef APP_H
#define APP_H

#include "miniaudio/miniaudio.h"
#include "render.h"

#include <stdbool.h>

enum Mode {
  STOPWATCH,
  TIMER,
};

typedef struct {
  enum Mode current_mode;
  ma_engine audio;
  RenderState render;

  bool running;
} Application;

int app_init(Application* app);
void app_fini(Application* app);
bool app_should_close(Application* app);

#endif // !APP_H
