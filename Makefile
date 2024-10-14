CC = gcc
EXE = renderer

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj


CFLAGS = -I$(INC_DIR) -Wall -Wextra -Wshadow -Wdouble-promotion \
		 -Wformat=2 -Wformat-truncation=2 -Wundef -fno-common \
		 -Wstack-usage=255 -Wconversion -Os -ffunction-sections \
		 -fdata-sections -Wpadded -fno-short-enums

DEPS = $(wildcard $(INC_DIR)/*.h)

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(DEPS)
	mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	-rm -r $(OBJ)
	-rm -r $(EXE)
	-rmdir $(OBJ_DIR)