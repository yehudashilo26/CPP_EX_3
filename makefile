
CXX=g++
CXXFLAGS=-std=c++11 -Werror -Wall -Wsign-conversion -g
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES = Demo2.cpp Board.cpp Catan.cpp Settlement.cpp Player.cpp Node.cpp Edge.cpp Card.cpp Hexagon.cpp Road.cpp
OBJS = $(SOURCES:.cpp=.o)

demo: $(OBJS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o demo $(OBJS)

catan: demo
	./demo

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $<
clean:
	rm -f demo *.o 

tidy:
	@echo "Running clang-tidy"
	@echo "-------------------------------"
	clang-tidy $(filter-out Test.cpp TestCounter.cpp , $(SOURCES)) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo
	@echo "Running valgrind"
	@echo "-------------------------------"
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

.PHONY: clean
