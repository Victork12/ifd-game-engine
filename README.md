# IFD Game Engine

A C++ text-adventure engine that parses and runs games written in **IFD (Interactive Fiction Document)**, a custom XML-style markup format for defining rooms, items, enemies, merchants, and map connections in a plain-text file. The engine ships with a sample dungeon-crawler, *DragonCrawl*, to demonstrate the format.

Rather than hard-coding a single game, the engine reads any `.ifd` file at runtime and builds the world (rooms, links, items, enemies, shop inventory) from that file alone — new games can be authored without touching a line of C++.

## Features

- **Custom markup language parser** — a hand-written tokenizer/parser (`IFDParser`) reads nested `<tag>...</tag>` structures from plain text, including a comment syntax (`%`)
- **Dynamic map graph** — rooms ("areas") are linked in four directions (up/down/left/right) and built from the file at load time, including support for *rules* that rewrite the map at runtime (e.g. using an item permanently unlocks a new exit)
- **Two interchangeable player types** — `BasicPlayer` (no stats) and `HPSPPlayer` (Health Points / Sanity Points), selected per-game via the `<ptype>` tag, demonstrating polymorphism through a shared `Player` base class
- **Item system** — three item behaviors: `basic` (lore/flavor only), `use` (rewrites map links), and `consume` (modifies player stats)
- **Combat system** — enemies occupy rooms and attack on entry; the player can fight back with specific weapon items or attempt to escape
- **Merchant / shop system** — rooms can contain a merchant who sells weapons for in-game currency, collected by exploring rooms
- **Custom linked-list container** (`uLList`) — the inventory, room contents, and merchant stock are all backed by a hand-rolled unsorted linked list template, rather than `std::vector` or `std::list`

## Project Structure

```
ifd-game-engine/
├── main.cpp              # Entry point
├── Game.h                # Main game loop, command parser, player setup
├── IFDParser.h           # Tokenizes raw .ifd file text into a token stream
├── Map.h                 # Base map: areas, links, rule application (V1 engine)
├── MapV2.h               # Extended map: adds items, enemies, merchants on top of Map
├── Area.h                # A single room's data (description, currency, flags)
├── Player.h              # Abstract player base class
├── BasicPlayer.h         # Simple player implementation (no stats)
├── HPSPPlayer.h          # Player implementation with HP/Sanity and combat
├── Enemy.h                # Enemy data (name, description, damage, state)
├── Merchant.h            # Merchant/shop data
├── Item.h                # Abstract item base class
├── AttackItem.h          # Weapon items (sold by merchants)
├── UseItem.h              # "Use"-type items (rewrite map links)
├── ConsumeItem.h          # "Consume"-type items (modify player stats)
├── LinkData.h            # Helper struct for a room's 4-directional links
├── structs.h             # Shared plain structs (Rule, Effect)
├── ull.h                 # Custom unsorted linked-list container template
├── ifd-game-engine.cbp   # Code::Blocks project file
├── DragonCrawl3.ifd      # Sample game data file (see "Sample Game" below)
└── .gitignore
```

## Requirements

- A C++17-compatible compiler (e.g. `g++`, `clang++`, or MSVC)
- No external libraries — only the C++ standard library is used

## Building and Running

### Option A: Command line (Linux/macOS/WSL)

```bash
g++ -std=c++17 -o ifd-game-engine main.cpp
./ifd-game-engine
```

### Option B: Code::Blocks (Windows/Linux/macOS)

