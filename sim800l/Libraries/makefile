# dyn. lib name
LIB_NAME = libsim800l.dll
# my catalogues
SIM800L_SRC_DIR = Libraries/sim800l_lib/src
SIM800L_INC_DIR = Libraries/sim800l_lib/inc
SIM800L_CONFIG_DIR = Libraries/sim800l_lib/config
LCD5110_SRC_DIR = Libraries/lcd5110_lib/src
LCD5110_INC_DIR = Libraries/lcd5110_lib/inc
BUILD_DIR = build

CC = gcc
CFLAGS = -Wall -shared -I$(SIM800L_INC_DIR) -I$(SIM800L_CONFIG_DIR) -I$(LCD5110_INC_DIR)
LDFLAGS = -shared

# Source and object files
SIM800L_SRC_FILES = $(wildcard $(SIM800L_SRC_DIR)/*.c)
LCD5110_SRC_FILES = $(wildcard $(LCD5110_SRC_DIR)/*.c)
SRC_FILES = $(SIM800L_SRC_FILES) $(LCD5110_SRC_FILES)

# Create object files from source files
OBJ_FILES = $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_FILES:.c=.o)))



all: $(LIB_NAME)

$(LIB_NAME): $(OBJ_FILES)
	@echo "[Linking] Creating dynamic library: $(LIB_NAME)"
	$(CC) $(LDFLAGS) -o $(LIB_NAME) $(OBJ_FILES)

# compiling sim800l files
$(BUILD_DIR)/%.o: $(SIM800L_SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@echo "[Compiling] $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

#compiling lcd5110 files
$(BUILD_DIR)/%.o: $(LCD5110_SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@echo "[Compiling] $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean
clean:
	@echo "[Cleaning] Removing build files and library"
	rm -rf $(BUILD_DIR) $(LIB_NAME)
