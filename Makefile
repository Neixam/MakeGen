#  Auteur       : Bourennane Amine
#  Creation     : 20-07-2021
#  Modification : 20-07-2021

#  Variable
purple	=	\033[0;35m
cyan	=	\033[0;36m
green	=	\033[0;32m
neutral	=	\033[0m
red		=	\033[31m

CC      =	gcc
CFLAGS  =	-ansi -pedantic -Wall
EXEC	=	MakeGen

INC_PATH=	includes/
SRC		=	Main.c \
			Write.c \
			StockData.c \
			Files.c \
			Process.c \
            BasicFt.c \

SRC_PATH= $(shell find src -type d)
vpath %.c $(foreach rep, $(SRC_PATH), $(rep))
OBJ_PATH=	obj/
OBJ		=	$(addprefix $(OBJ_PATH),$(SRC:.c=.o))

#  Compilation
$(EXEC)				:	$(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_PATH)Main.o		:	$(INC_PATH)StockData.h $(INC_PATH)Process.h

$(OBJ_PATH)Write.o		:	$(INC_PATH)Write.h $(INC_PATH)Files.h

$(OBJ_PATH)StockData.o	:	$(INC_PATH)StockData.h $(INC_PATH)BasicFt.h $(INC_PATH)Files.h

$(OBJ_PATH)Files.o		:	$(INC_PATH)Files.h $(INC_PATH)BasicFt.h

$(OBJ_PATH)Process.o	:	$(INC_PATH)Process.h $(INC_PATH)Files.h $(INC_PATH)StockData.h

$(OBJ_PATH)%.o			:	%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) -o $@ -c $< $(CFLAGS) -I $(INC_PATH)

#  Rules
all			: $(EXEC)

clean		:
	@echo "${red}Deleted objects ...${neutral}"
	@/bin/rm -rf $(OBJ_PATH) 
	@echo "${green}END${neutral}"

mrproper	:	clean
	@echo "${red}Uninstall project ...${neutral}"
	@/bin/rm -rf $(EXEC)
	@echo "${green}END${neutral}"

re			:	mrproper all
