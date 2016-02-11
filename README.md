# ceres-emscripten
Builds a small C++ program that uses Ceres.
Uses emscripten to target js.

## Building
Configure and build the javascript target by running `./build_js.sh`.

## ToDos
- Learn how to use Embind or WebIDL to generate a nice JS interface to C++ code
- Implement a simple interface that involves running the solver for a fixed amount of time inside the render loop
  - e.g. a circle that wants to be exactly 2 units away from the mouse

