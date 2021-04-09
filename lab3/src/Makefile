NAME		= lab3


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
	gcc $(CFLAGS) $(OBJS) -o $(NAME)

task5: $(OBJSM) $(OBJSSQ)
	gcc $(CFLAGS) $(OBJSSQ) -o sequential_min_max
	gcc $(CFLAGS) $(OBJSM) -o task5


$(OBJRID)%.o: %.c
	@mkdir -p $(OBJRID)
	gcc $(OPTFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJRID)
	@rm -rf task5
	@rm -rf sequential_min_max
	@rm -rf utils.o
	@rm -rf find_min_max.o
	@rm -rf a.out
	@rm -rf lab3

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	fclean all re clean
