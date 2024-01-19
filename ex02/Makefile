NAME =	PmergeMe

SRC =	main.cpp \
		PmergeMe.cpp

OBJ		= ${SRC:%.cpp=objects/%.o}

CC		= c++
FLAGS	= -Wall -Wextra -Werror -std=c++98 -g3

${NAME}: ${OBJ} *.hpp
		 ${CC} ${FLAGS} -o ${NAME} ${OBJ}

objects/%.o: %.cpp
			mkdir -p $(dir $@)
			${CC} ${FLAGS} -c -o $@ $^

all:	${NAME}

clean:
		rm -rf objects

fclean:	clean
		rm -rf ${NAME}

re:		fclean all

.PHONY: clean fclean all re% 