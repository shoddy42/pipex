# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: wkonings <wkonings@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 16:21:56 by wkonings      #+#    #+#                  #
#    Updated: 2022/11/05 17:26:34 by wkonings      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


# --------------- VARIABLES ---------------#

NAME		:=	pipex
CC			:=	gcc
FLAGS		:=	-Wall -Wextra -Werror

# --------------- DIRECTORIES ------------ #

BIN_DIR		:=
INCLUDE_DIR	:=	include
LIBS_DIR	:=	libft
OBJS_DIR	:= 	obj
SRC_DIR		:=	src

# --------------- FILES -------------------#

HEADERS		:=	$(addprefix $(INCLUDE_DIR)/, pipex.h)
FILES		:=	pipex utils heredoc get_next_line_bonus get_next_line_utils_bonus
SRCS		:=	$(addprefix $(SRC_DIR)/,$(FILES:%=%.c))
OBJS		:=	$(addprefix $(OBJS_DIR)/,$(notdir $(SRCS:%.c=%.o)))
LIB_LIST	:=	$(LIBS_DIR)/libft.a
LIB_FT		:=	libft
INC			:=	-I include

all: $(NAME)

$(NAME): $(OBJS) $(LIB_LIST)
	$(CC) $(FLAGS) $(INC) -o $(NAME) $^

$(OBJS_DIR):
	@mkdir -p $@

$(OBJS_DIR)/%.o:$(SRC_DIR)/%.c $(HEADERS) | $(OBJS_DIR)
	$(CC) $(FLAGS) $(INC) -c $< -o $@ 

$(LIB_LIST):
	@make -C $(LIBS_DIR)

clean:
	/bin/rm -rf $(OBJS_DIR)

fclean:	clean
	/bin/rm -f $(NAME)

libclean:
	@make -C $(LIBS_DIR) clean
	@$(RM) $(LIBS_FT).a

flclean: libclean fclean

re: fclean all

.PHONY: clean fclean re libclean flclean