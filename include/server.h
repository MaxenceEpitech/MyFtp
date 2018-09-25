/*
** EPITECH PROJECT, 2018
**
** File description:
** myftp
*/

#ifndef SERVER_H_
# define SERVER_H_

/*      __________ ________________________ __________
**
**                        INCLUDES
**      __________ ________________________ __________
*/
# include <stdio.h>
# include <stdbool.h>

/*      __________ ________________________ __________
**
**                        DEFINES
**      __________ ________________________ __________
*/
# define E_MALLOC "Malloc fail.\n"

# define USAGE_1 "USAGE: ./server port path\n"
# define USAGE_2 "\tport is the port number on which the server socket listens\n"
# define USAGE_3 "\tpath is the path to the home directory for the Anonymous user\n"

# define BUFFER_SIZE 1024

# define E_PERM "Permission denied."
# define E_PASS "Login with USER first."
# define E_USER "Login with USER first."
# define E_LOGIN "Please login with USER and PASS."
# define E_BLOGIN "Login incorrect."
# define E_CMD "Unknown command."
# define E_CLOSE "Error occured while closing client fd.\n"
# define E_DIR "Failed to change directory."

# define I_PASS "Please specify the password."
# define I_DIR "Directory successfully changed."
# define I_CMD "214 The following commands are recognized : "

/*
**                   __ Returns Values __
*/
# define SUCCESS	0
# define ERROR		84

/*
**                       __ TypeDef __
*/
typedef struct s_data {
	int port;
	char *path;
	char *username;
	char *password;
	char *ip;
	int c_fd;
	int s_fd;
	bool connected;
	int pasv_fd;
} t_data;

typedef struct s_ptr {
	char *str;
	int (*fnc)();
} t_ptr;

/*      __________ ________________________ __________
**
**                         Myftp
**      __________ ________________________ __________
*/
/*
**		     __ my_str_to_wordtab.c __
*/
int count_words(char *, char);
char *alloc_line(char *, char, int *);
char **my_str_to_wordtab(char *, char);

/*
**                   __ tool.c __
*/
int check_usage(int, char **);
char *clear_cmd(char *);
void send_message(int, char *, t_data *);

/*
**                   __ run.c __
*/
int run(t_data *);

/*
**                   __ dir.c __
*/
int cwd(char **, t_data *);
int cdup(char **, t_data *);
int dele(char **, t_data *);
int pwd(char **, t_data *);

/*
**                   __ init.c __
*/
t_data *init(char **);
void clear(t_data *);

/*
**                   __ server.c __
*/
int connect_to_server(t_data *, int);
int username(char **, t_data *);
int password(char **, t_data *);

/*
**                   __ run.c __
*/
int quit(char **, t_data *);
int run(t_data *);
int loop(t_data *, char **);
int help(char **, t_data *);

/*
**                   __ list.c __
*/
int list(char **, t_data *);

/*
**                   __ get_next_line.c __
*/
char *get_next_line(const int fd);

/*
**                   __ command.c __
*/
int noop(char **tab, t_data *);
int pasv(char **tab, t_data *);
int port(char **tab, t_data *);

#endif /* !SERVER_H_ */
