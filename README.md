# ood-game
rpg game - uni project

## Setup
1. **Requirements:**

    - Linux OS, probably would work on any popular distro (tested on arch, manjaro and ubuntu)
    - C++ 20
    - CMake 3.16 or newer
2. **Build:**
    ```bash
    cmake -S . -B build
    cmake --build build
    ```
3. **Run:**
    
    to start as server (default port is `5555`)
    ```bash
    ./build/rpg --server [port]
    ```
    
    to start as client (default ip:port is `[127.0.0.1:5555]`)
    ```bash
    ./build/rpg --client [ip:port]
    ```

    **note:** the game loads `config.ini`

## Instruction
1. **Icons**:
    - Wall (`██`)
    - Player ( e.g `3 `)
    - Enemy (` @`)
    - Item(s) on the ground (`* `)
2. **Controls:**
    - to move use **WASD** keys
    - to pick up an item that is on the cell the ¶ is on press **E**
    - to drop of a item to the ground press **G**
    - to equip a weapon from invertory press **K**
    - to unquip a equiped weapon press **L**
    - to get info about item in the invetory press **I**
    - to battle enemy press **F**
    - to get full logs press **J**
    - to exit a game press **Q**
