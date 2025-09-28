NAME:=btc
CFLAGS:= -g -std=c++98 -Wall -Werror -Wextra
CC:= c++

OBJS:= ${patsubst(%.cpp, %.o, ${SRCS})}
SRCS:=srcs/main.cpp srcs/BitcoinExchange.cpp 


all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: re fclean clean all

