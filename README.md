# Gravity Simulation

Simulation of gravity using the Barnes-Hut Algorithm and C++. Bodies are visualized using SFML.
When bodies are sufficiently close to each other, they collide elastically.

## Instructions
1. Clone this repository and enter the project directory.
2. Create a build directory: `mkdir build && cd build`
3. Use cmake to create a Makefile and build `cmake .. && cmake --build .`
4. Run the simulation using `./gravity [number of bodies] <theta threshold threads=1>`. Example: `./gravity 1000 0.5 4`

## Todo
[] Improve multithreading, so threads are not recreated on each frame. Instead, create `numThreads` worker threads when the simulation begins. For each tick, add the planets to the queue. When the queue is not empty, one of the workers will pop and process one planet from the queue.

![demo image](https://github.com/ryanp8/gravity/blob/main/assets/demo.png?raw=true)
