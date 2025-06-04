# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: You <you@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04                                #+#    #+#              #
#    Updated: 2025/06/04                                ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
SRC		= src/main.c src/print_error.c
OBJS	= $(SRC:.c=.o)
CC		= cc
FLAGS	= -Wall -Wextra -Werror -g

RESET		= \033[0m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
MAGENTA		= \033[1;35m
CYAN		= \033[1;36m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo -n "$(BLUE)Compiling: ["
	@i=0; total=30; \
	while [ $$i -le $$total ]; do \
		percent=$$(( 100 * $$i / $$total )); \
		done=$$(( $$total - $$i )); \
		printf "\r$(BLUE)Compiling: ["; \
		printf "%0.s█" `seq 1 $$i`; \
		printf "%0.s " `seq 1 $$done`; \
		printf "] %3d%%" $$percent; \
		sleep 0.02; \
		i=`expr $$i + 1`; \
	done; \
	echo "$(RESET)"
	@echo ""
	@echo "$(MAGENTA)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(CYAN)    ⚙️  Philosopher compilation complete! ⚙️    $(RESET)"
	@echo "$(MAGENTA)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo ""
	@echo "$(BLUE)✓ by meel-war$(RESET)"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "$(YELLOW)[Compiling] $< ✅$(RESET)"

clean:
	@rm -rf $(OBJS)
	@echo "$(YELLOW)[🧹] Object files cleaned.$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)[🔥] Executable and all cleaned.$(RESET)"

re: fclean all

v: $(NAME)
	@echo "$(BLUE)[🔍] Running Valgrind with args: $(ARGS)$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

.PHONY: all clean fclean re v
