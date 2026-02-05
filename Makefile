NAME            =   minishell
SRC             =   minishell.c \
					error.c\
					paths.c\
					prompt.c\
					exect.c\
					parser.c\
					parser_aux.c\
					cd_echo.c\
					env_pwd.c\
					pipelinig.c\
					utils/lib_ft.c utils/lib_ft1.c utils/ft_split.c utils/ft_atoi.c utils/ft_itoa.c\
					utils/split_outside_quotes.c\
					matrix.c\
					quotes.c\
					quotes_expansion.c\
					quotes_processing.c\
					redirections.c\
					redirections_aux.c\
					redirections_parsing.c\
					heredoc.c\
					pipe_aux.c\
					pipe_child.c\
					variables.c\
					variables_aux.c\
					export.c\
					export_aux.c\
					unset.c\
					export_utils.c\
					exit_status.c\
					signals.c\
					cd_echo_aux.c\

CC          =   gcc
CFLAGS          =   -Wall -Wextra -Werror -g3 -g -lreadline -lhistory

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
		@echo -e "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CYAN}"
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:			pato 
				@echo -e "$(RED)Deleting ${YELLOW}.o ${CLR_RMV}"
				$(RM) $(OBJS)

pato:			
				@clear 
				@echo -e "$(RED)███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
				@echo -e "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
				@echo -e "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
				@echo -e "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
				@echo -e "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
				@echo -e "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"


fclean:         clean
				@echo "$(RED)Deleting ${YELLOW}.a ${CLR_RMV}"
				$(RM) $(NAME)

re:             fclean all

.PHONY: all clean fclean re
