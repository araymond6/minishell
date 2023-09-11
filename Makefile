NAME = minishell
LIBFT = $(LIB_DIR)/libft.a

CC = gcc
CFLAGS = -lncurses -g #-Wall -Werror -Wextra

LIBRLINE = readline-8.2
LIBRLINE_DIR = ./libs/readline/
RLINE = $(LIBRLINE_DIR)libreadline.a

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = include/
LIB_DIR = libft

SRCS =	build-in.c \
		change_fd.c \
		command.c \
		exec.c \
		here_doc.c \
		main_val.c \
		parsing_exec.c \
		path.c \
		redirections.c \
		s_cmd_attribution.c \
		save_path_aurelia.c \
		utils_exec_2.c \
		utils_exec.c
		
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
	@echo "$(GREEN)----$(MAGENTA)Creating folder...$(GREEN)----$(RESET)"
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(GREEN)----$(MAGENTA)  Folder created!! $(GREEN)----$(RESET)"

$(NAME): $(OBJ_PRE)
	@echo "$(GREEN)----$(MAGENTA)Compiling minishell..$(GREEN)----$(RESET)"
	$(CC) $(CFLAGS) $(RLINE) $(LIBFT) -o $@ $^
	@echo "$(GREEN)-----$(MAGENTA)Minishell compiled!$(GREEN)-----$(RESET)"

clean:
	@echo "$(GREEN)-----$(MAGENTA) Cleaning project...  $(GREEN)-----$(RESET)"
	rm -rf $(OBJ_DIR)
	rm -rf $(LIBRLINE_DIR)
	make clean -C $(LIB_DIR)
	@echo "$(GREEN)------$(MAGENTA)  Project cleaned!  $(GREEN)------$(RESET)"

fclean: clean
	@echo "$(GREEN)-----$(MAGENTA) Removing program...  $(GREEN)-----$(RESET)"
	rm -rf $(NAME)
	make fclean -C $(LIB_DIR)
	@echo "$(GREEN)------$(MAGENTA)  Program removed!  $(GREEN)------$(RESET)"

readline: 
	@if [ ! -f ./libs/readline/libreadline.a ]; then \
		mkdir -p $(LIBRLINE_DIR); \
		curl -O https://ftp.gnu.org/gnu/readline/$(LIBRLINE).tar.gz; \
		tar -xf $(LIBRLINE).tar.gz; \
		rm -rf $(LIBRLINE).tar.gz; \
		cd $(LIBRLINE) && bash configure && make; \
		mv ./libreadline.a ../libs/readline; \
		rm -rf ../$(LIBRLINE); \
		echo "${GREEN}READLINE INSTALLED${RESET}"; \
		fi

lib: 
	@make -C $(LIB_DIR)

debug: CFLAGS+=-g
debug: all

re: fclean all

.PHONY: re debug fclean clean all run readline libfile