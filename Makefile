NAME = ./ircserv


SRC = srcs/main.cpp \
	  srcs/external_func.cpp \
	  srcs/Server.cpp \
	  srcs/client.cpp \
	  srcs/parse.cpp \
	  srcs/sendMsg.cpp \
	  srcs/channel.cpp \
	  srcs/commands.cpp \

CXX		= c++

CXXFLAGS	= -std=c++98 -Wall -Wextra -Werror 

OBJS 	= $(SRC:.cpp=.o)

all: $(NAME) 

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)

%.o : %.cpp %.hpp
	c++ ${CXXFLAGS}  -c $< -o $@
	


clean:
	rm -rf $(OBJS)
	rm -rf client server

fclean : clean
	rm -rf $(NAME)

re : fclean all


push : 
	git add .
	git commit -m "IRC"
	git push