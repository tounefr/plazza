
CC = g++

SRCS =  common/Task.cpp \
        common/Thread.cpp \
        encryption/CaesarCipher.cpp \
        encryption/Cipher.cpp \
        encryption/XorCipher.cpp \
        network/IPSocket.cpp \
        network/Socket.cpp \
        network/UnixSocket.cpp \
        parsing/Parsing.cpp \
        Logger.cpp \
        Plazza.cpp \
        ProcessWrapper.cpp \
        Scheduler.cpp \
        Worker.cpp \
        WorkerPool.cpp \
        main.cpp

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
