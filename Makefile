
CC = g++

SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

RM = rm -f

NAME = plazza

LDFLAGS =

CFLAGS = -Wall

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

all: $(NAME)

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) $(OBJS)

re: fclean all

ui:
	@echo "TODO"

.PHONY: fclean clean re all
