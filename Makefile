all: rpg

rpg: main.cpp
	g++ -std=c++20 -Wall -Wextra -O2 main.cpp -o rpg

run: rpg
	./rpg

clean:
	rm -f rpg