# ood-game
rpg game - uni project

## Setup
1. **Requirements:**

    - Linux OS, probably would work on any popular distro (tested on arch, manjaro and ubuntu)
    - C++ 20
    - CMake 3.16 or newer
2. **Run:**

    run from repo directory:
    ```bash
    cmake -S . -B build
    cmake --build build
    ./build/rpg
    ```
    
    can also pass another config file:
    ```bash
    ./build/rpg <your_config_file_path>
    ```

    the game loads `config.ini` before startup:
    ```ini
    player_name=Ken
    log_file=logs/game.log
    ```



## Instruction
1. **Icons**:
    - Wall (`██`)
    - Player (`¶ `)
    - Enemy (` @`)
    - Items on the ground (` *`)
2. **Controls:**
    - to move use **WASD** keys
    - to pick up an item that is on the cell the ¶ is on press **E**
    - to drop of a item to the ground press **G**
    - to equip a weapon from invertory press **K**
    - to unquip a equiped weapon press **L**
    - to get info about item in the invetory press **I**
    - to battle enemy press **F**
    - to exit a game press **Q**
