/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** cpp
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>
#include <unistd.h>

#include "server.h"

int noop(char **tab, t_data *data)
{
	if (data->connected == false) {
		send_message(530, E_LOGIN, data);
	} else {
		send_message(200, "noop", data);
	}
	return (SUCCESS);
}

int create_port(int port, t_data *data)
{
	struct sockaddr_in s_in;
	int last = rand() % 50 + 1;
	int fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
	int value = 1;

	port = 255 * 256 + last;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	if ((fd == -1) ||
		((bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in))) == -1)
		|| (((listen(fd, 3)) == -1))) {
		create_port(255 * 256 + last, data);
	}
	send_message(-1, "227 Entering Passive Mode (", data);
	dprintf(data->c_fd, "%s,255,%d).\r\n", data->ip, last);
	printf("port = %d\n", 255 * 256 + last);
	return (fd);
}

int pasv(char **tab, t_data *data)
{
	struct sockaddr_in in_client;
	socklen_t in_size = sizeof(in_client);

	if (data->connected == false) {
		send_message(530, E_LOGIN, data);
	} else {
		data->pasv_fd = create_port(255 * 256 + rand() % 50 + 1, data);
		data->pasv_fd = accept(data->pasv_fd,
				(struct sockaddr *)&in_client,
				&in_size);
		if (data->pasv_fd == -1) {
			perror("Failed to accept");
			close(data->pasv_fd);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int port(char **tab, t_data *data)
{
	if (data->connected == false) {
		send_message(530, E_LOGIN, data);
	} else {
		if (tab[1] == NULL) {
			send_message(500, "Illegal PORT command.", data);
			return (SUCCESS);
		}
		send_message(200, "port", data);
	}
	return (SUCCESS);
}
