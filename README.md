# C-Games

A collection of simple games built in C using [raylib](https://www.raylib.com/). I'm trying out making simple games while learning C :)

## Games

### Breakout

A breakout-style game where you control a paddle to hit blocks.

**Controls:**

- `←` / `→` - Move paddle
- `R` - Reset game

```bash
make breakout
./breakout_bin
```

### Points

Collect blocks by moving your rectangle around the screen.

**Controls:**

- `←` / `→` / `↑` / `↓` - Move
- `U` / `D` - Grow/shrink size
- `R` - Reset game

```bash
make points
./points_bin
```

## Building

Requires raylib installed (on macOS: `brew install raylib`).

```bash
make        # Build all games
make clean  # Remove binaries
```

## Requirements

- C compiler
- raylib library
