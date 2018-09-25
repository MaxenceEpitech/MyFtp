/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** cpp
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "server.h"

int list(char **tab, t_data *data)
{
	int save = dup(1);

	if (data->connected == false) {
		send_message(530, E_LOGIN, data);
	} else if (data->pasv_fd == -1) {
		send_message(425, "Use PORT or PASV first.", data);
	} else {
		send_message(150, "Here comes the directory listing.", data);
		send_message(226, "Directory send OK.", data);
		dup2(data->pasv_fd, 1);
		system("ls -l");
		dup2(save, 1);
		close(data->pasv_fd);
		data->pasv_fd = -1;
	}
	return (SUCCESS);
}
