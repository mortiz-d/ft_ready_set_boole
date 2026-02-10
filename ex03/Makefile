# COLORS #
GREEN = @echo "\033[0;32m"
BLUE = @echo "\033[0;34m" 
PURPLE = @echo "\033[0;35m"
CYAN = @echo "\033[0;36m"
RESET = "\033[1;0m"


# VARIABLES #
NAME = boole
CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -Werror
INCLUDE = -I../files/include

# PATHS #
SRC_PATH   = srcs
FILES_PATH = ../files/srcs
OBJ_PATH   = ../objects

# SOURCES #
SRC = main.cpp 
FILE = aux.cpp boole.cpp Node.cpp ExpressionTree.cpp

SRCS  = $(addprefix $(SRC_PATH)/, $(SRC))
FILES = $(addprefix $(FILES_PATH)/, $(FILE))

ALL_SRCS = $(SRCS) $(FILES)

# OBJECTS #
OBJS = $(addprefix $(OBJ_PATH)/, $(notdir $(ALL_SRCS:.cpp=.o)))

# RULES #
all: $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_PATH)/%.o: $(FILES_PATH)/%.cpp | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	$(GREEN)PROGRAM $(NAME) ASSEMBLED $(RESET)

clean:
	@rm -rf $(OBJ_PATH)
	$(PURPLE)CLEANED OBJECTS$(RESET)

fclean: clean
	@rm -f $(NAME)
	$(PURPLE)CLEANED EXECUTABLE$(RESET)

re: fclean all

.PHONY: all clean fclean re
