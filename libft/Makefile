# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 10:47:24 by vlambert          #+#    #+#              #
#*   Updated: 2019/08/29 16:11:24 by bopopovi         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

CC			=	/usr/bin/gcc

CFLAGS		=	-Wall -Wextra -Werror

DEBUG		=

SRC			=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
		ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
		ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
		ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_strtoupper.c ft_tolower.c ft_memalloc.c ft_memdel.c \
		ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
		ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
		ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c \
		ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c \
		ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_printf.c \
		ft_printf_buffer.c ft_printf_color.c ft_printf_dtoa.c \
		ft_printf_get_flags.c ft_printf_ldtoa.c ft_printf_print_arg.c \
		ft_printf_tools.c ft_printf_type_char.c ft_printf_type_dbl.c \
		ft_printf_type_int.c ft_printf_type_ldbl.c ft_printf_type_others.c \
		ft_printf_type_str.c ft_gnl.c ft_realloc.c ft_strcdup.c ft_strclen.c \
	    ft_strjoinfree.c ft_read_all.c ft_raws_nbr.c ft_free_tab2d.c \
		ft_strcpyfast.c ft_atol.c ft_splitwhitespaces.c ft_splitandspaces.c \
		ft_reversebyte.c ft_toupper.c ft_isupper.c ft_strchrn.c ft_wctomb.c \
		ft_strrev.c ft_isspace.c ft_strcasestr.c ft_wcslen.c ft_wcsnlen.c \
		ft_strcasenequ.c ft_vprintf.c ft_ccat.c ft_strreplace.c


INC			=	color.h ft_printf.h get_next_line.h libft.h

OBJ			=	$(SRC:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJ) $(INC)
	@ echo "\033[0;33mCompilation de la libft...\x1b[0m"
	@ ar rc $(NAME) $(OBJ)
	@ ranlib $(NAME)
	@ echo "\033[0;32mLibft compilée -> OK\x1b[0m"

%.o			:	%.c $(INC)
	@ $(CC) $(DEBUG) $(CFLAGS) -c $<
	
clean		:
	@ rm -rf $(OBJ)
	@ echo "\033[0;31mSuppression des .o \033[0;33m-> \033[0;32mOK\x1b[0m"

fclean		:	clean
	@ rm -rf $(NAME)
	@ echo "\033[0;31mSuppression de la libft \033[0;33m-> \033[0;32mOK\x1b[0m"

re: fclean
	@ make all

.PHONY: clean fclean re all
