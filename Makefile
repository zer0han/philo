# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 17:37:52 by rdalal            #+#    #+#              #
#    Updated: 2025/04/30 15:14:28 by rdalal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

HEAD	= includes/

CC		= cc

CFLAGS	= -Wextra -Wall -Werror

SRCS_UTILS	= clean.c utils.c utils2.c init.c philo.c main.c watcher.c 

SRCS_UTILS_PATH	= srcs/

SRCS	=	$(addprefix $(SRCS_UTILS_PATH), $(SRCS_UTILS)) \

OBJS	= $(SRCS:.c=.o)

all: $(NAME)
		$(print_flag)

$(NAME):	$(OBJS) $(HEAD)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "$(GREEN)🚀 $(NAME) BUILT SUCCESSFULLY! 🚀$(RESET)"

.c.o:
			@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEAD)
			@echo "$(YELLOW)COMPILING: $<$(RESET)"

clean:	root-clean
		@echo "$(RED)🧹 CLEANED OBJECT FILES 🧹$(RESET)"
		@echo "$(GREEN)"
		@cat ascii_art_fclean.txt
		@echo "$(RESET)"
	
root-clean:
			@rm -f $(OBJS)

fclean: root-fclean
		@echo "$(RED) 🧹🧹 FULL CLEAN COMPLETE 🧹🧹$(RESET)"
		@echo "$(BABEBLUEB)"
		@cat ascii_art_fclean.txt
		@echo "$(RESET)"

root-fclean: root-clean
			@rm -f $(NAME)
			
re: fclean all

.PHONY: all clean fclean re root-clean root-fclean

# Colors
RESET = \033[0m
BOLD = \033[1m
GREEN = \033[1;32m
BLUE = \033[1;34m
BABEBLUEB = \033[1;38;5;153m
RED = \033[1;31m
PSTL_ORGB = \033[1;38;2;255;179;102m
YELLOW = \033[1;33m

define print_flag
	@echo "$(GREEN) 🚀 COMPILATION COMPLETE 🚀$(RESET)"
	@echo "$(BLUE).☆.｡.:*・°･.｡*･.｡* .☆.｡.:*.☆.｡.:*・°･.｡*･.｡*.☆.｡.:*.☆.｡.:*.☆.｡.:*.☆.｡.:*.☆.｡.:*.☆.｡.:*.☆.｡.:*$(RESET)"
	@echo "$(PSTL_ORGB)"
	@cat ascii_art.txt
	@echo ""
	@echo "$(RESET)"
	@echo "$(BLUE).☆.｡.:*・°･.｡*･.｡* .☆.｡.:*.☆.｡.:*・°･.｡*･.｡*.☆.｡.:*.☆.｡.:*.☆.｡.:*.☆.｡.:*.☆.｡.:*.☆.｡.:*.☆.｡.:*$(RESET)"
endef