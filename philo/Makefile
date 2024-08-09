# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zchia <zchia@42.sg>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/07 01:49:45 by zchia             #+#    #+#              #
#    Updated: 2024/07/07 01:49:45 by zchia            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   philo

CC          =   gcc
CFLAGS      =   -g -Werror -Wextra -Wall

SRC_PATH    =   src/
OBJ_PATH    =   obj/

SRC         =   philo.c \
				eat_sleep_think.c \
				est_utils.c \
				ft_minilib.c \
				ft_strlib.c \
				ft_miniprintf.c

OBJ         =   $(SRC:.c=.o)
OBJS        =   $(addprefix $(OBJ_PATH), $(OBJ))

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "Philosophers is ready."

clean:
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(NAME)
	@echo "Philosophers is removed."

re: fclean all

.PHONY: all re clean fclean
