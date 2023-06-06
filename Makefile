all: chess

chess: main.cpp board.cpp
	g++ main.cpp board.cpp -o chess -lraylib

.PHONY: clean
clean:
	rm -rf chess
