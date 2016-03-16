NAME = minishell
INCLUDES=./includes
INCLUDES_FT_PRINTF=./ft_printf/includes
CC = clang
LIB=./ft_printf/
SRC_PATH=./srcs/
FLAG=-Wall -Wextra -g

SRCS= main.c app.c read_env.c put_error.c command.c loop.c get_next_line.c \
	  built_in.c \
	  bi_exit.c

OBJ=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIB)libftprintf.a $(OBJ) $(INCLUDES)/get_next_line.h $(INCLUDES_FT_PRINTF)/ft_printf.h \
	$(INCLUDES)/minishell.h
	$(CC) -o $(NAME) -I$(INCLUDES_FT_PRINTF) -I$(INCLUDES) $(OBJ) -L$(LIB) -lftprintf

%.o: $(SRC_PATH)%.c $(INCLUDES)/minishell.h
	$(CC) -c $(FLAG) $< -I$(INCLUDES_FT_PRINTF) -I$(INCLUDES)

$(LIB)libftprintf.a:
	make -C $(LIB)
	make clean -C $(LIB)

clean:
	make clean -C $(LIB)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIB)
	rm -f $(NAME)

re: fclean $(NAME)
