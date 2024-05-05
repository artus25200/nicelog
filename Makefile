##
# Nicelog
#
# @file
# @version 0.1

SRC := $(shell find src -name *.c)
OBJ_DIR := obj
OBJ := $(SRC:%.c=%.o)
TARGET := bin/nicelog.a

default: clean makedir $(TARGET)

clean:
	@-rm -rf bin $(OBJ_DIR)

makedir:
	@mkdir bin
	@mkdir $(OBJ_DIR)

$(TARGET): $(OBJ)
	@echo $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(INCLUDE) -c $< -o $(OBJ_DIR)/$(notdir $@)

# end
