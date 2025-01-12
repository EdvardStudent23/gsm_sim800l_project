LIB_NAME = libsim800l.dll

SIM800L_SRC_DIR = Libraries/sim800l_lib/src
SIM800L_INC_DIR = Libraries/sim800l_lib/inc
SIM800L_CONFIG_DIR = Libraries/sim800l_lib/config
LCD5110_SRC_DIR = Core/Src/lcd5110
LCD5110_INC_DIR = Core/Inc/lcd5110
BUILD_DIR = build

CC = gcc
CFLAGS = -Wall -shared -I$(SIM800L_INC_DIR) -I$(SIM800L_CONFIG_DIR) -I$(LCD5110_INC_DIR) -D_EXPORTS
LDFLAGS = -shared -Wl,--out-implib=$(BUILD_DIR)/libsim800l.a -Wl,--dll

SIM800L_SRC_FILES = $(wildcard $(SIM800L_SRC_DIR)/*.c)
LCD5110_SRC_FILES = $(wildcard $(LCD5110_SRC_DIR)/*.c)
SRC_FILES = $(SIM800L_SRC_FILES) $(LCD5110_SRC_FILES)

OBJ_FILES = $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_FILES:.c=.o)))


all: $(LIB_NAME)

$(LIB_NAME): $(OBJ_FILES)
	@echo "[Linking] creating dll: $(LIB_NAME)"
	$(CC) $(LDFLAGS) -o $(LIB_NAME) $(OBJ_FILES)


$(BUILD_DIR)/%.o: $(SIM800L_SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@echo "[Compiling] $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(LCD5110_SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@echo "[Compiling] $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean
clean:
	@echo "[Cleaning] remove build and lib"
	rm -rf $(BUILD_DIR) $(LIB_NAME)