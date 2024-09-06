CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

BUILD_DIR = build
GCOV_BUILD_DIR = $(BUILD_DIR)/gcov_report
SRC_DIRS = functions

SRCS = $(wildcard matrix.c)
SRC_FILES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

TEST_SRCS = tests.c

OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
OBJ_FILES = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
TEST_OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(TEST_SRCS))

GCOV_OBJS = $(patsubst %.c, $(GCOV_BUILD_DIR)/%.o, $(SRCS))
GCOV_OBJ_FILES = $(patsubst %.c, $(GCOV_BUILD_DIR)/%.o, $(SRC_FILES))
GCOV_TEST_OBJS = $(patsubst %.c, $(GCOV_BUILD_DIR)/%.o, $(TEST_SRCS))

LIB_NAME = matrix
LIB_FILE = $(LIB_NAME).a

ifeq ($(shell uname), Darwin)
CHECK_LIB = -lcheck -lm -lpthread
else
CHECK_LIB = -lcheck -lm -lsubunit -lpthread -lrt
endif

all: create_dirs $(LIB_FILE) test gcov_report

create_dirs:
	@mkdir -p $(BUILD_DIR) $(foreach dir, $(SRC_DIRS), $(BUILD_DIR)/$(dir))

$(BUILD_DIR)/%.o: %.c | create_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_FILE): $(OBJS) $(OBJ_FILES)
	ar rcs $@ $^
	ranlib $@

test: $(OBJS) $(OBJ_FILES) $(TEST_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(CHECK_LIB)
	./test

gcov_report: create_gcov_dirs $(GCOV_OBJS) $(GCOV_OBJ_FILES) $(GCOV_TEST_OBJS)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(GCOV_OBJS) $(GCOV_OBJ_FILES) $(GCOV_TEST_OBJS) -o $(GCOV_BUILD_DIR)/test $(CHECK_LIB)
	$(GCOV_BUILD_DIR)/test
	gcov $(GCOV_BUILD_DIR)/tests.c
	lcov -t "gcov_report" -o $(GCOV_BUILD_DIR)/gcov_report.info -c -d $(GCOV_BUILD_DIR)
	genhtml -o $(GCOV_BUILD_DIR)/gcov_report $(GCOV_BUILD_DIR)/gcov_report.info
	open $(GCOV_BUILD_DIR)/gcov_report/index.html

create_gcov_dirs:
	@mkdir -p $(GCOV_BUILD_DIR) $(foreach dir, $(SRC_DIRS), $(GCOV_BUILD_DIR)/$(dir))

$(GCOV_BUILD_DIR)/%.o: %.c | create_gcov_dirs
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(LIB_FILE) test gcov_report.info tests.c.gcov

.PHONY: all clean test gcov_report create_dirs create_gcov_dirs