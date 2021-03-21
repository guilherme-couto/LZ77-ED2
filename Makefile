CXX_COMPILER = g++

INCLUDE_DIRS = -I./include

CXX_FLAGS    = -std=c++17 -g $(INCLUDE_DIRS)


# source files
srcfiles        := $(wildcard *.cpp) $(wildcard src/*.cpp)
objects         := $(patsubst %.cpp, %.o, $(srcfiles))


grafos: $(objects)
	$(CXX_COMPILER) -o lz77 $(CXX_FLAGS) $(objects) $(LDFLAGS)

clean:
	rm -f $(objects) lz77
#
# How to compile C++
#
%.o : %.cpp
	@echo "Compiling C++ "$<"..."
	$(CXX_COMPILER) $(CXX_FLAGS) -c $< -o $@
