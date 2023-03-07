#!/bin/bash
gcc -o main.app main.c $(sdl2-config --cflags --static-libs) 
./main.app
