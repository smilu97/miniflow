CC := g++
CFLAGS := -I headers --std=c++14
MODS := graph array
TESTS := graph
SRCS := $(foreach mod, $(MODS), cpp/$(mod).cc)
OBJS := $(foreach mod, $(MODS), cpp/$(mod).o)
TEST_SRCS := $(foreach test, $(TESTS), cpp/test_$(test).cc)
TEST_OBJS := $(foreach test, $(TESTS), cpp/test_$(test).o)

.cc.o:
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(SRCS) cpp/test_graph.cc -o test/test_graph
	test/test_graph

clean:
	@rm $(OBJS) $(TEST_OBJS)