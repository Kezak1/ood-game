all: rpg

SRC := $(wildcard src/*.cpp)

rpg: $(SRC)
	g++ -std=c++20 -Wall -Wextra -O2 $(SRC) -o $@

run: rpg
	./rpg

clean:
	rm -f rpg
