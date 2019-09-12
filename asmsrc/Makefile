CC				=	/usr/bin/gcc

CFLAGS			=	-Wall -Wextra -Werror -g 

MAKE			=	/usr/bin/make

DEBUG			=

RM				=	/bin/rm

MKDIR			=	/bin/mkdir -p

NAME			=	asm

TARGET			=	../$(NAME)

SRC_DIR			=	srcs

ASM_SRC			=	\
		main.c print.c header.c freecom.c free.c tools.c charman.c label.c\
		instruction.c fillparams.c parsingseparator.c params.c filllabel.c\
		fillgeneric.c fillgeneric2.c params2.c paramgen.c syntaxerror.c\
		errorparams.c searchlabel.c write_code.c nameandcom.c strclentab.c\
		file.c label1.c retgnl.c utils.c

SRC_NAME		=	$(ASM_SRC)

SRC				=	$(addprefix $(SRC_DIR)/,$(SRC_NAME))

OBJ_DIR			=	objs

OBJ_NAME		=	$(SRC_NAME:.c=.o)

OBJ				=	$(addprefix $(OBJ_DIR)/,$(OBJ_NAME))

LIB_DIR			=	../libft

LDLIBS			=	-lft -lncurses

LDFLAGS			=	-L $(LIB_DIR)

INC				=	../includes

LIB_HEADERS		=	$(addprefix $(LIB_DIR)/, libft.h color.h)

HEADERS			=	$(LIB_HEADERS) $(addprefix ../includes/, asm.h op.h)

CPPFLAGS		=	$(addprefix -I, $(INC))

############################## RULES ###########################################

all				:	$(TARGET)

$(TARGET)		:	$(OBJ)
	@ $(MAKE) -C $(LIB_DIR) 2> /dev/null 1> /dev/null
	@ $(CC) $(CFLAGS) $(DEBUG) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@ echo "$(GREEN)$(NAME) compilé$(WHITE)"

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c $(HEADERS)
	@ $(MKODIR)
	@ $(CC) $(DEBUG) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean			:
	@ echo "$(RED)Suppression des .o$(WHITE)"
	@ $(RM) -rf $(OBJ_DIR)

fclean			:	clean
		@ $(RM) -f $(TARGET)

re				:	fclean all

MKODIR			=	if [ ! -d $(OBJ_DIR) ]; then \
		$(MKDIR) $(OBJ_DIR); fi

############################## DISPLAY #########################################

YELLOW			=	\033[0;33m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
WHITE			=	\x1b[0m

############################## OTHER ###########################################

.PHONY			:	clean fclean re all
