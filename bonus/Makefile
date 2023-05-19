NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror
SRCS = ft_atoi.c philo.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o:%.c philo.h
	@$(CC) $(CFLAGS) -c $<

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean 
	@rm -f $(NAME)

re: fclean all 

.PHONY: clean fclean re all