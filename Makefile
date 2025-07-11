SRC= builtins/builtins.c builtins/ft_cd_handler.c builtins/ft_echo.c builtins/ft_export.c exec_util.c\
	execution.c utils2.c builtins/utils.c ifs_split.c builtins/uns_exp_exit.c mask_creation.c redirections_handle.c\
	minishell.c store_data_process.c handle_cmd_flage.c prompt_gen.c tokenize_utils.c quote_utils.c make_nd_store_env.c\
	heap_controller/g_container.c  heap_controller/managment_utils.c redirection_utils.c release_boxs.c aditional_utils.c\
	code_handler.c herdoc_reader.c key_parse_utlis.c reset_boxs_utils.c syntax_check.c init_shlvl.c sig_hand.c pipe_utils.c\
	reader_helper.c tokens_seter.c child_exec.c builtins/export_utils.c cmd_path_check.c env_handle.c expansion/extend_fns.c\
	expansion/expansion_handle.c expansion/expand_utils.c

OBJ= $(SRC:%.c=%.o)
NAME= Sheru
LIBS= libs/libft.a
CC= cc
CFLAGS= -Wall -Werror -Wextra -ggdb

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(OBJ) -O1 -Llibs -lft -lreadline -o $(NAME)

%.o: %.c
	$(CC) -O1 -I includes $(CFLAGS) -c $< -o $@

$(LIBS):
	mkdir -p libs
	make -C libft

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(LIBS) libs $(NAME)

re: fclean all

.PHONY: all re clean fclean

.SECONDARY: $(OBJ)