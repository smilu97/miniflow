CC := g++
CFLAGS := -I headers --std=c++14
MODS := graph array util
TESTS := graph op
SRCS := $(foreach mod, $(MODS), cpp/$(mod).cc)
OBJS := $(foreach mod, $(MODS), cpp/$(mod).o)
TEST_SRCS := $(foreach test, $(TESTS), tests/test_$(test).cc)
TEST_OBJS := $(foreach test, $(TESTS), tests/test_$(test).o)

.cc.o:
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(OBJS) $(TEST_OBJS)
	for testo in $(TEST_OBJS) ; do \
		$(CC) $(CFLAGS) $(OBJS) $$testo -o test ; \
		./test ; \
	done

clean:
	@rm $(OBJS) $(TEST_OBJS)