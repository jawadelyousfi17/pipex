CSRC = pipex.c pipex_utils.c

OBJS=$(CSRC:.c=.o)

NAME=pipex

all : $(NAME)

$(NAME) : $(OBJS)
	cc $(OBJS) ./libft/libft.a -o pipex
%.o : %.c
	cc -c $< -o $@

clean :
	rm -rf *.o 
fclean : clean 