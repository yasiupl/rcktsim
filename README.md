# rcktsim
Simple C++ 2D Rocket Simulation. School Project.


## Dependencies
* SFML

## Installation

On Arch:
    ```sudo pacman -S sfml```

On Ubuntu:
    ```sudo apt-get install libsfml-dev```

Then: ```make help```

![rcktsim](https://raw.githubusercontent.com/yasiupl/rcktsim/master/rcktsim.png)

## Gameplay

### Objective
    Shoot down as many enemy spacecraft and missles as possible.
    Your final score is the number of points acquired times the dificulty level.

### Controls
    F1 - Print help message
    W-S / Up-Down - Throttle Up-Down
    A-D / Left-Right - Rotate Left-Right
    E - Shoot rocket
    Space - Toggle engine thrust

### Dificulty levels
    
    1 - I'm too young to die - Enemies fly in straight lines, no missles
    2 - Hey, not too rough - Enemies try to follow you, no missles
    3 - Hurt me plenty - Enemies follow you, shoot missles that fly in straight lines
    4 - Ultra-violence - Enemies follow you, missles lock onto you
