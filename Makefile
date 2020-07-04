tetris: main.o game_logic.o tetrimino.o draw.o
	g++ -o tetris main.o game_logic.o tetrimino.o draw.o \
	-DSFML_STATIC \
	-I include \
	-L lib \
	-lsfml-graphics-s \
	-lsfml-window-s \
	-lsfml-system-s \
	-lopengl32 \
	-lwinmm \
	-lgdi32 \
	-lfreetype \
	-ljpeg

main.o : main.cpp game_logic.h global_var.h
	g++ -c main.cpp -DSFML_STATIC \
	-I include \
	-L lib \
	-lsfml-graphics-s \
	-lsfml-window-s \
	-lsfml-system-s \
	-lopengl32 \
	-lwinmm \
	-lgdi32 \
	-lfreetype \
	-ljpeg

game_logic.o : game_logic.h global_var.h
	g++ -c game_logic.cpp -DSFML_STATIC \
	-I include \
	-L lib \
	-lsfml-graphics-s \
	-lsfml-window-s \
	-lsfml-system-s \
	-lopengl32 \
	-lwinmm \
	-lgdi32 \
	-lfreetype \
	-ljpeg

tetrimino.o : Tetrimino.h game_logic.h global_var.h
	g++ -c Tetrimino.cpp -DSFML_STATIC \
	-I include \
	-L lib \
	-lsfml-graphics-s \
	-lsfml-window-s \
	-lsfml-system-s \
	-lopengl32 \
	-lwinmm \
	-lgdi32 \
	-lfreetype \
	-ljpeg

draw.o : Draw.h global_var.h Tetrimino.h
	g++ -c Draw.cpp -DSFML_STATIC \
	-I include \
	-L lib \
	-lsfml-graphics-s \
	-lsfml-window-s \
	-lsfml-system-s \
	-lopengl32 \
	-lwinmm \
	-lgdi32 \
	-lfreetype \
	-ljpeg

clean :
	rm main.o game_logic.o draw.o tetrimino.o 