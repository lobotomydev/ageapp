CC = g++
CFLAGS = `pkg-config --cflags gtk+-3.0` -std=c++11
LIBS = `pkg-config --libs gtk+-3.0`

TARGET = ageapp
SOURCE = age_app.cpp

$(TARGET): $(SOURCE)
	$(CC) $(SOURCE) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

deps-arch:
	sudo pacman -S gtk3 gcc

deps-debian:
	sudo apt install g++ libgtk-3-dev

deps-fedora:
	sudo dnf install gcc-c++ gtk3-devel

run:
	./$(TARGET)

.PHONY: clean install-deps_pacman install-deps_apt install-deps_dnf run