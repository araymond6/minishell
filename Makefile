NAME = minishell
LIBFT = $(LIB_DIR)/libft.a

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

LFLAGS = -lreadline -lncurses

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = include/
LIB_DIR = libft
RL_DIR = include/readline
RL = readline-8.2
RLINE = $(RL_DIR)/libreadline.a

SRCS =	build-in.c \
		here_doc.c \
		path.c \
		s_cmd_attribution.c \
		utils_exec.c \
		main.c \
		parsing.c \
		utils_parse.c \
		utils_parse_2.c \
		utils.c \
		export.c \
		env_unset.c \
		env_utils.c \
		utils.c \
		pwd_cd_echo.c \
		exit.c \
		heredoc_substitution.c \
		signal.c \
		token.c \
		count_tokens.c \
		get_tokens.c \
		child.c \
		execution2_0.c \
		process2_0.c \
		redirection2_0.c \
		parsing_check2_0.c \
		command_arg.c \
		token_utils.c \
		substitution.c 
		
VPATH = $(SRC_DIR) $(INC_DIR) $(OBJ_DIR)

OBJS = $(SRCS:%.c=%.o)
OBJ_PRE = $(addprefix $(OBJ_DIR), $(OBJS))

DEP = minishell.h
DEP_PRE = $(addprefix $(INC_DIR), $(DEP))

# Colors
RESET = \033[0m
GREEN = \033[92m
MAGENTA = \033[95m

all: readline lib $(NAME)

$(OBJ_DIR)%.o: %.c $(DEP_PRE)
	@echo "$(GREEN)----$(MAGENTA)Compiling $<...$(GREEN)----$(RESET)"
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(GREEN)----$(MAGENTA) $< compiled!! $(GREEN)----$(RESET)"

$(NAME): $(OBJ_PRE)
	@echo "$(GREEN)----$(MAGENTA)Compiling minishell..$(GREEN)----$(RESET)"
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(RLINE) $(LFLAGS)
	@echo "$(GREEN)-----$(MAGENTA)Minishell compiled!$(GREEN)-----$(RESET)"

readline:
	@if [ ! -f ./include/readline/libreadline.a ]; then \
		mkdir -p $(RL_DIR); \
		curl -O https://ftp.gnu.org/gnu/readline/$(RL).tar.gz; \
		tar -xf $(RL).tar.gz; \
		rm -rf $(RL).tar.gz; \
		cd $(RL) && bash configure && make; \
		mv ./libreadline.a ../$(RL_DIR); \
		rm -rf ../$(RL); \
		fi

clean:
	@echo "$(GREEN)-----$(MAGENTA) Cleaning project...  $(GREEN)-----$(RESET)"
	rm -rf $(OBJ_DIR)
	rm -rf $(RLINE)
	make clean -C $(LIB_DIR)
	@echo "$(GREEN)------$(MAGENTA)  Project cleaned!  $(GREEN)------$(RESET)"

fclean: clean
	@echo "$(GREEN)-----$(MAGENTA) Removing program...  $(GREEN)-----$(RESET)"
	rm -rf $(NAME)
	make fclean -C $(LIB_DIR)
	@echo "$(GREEN)------$(MAGENTA)  Program removed!  $(GREEN)------$(RESET)"

lib: 
	@make -C $(LIB_DIR)

debug: CFLAGS+=-g
debug: all

val: CFLAGS+=-g
val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes --suppressions=supp.txt ./minishell 

run: all
	./$(NAME)

re: fclean all

.PHONY: re debug fclean clean all run readline libfile