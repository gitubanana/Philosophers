CFLAGS		= -Wall -Werror -Wextra
#THREADFLAG	= -g -fsanitize=thread
OBJS_DIR	= objects/
NAME		= philo_bonus
SRC	 		= philo_bonus.c utils_bonus.c simulation2_bonus.c simulation_bonus.c
OBJS 		= $(addprefix $(OBJS_DIR), $(SRC:.c=.o))
HEADER 		= philo_bonus.h


all : $(NAME)

$(OBJS_DIR) :
	mkdir $@

$(OBJS_DIR)%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) $(THREADFLAG) -c $< -o $@

$(NAME) : $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(THREADFLAG) $(OBJS) -o $@

clean :
	$(RM) -r $(OBJS_DIR)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
