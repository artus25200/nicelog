##
# Nicelog
#
# @file
# @version 0.1



TARGET := nicelog.a
SRC := nicelog.c
OBJ := nicelog.o


default: $(TARGET)
$(TARGET): $(OBJ)
	ar rcs $@ $^

$(OBJ): $(SRC)
	$(CC) -c  -o $@ $^

clean:
	@rm -f $(OBJ) $(TARGET)

# end
