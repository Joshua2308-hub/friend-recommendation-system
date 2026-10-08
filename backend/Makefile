CC = gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
CPPFLAGS += -Iinclude
CORE = src/graph.c src/hashtable.c src/queue.c src/bfs.c src/heap.c src/sort.c src/stack.c src/trie.c src/unionfind.c
APP = $(CORE) src/recommend.c src/requests.c src/persistence.c src/json.c src/stats.c src/server.c src/main.c
ifeq ($(OS),Windows_NT)
TARGET = friendgraph.exe
TEST_GRAPH = test_graph.exe
TEST_RECOMMEND = test_recommend.exe
RUN_PREFIX = .\\
else
TARGET = friendgraph
TEST_GRAPH = test_graph
TEST_RECOMMEND = test_recommend
RUN_PREFIX = ./
endif
.PHONY: all test run clean
all: $(TARGET)
$(TARGET): $(APP)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $(APP) $(LDLIBS)
test_graph: tests/test_graph.c $(CORE)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(TEST_GRAPH) tests/test_graph.c $(CORE)
test_recommend: tests/test_recommend.c $(CORE) src/recommend.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(TEST_RECOMMEND) tests/test_recommend.c $(CORE) src/recommend.c
ifneq ($(IN_PROCESS_TEST),)
test:
	$(IN_PROCESS_TEST) -run -Iinclude tests/test_graph_all.c
	$(IN_PROCESS_TEST) -run -Iinclude tests/test_recommend_all.c
	$(IN_PROCESS_TEST) -run -Iinclude tests/test_api_all.c
else
test: test_graph test_recommend
	$(RUN_PREFIX)$(TEST_GRAPH)
	$(RUN_PREFIX)$(TEST_RECOMMEND)
endif
run: all
	$(RUN_PREFIX)$(TARGET)
clean:
	-del /Q test_graph.exe test_recommend.exe friendgraph.exe 2>NUL
	-rm -f test_graph test_recommend friendgraph
