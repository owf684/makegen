rm makegen.a makegen.h.gch;
g++ --std=c++20 makegen.h;
ar rcs makegen.a makegen.h.gch;

