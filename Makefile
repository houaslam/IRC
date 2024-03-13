NAME = Webserver
CXX = c++
CXX += -fsanitize=address -g3
CXXFLAGS = -Wall -Wextra -Werror
EXTRA_CFLAGS = -std=c++98

SRC = srcs/main.cpp 

OBJ = ${SRC:.cpp=.o} ${CNF:.cpp=.o}

all : ${NAME}

%.o : %.cpp %.hpp 
	c++ ${CXXFLAGS} ${EXTRA_CFLAGS} -c $< -o $@

${NAME} : ${OBJ}
	${CXX}  ${OBJ} -o ${NAME}

clean :
	rm -rf ${OBJ}
	rm -rf client server

fclean : clean
	rm -rf ${NAME}

re : fclean all

push : 
	git add .
	git commit -m "IRC"
	git push