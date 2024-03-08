CXX= g++
CXXFLAGS= -std=c++20
LDFLAGS= -lstdc++ -lSDL2

all: fuzzy_engine

fuzzy_engine: main.o \
	bird.o \
	collider_component.o \
	collision_engine.o \
	fuzzy_engine_interface.o \
	game_object.o \
	graphics_engine.o \
	input_engine.o \
	physics_component.o \
	physics_engine.o \
	sprite_component.o \
	sprite_engine.o \
	test_platform.o \

	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o fuzzy_engine ./build/main.o \
	./build/bird.o \
	./build/collider_component.o \
	./build/collision_engine.o \
	./build/fuzzy_engine_interface.o \
	./build/game_object.o \
	./build/graphics_engine.o \
	./build/input_engine.o \
	./build/physics_component.o \
	./build/physics_engine.o \
	./build/sprite_component.o \
	./build/sprite_engine.o \
	./build/test_platform.o \


main.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./main.cpp -o ./build/main.o

bird.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./game_data/objects/player_object/bird.cpp -o ./build/bird.o

collider_component.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./includes/components/collider_component.cpp -o ./build/collider_component.o

collision_engine.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./includes/engines/collision_engine.cpp -o ./build/collision_engine.o

fuzzy_engine_interface.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./includes/shared_memory/fuzzy_engine_interface.cpp -o ./build/fuzzy_engine_interface.o

game_object.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./includes/objects/game_object.cpp -o ./build/game_object.o

graphics_engine.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./includes/engines/graphics_engine.cpp -o ./build/graphics_engine.o

input_engine.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./includes/engines/input_engine.cpp -o ./build/input_engine.o

physics_component.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./includes/components/physics_component.cpp -o ./build/physics_component.o

physics_engine.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./includes/engines/physics_engine.cpp -o ./build/physics_engine.o

sprite_component.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./includes/components/sprite_component.cpp -o ./build/sprite_component.o

sprite_engine.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./includes/engines/sprite_engine.cpp -o ./build/sprite_engine.o

test_platform.o: 
	 $(CXX) $(CXXFLAGS) $(LDFLAGS) -c ./game_data/objects/environment_objects/test_platform.cpp -o ./build/test_platform.o

clean: 
	 rm -f ./build/*.o fuzzy_engine