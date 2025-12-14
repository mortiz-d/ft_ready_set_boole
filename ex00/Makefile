# COLORS #
GREEN = @echo "\033[0;32m"
BLUE = @echo "\033[0;34m" 
PURPLE = @echo "\033[0;35m"
CYAN = @echo "\033[0;36m"
RESET = "\033[1;0m"

# VARIABLES #
NAME = boole
CC = clang++
INCLUDE = -I./include
CFLAGS = -std=c++98 -Wall -Werror -Wextra 

# PATHs #
SRC_PATH    = srcs
OBJ_PATH    = objects

# SOURCES #
SRC =  main.cpp

# RULES #
all: $(NAME)

OBJ_NAME = $(SRC:%.cpp=%.o)

SRCS = $(addprefix $(SRC_PATH)/, $(SRC))

OBJS =  $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH) 2> /dev/null

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
            
$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)
	$(GREEN)PROGRAM $(NAME) ASSEMBLED $(RESET)

##RULES
$(MAKE): make

clean:
	@rm -rf $(OBJ_PATH)
	@$(PURPLE)CLEANED $(NAME) OBJECTS $(RESET)
	
fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(cd)
	$(PURPLE)CLEANED DIRECTORY AND EXEC $(RESET)

re: fclean all

PHONY.: all clean fclean re norminette test
