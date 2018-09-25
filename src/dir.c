/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** cpp
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"

int cwd(char **tab, t_data *data)
{
	if (data->connected == true) {
		if (tab[1] != NULL) {
			if ((chdir(tab[1])) != -1)
				send_message(250, I_DIR, data);
			else
				send_message(550, E_DIR, data);
		} else
			send_message(550, E_DIR, data);
	} else
		send_message(530, E_LOGIN, data);
	return (SUCCESS);
}

int cdup(char **tab, t_data *data)
{
	if (data->connected == true) {
		if (chdir("..") != -1)
			send_message(250, I_DIR, data);
		else
			send_message(550, E_DIR, data);
	} else {
		send_message(530, E_LOGIN, data);
	}
	return (SUCCESS);
}

int dele(char **tab, t_data *data)
{
	return (SUCCESS);
}

char *get_dir(void)
{
	char *dir = getcwd((char *)NULL, 0);
	char *new;
	int i = 1;

	if (dir == NULL)
		return (NULL);
	new = malloc(sizeof(char) * (strlen(dir) + 3));
	new[0] = 34;
	for (i = 1; dir[i - 1]; i++) {
		new[i] = dir[i - 1];
	}
	new[i] = 34;
	new[i + 1] = 0;
	return (new);
}

int pwd(char **tab, t_data *data)
{
	char *dir;

	if (data->connected == true) {
		dir = get_dir();
		if (dir == NULL)
			return (ERROR);
		send_message(257, dir, data);
	} else
		send_message(530, E_LOGIN, data);
	return (SUCCESS);
}
