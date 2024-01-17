CC = g++

CFLAGS = -Wall -Wextra -std=c++17

EXEC = testiki

LDLIBS = -lUnitTest++

SRCS = modAlphaCipher.cpp test.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
