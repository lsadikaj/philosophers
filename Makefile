# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 23:02:56 by lsadikaj          #+#    #+#              #
#    Updated: 2025/05/29 17:41:15 by lsadikaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

# Dossiers
SRCDIR = source
INCDIR = include
OBJDIR = obj

# Fichiers source
SRCS = $(SRCDIR)/main.c \
       $(SRCDIR)/parser.c \
       $(SRCDIR)/init.c \
       $(SRCDIR)/utils.c \
       $(SRCDIR)/utils2.c \
       $(SRCDIR)/safe_functions.c \
       $(SRCDIR)/simulation.c \
       $(SRCDIR)/monitor.c \
       $(SRCDIR)/write.c \
       $(SRCDIR)/synchro_utils.c

# Fichiers objets
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Compilation des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Compilation de l'exécutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Règle principale
all: $(NAME)

# Nettoyage
clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
