
CC = g++

SRCS =  main.cpp \
        Plazza.cpp \
        Task.cpp \
        Scheduler.cpp \
        Worker.cpp \
        Thread.cpp \
        Logger.cpp \
        ProcessWrapper.cpp

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
