# all:
# 	g++ -Isrc/Include -Lsrc/lib -w -Wl,-subsystem,windows -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

# all:
# 	g++ -Isrc/Include -Lsrc/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all:
	g++ -Isrc/Include -Lsrc/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
n:
	g++ -Isrc/Include -Lsrc/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2

cn:
	g++ -Isrc/Include -Lsrc/lib -o main main.c -lmingw32 -lSDL2main -lSDL2
r:
	./main

c:
	rm main
