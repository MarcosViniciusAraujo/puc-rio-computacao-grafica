
TARGET = t

all: $(TARGET)

INC = -I. -I/Users/celes/Work/include -I/opt/homebrew/include 
LIB = -L.  -L/opt/homebrew/lib

CPP = CC
#CPPFLAGS = -O2 -Wall -std=c++17 -DGL_SILENCE_DEPRECATION 
CPPFLAGS = -g -Wall -std=c++17 -DGL_SILENCE_DEPRECATION 

SRC = \
  main.cpp \
  error.cpp \
  shader.cpp \
  buffer.cpp \

OBJ = $(addsuffix .o, $(basename $(SRC))) 

.cpp.o:
	$(CPP) $(INC) $(CPPFLAGS) -c $< -o $@ 

$(TARGET): $(OBJ) 
	$(CXX) $(LIB) -o $@ $(OBJ) -lstdc++ -lglfw3 -lopengl32 -lglu32 -lgdi32 -lglu32 -lfreeglut

clean:
	rm -f test $(OBJ) 


