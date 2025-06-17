# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 23:02:56 by lsadikaj          #+#    #+#              #
#    Updated: 2025/06/17 13:58:22 by lsadikaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

# Dossiers
SRC_DIR = source
INC_DIR = include
OBJ_DIR = obj

# Fichiers source
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/parser.c \
       $(SRC_DIR)/init.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/utils2.c \
       $(SRC_DIR)/safe_functions.c \
       $(SRC_DIR)/simulation.c \
       $(SRC_DIR)/monitor.c \
       $(SRC_DIR)/write.c \
       $(SRC_DIR)/synchro_utils.c

# Fichiers objets
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Compilation de l'exécutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Règle principale
all: $(NAME)

# Nettoyage
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
