# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/20 09:36:54 by fcarranz          #+#    #+#              #
#    Updated: 2024/09/01 11:56:52 by fcarranz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Formatting colours
# R		Red text
# G		Green text
# GR	Gray text
# Y		Yellow text
# B		Blue text
# M		Magenta text
# C		Cyan text
# W		White text
# RST 	Reset to default
# BLD 	Bold text
# CLS	Clear screen
R = \033[31m
G = \033[32m
GR=	\033[90m
Y = \033[33m
B = \033[34m
M = \033[35m
C = \033[36m
W = \033[37m
RST = \033[0m
BLD = \033[1m
CLS = \033[2J
# END Formatting colours

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -MMD -g
INC = -Iinc/

SRC_PATH = src/
OBJ_PATH = obj/
DEP_PATH = dep/

SRC = main.c \
	  utils.c \
	  parser.c \
	  sleep_ml.c \
	  init_forks.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))
DEPS = $(addprefix $(DEP_PATH), $(DEP))

.PHONY: all clean fclean re

all: $(NAME)
	@echo "\v\v\v"
	@echo "\t💭  $(BLD)$(G)$(NAME) ready!$(RST)  🤔"
	@echo "\v\v\v"
	
$(NAME): Makefile $(OBJS)
	@echo "$(BLD)"
	$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "$(RST)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH) $(DEP_PATH)
	@echo -n "$(GR)"
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo -n "$(RST)"
	@mv $(@:.o=.d) $(DEP_PATH)

clean:
	@echo -n "$(R)"
	rm -rf $(DEP_PATH) $(OBJ_PATH)
	@echo -n "$(RST)"

fclean: clean
	@echo -n "$(R)"
	rm -f $(NAME)
	@echo -n "$(RST)"

re: fclean all

-include $(DEPS)