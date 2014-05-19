# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/25 20:36:16 by gpetrov           #+#    #+#              #
#    Updated: 2014/05/17 18:47:07 by gpetrov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= client
NAME2		= serveur
FILES		= main.c
FILES2		= main.c tools.c
SRCS		= $(addprefix client_dir/srcs/, $(FILES))
SRCS2	 	= $(addprefix serveur_dir/srcs/, $(FILES2))
OBJS		= $(SRCS:client_dir/srcs/%.c=client_dir/.obj/%.o)
OBJS2		= $(SRCS:serveur_dir/srcs/%.c=serveur_dir/.obj/%.o)
INC			= -I client_dir/includes -I libft/includes
INC2		= -I serveur_dir/includes -I libft/includes
FLAGS		=  -Wall -Wextra -Werror -g
LIB			= -L libft -lft

all: $(NAME) $(NAME2)

$(NAME): $(OBJS) $(OBJS2)
	@make -C libft
	@cc $(FLAGS) $(SRCS) -o $(NAME) $(INC) $(LIB)
	@cc $(FLAGS) $(SRCS2) -o $(NAME2) $(INC2) $(LIB)
	@echo "\n > \033[36mft_p\033[m project compilation [\033[32mDONE\033[m]\n"

client_dir/.obj/%.o: client_dir/srcs/%.c
	@mkdir -p client_dir/.obj
	@cc -c $< -o $@ $(FLAGS) $(INC)

serveur_dir/.obj/%.o: serveur_dir/srcs/%.c
	@mkdir -p serveur_dir/.obj
	@cc -c $< -o $@ $(FLAGS) $(INC2)

clean:
	@rm -rf .obj

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@rm -f $(NAME2)
	@echo "fclean : [\033[32mDONE\033[m]"

re: fclean all

