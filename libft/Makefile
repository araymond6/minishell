NAME = libft.a

OBJ_DIR = obj/
SRC_DIR = src

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
	ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_memcpy.c \
	ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_memchr.c ft_strnstr.c ft_memcmp.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c \
	get_next_line_utils.c ft_realloc.c

B_SRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

OBJ = $(SRC:%.c=%.o)
B_OBJ = $(B_SRC:%.c=%.o)
OBJ_LIST = $(OBJ) $(B_OBJ)
OBJ_PRE = $(addprefix $(OBJ_DIR), $(OBJ_LIST))
DEP = libft.h get_next_line.h
VPATH = $(SRC_DIR)

CFLAGS = -Wall -Wextra -Werror
CC = gcc

all: $(NAME)

$(OBJ_DIR)%.o: %.c $(DEP)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ_PRE)
	@ar -rc $(NAME) $^

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all