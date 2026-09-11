#include "app.h"

#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    Application app;

    if (app_init(&app) != 0) {
        return EXIT_FAILURE;
    }

    while (app.running) {

    }

    app_fini(&app);

    return EXIT_SUCCESS;
}
