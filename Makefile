
CC = g++

SRCS =  Plazza.cpp \
        main.cpp \
        encryption/CaesarCipher.cpp \
        encryption/Cipher.cpp \
        encryption/XorCipher.cpp \
        network/ip/ServerSocket.cpp \
        network/ip/Socket.cpp \
        parsing/InstructionsParsing.cpp \
        parsing/FileParsing.cpp \
        core/ProcessWrapper.cpp \
        core/Scheduler.cpp \
        core/Worker.cpp \
        core/WorkerPool.cpp \
        common/Task.cpp \
        common/Thread.cpp \
        common/Logger.cpp \
        common/ConditionVariable.cpp \
        common/Client.cpp

OBJS = $(SRCS:.cpp=.o)

RM = rm -f

NAME = plazza

LDFLAGS = -I.

CFLAGS = -std=c++11 -Wall -lpthread

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
