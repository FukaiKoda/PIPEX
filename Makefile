CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC = main.c init.c ft_split.c ft_printf.c tools.c path_functions.c

OBJ = ${SRC:%.c=%.o}

BONUS_SRC = main_bonus.c init.c ft_split.c ft_printf.c path_functions.c \
		get_next_line.c get_next_line_utils.c tools1_bonus.c tools2_bonus.c

BONUS_OBJ = ${BONUS_SRC:%.c=%.o}

RM = rm -rf

NAME = pipex

FAKE_FILE = .bonus_relink

all: ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${SRC} -o $@

bonus: ${FAKE_FILE}

${FAKE_FILE}: ${BONUS_OBJ}
	${CC} ${CFLAGS} ${BONUS_SRC} -o ${NAME}
	@touch ${FAKE_FILE}

clean:
	${RM} ${OBJ} ${BONUS_OBJ} ${FAKE_FILE}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
