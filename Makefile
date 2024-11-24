NAME            =   minishell
SRC             =   minishell.c \
					error.c\
					paths.c\
					prompt.c\
					exect.c\
					parser.c\
					utils/lib_ft.c utils/lib_ft1.c utils/ft_split.c

CC          =   gcc
CFLAGS          =   -Wall -Wextra -Werror -g3 -g -fsanitize=address -lreadline -lhistory

RM              =   rm -f
CLR_RMV     := \033[0m
RED         := \033[1;31m
GREEN       := \033[1;32m
YELLOW      := \033[1;33m
BLUE        := \033[1;34m
CYAN        := \033[1;36m

OBJS = $(SRC:.c=.o)

all: $(NAME) pato

$(NAME): $(OBJS)
		@clear
		@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CYAN}"
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:			pato 
				@echo "$(RED)Deleting ${YELLOW}.o ${CLR_RMV}"
				$(RM) $(OBJS)

pato:			
				@clear 
				@echo "$(BLUE)███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
				@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
				@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
				@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
				@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
				@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"


fclean:         clean
				@echo "$(RED)Deleting ${YELLOW}.a ${CLR_RMV}"
				$(RM) $(NAME)

re:             fclean all

.PHONY: all clean fclean re