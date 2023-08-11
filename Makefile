# Executable
NAME		= philo

# Compiler and flags
CC			= gcc
CFLAGS		= -Wall -Wextra
CFLAGS		+= -Werror
#  CFLAGS		+= -fsanitize=thread
# CFLAGS		+= -fsanitize=address


# Sources files
SRC		= ./src/main.c \
			./src/check_input.c \
			./src/check_meals.c \
			./src/destroy_mutex.c \
			./src/init.c \
			./src/start_routine.c \
			./src/threads.c \
			./src/utils_libft.c \
			./src/utils.c \

# Objects files
OBJ		= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

# Object Directory
OBJDIR 		= obj

# Colors
BOLD		= \033[1m
ITALIC		= \033[3m
UNDER 		= \033[4m
GREEN		= \033[32;1m
INDIGO		= \033[38;2;75;0;130m
CORAL		= \033[38;2;255;127;80m
RESET		= \033[0m

# Targets
all:		$(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@echo "$(CORAL) $(UNDER) $(BOLD) $(ITALIC) ✨Compilation Done✨   $(RESET)"

$(OBJDIR)/%.o: ./src/%.c
		@mkdir -p $(OBJDIR)
		$(CC) $(CFLAGS) -c -o $@ $^

# Clean
clean:
		@rm -rf $(OBJDIR)
		@echo "$(GREEN) $(ITALIC) ✅ Cleaned object files ✅$(RESET)"

fclean: clean
		@rm -f $(NAME)
		@echo "$(GREEN) $(ITALIC)	  ✅ ✅ ✅$(RESET)"

re:		fclean all

.PHONY: all clean fclean re