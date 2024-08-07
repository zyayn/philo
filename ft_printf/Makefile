# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zchia <zchia@42.sg>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/21 21:41:13 by zchia             #+#    #+#              #
#    Updated: 2024/07/14 17:32:29 by zchia            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT_PATH = ../libft/
LIBFT_SRCS = $(LIBFT_PATH)ft_putchar_fd.c \
             $(LIBFT_PATH)ft_putstr_fd.c \
             $(LIBFT_PATH)ft_strlen.c
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

SRCS = \
	ft_printf.c \
	ft_strlcpy.c \
	ft_getstr.c \
	ft_itoa.c \
	ft_uitoa.c \
	ft_htoa.c \
	ft_ptoa.c

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -I $(LIBFT_PATH)

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT_OBJS}
	ar -r ${NAME} ${OBJS} ${LIBFT_OBJS}

$(OBJS): %.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

$(LIBFT_OBJS): %.o: %.c
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -rf ${OBJS} ${LIBFT_OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
