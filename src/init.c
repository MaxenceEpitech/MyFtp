/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** cpp
*/

#include <stdlib.h>
#include <string.h>

#include "server.h"

t_data *init(char **av)
{
	t_data *data = malloc(sizeof(t_data));

	if (data == NULL) {
		printf("At init : %s", E_MALLOC);
		return (NULL);
	}
	data->port = atoi(av[1]);
	data->path = strdup(av[2]);
	data->username = NULL;
	data->password = NULL;
	if (data->port < 0 || data->path == NULL) {
		printf("%s%s%s", USAGE_1, USAGE_2, USAGE_3);
		return (NULL);
	}
	return (data);
}

void clear(t_data *data)
{
	free(data->path);
	if (data->username != NULL && data->password != NULL) {
		free(data->username);
		free(data->password);
	}
	free(data);
}
