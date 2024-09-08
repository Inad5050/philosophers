# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dani <dani@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 19:01:54 by dani              #+#    #+#              #
#    Updated: 2024/09/09 00:04:00 by dani             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BONUS = philo_bonus
CC = gcc
CCFLAGS = -Wall -Wextra -Werror

#colors
COLOR_GREEN = \033[0;32m
COLOR_RESET = \033[0m

#sources
SRC_BONUS_DIR = ./
SRC_BONUS_FILES = auxiliars_bonus.c checker_bonus.c exit_bonus.c libft_bonus.c main_bonus.c parsing_bonus.c threads_bonus.c
SRC_BONUS = $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS_FILES))
OBJ_BONUS = $(SRC_BONUS:.c=.o)

#headers
INCLUDE = -I./

#bonus
all: $(NAME_BONUS)
	@echo "$(COLOR_GREEN)------------ PROCESS FINISHED ------------ $(COLOR_RESET)"

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CCFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@ $(INCLUDE)
	@echo "$(COLOR_GREEN)------------ MESSAGE: $@ COMPILED ------------ $(COLOR_RESET)"

#additional
clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	@echo "$(COLOR_GREEN)------------ MESSAGE: CLEANING COMPLETED ------------ $(COLOR_RESET)"
	
fclean: 
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	@echo "$(COLOR_GREEN)------------ MESSAGE: CLEANING COMPLETED ------------ $(COLOR_RESET)"

re: fclean all

.PHONY:	all clean fclean re
