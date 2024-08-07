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
BONUS_NAME  =   philo_bonus

CC          =   gcc
CFLAGS      =   -g -Werror -Wextra -Wall

LIBFT_PATH  =   libft/
LIBFT_NAME  =   libft.a
LIBFT       =   $(LIBFT_PATH)$(LIBFT_NAME)

FTPRINTF_PATH	= ft_printf/
FTPRINTF_NAME	= libftprintf.a
FTPRINTF		= $(FTPRINTF_PATH)$(FTPRINTF_NAME)

SRC_PATH    =   src/
OBJ_PATH    =   obj/

SRC         =   philo.c \
				eat_sleep_think.c \
				est_utils.c
BSRCS       =   philo_bonus.c

OBJ         =   $(SRC:.c=.o)
BOBJ        =   $(BSRCS:.c=.o)
OBJS        =   $(addprefix $(OBJ_PATH), $(OBJ))
BOBJS       =   $(addprefix $(OBJ_PATH), $(BOBJ))

all: $(LIBFT) $(FTPRINTF) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(FTPRINTF):
	@make -C $(FTPRINTF_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(FTPRINTF)
	@echo "Philosophers is ready."

$(BONUS_NAME): $(BOBJS) $(LIBFT) $(FTPRINTF)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BOBJS) $(LIBFT) $(FTPRINTF)
	@echo "Philosophers with bonus is ready."

bonus: $(BONUS_NAME)

clean:
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_PATH)
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(FTPRINTF_PATH)

fclean: clean
	@rm -rf $(NAME) $(BONUS_NAME)
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(FTPRINTF_PATH)
	@echo "Philosophers is removed."

re: fclean all

.PHONY: all re clean fclean bonus
