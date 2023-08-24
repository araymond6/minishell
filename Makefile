NAME = minishell
LIBFT = $(LIB_DIR)/libft.a

CC = gcc
CFLAGS = #-Wall -Werror -Wextra

LFLAGS = -lreadline
RLINE_DIR = -L${HOME}/.brew/opt/readline/lib

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = include/
LIB_DIR = libft

VPATH = $(SRC_DIR) $(INC_DIR) $(OBJ_DIR)
SRCS =	main.c \
		parsing.c \
		parse_utils.c \
		init_utils.c \
		error.c \
		quote.c \
		doublequote.c

OBJS = $(SRCS:%.c=%.o)
OBJ_PRE = $(addprefix $(OBJ_DIR), $(OBJS))

DEP = minishell.h
DEP_PRE = $(addprefix $(INC_DIR), $(DEP))

# Colors
RESET = \033[0m
GREEN = \033[92m
MAGENTA = \033[95m

all: lib $(NAME)

run: all
	./philo 5 800 200 200

$(OBJ_DIR)%.o: %.c $(DEP_PRE)
	@echo "$(GREEN)----$(MAGENTA)Creating folder...$(GREEN)----$(RESET)"
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(GREEN)----$(MAGENTA)  Folder created!! $(GREEN)----$(RESET)"

$(NAME): $(OBJ_PRE)
	@echo "$(GREEN)----$(MAGENTA)Compiling minishell..$(GREEN)----$(RESET)"
	$(CC) $(CFLAGS) $(RLINE_DIR) $(LFLAGS) $(LIBFT) -o $@ $^
	@echo "$(GREEN)-----$(MAGENTA)Minishell compiled!$(GREEN)-----$(RESET)"

clean:
	@echo "$(GREEN)-----$(MAGENTA) Cleaning project...  $(GREEN)-----$(RESET)"
	rm -rf $(OBJ_DIR)
	make clean -C $(LIB_DIR)
	@echo "$(GREEN)------$(MAGENTA)  Project cleaned!  $(GREEN)------$(RESET)"

fclean: clean
	@echo "$(GREEN)-----$(MAGENTA) Removing program...  $(GREEN)-----$(RESET)"
	rm -rf $(NAME)
	make fclean -C $(LIB_DIR)
	@echo "$(GREEN)------$(MAGENTA)  Program removed!  $(GREEN)------$(RESET)"

readline: 
	brew install readline

lib: 
	@make -C $(LIB_DIR)

debug: CFLAGS+=-g
debug: all

re: fclean all

.PHONY: re debug fclean clean all run readline lib