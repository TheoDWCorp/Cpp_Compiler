CC = g++ -std=c++17 -lstdc++fs

bin = test_scanner

%.o : %.cpp 
	$(CC) -c $^ -o $@

$(bin): $(bin:%=%.o)
	$(CC) $^ -o $@

all: $(bin)

clean : 
	@rm -f $(bin)
	@rm -f $(bin).o