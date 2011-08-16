CC = g++
LIBS = -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -mwindows libSDL_gfx.dll
INCLUDE = -Iinclude -IC:/MinGW/include/SDL
OFILES = bin/main.o \
	bin/CollisionSystem.o \
	bin/EventHandler.o \
	bin/FontRender.o \
	bin/GameMain.o \
	bin/GameState.o \
	bin/MenuState.o \
	bin/Player.o \
	bin/Recorder.o \
	bin/SoundManager.o \
	bin/Sprite.o \
	bin/StateTest.o \
	bin/TextObject.o

bin/ggj: $(OFILES)
	$(CC) -o bin/ggj.exe $(OFILES) $(LIBS)

bin/%.o: src/%.cpp
	$(CC) $(INCLUDE) -o $@ -c $?

clean:
	rm $(OFILES) bin/ggj.exe

tags : 
	ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .
