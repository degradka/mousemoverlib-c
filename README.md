# movecursor-c
build:
gcc -o movecursor movecursor.c -lX11 -lXtst -lXinerama
run:
./movecursor {monitor number: 0} {x coords: 100} {y coords: 100}
