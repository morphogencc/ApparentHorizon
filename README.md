# Apparent Horizon


## OSC Format
Listens for OSC messages on localhost (127.0.0.1), port 7000.

Current messages are:

- `/create/rect` -- creates a rectangle
- `/create/triangle` -- create an equilateral triangle (no value is random, otherwise 0-3 bottom, left, up, right)
- `/create/cube` -- create a cube
- `/camera/position/` -- move the camera to the position of the argument (starts at z = -2.0; negative z is forward)

Messages to be implemented are:
- `/create/righttriangle/` -- create a right triangle
- `/color/hue` -- set the current hue of the shapes
- `/color/saturation` -- set the current saturation of created shapes
- `/camera/heading/x/` -- set the camera's x heading
- `/camera/heading/y/` -- set the camera's y heading

The preferred OSC source is [Duration](http://duration.cc/); all fo the messages and values are configured to be
compatible with it.

Thus, all float messages require inputs from 0 - 1.

# TO DO
- Add cubes to projectable objects
- Add right triangles OSC message
- Add functions / OSC messages for moving camera angle
- Add second camera to each Perspective object
- Extend screen to two cameras / projectors
