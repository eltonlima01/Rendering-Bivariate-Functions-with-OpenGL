CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++17 -MMD -MP -Iinclude/imgui -Iinclude/imgui/backends
LIBS = -lglfw

SRC = src/main.cpp \
	include/glad/glad.c \
	shaders/Shader.cpp \
	utils/glfw.cpp \
	utils/camera.cpp \
	model/world.cpp \
	model/points.cpp \
	model/private/Axis.cpp \
	model/private/Grid.cpp \
	model/private/Ground.cpp

SRC += include/imgui/imgui.cpp \
	include/imgui/imgui_draw.cpp \
	include/imgui/imgui_tables.cpp \
	include/imgui/imgui_widgets.cpp \
	include/imgui/backends/imgui_impl_glfw.cpp \
	include/imgui/backends/imgui_impl_opengl3.cpp \

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