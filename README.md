# Gravity Simulation

Simulation of gravity using Barnes-Hut Algorithm, improving time complexity from O(n^2) to O(nlog(n)). Bodies are visualized using SFML.
When bodies are sufficiently close to each other, they collide elastically.

### Todo
- [x] Add multithreading
  - Once all the bodies have been added to the quadtree, their accelerations can be computed independently from each other.
- [ ] Improve multithreading
  - From testing, basic multithreading is inefficient. Threads should not be recreated on each frame.
  - New approach: create `numThreads` worker threads when the simulation begins and create a queue to store planets that must be processed. For each tick, add the planets to the queue. While the queue is not empty, each of the workers will pop and process planets from the queue. In progress: learn about locks, `std::condition_variable`.
- [ ] Fix collision checking
  - Collisions that should occur at an edge of a quadtree subregion are not detected because collisions are based on tree depth.
- [ ] Create models
  - [ ] Solar system that scales the view to the correct size and uses the proper distances/masses of the planets and the sun.
  - [ ] Two colliding galaxies

## Instructions
1. Clone this repository and enter the project directory.
2. Create a build directory: `mkdir build && cd build`
3. Use cmake to create a Makefile and build `cmake .. && cmake --build .`
4. Run the simulation using `./gravity [number of bodies] <theta threshold threads=1>`. Example: `./gravity 1000 0.5 4`

![demo image](https://github.com/ryanp8/gravity/blob/main/assets/demo.png?raw=true)
