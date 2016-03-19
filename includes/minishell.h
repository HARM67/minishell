#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "ft_printf.h"
# include "get_next_line.h"

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <signal.h>

# define ENV_NAME_LENGTH		256
# define ENV_CONTENT_LENGTH		4096

# define COMMAND_ELEM_LENGTH	1024
# define BUILT_IN_CMD_LENGTH	256
# define NBR_BUILTIN			5

# define MAX_PROMT_LENGTH		256
# define MAX_FILENAME			256


typedef struct s_app			t_app;
typedef struct s_elem_env		t_elem_env;
typedef struct s_env			t_env;
typedef struct s_elem_command	t_elem_command;
typedef struct s_command		t_command;
typedef struct s_built_in		t_built_in;
typedef struct s_file_out		t_file_out;
typedef struct s_file_in		t_file_in;
typedef struct s_file_lst		t_file_lst;
typedef struct stat				t_stat;

struct				s_built_in
{
	char			command[BUILT_IN_CMD_LENGTH];
	int				size;
	void			(*do_it)(t_app *);
};

struct				s_elem_command
{
	t_elem_command	*next;
	t_elem_command	*previous;
	int				size;
	int				pos;
	char			command[COMMAND_ELEM_LENGTH];
};

struct				s_file_out
{
	char			filename[MAX_FILENAME];
	int				fd;
	int				size;
	t_file_out		*next;
	t_file_out		*previous;
};

struct				s_file_in
{
	char			filename[MAX_FILENAME];
	int				fd;
	int				size;
	t_file_in		*next;
	t_file_in		*previous;
};

struct				s_file_lst
{
	t_file_out		*first_out;
	t_file_out		*last_out;
	t_file_in		*first_in;
	t_file_in		*last_in;
	int				nbr_in;
	int				nbr_out;
};

struct				s_command
{
	char			env_find[ENV_NAME_LENGTH];
	t_elem_command	*first;
	t_elem_command	*last;
	t_elem_command	*current;
	t_command		*next;
	t_command		*previous;
	t_file_lst		files;
	pid_t			child_pid;
	char			*cmd;
	int				env_find_tmp;
	int				size;
	char			piped;
	int				fildes[2];

//	int				token;
};

struct				s_elem_env
{
	char			name[ENV_NAME_LENGTH];
	char			content[ENV_CONTENT_LENGTH];
	int				size;
	t_elem_env		*next;
	t_elem_env		*previous;
};

struct				s_env
{
	t_elem_env		*first;
	t_elem_env		*last;
	int				size;
};

struct 				s_app
{
	char			prompt[MAX_PROMT_LENGTH];
	t_built_in		bi_cmd[NBR_BUILTIN];
	t_env			environement;
	t_command		lst_cmd;
	t_command		*first_cmd;
	t_command		*last_cmd;
	t_command		*cur_cmd;
	int				token;
	int				nbr_cmd;
	int				bad_cmd;
	int				ac;
	char			**av;
	char			**env;
	char			*str_cur_cmd;
	unsigned char	stop;
};

/*
** app.c
*/
void				init_app(t_app *app);
void				run_app(t_app *app);

/*
**	put_error.c
*/
void				put_error(char *str);
void				put_error_cmd(t_app *app, char	*str);

/*
** read_env.c
*/
void				print_tab(char	**tab);
t_elem_env			*new_env(t_app *app, char *line);
char				**env_to_tab(t_app *app);
void				insert_env(t_app *app);
void				insert_new_env(t_app *app, t_elem_env *new);
void				read_env(t_app *app);

/*
** loop.c
*/
void				loop(t_app *app);

/*
** command.c
*/
void				clean_cmd(t_command	*lst);
char				**cmd_to_tab(t_app *app);
void				decode_command(t_app *app);

/*
** built_in.c
*/
void				init_built_in(t_app *app);
int					check_built_in(t_app *app);

/*
** exec.c
*/
void				execute(t_app *app);

/*
** environement
*/
t_elem_env			*get_env(t_app *app, char *env);

/*
** prompt.c
*/
void				print_prompt(t_app *app);

/*
** lst_command.c 
*/
void				insert_new_lst_command(t_app *app);
void				clean_lst_command(t_app *app);

/*
** files.c
*/
void				print_files_lst(t_file_lst *lst);
int					is_file_char(char c);
void				insert_file_out(t_file_lst *lst);
void				insert_file_in(t_file_lst *lst);
void				clean_file_lst(t_file_lst *lst);
void				link_out_file(t_file_lst *lst);
void				link_in_file(t_file_lst *lst);

/*
** bi_??
*/
void				bi_exit(t_app *app);
void				bi_setenv(t_app *app);
void				bi_unsetenv(t_app *app);
void				bi_cd(t_app *app);
#endif
