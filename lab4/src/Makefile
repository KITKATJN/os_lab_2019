NAME		= lab4


SRCS		= parallel_min_max.c  utils.c find_min_max.c
SRCSSQ		= sequential_min_max.c  utils.c find_min_max.c
SRCSMAIN		= main.c

OBJ			= $(SRCS:.c=.o)
OBJS		= $(addprefix $(OBJRID), $(OBJ))

OBJSQ			= $(SRCSSQ:.c=.o)
OBJSSQ		= $(addprefix $(OBJRID), $(OBJSQ))

OBJM			= $(SRCSMAIN:.c=.o)
OBJSM		= $(addprefix $(OBJRID), $(OBJM))

CFLAGS		=  -Wall -Werror -Wextra
OPTFLAGS	= -O3

OBJRID		= objs/

FIND_MIN_MAX		= find_min_max.h
UTILS_H		= utils.h

all:	$(NAME)

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $(NAME) && ./$(NAME) --seed "10" --array_size "160" --pnum "160" --timeout "1"

memory:
	gcc process_memory.c -o memory && ./memory

parallel:
	gcc -pthread parallel_sum.c utils.c find_min_max.c -o parallel && ./parallel --seed "10" --array_size "10" --threads_num "10"

$(OBJRID)%.o: %.c
	@mkdir -p $(OBJRID)
	gcc $(OPTFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJRID)
	@rm -rf memory
	@rm -rf sequential_min_max
	@rm -rf utils.o
	@rm -rf find_min_max.o
	@rm -rf a.out
	@rm -rf lab4
	@rm -rf parallel

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	fclean all re clean
