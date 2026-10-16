# CellCraft
A lightweight **Minecraft server that runs on PlayStation 3**, ported from UCraft (a Minecraft server implementation written in C, designed for machines with limited resources).


CellCraft implements just the bare essentials of the Minecraft protocol: clients can join,
explore a procedurally generated world, chat, and break and place blocks. It provides the
foundation for **very primitive Minecraft gameplay** — not a full server replacement.

Currently supports **Minecraft 26.2** clients

## Features

- **Runs on real PS3 hardware** (and RPCS3) — LV2 networking through a dedicated `wrapper_ps3.h` portability layer
- **Procedural terrain generation** — an explorable world generated on demand as players move around
- **Primitive Minecraft gameplay** — walk around, chat with other players, and break/place blocks
- **Online-mode encryption** — authenticated logins through mbedTLS, or offline mode without it
- **Tiny footprint** — fits comfortably in the PS3's memory

## Building for PS3

You need the PS3 toolchain with PSL1GHT and portlibs (zlib, mbedTLS) installed, e.g. at `/usr/local/ps3dev`:

```bash
git clone https://github.com/0xagvz/CellCraft.git
cd CellCraft
make            # server without Mojang auth (offline-capable clients)
make pkg        # builds build-ps3/CellCraft.pkg, installable on PS3
```

The package installs as `CellCraft` (`CELLCRAFT`) and listens on `*:25565`.
Run it and connect with a Minecraft 26.2 client in offline mode (or online mode with `AUTH=1`).

```bash
git submodule update --init 3rdparty/lwjson   # only needed for AUTH=1
```

## Building for PC (debug)

The original CMake build still works and is handy to tell port bugs apart from protocol bugs:

```bash
git submodule update --init --recursive
cmake -S . -B build/pc -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF
cmake --build build/pc --parallel
./build/pc/src/CellCraft
```

## Porting notes

- `include/CellCraft/wrapper_ps3.h` maps every `U_*` call to PSL1GHT (`net*` API, `SO_NBIO` non-blocking, `lv2errno` translation). The `FD_*` macros strip `SOCKET_FD_MASK` because LV2 indexes raw descriptors.
- PS3 is big-endian: the build passes `-DENDIAN=0`.
- `signal(SIGINT)` does not exist on PS3: shutdown goes through a `sysutil` callback (`SYSUTIL_EXIT_GAME`).
- Logs go to the PS3 TTY (`sysTtyWrite`, visible via ps3load / RPCS3).
- `lwjson` (2 pure-C files) compiles unmodified with `ppu-gcc`.

## Credits

- [vimpop](https://github.com/vimpop/UCraft) — creator of **UCraft**, the upstream project this is ported from. All game, protocol and world code is theirs.
- [Mojang](https://www.minecraft.net) — creators of Minecraft.
- [PSL1GHT](https://github.com/ps3dev/PSL1GHT) — the open-source PS3 SDK by the ps3dev team that makes this port possible.
- [Bixilon](https://bixilon.de/en) and [wiki.vg](https://wiki.vg/Main_Page) — for documenting Minecraft's protocol (via upstream UCraft).

## License

[MIT](LICENSE.txt) (same as upstream UCraft).
