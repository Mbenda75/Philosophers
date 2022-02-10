# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/22 11:48:55 by benmoham          #+#    #+#              #
#    Updated: 2022/02/10 20:42:31 by benmoham         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	philo.c		\
				routine.c		\
				utils_struc.c 	\
				main.c	\
				parse_philo.c	\
			
OBJS			= $(SRCS:.c=.o)

NAME			= philo

CFLAGS			= -Wall -Wextra -Werror -g3 -pthread -fsanitize=thread

RM				= rm -f

CC				= gcc

AR				= ar rcs

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

all:			$(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME) 

re:				fclean all


.PHONY:			all clean fclean c.o re 