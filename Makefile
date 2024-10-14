maze: maze.cc
	g++ maze.cc -o maze

.PHONY: run, clean

run: maze
	./maze

clean:
	rm -f maze
