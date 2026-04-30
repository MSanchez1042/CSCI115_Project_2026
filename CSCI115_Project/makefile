CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = project

SRC = $(wildcard *.cpp)
OBJS = $(SRC:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)