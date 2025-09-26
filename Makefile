CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -MMD -MP
LIBS = -lglfw

SRC = \
src/main.cpp \
include/glad/glad.c \
shaders/Shader.cpp \
utils/glfw.cpp \
utils/camera.cpp \
model/world.cpp \
model/Points.cpp \
model/private/Axis.cpp \
model/private/Grid.cpp \
model/private/Ground.cpp

OBJ = $(SRC:.cpp=.o)
OBJ := $(OBJ:.c=.o)
DEP = $(OBJ:.o=.d)

TARGET = main.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)
	rm -f $(OBJ) $(DEP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

-include $(DEP)