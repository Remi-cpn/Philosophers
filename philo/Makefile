# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/07 09:56:21 by rcompain          #+#    #+#              #
#    Updated: 2026/02/18 14:52:27 by rcompain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   SETTINGS                                   #
# **************************************************************************** #

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
AR			= ar rcs

# **************************************************************************** #
#                                   PATHS                                      #
# **************************************************************************** #

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

SRC			= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/utils.c \
			  $(SRC_DIR)/init.c \
			  $(SRC_DIR)/exit.c \
			  $(SRC_DIR)/routine.c \
			  $(SRC_DIR)/monitoring.c

OBJ			= ${SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o}

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: banner $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJ) -o $(NAME)
	@echo "\r\033[2K$(CYAN)📝 Compiled project files: $(BOLD)$(GREEN)[OK]$(RESET)"
	@echo "$(BOLD) $(GREEN)\n         Project compiled successfully ✅$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@printf "\r\033[2K$(CYAN)📝 Compiled project files: %s$(RESET)" "$<"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(CYAN)Object files removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(CYAN)Executable removed$(RESET)"

re: fclean all

# **************************************************************************** #
#                                   DECO & COLORS                              #
# **************************************************************************** #

GREEN		= \033[32m
CYAN		= \033[36m
ORANGE  	= \033[38;5;214m
RESET		= \033[0m

BOLD		=\033[1m

BANNER = \
"$(BOLD)$(ORANGE)\n\n  	          Compilation ...  $(RESET)\n"\

banner:
	@echo $(BANNER)

.PHONY: all clean fclean re banner

