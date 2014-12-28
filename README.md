# Apparent Horizon


## OSC Format
Listens for OSC messages on localhost (127.0.0.1), port 7000.

Current messages are:

- `/create/rect` -- creates a rectangle (0-8 for smaller rectangles)
- `/create/triangle` -- create an equilateral triangle (no value is random, otherwise 0-3 bottom, left, up, right)
- `/create/righttriangle/` -- create a right triangle (same values as above)
- `/camera/position/` -- move the camera to the position of the argument (starts at z = -2.0; negative z is forward)
- `/camera/heading value heading` where value is the angle to change our heading by, and the heading is 1 for 'x' and 2
  for 'y'.

Messages to be implemented are:
- `/color/saturation` -- set the current saturation of created shapes
- `/perspective/alpha value perspectiveId` -- set the alpha value of a perpsective `perspectiveId` (0 or 1 for now)

# TO DO
- Velocity --> hue for all shapes
- Master saturation OSC message
- How to keep tunnel continuous
- Get screen working on two cameras / monitors
- Line Thickness
- Replace brightness with alpha
- why do some shapes desaturate?
- Add cubes to projectable objects
