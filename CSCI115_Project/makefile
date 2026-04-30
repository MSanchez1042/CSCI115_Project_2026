CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = project

SRC = project.cpp benchmark.cpp myGraph.cpp myPriorityQueue.cpp myQueue.cpp mySCList.cpp GraphAL.cpp Queue.cpp PriorityQueue.cpp

OBJ = $(SRC:.cpp=.o)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)