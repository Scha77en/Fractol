# Fractol

Fractol is a graphical program written in C as part of the 42 Network curriculum. It allows real-time exploration and visualization of various fractals, including Mandelbrot, Julia, and others. The project is an introduction to graphics programming, event handling, and mathematical visualization.

## Features

- Interactive display of Mandelbrot, Julia, and other fractals
- Real-time zoom, pan, and color changes
- Julia set parameter manipulation with mouse movement
- Support for multiple color palettes
- Bonus: Additional fractal types (e.g., Burning Ship)

## Installation

### Dependencies

- `minilibx` (the graphics library provided by 42)
- X11 (for Linux) or equivalent for macOS

### Build

```bash
make
```

## Usage

```bash
./fractol <fractal>
```
Available fractals:
- `mandelbrot`
- `julia`
- `burningship` (bonus)

Example:
```bash
./fractol mandelbrot
./fractol julia
```

## Controls

- Zoom in/out: Mouse scroll
- Move: Arrow keys or mouse drag
- Exit: ESC

## Bonus Features

- Extra fractal types (Burning Ship)
- More interactive controls (e.g., mouse drag, parameter change)

## Project Structure

- `src/` — source code
- `includes/` — header files
- `Makefile` — build instructions

## Author

- Scha77en

---
