LIBS=-lSDL2 -lGLEW  -lOpenGL -lpthread
main:
	make -C gpu
	g++  -c $(LIBS) main.c -o main.o
	g++ -c $(LIBS) mmu.c -o mmu.o
	g++ -c $(LIBS) cpu.c -o cpu.o
	g++ gpu/main.o gpu/shader.o gpu/camera_out.o gpu/loadfile.o gpu/display.o gpu/model.o gpu/mesh.o gpu/error.o gpu/texture.o gpu/stb_image.o gpu/camera.o gpu/render_public.o gpu/render_manager.o main.o mmu.o cpu.o -o out $(LIBS)
run:
	$(MAKE) main
	./out
gdb:
	$(MAKE) main
	gdb ./out
