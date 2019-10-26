CFLAGS=-ggdb
LIBS=-lSDL2 -lGLEW  -lOpenGL -lpthread
main:
	make -C gpu
	make -C gpu/rendering_lib
	g++  -c $(LIBS) $(CFLAGS) main.c -o main.o
	g++ -c $(LIBS) $(CFLAGS) mmu.c -o mmu.o
	g++ -c $(LIBS) $(CFLAGS) cpu/cpu.c -o cpu/cpu.o
	g++ gpu/gpu.o gpu/rendering_lib/shader.o gpu/rendering_lib/camera_out.o \
	gpu/rendering_lib/loadfile.o gpu/rendering_lib/display.o gpu/rendering_lib/model.o \
	gpu/rendering_lib/mesh.o gpu/rendering_lib/error.o gpu/rendering_lib/texture.o gpu/rendering_lib/stb_image.o gpu/rendering_lib/camera.o gpu/rendering_lib/render_public.o gpu/rendering_lib/render_manager.o main.o mmu.o cpu/cpu.o -o out $(LIBS)
run:
	$(MAKE) main
	./out
gdb:
	$(MAKE) main
	gdb ./out
