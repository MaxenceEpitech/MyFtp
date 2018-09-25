/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** cpp
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "server.h"

int quit(char **tab, t_data *data)
{
	printf("Client disconected IP = [%s]\n", data->ip);
	send_message(221, "Goodbye.", data);
	exit(SUCCESS);
	return (SUCCESS);
}

int check_usage(int ac, char **av)
{
	if (ac < 3 || strcmp(av[1], "-help") == 0) {
		printf("%s%s%s", USAGE_1, USAGE_2, USAGE_3);
		return (ERROR);
	}
	return (SUCCESS);
}

char *clear_cmd(char *cmd)
{
	char *new = malloc(sizeof(char) * (strlen(cmd) + 1));

	if (new == NULL)
		return (NULL);
	else if (strlen(cmd) == 0)
		return ("");
	for (int i = 0; cmd[i] != 0
		&& cmd[i] != '\n'
		&& cmd[i] != '\r'; i++) {
		new[i] = cmd[i];
	}
	new[strlen(cmd)] = 0;
	return (new);
}

void send_message(int id, char *msg, t_data *data)
{
	if (id >= 0) {
		dprintf(data->c_fd, "%d %s\r\n", id, msg);
	} else if (id == -1) {
		dprintf(data->c_fd, "%s", msg);
	} else {
		dprintf(data->c_fd, "\r\n");
	}
}