1. Open `ifd-game-engine.cbp` in [Code::Blocks](https://www.codeblocks.org/)
2. Build and run (F9), or Build (Ctrl+F9) then Run (Ctrl+F10)

### Running the game

On launch, the program will ask for a game file name:

```
Enter your gamefile name (i.e. filename.txt)
```

Type:

```
DragonCrawl3.ifd
```

> **Important — working directory matters.** The program looks for this file relative to whatever folder you *ran the executable from*, not the folder the executable itself lives in. If you built and ran it from the project's root folder (as shown in Option A above), `DragonCrawl3.ifd` will work as-is.
>
> If you're using an IDE (e.g. Code::Blocks) and it runs the program from a different folder — commonly `bin/Debug/` or `bin/Release/` — either:
> - Copy `DragonCrawl3.ifd` into that same build output folder, **or**
> - Type a path relative to that folder instead, e.g. `../../DragonCrawl3.ifd`
>
> As of this version, typing an incorrect or unreachable path now prints a clear `Error: could not open game file "..."` message instead of silently failing — if you see that error, it means the path you typed doesn't resolve from wherever the program is actually running.

## How to Play (Player's Manual)

Once the game loads, you'll see the description of your starting room, followed by a movement prompt. Type a command and press Enter.

### Movement

| Command | Effect |
|---|---|
| `u` | Move up |
| `d` | Move down |
| `l` | Move left |
| `r` | Move right |

If a direction has no exit, you'll see *"There appears to be no way to go that direction."* — this is often intentional (a dead end), not a bug. Some rooms only open new exits after you use a specific item there.

### Items

| Command | Effect |
|---|---|
| `search` | List the items currently in your room |
| `take` | Pick up an item from the room (you'll be asked which one) |
| `leave` (or `drop`) | Drop an item from your inventory into the current room |
| `inventory` | List everything you're currently carrying |
| `examine` | Show the description of an item in your inventory |
| `use` | Use a **use**-type item (these can permanently change the map, e.g. unlocking doors) |
| `consume` | Consume a **consume**-type item (these affect your stats — healing, damage, etc.) |

When prompted for an item name, type it exactly as shown by `search` or `inventory` (case-sensitive, e.g. `Silver Bell`).

### Combat

If an enemy is in your room and still alive, it attacks automatically when you enter. You'll be prompted:

```
Attack <Enemy Name> with:
```

Type the exact name of a weapon in your inventory (e.g. `Sword` or `Dagger`) to fight back, or type `escape` to flee back the way you came. Weapons must be bought from a merchant before combat — you do not start the game with one.

### Merchants

| Command | Effect |
|---|---|
| `interact` | Talk to the merchant in your current room (only works in rooms with a merchant) |

You'll see the merchant's stock and prices, and be asked if you'd like to buy something. Currency is collected automatically the first time you enter a new room.

### Other Commands

| Command | Effect |
|---|---|
| `stats` | Show your current stats (HP/Sanity, if playing as an HPSP player) |
| `reset` | Restart the game from the first room (keeps the same loaded file) |
| `help` | Show the in-game command list |
| `iseedeadpeople` | Cheat code — reveals the entire map and all room connections |
| `exit` | Quit the game |

### Walkthrough Tip for the Sample Game

The starting room in `DragonCrawl3.ifd` has no exits at first — `search`, then `take` the **Silver Bell**, then `use` it to unlock all four doors. Visit the merchant (`interact`) before heading into the dungeon, since the first enemy encounter requires a weapon to survive.

## The IFD Format, Briefly

IFD is a custom tag-based format (similar in spirit to HTML/XML, but simpler) for describing a text-adventure game's world in a plain-text file:

- `<game>...</game>` wraps the entire file
- `<area>...</area>` defines one room, with a `<desc>` and `<feats>` (insta-death / goal flags)
- `<links>...</links>` defines the four-directional connections between every room, in room order
- `<item>...</item>` defines an in-game item, nested inside a `basic`, `use`, `consume`, or `attack` type tag
- `<enemy>...</enemy>` and `<merch>...</merch>` define enemies and shop inventories
- Lines starting with `%` are comments and are ignored by the parser

See the contents of `games/DragonCrawl3.ifd` for a complete working example.

## Bug Fixes Applied

This codebase was reviewed and the following correctness issues were found and fixed:

| Issue | File | Problem | Fix |
|---|---|---|---|
| Heap use-after-free | `HPSPPlayer.h` (`buy()`) | The merchant's item node was deleted, then its price was read from the now-freed pointer immediately after — causing an intermittent crash whenever a player bought an item | Cache the item's price in a local variable *before* deleting the node |
| Operator precedence bug | `HPSPPlayer.h` (`Combat()`) | `found && n != "Sword" \|\| n != "Dagger"` was parsed as `(found && n != "Sword") OR (n != "Dagger")`, which is true for nearly any input — making combat almost always reject valid attacks and never resolve | Corrected to use `&&` throughout, so both conditions are required as originally intended |
| Process killed silently | `HPSPPlayer.h` (`Combat()`) | Re-entering a room with an already-defeated enemy called `exit(0)`, terminating the entire program with no message | Replaced with a normal `return`, so combat is simply skipped for dead enemies |
| Dangling `else` (logic bug) | `BasicPlayer.h` (`consume()`) | A missing pair of `{ }` meant `return;` executed unconditionally after the `else`, so a successfully consumed item's "active message" text was never printed | Added braces so the `return` is correctly scoped to the `else` branch only |
| Undefined return value | `BasicPlayer.h` (`getPlayerMoney()`, `Combat()`) | Both functions had a non-`void` return type but no `return` statement, which is undefined behavior in C++ | Added explicit return values (`BasicPlayer` does not track money or support combat, so these return safe defaults) |
| Misleading indentation | `ull.h` (`deleteNode()`) | `delete current;` was indented as if scoped inside an `if`, but actually ran unconditionally — functionally harmless here, but misleading for future maintainers | Re-indented to match actual control flow |
| Silent failure on bad file path | `IFDParser.h` (`tokenIt()`) | If the game file path didn't resolve, the program never checked whether the file actually opened — it just silently parsed zero tokens, making it look like the program had hung or done nothing | Added an explicit open-check that prints a clear error message and exits if the file can't be found |

All fixes were verified with [AddressSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer) and manual playthroughs (buying a weapon, fighting and defeating an enemy, using and consuming items, resetting the game).

## Possible Future Improvements

- Replace remaining `int i` / `vector::size()` comparisons with `size_t` to silence sign-comparison warnings
- Add a proper "Game Over" / "You Win" screen instead of ending via early `return`
- Persist player progress to a save file
- Add unit tests for the `IFDParser` tokenizer and `Map` link-building logic
- Validate `.ifd` files against the format spec before loading, with clearer error messages on malformed input

## Authors

Originally created as a course project. IFD format originally specified by Dr. Ray, extended (v3) for items, enemies, and merchants.

## License

This project is shared for educational and portfolio purposes.
