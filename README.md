# CellCraft
<p align="center">
  <img src="assets/icon.png" alt="CellCraft logo" width="128" />
</p>

A lightweight **Minecraft server that runs on PlayStation 3**, ported from UCraft (a Minecraft server implementation written in C, designed for machines with limited resources).


CellCraft implements just the bare essentials of the Minecraft protocol: clients can join,
explore a procedurally generated world, chat, and break and place blocks. It provides the
foundation for **very primitive Minecraft gameplay** — not a full server replacement.

Currently supports **Minecraft 26.2** clients

You will need to have HEN or CFW in your ps3
## Features

- **Runs on real PS3 hardware** (and RPCS3) — LV2 networking through a dedicated `wrapper_ps3.h` portability layer
- **Procedural terrain generation** — an explorable world generated on demand as players move around
- **Primitive Minecraft gameplay** — walk around, chat with other players, and break/place blocks
- **Online-mode encryption** — authenticated logins through mbedTLS, or offline mode without it
- **Tiny footprint** — fits comfortably in the PS3's memory

## Limitations

- **Worlds are not saved.** Terrain regenerates identically from the seed on every boot, but blocks you break or place only live in RAM and are lost when the server stops.

## Building for PS3

You need the PS3 toolchain with PSL1GHT and portlibs (zlib, mbedTLS) installed, e.g. at `/usr/local/ps3dev`:

```bash
git clone https://github.com/0xagvz/CellCraft.git
cd CellCraft
make            # server without Mojang auth (offline-capable clients)
make pkg        # builds build-ps3/CellCraft.pkg, installable on PS3
```

The package installs as `CellCraft` (`CELLCRAFT`) and listens on `*:25565`.
Run it and connect with a Minecraft 26.2 client.

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

## Credits

- [vimpop](https://github.com/vimpop/UCraft) — creator of **UCraft**, the upstream project this is ported from. All game, protocol and world code is theirs.
- [Mojang](https://www.minecraft.net) — creators of Minecraft.
- [PSL1GHT](https://github.com/ps3dev/PSL1GHT) — the open-source PS3 SDK by the ps3dev team that makes this port possible.
- [Bixilon](https://bixilon.de/en) and [wiki.vg](https://wiki.vg/Main_Page) — for documenting Minecraft's protocol (via upstream UCraft).

## License

[MIT](LICENSE.txt) (same as upstream UCraft).
