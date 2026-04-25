CXX = g++
CXXFLAGS = -std=c++17 -Wall

TARGET = poker

SRCS = main.cpp Casino.cpp Game.cpp Player.cpp Deck.cpp HandEvaluator.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)