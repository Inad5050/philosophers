# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 19:01:54 by dani              #+#    #+#              #
#    Updated: 2024/09/11 21:03:06 by dangonz3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CCFLAGS = -Wall -Wextra -Werror

#colors
COLOR_GREEN = \033[0;32m
COLOR_RESET = \033[0m

#sources
SRC_DIR = ./
SRC_FILES =  auxiliars.c checker.c exit.c main.c others.c parsing.c threads.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(SRC:.c=.o)

#headers
INCLUDE = -I./includes/

#program
all: $(NAME)
	@echo "$(COLOR_GREEN)------------ PROCESS FINISHED ------------ $(COLOR_RESET)"

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o $(NAME)

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
