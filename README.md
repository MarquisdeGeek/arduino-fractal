# Arduino Fractal
A mandelbrot set generator for the Arduino with a TFT touch screen

This project is essentially a 'note to self' on using the TFT. The biggest issue
with running this is making sure the pins (XP, XM, YP, YM) are correct as they
change with every version of the hardware, it seems.

Depending on hardware, you might also need to reverse the Y co-ordinate in your
getPoint function, in the library code.

The first fractal drawn comes from memory, for speed. After this all Mandelbrots
are computed. There is a black line tracing its progress. You can touch the screen
at any point during a compute cycle to zoom in on that area.

All parameters are fixed.

MarquisdeGeek.com
