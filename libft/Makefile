# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyelena <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/04 09:25:06 by jyelena           #+#    #+#              #
#    Updated: 2020/11/07 22:49:50 by jyelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc

LIB		=	ar rc libft.a

FLAGS	=	-Wall -Wextra -Werror

NAME	=	libft.a

DIRSRC	=	./

DIRHEAD	=	./

SRC		=	$(DIRSRC)ft_memset.c \
			$(DIRSRC)ft_bzero.c \
			$(DIRSRC)ft_memcpy.c \
			$(DIRSRC)ft_memccpy.c \
			$(DIRSRC)ft_memmove.c \
			$(DIRSRC)ft_memchr.c \
			$(DIRSRC)ft_memcmp.c \
			$(DIRSRC)ft_strlen.c \
			$(DIRSRC)ft_strlcpy.c \
			$(DIRSRC)ft_strlcat.c \
			$(DIRSRC)ft_strchr.c \
			$(DIRSRC)ft_strrchr.c \
			$(DIRSRC)ft_strnstr.c \
			$(DIRSRC)ft_strncmp.c \
			$(DIRSRC)ft_atoi.c \
			$(DIRSRC)ft_isalpha.c \
			$(DIRSRC)ft_isdigit.c \
			$(DIRSRC)ft_isalnum.c \
			$(DIRSRC)ft_isascii.c \
			$(DIRSRC)ft_isprint.c \
			$(DIRSRC)ft_toupper.c \
			$(DIRSRC)ft_tolower.c \
			$(DIRSRC)ft_calloc.c \
			$(DIRSRC)ft_strdup.c \
			$(DIRSRC)ft_substr.c \
			$(DIRSRC)ft_strjoin.c \
			$(DIRSRC)ft_strtrim.c \
			$(DIRSRC)ft_split.c \
			$(DIRSRC)ft_itoa.c \
			$(DIRSRC)ft_strmapi.c \
			$(DIRSRC)ft_putchar_fd.c \
			$(DIRSRC)ft_putstr_fd.c \
			$(DIRSRC)ft_putendl_fd.c \
			$(DIRSRC)ft_putnbr_fd.c \
			$(DIRSRC)ft_strcpy.c \
			$(DIRSRC)ft_newstring.c

SRC_B	=	$(DIRSRC)ft_lstnew.c \
			$(DIRSRC)ft_lstadd_front.c \
			$(DIRSRC)ft_lstsize.c \
			$(DIRSRC)ft_lstlast.c \
			$(DIRSRC)ft_lstadd_back.c \
			$(DIRSRC)ft_lstdelone.c \
			$(DIRSRC)ft_lstclear.c \
			$(DIRSRC)ft_lstiter.c \
			$(DIRSRC)ft_lstmap.c

OBJ		=	$(SRC:.c=.o)

OBJ_B	=	$(SRC_B:.c=.o)

.c.o:
			$(CC) $(FLAGS) -c -I$(DIRHEAD) $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(LIB) $(OBJ)

bonus:		$(OBJ) $(OBJ_B)
			ar rc $(NAME) $(OBJ) $(OBJ_B)

clean:
			rm -f $(OBJ) $(OBJ_B)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

so:			$(OBJ) $(OBJ_B)
			gcc -o libft.so $(OBJ) $(OBJ_B) -shared

norm:
			@norminette -R CheckDefine *.h
			@norminette -R CheckForbiddenSourceHeader *.c

.PHONY:		all clean fclean re so bonus norm