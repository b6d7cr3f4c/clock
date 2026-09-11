# Clock

A simple terminal clock application written in C.

## Post-Install

```bash
git submodule update --init --recursive
```

## Compile

```bash
cc src/main.c src/app.c src/render.c external/miniaudio/miniaudio.c -o build/clock -lm -lpthread -Iexternal
```

## Run

```bash
./clock
```
