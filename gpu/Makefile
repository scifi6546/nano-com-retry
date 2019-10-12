CC=g++
LIBS=-lSDL2 -lGLEW  -lOpenGL
CFLAGS=-I -w -ggdb
main: main.cpp 
	$(CC) -c $(CFLAGS) main.cpp -o main.o
	$(MAKE) shader
	$(MAKE) loadfile
	$(MAKE) render_manager
	$(MAKE) camera_out
	$(MAKE) error
	$(MAKE) render_public
	$(MAKE) model
	$(CC) -c $(CFLAGS) display.cpp -o display.o
	$(CC) -c $(CFLAGS) texture.cpp -o texture.o
	$(CC) -c $(CFLAGS) mesh.cpp -o mesh.o
	$(CC) -c $(CFLAGS) stb_image.c -o stb_image.o
	$(CC) -c $(CFLAGS) camera.cpp -o camera.o
	$(CC) $(CFLAGS) main.o shader.o camera_out.o loadfile.o display.o model.o mesh.o error.o texture.o stb_image.o camera.o render_public.o render_manager.o -o out $(LIBS)
run:
	$(MAKE) main
	./out
gpu:
	$(MAKE) main
	optirun ./out
game_engine: game_engine.cpp
	$(CC) -c $(CFLAGS) game_engine.cpp -o game_engine.o

model: model.cpp
	$(CC) -c $(CFLAGS) model.cpp -o model.o
shader: shader.cpp
	$(CC) -c $(CFLAGS) shader.cpp -o shader.o
camera_out: camera_out.cpp
	$(CC) -c $(CFLAGS) camera_out.cpp -o camera_out.o
loadfile: loadfile.cpp
	$(CC) -c $(CFLAGS) loadfile.cpp -o loadfile.o
world_gen: world_gen.cpp
	$(CC) -c $(CFLAGS) world_gen.cpp -o world_gen.o
render_manager:
	$(CC) -c $(CFLAGS) render_manager.cpp -o render_manager.o
physics:
	$(CC) -c $(CFLAGS) physics.cpp -o physics.o
entity:
	$(CC) -c $(CFLAGS) entity.cpp -o entity.o
player:
	$(CC) -c $(CFLAGS) player.cpp -o player.o
error:
	$(CC) -c $(CFLAGS) error.cpp -o error.o
render_public:
	$(CC) -c $(CFLAGS) render_public.cpp -o render_public.o
gui_element:
	$(CC) -c $(CFLAGS) gui_element.cpp -o gui_element.o
debug:
	$(MAKE) main
	gdb out
all:
	$(MAKE) main
