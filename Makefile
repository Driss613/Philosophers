# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 08:08:17 by drabarza          #+#    #+#              #
#    Updated: 2024/10/09 05:54:58 by drabarza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[3;32m
GREENS = \033[7;32m
YELLOW = \033[3;33m
RED = \033[3;31m
NC = \033[0m

NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra
SRC =	philo.c \
		parsing.c \
		init_mutex.c \
		ft_atoi.c \
		init.c \
		thread_create.c \
		main_routine.c \
		routine.c \
		utils_routine.c \
		free_all.c
OBJ = $(SRC:.c=.o)
CURRENT_DATE = $(shell date +"%d/%m/%Y %H:%M:%S")
MAKEFLAGS += -s

all: header $(NAME)

$(NAME) : $(OBJ)
	@${CC} ${FLAGS} $(OBJ) -o $@

header:
	@clear
	@echo "${GREEN}██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗"
	@echo "██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝"
	@echo "██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗"
	@echo "██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║"
	@echo "██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║"
	@echo "╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝"
	@echo "Compilation in progress...${NC}"

%.o : %.c
	@${CC} ${FLAGS} -c $< -o $@
	@echo "${CURRENT_DATE} ${GREENS}[CMD]${NC}${GREEN} - $(basename $<)${NC}"

clean:
	@echo "${RED}Cleaning object files...${NC}"
	@rm -f ${OBJ}
	@echo "${RED}Cleaning completed.${NC}"

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re header
