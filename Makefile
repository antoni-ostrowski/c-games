
LDFLAGS = -L/opt/homebrew/opt/raylib/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
CFLAGS = -Wall -Wextra -std=c23 -pedantic -I/opt/homebrew/opt/raylib/include

points: points.c
	cc $(CFLAGS) $(LDFLAGS) -o points points.c -fsanitize=address -g 

breakout: breakout.c
	cc $(CFLAGS) $(LDFLAGS) -o breakout breakout.c -fsanitize=address -g 
