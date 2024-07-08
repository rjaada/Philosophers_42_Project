# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 13:50:41 by rjaada            #+#    #+#              #
#    Updated: 2024/07/02 16:30:30 by rjaada           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Philosophers
IDIR = ../include
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(IDIR)

ODIR = obj
LDIR = ../lib

LIBS = -lm

DEPS = $(IDIR)/Philosophers.h
OBJ = main.o utils.o
OBJ := $(patsubst %,$(ODIR)/%,$(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o : %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

clean:
    rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

fclean: clean
    rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re $(NAME)