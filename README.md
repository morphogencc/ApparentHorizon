# Apparent Horizon


## OSC Format
Listens for OSC messages on localhost (127.0.0.1), port 7000.

Current messages are:

- `/create/rect` -- creates a rectangle (0-8 for smaller rectangles)
- `/create/triangle` -- create an equilateral triangle (no value is random, otherwise 0-3 bottom, left, up, right)
- `/create/righttriangle` -- create a right triangle (same values as above)
- `/shape/speed` -- set shape speed
- `/shape/rotationspeed` -- set shape rotation speed
- `/color/saturation` -- set the current saturation of created shapes
- `/camera/position` -- move the camera to the position of the argument (starts at z = -2.0; negative z is forward)
- `/camera/heading value heading` where value is the angle to change our heading by, and the heading is 1 for 'x' and 2
  for 'y'.
- `/perspective/left/alpha value` -- set the alpha value of the 'left' perspective
- `/perspective/right/alpha value` -- set the alpha value of the 'right' perspective
