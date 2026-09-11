# Clock

A simple terminal clock application written in C.

## Compile

```bash
cc src/main.c src/app.c src/render.c external/miniaudio/miniaudio.c -o clock -lm -lpthread -Iexternal
```

## Run

```bash
./clock
```
