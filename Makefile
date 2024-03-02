CXX= g++
CXXFLAGS= -std=c++20
LDFLAGS= -lstdc++

all: print_util

print_util: main.o \
	print_util.o \

	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o print_util ./build/main.o \
	./build/print_util.o \


main.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./src/main.cpp -o ./build/main.o

print_util.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./src/print_util.cpp -o ./build/print_util.o

