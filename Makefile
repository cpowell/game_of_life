PROG=gol
CXX=g++
ifneq (,$(shell which clang 2>/dev/null))
CXX=clang++
endif # clang
CXXFLAGS=-std=c++11 -stdlib=libc++

ifeq ($(shell uname), Linux)
LIBS+= -lrt
endif

all:  release

release: game_of_life/board.cpp game_of_life/main.cpp
	$(CXX) -O2 -DNDEBUG -D_CONSOLE $(CXXFLAGS) -o $(PROG) $^ -ltbb $(LIBS)

debug: game_of_life/board.cpp game_of_life/main.cpp
	$(CXX) -O0 -D_CONSOLE -g -DTBB_USE_DEBUG  $(CXXFLAGS) -o $(PROG) $^ -ltbb $(LIBS)

clean:
	rm -f $(PROG) *.o *.d
	rm -rf *.dSYM


