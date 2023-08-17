# Build all the tools
all:
	mkdir -p dist/tools
	gcc -o dist/tools/map src/tools/map.c
	gcc -o dist/tools/palettes src/tools/palettes.c
	gcc -o dist/tools/textnibs src/tools/textnibs.c
