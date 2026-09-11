#include "app.h"
#include <stdbool.h>

int app_init(Application* app) {
  if (render_init(&app->render) != 0) {
    return -1;
  }

  if (ma_engine_init(NULL, &app->audio) !=  MA_SUCCESS ) {
    return -1;
  }

  ma_engine_set_volume(&app->audio, 5.0);

  app->running = true;

  return 0;
}

void app_fini(Application* app) {
  ma_engine_uninit(&app->audio);
  render_fini(&app->render);

  app->running = false;
}

bool app_should_close(Application *app) {
 return  false;
}
