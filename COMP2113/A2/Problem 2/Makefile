FLAGS = -pedantic-errors -std=c++11

TARGET = gradecounter
OBJECTS = gradebook.o main.o

gradebook.o: gradebook.cpp gradebook.h
	g++ $(FLAGS) -c $<
main.o: main.cpp gradebook.h
	g++ $(FLAGS) -c $<
$(TARGET): $(OBJECTS)
	g++ $(FLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)
