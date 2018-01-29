# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abodnar <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/12 12:19:01 by abodnar           #+#    #+#              #
#    Updated: 2018/01/12 16:26:37 by abodnar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c ft_parse_printf.c ft_get_numbers.c ft_get_unsign_ptr.c \
	ft_prec_width.c ft_flags.c ft_get_unichar.c ft_get_unistr.c \
	ft_unknown_spec_printf.c

OFLS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o : %.c
	gcc -I. -Wall -Werror -Wextra -c $< -o $@

$(NAME): $(OFLS) ft_printf.h
	make -C libft
	cp ./libft/libft.a ./$(NAME)
	ar rc $(NAME) $(OFLS)
	ranlib $(NAME)

clean:
	make clean -C libft/
	/bin/rm -f $(OFLS)

fclean: clean
	make fclean -C libft/
	/bin/rm -f libft.a
	/bin/rm -f $(NAME)

re: fclean all
	#comment
