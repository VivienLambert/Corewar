CC				=	/usr/bin/gcc

CFLAGS			=	-Wall -Wextra -Werror

MAKE			=	/usr/bin/make

RM				=	/bin/rm

DEBUG			=

LN				=	ln -s

NAME_ASM		=	asm

ASM_DIR			=	asmsrc

NAME_VM			=	corewar

VM_DIR			=	vm

NAME_VISU		=	visu

SRC_VISU		=	visu_go/main.go visu_go/display.go visu_go/keys.go\
					visu_go/read.go

LIB_DIR			=	libft

############################## RULES ###########################################

all				: $(NAME_VISU)
	@ $(MAKE) $(CFLAGS) -C $(LIB_DIR)
	@ $(MAKE) $(CFLAGS) -C $(ASM_DIR)
	@ $(MAKE) $(CFLAGS) -C $(VM_DIR)

$(NAME_ASM)		:
	@ $(MAKE) $(CFLAGS) -C $(ASM_DIR)

$(NAME_VM)		:
	@ $(MAKE) $(CFLAGS) -C $(VM_DIR)

$(NAME_VISU)	: $(SRC_VISU)
	go build -o $(NAME_VISU) ./visu_go

clean			:
	@ $(MAKE) clean -C $(LIB_DIR)
	@ $(MAKE) clean -C $(ASM_DIR)
	@ $(MAKE) clean -C $(VM_DIR)
	@ rm -f ./visu

fclean			:	clean
	@ $(MAKE) fclean -C $(LIB_DIR)
	@ $(MAKE) fclean -C $(ASM_DIR)
	@ $(MAKE) fclean -C $(VM_DIR)
	@ rm -f ./visu

re				:	fclean
	@ $(MAKE) all

############################## DISPLAY #########################################

YELLOW			=	\033[0;33m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
WHITE			=	\x1b[0m

############################## OTHER ###########################################

.PHONY			:	clean fclean re all $(NAME_VM) $(NAME_ASM)
