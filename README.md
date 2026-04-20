# cub3D

`cub3D` is a 3D raycasting engine built in C with the MLX42 graphics library. The program reads a `.cub` map file, validates the level layout and resources, then renders a first-person view of the maze with textured walls, ceiling and floor colors, player movement, rotation, and a minimap overlay.

## Screenshots

![Gameplay](Screenshot%202026-04-20%20104428.png)

## Features

- Parses `.cub` configuration files
- Loads four wall textures from the map file
- Supports floor and ceiling RGB colors
- Renders a Wolfenstein-style raycasted scene
- Handles player movement and collision detection
- Displays a toggleable minimap

## Requirements

- A C compiler such as `cc` or `clang`
- `make`
- CMake and the build tools required by MLX42
- GLFW and the libraries needed by your system to build MLX42

The Makefile automatically clones and builds the bundled `libraries` dependency and `MLX42` if they are missing.

## Build

From the project root:

```bash
make
```

This produces the `cub3D` executable.

To clean generated files:

```bash
make clean
make fclean
make re
```

## Run

Launch the program with a valid `.cub` file:

```bash
./cub3D maps/map.cub
```

You can also try the other sample maps in the `maps/` directory.

## Controls

- `W` - move forward
- `S` - move backward
- `A` - strafe left
- `D` - strafe right
- `Left Arrow` - rotate left
- `Right Arrow` - rotate right
- `M` - toggle the minimap
- `Esc` - close the window

## Map Format

The parser expects a `.cub` file with this structure:

1. Four texture paths:
	- `NO` north wall texture
	- `SO` south wall texture
	- `WE` west wall texture
	- `EA` east wall texture
2. Two color definitions:
	- `F r,g,b` for the floor
	- `C r,g,b` for the ceiling
3. A map made of:
	- `1` for walls
	- `0` for empty spaces
	- one player start position: `N`, `S`, `E`, or `W`
	- spaces for padding around the map shape

Example:

```text
NO textures/north.png
SO textures/south.png
WE textures/west.png
EA textures/east.png

F 220,100,0
C 225,30,0

111111
100001
10N001
111111
```

The map must be fully closed and contain exactly one player start position.

## Project Structure

- `src/parsing/` - file validation, map parsing, and map checks
- `src/init/` - game initialization and resource setup
- `src/raycasting/` - ray casting and scene rendering
- `src/execution/` - movement, input handling, minimap, texture rendering
- `src/rests/` - shared utility helpers
- `inc/` - project headers and data structures
- `maps/` - sample `.cub` maps
- `textures/` - texture assets

## Notes

- The game uses a fixed window size of `1600x1080`.
- Player movement is blocked by wall tiles.
- The minimap is rendered on top of the 3D view when enabled.
