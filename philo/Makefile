# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sujpark <sujpark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 17:37:06 by sujpark           #+#    #+#              #
#    Updated: 2022/09/08 19:14:16 by sujpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	philo

SRCS	:=	check_flag.c free.c main.c monitoring.c philo_util.c parse.c \
			philo.c philo_action.c set_flag.c utils.c error.c philo_fork.c \
			init_monitor.c

INCS	:=	philo.h

OBJS	:=	$(SRCS:.c=.o)

CC		:=	cc
CFLAGS	:=	-Wall -Wextra -Werror
LDFLAGS	:=	-Wall -Wextra -Werror

RM		:=	rm -f

.PHONY	:	all
all		:	$(NAME)

$(NAME)	:	$(OBJS) $(INCS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

%.o		:	%.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY	:	clean
clean	:
	$(RM) $(OBJS)

.PHONY	:	fclean
fclean	:	clean
	$(RM) $(NAME)

.PHONY	:	re
re		:
	make fclean
	make all
