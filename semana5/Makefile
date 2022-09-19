
TARGET = t

all: $(TARGET)

INC = -I. -I/opt/homebrew/include 
LIB = -L.  -L/opt/homebrew/lib

CPP = CC
#CPPFLAGS = -O2 -Wall -std=c++17 -DGL_SILENCE_DEPRECATION 
CPPFLAGS = -g -Wall -std=c++17 -DGL_SILENCE_DEPRECATION 

SRC = \
  arcball.cpp \
  camera.cpp \
  cube.cpp \
  cube_array.cpp \
  grid.cpp \
  error.cpp \
  light.cpp \
  objlight.cpp \
  material.cpp \
  node.cpp \
  scene.cpp \
  solar_syst.cpp \
  sphere.cpp \
  transform.cpp \
  main_glfw.cpp \

OBJ = $(addsuffix .o, $(basename $(SRC))) 

.cpp.o:
	$(CPP) $(INC) $(CPPFLAGS) -c $< -o $@ 

$(TARGET): $(OBJ) Makefile 
	$(CXX) $(LIB) -o $@ $(OBJ) -lglfw3 -lopengl32 -lglu32 -lgdi32 -lglu32 -lfreeglut

clean:
	rm -f $(TARGET) $(OBJ)


