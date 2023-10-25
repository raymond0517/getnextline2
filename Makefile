# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhsu <rhsu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/26 23:46:48 by rhsu              #+#    #+#              #
#    Updated: 2023/10/20 18:23:30 by rhsu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
NAME = libgetnextline.a
INC = get_next_line.h

OBJS = *.o

CFILES = get_next_line.c \
		get_next_line_utils.c 

OFILES = $(CFILES:.c=.o)

BONUS_CFILES = 	get_next_line_bonus.c \
		get_next_line_utils_bonus.c

BONUS_OFILES = $(BONUS_CFILES:.c=.o)

.PHONY: all bonus clean fclean re 

all: $(NAME)

$(NAME): $(OFILES)
	ar rc $(NAME) $(OFILES)
	ranlib $(NAME)
	@echo "$@ compiled"

bonus: $(BONUS_OFILES)
	ar rc $(NAME) $(BONUS_OFILES)
	ranlib $(NAME)
	@echo "bonus library compiled"

%.o : %.c $(INC)
	cc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OFILES) $(BONUS_OFILES)
	@echo "getnextline objects file removed"

fclean:	clean
	@rm -f $(NAME)
	@echo "$(NAME) removed "

re: fclean all
