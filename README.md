*This project has been created as part of the 42 curriculum by lsadikaj.*

# FDF

## Description

FDF is a graphics project about building a wireframe model of a 3D landscape from a 2D grid of altitude points. The program reads a `.fdf` map file, where each value represents the altitude (z) of a point on the grid, and connects neighboring points with line segments to form a mesh. The result is rendered in real time using the school's MiniLibX library.

The mandatory part renders the landscape in isometric projection. The bonus part adds an alternative spherical projection, camera controls (zoom, translation, rotation), per point coloring with gradient interpolation, and a few extra display options.

## Instructions

### Requirements

- Linux or macOS
- MiniLibX (system version or bundled sources, handled automatically by the Makefile)
- X11 development libraries (Linux) or Metal / Cocoa frameworks (macOS)
- `cc` / `gcc` with `-Wall -Wextra -Werror`
- `make`

### Compilation

```
git clone <repository-url> fdf
cd fdf
make
```

The Makefile detects the OS automatically, builds `libft` and MiniLibX if needed, then compiles and links the project. It does not relink unnecessarily.

### Execution

```
./fdf maps/<map_name>.fdf
```

The program takes a single argument: a map file in `.fdf` format.

### Controls

| Key | Effect |
|---|---|
| Arrow keys | Translate the model |
| `+` / `-` | Zoom in / out |
| `W` / `S` | Rotate around the X axis |
| `A` / `D` | Rotate around the Y axis |
| `Page Up` / `Page Down` | Increase / decrease altitude scale |
| `P` | Toggle between isometric and spherical projection |
| `Space` | Cycle through color palettes |
| `H` | Toggle wireframe line visibility |
| `ESC` | Closes the window and exits cleanly |
| Red cross (window frame) | Closes the window and exits cleanly |

## Map file format (.fdf)

Each line of the file is a row of the grid, and each value in a row is a point separated by spaces. The value is the altitude (z) of the point at that position; its column and row indexes give the x and y coordinates.

```
0 0 0 0 0
0 10 10 10 0
0 10 20 10 0
0 10 10 10 0
0 0 0 0 0
```

A point can optionally be given an explicit color by appending a comma followed by a hexadecimal RGB value, for example `10,FF0000`. When no color is given, the point is colored automatically through gradient interpolation based on the altitude of its neighbors.

## Supported features

**Mandatory**

- Parsing of `.fdf` map files into a grid of 3D points
- Wireframe rendering by connecting neighboring points with line segments
- Isometric projection
- Smooth window management (minimizing, switching focus, etc.)
- Clean exit on `ESC` and on closing the window

**Bonus**

- Extra spherical projection, toggled with `P`
- Zoom in and out
- Translation of the model
- Rotation around the X and Y axes
- Per point color parsing, with gradient interpolation between connected points
- Multiple color palettes, cycled with `Space`
- Toggleable line visibility

## Resources

- MiniLibX documentation (42 school library), the primary reference for opening a window, creating images, and handling keyboard and mouse events.
- Bresenham's line algorithm, used to draw the line segments pixel by pixel between two points.
- General references on isometric and spherical projection math.

### Use of AI

AI was used as a learning aid rather than a code generator, mainly to clarify specific points through iteration: how the MiniLibX event hooks work, the math behind isometric and spherical projection, how to derive and implement Bresenham's algorithm, and how to debug a segmentation fault caused by a mismatch between the image buffer size and the bounds checked in the pixel drawing function. The goal throughout was to understand every part of the project well enough to explain and defend it, not to produce code that would be copied without understanding.