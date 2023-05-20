NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror  -g -fsanitize=thread
SRCS = ft_atoi.c philo.c philo_utils.c\

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