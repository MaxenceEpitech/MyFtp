/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** cpp
*/

#include <string.h>
#include <stdlib.h>

#include "server.h"

static t_ptr g_cmd[12] =
{
	{"USER", username},
	{"PASS", password},
	{"CWD", cwd},
	{"CDUP", cdup},
	{"HELP", help},
	{"noop", noop},
	{"PWD", pwd},
	{"QUIT", quit},
	{"PASV", pasv},
	{"PORT", port},
	{"LIST", list},
	{NULL}
};

char *clear_ret(char *cmd)
{
	char *new = malloc(sizeof(char) * (strlen(cmd) + 1));
	int i;

	if (new == NULL)
		return (NULL);
	for (i = 0; cmd[i] != 0 && cmd[i] != '\r'; i++) {
		new[i] = cmd[i];
	}
	new[i] = 0;
	return (new);
}

int run(t_data *data)
{
	size_t size = BUFFER_SIZE;
	char *cmd = malloc(sizeof(char) * size);
	char **tab;

	send_message(220, "Hello newcomer.", data);
	if (cmd == NULL)
		return (ERROR);
	cmd = get_next_line(data->c_fd);
	while (1) {
		tab = my_str_to_wordtab(clear_ret(cmd), ' ');
		if (tab == NULL || tab[0] == NULL)
			return (ERROR);
		else if (strcmp(cmd, "") != 0
			&& loop(data, tab) == ERROR)
			return (ERROR);
		cmd = get_next_line(data->c_fd);
	}
	return (SUCCESS);
}

int loop(t_data *data, char **tab)
{
	for (int i = 0; g_cmd[i].str; i++) {
		if (strcasecmp(tab[0], g_cmd[i].str) == 0) {
			if (g_cmd[i].fnc(tab, data) == ERROR)
				return (ERROR);
			return (SUCCESS);
		}
	}
	if (data->connected == true) {
		send_message(500, E_CMD, data);
	} else {
		send_message(530, E_LOGIN, data);
	}
	return (SUCCESS);
}

int help(char **tab, t_data *data)
{
	send_message(-1, I_CMD, data);
	for (int i = 0; g_cmd[i].str != NULL; i++) {
		send_message(-1, g_cmd[i].str, data);
		send_message(-1, " ", data);
	}
	send_message(-2, "", data);
}
