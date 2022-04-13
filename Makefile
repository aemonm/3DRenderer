build:
	mkdir dist
	clang -Wall -std=c99 src/*.c  -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -o ./dist/renderer
run:
	./dist/renderer
clean:
	rm -rf ./dist