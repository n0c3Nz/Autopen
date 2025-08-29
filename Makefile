# Variables
CXX := g++
CXXFLAGS := -Wall -Wextra -I./inc -std=c++17
SRC := $(wildcard ./src/*.cpp)
OBJ := $(SRC:./src/%.cpp=./obj/%.o)
TARGET := autopen

# Colores
GREEN := \033[0;32m
YELLOW := \033[1;33m
RESET := \033[0m

# Reglas
all: $(TARGET)

./obj/%.o: ./src/%.cpp | ./obj
	@echo -e "$(YELLOW)[Compilando]$<$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	@echo -e "$(GREEN)[Enlazando]$@$(RESET)"
	@$(CXX) $(OBJ) -o $@

./obj:
	@mkdir -p ./obj

clean:
	@echo -e "$(YELLOW)[Limpiando]$(RESET)"
	@rm -rf ./obj

fclean: clean
	@echo -e "$(YELLOW)[Limpiando binario]$(RESET)"
	@rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re