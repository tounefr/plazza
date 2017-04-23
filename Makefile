
CC = g++

SRCS =  common/Task.cpp \
        common/Thread.cpp \
        common/Logger.cpp \
        encryption/CaesarCipher.cpp \
        encryption/Cipher.cpp \
        encryption/XorCipher.cpp \
        network/IPSocket.cpp \
        network/Socket.cpp \
        network/UnixSocket.cpp \
        parsing/Parsing.cpp \
        core/ProcessWrapper.cpp \
        core/Scheduler.cpp \
        core/Worker.cpp \
        core/WorkerPool.cpp \
        Plazza.cpp \
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
