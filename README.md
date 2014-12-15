# Apparent Horizon

Listens for OSC messages on localhost (127.0.0.1), port 7000.

Current messages are:

`/create/rect` -- creates a rectangle
`/create/triangle` -- create an equilateral triangle
`/create/cube` -- create a cube
`/camera/position/` -- move the camera to the position of the argument (starts at z = -2.0; negative z is forward)

Messages to be implemented are:
`/color/hue` -- set the current hue of the shapes
`/color/saturation` -- set the current saturation of created shapes
`/camera/heading/x/` -- set the camera's x heading
`/camera/heading/y/` -- set the camera's y heading

# TO DO
- Add cubes to projectable objects
- Add right triangles to projectable objects
- Add functions / OSC endpoint for moving camera angle
- Add second camera to each Perspective object
- Extend screen to two cameras / projectors
