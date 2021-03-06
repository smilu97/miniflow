CC := g++
CFLAGS := -I headers --std=c++17
MODS := graph array util ops
TESTS := graph op broadcast
SRCS := $(foreach mod, $(MODS), cpp/$(mod).cc)
OBJS := $(foreach mod, $(MODS), cpp/$(mod).o)
TEST_SRCS := $(foreach test, $(TESTS), tests/test_$(test).cc)
TEST_OBJS := $(foreach test, $(TESTS), tests/test_$(test).o)

all: test

.cc.o:
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(OBJS) $(TEST_OBJS)
	for testo in $(TEST_OBJS) ; do \
		$(CC) $(CFLAGS) $(OBJS) $$testo -o test ; \
		./test ; \
	done
	make clean

clean:
	@rm $(OBJS) $(TEST_OBJS)