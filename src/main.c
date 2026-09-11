#include "app.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>

int main(int argc, char *argv[]) {
  int opt;
  int total_seconds;

  char *soundfile;

  while ((opt = getopt(argc, argv, "t:s:")) != -1) {
    switch (opt) {
    case 't':
      total_seconds = atoi(optarg);
      break;

    case 's':
      soundfile = optarg;
      break;

    default:
      fprintf(stderr, "Usage: %s [-t secs] [-s soundfile]\n", argv[0]);
      return EXIT_FAILURE;
    }
  }

  Application app;

  if (app_init(&app) != 0) {
    return EXIT_FAILURE;
  }

  ma_sound sound;
  struct timespec ts = {.tv_sec = 1};

  ma_sound_init_from_file(&app.audio, soundfile, 0, NULL, NULL, &sound);
  ma_sound_set_looping(&sound, MA_TRUE);

  while (app.running) {
    if (total_seconds >= 0) {
      int minutes = total_seconds / 60;
      int seconds = total_seconds % 60;

      char input[8];

      snprintf(input, sizeof(input), "%02d:%02d", minutes, seconds);

      render_draw(&app.render, input);

      if (total_seconds == 0) {
        if (!ma_sound_is_playing(&sound)) {
          ma_sound_start(&sound);
        }
      }

      nanosleep(&ts, NULL);
      total_seconds--;
    }
  }

  app_fini(&app);

  return EXIT_SUCCESS;
}
