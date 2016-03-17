#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include "ft_printf.h"
# include "get_next_line.h"

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>

# define ENV_NAME_LENGTH		256
# define ENV_CONTENT_LENGTH		4096

# define COMMAND_ELEM_LENGTH	1024
# define BUILT_IN_CMD_LENGTH	256
# define NBR_BUILTIN			1

# define MAX_PROMT_LENGTH		256


typedef struct s_app			t_app;
typedef struct s_elem_env		t_elem_env;
typedef struct s_env			t_env;
typedef struct s_elem_command	t_elem_command;
typedef struct s_command		t_command;
typedef struct s_built_in		t_built_in;
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

struct				s_command
{
	t_elem_command	*first;
	t_elem_command	*last;
	t_elem_command	*current;
	int				size;
	int				token;
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

/*
** read_env.c
*/
char				**env_to_tab(t_app *app);
void				insert_env(t_app *app, int iteration);
void				read_env(t_app *app);

/*
** loop.c
*/
void				loop(t_app *app);

/*
** command.c
*/
char				**cmd_to_tab(t_app *app);
void				decode_command(t_app *app);

/*
** bi_??
*/
void				bi_exit(t_app *app);

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
#endif
