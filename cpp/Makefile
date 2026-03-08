CC = g++
CFLAGS = -Iinclude -std=c++20

# --- Bridge Rules (Allows you to skip the folder names in terminal) ---

%.o: build/%.o
	@:

%.exe: bin/%.exe
	@:

# --- Build Rules ---

# Links the object files and creates the exe in bin/
bin/main.exe : build/oscillator.o build/simulation.o build/main.o
	$(CC) $^ -o $@

# Compiles source files from src/ into object files in build/
build/%.o : src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Dependencies
build/oscillator.o : src/oscillator.cpp
build/simulation.o : src/simulation.cpp  src/oscillator.cpp
build/main.o : src/main.cpp src/simulation.cpp src/oscillator.cpp

clean:
	if exist bin\*.exe del /Q /F bin\*.exe
	if exist build\*.o del /Q /F build\*.o