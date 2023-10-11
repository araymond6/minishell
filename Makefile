NAME = minishell
LIBFT = $(LIB_DIR)/libft.a

CC = gcc
CFLAGS = -g #-fsanitize=address #-Wall -Wextra -Werror

LFLAGS = -lreadline -lncurses
RLINE_DIR = -L${HOME}/.brew/opt/readline/lib

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = include/
LIB_DIR = libft

SRCS =	build-in.c \
		change_fd.c \
		command.c \
		exec.c \
		here_doc.c \
		parsing_exec.c \
		path.c \
		redirections.c \
		s_cmd_attribution.c \
		utils_exec_2.c \
		utils_exec.c \
		main.c \
		parsing.c \
		parsing2.c \
		parsing3.c \
		utils_parse.c \
		utils_parse_2.c \
		quote.c \
		doublequote.c \
		dollarsign.c \
		substitution.c \
		utils.c \
		export.c \
		env_unset.c \
		env_utils.c \
		utils.c \
		pwd_cd_echo.c \
		exit.c  
		
VPATH = $(SRC_DIR) $(INC_DIR) $(OBJ_DIR)

OBJS = $(SRCS:%.c=%.o)
OBJ_PRE = $(addprefix $(OBJ_DIR), $(OBJS))

DEP = minishell.h
DEP_PRE = $(addprefix $(INC_DIR), $(DEP))

# Colors
RESET = \033[0m
GREEN = \033[92m
MAGENTA = \033[95m

all: lib $(NAME)

$(OBJ_DIR)%.o: %.c $(DEP_PRE)
	@echo "$(GREEN)----$(MAGENTA)Compiling $<...$(GREEN)----$(RESET)"
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(GREEN)----$(MAGENTA) $< compiled!! $(GREEN)----$(RESET)"

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

.PHONY: re debug fclean clean all run readline libfile