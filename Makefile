NAME		= libasm.a
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
ASM			= nasm
ASMFLAGS	= -f elf64
AR			= ar rcs
RM			= rm -f

SRCS		= ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s

OBJS		= $(SRCS:.s=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) test_libasm

re: fclean all

test: $(NAME)
	$(CC) $(CFLAGS) -o test_libasm main.c -L. -lasm
	./test_libasm 