# Simple IoT LCD Game Creator for Learning

This project is a lightweight framework for building simple LCD games on ESP32 (and other microcontrollers) using:

- I2C LCD (`LiquidCrystal_I2C`)
- Rotary encoder (rotation for horizontal movement)
- Encoder push button (short press and long press)

The goal is to make game creation easier by providing reusable drawing, movement, collision, and menu/state logic.

## What Is Included

The `main` folder contains a modular `.ino` split:

- `main/main.ino`: hardware setup, input interrupt, global state, and main loop.
- `main/a_HelperFunctions.ino`: reusable object movement and drawing helpers.
- `main/z_Menus.ino`: choose menu and pause menu loops.
- `main/z_Switches.ino`: state/game switching logic.
- `main/g_Rocket.ino`: example game loop (`rocketLoop`).
- `main/g_Chase.ino`: example game loop (`chaseLoop`) with simple collision behavior.

## Core Concepts

### 1) `axis` and `object`

The framework models entities with:

- `axis`: stores `value`, `min`, `max`
- `object`: stores `x`, `y`, display `text`, `teleport` mode, and a generic `flag`

This keeps movement and rendering consistent across menus and games.

### 2) State machine

Main app states:

- `STATE_CHOOSE`: game selection screen
- `STATE_GAMING`: active game loop
- `STATE_PAUSED`: pause menu (hold button)

Game selector enum:

- `GAME_ROCKET`
- `GAME_CHASE`
- `GAME_COUNT` (must stay last)

### 3) Input model

- Rotary interrupt updates `direction` (`-1` / `+1`) and `rotatedEncoder`.
- Short press sets `pressedButton = true`.
- Long press (`buttonHeld = 1000 ms`) enters pause menu via `pausedSetup()`.
- Debounce uses `debounceDelay = 150 ms`.

## Helper API (from `a_HelperFunctions.ino`)

- `clearCustom(col, row, len)`: clears a custom LCD segment.
- `clearObj(obj)`: clears object text at current position.
- `updateObjectAxis(obj, ax, move)`: applies movement with boundary or teleport wrapping.
- `updateObjectPosition(obj, move_x, move_y)`: updates x/y together.
- `drawStaticObject(obj)`: prints object text at current coordinates.
- `drawMovingObject(obj)`: clears, moves by `obj.flag` on x, redraws.
- `drawRandomStaticObject(obj)`: randomizes x/y, redraws.
- `drawRandomMovingObject(obj)`: random step movement and redraw.
- `drawPlayerObject(obj)`: player control using encoder/button flags.
- `isCollision(a, b)`: exact coordinate collision check.

## Current Example Games

### Rocket

- Object: `"3=>"`
- Controlled by encoder/button through `drawPlayerObject()`
- Loop: `rocketLoop()`

### Chase

- Player: `"X"`
- Target: `"O"`
- When collision occurs, target respawns (flag reset behavior)
- Loop: `chaseLoop()`

## Hardware Notes

Current pin mapping in `main/main.ino`:

- `CLK = 35`
- `DT = 27`
- `BTN = 25`

LCD config:

- I2C address: `0x3F`
- size: `16x2`

If your board/wiring differs, change these constants in `main/main.ino`.

## How To Add a New Game

1. Create a new file in `main/`, for example `g_MyGame.ino`.
2. Implement your loop, for example `void myGameLoop(){ ... }`.
3. Add a title `object` in `main/main.ino`.
4. Add the title object to `chooseOpt[]`.
5. Add enum value to `Game` before `GAME_COUNT`.
6. Add a case in `switchGameLoop()` that calls your new loop.

Important: keep the order of entries in `chooseOpt[]` aligned with `enum Game`.

## Planned Expansion (More Controls)

My plan is to expand the control options over time.

Future updates may include support for additional input methods beyond the rotary encoder.

The goal is to keep the code simple while making game interaction more flexible.

## Compatibility

- Primary target: ESP32 + Arduino framework
- Likely portable to other Arduino-compatible boards with minor pin/interrupt adjustments

## License

See `LICENSE`.