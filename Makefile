
CC = g++

SRCS =  main.cpp \
        Plazza.cpp \
        Task.cpp \
        Scheduler.cpp \
        WorkerPool.cpp \
        Thread.cpp \
        Logger.cpp \
        ProcessWrapper.cpp \
        Worker.cpp \
        NamedPipeEndPoint.cpp

OBJS = $(SRCS:.cpp=.o)

RM = rm -f

NAME = plazza

LDFLAGS =

CFLAGS = -Wall -lpthread

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
