##
# Nicelog
#
# @file
# @version 0.1



TARGET := bin/nicelog.a
SRC := src/nicelog.c
OBJ := obj/nicelog.o
INCLUDE := -Iinclude

default: $(TARGET)
$(TARGET): $(OBJ)
	ar rcs $@ $^

$(OBJ): $(SRC)
	$(CC) $(INCLUDE) -c  -o $@ $^

clean:
	@rm -f $(OBJ) $(TARGET)

# end
