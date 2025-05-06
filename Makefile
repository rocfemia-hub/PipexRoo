LIB = ar rcs
RM = rm -f

CC = cc

BLUE   = \033[34m
RESET  = \033[0m

CCFLAGS = -Wall -Wextra -Werror -g3

SRC_DIR = src

SRC = pipex.c\

OBJ = $(SRC:.c=.o)

INCLUDE = pipex.h

NAME = pipex

LIBFTA = Helicopter/libft.a

all: $(NAME)

%.o: %.c
	@$(CC) $(CCFLAGS) -I/Helicopter/libft.h -I/usr/include -O3 -c $< -o $@

$(NAME): $(OBJ)
	@cd Helicopter && make
	@$(CC) $(CCFLAGS) $(OBJ) -Ilibft_ext $(LIBFTA) -o $(NAME)
@echo "$(BLUE)        ||>>    $(BLUE)pipex compiled!!    <<||$(RESET)"

clean:
	@$(RM) $(OBJ)
	@cd Helicopter && make clean

fclean:
	@$(RM) $(NAME) $(OBJ)
	@cd Helicopter && make fclean

re: fclean all

.PHONY: all clean fclean re	