# Makefile
PROJECT_NAME = distributedRayTracer

# Diretorios
SRC_DIR = src include
BUILD_DIR = build

# Opcoes do compildador
CC = g++ -std=c++20
CC_FLAGS = -Wall -O3 -Iinclude -pg -fno-omit-frame-pointer

SRCS = $(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.cpp))
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Regra default
all: $(PROJECT_NAME)

# Link
$(PROJECT_NAME): $(OBJS)
	@echo "Linking $@..."
	$(CC) -o $@ $^

# Compilacao
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CC) $(CC_FLAGS) -c $< -o $@

# Limpa artefatos
clean:
	@echo "Cleaning..."
	@rm -v -rf $(BUILD_DIR) $(PROJECT_NAME)

# Phony targets
.PHONY: all clean
