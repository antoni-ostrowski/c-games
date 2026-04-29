
LDFLAGS = -L/opt/homebrew/opt/raylib/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
CFLAGS = -Wall -Wextra -std=c23 -pedantic -I/opt/homebrew/opt/raylib/include

points: ./points/points.c
	cc $(CFLAGS) $(LDFLAGS) -o points_bin ./points/points.c -fsanitize=address -g 

.PHONY: breakout points clean

breakout: ./breakout/breakout.c
	cc $(CFLAGS) $(LDFLAGS) ./breakout/breakout.c -o breakout_bin -fsanitize=address -g

clean:
	rm -f breakout_bin points_bin 
