/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** cpp
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "server.h"

int connect_to_server(t_data *data, int s_fd)
{
	struct sockaddr_in in_client;
	socklen_t in_size = sizeof(in_client);

	data->c_fd = accept(s_fd, (struct sockaddr *)&in_client, &in_size);
	if (data->c_fd == -1) {
		perror("Failed to accept");
		close(s_fd);
		return (ERROR);
	}
	data->s_fd = s_fd;
	data->ip = inet_ntoa(in_client.sin_addr);
	for (int i = 0; data->ip[i]; i++)
		if (data->ip[i] == '.')
			data->ip[i] = ',';
	data->connected = false;
	data->pasv_fd = -1;
	printf("Client conected IP = [%s]\n", data->ip);
	return (SUCCESS);
}

int username(char **tab, t_data *data)
{
	if (data->connected != true) {
		if (tab[1] == NULL) {
			send_message(530, E_PERM, data);
			return (SUCCESS);
		}
		send_message(331, I_PASS, data);
		data->username = strdup(tab[1]);
	} else {
		send_message(530, "Can t change user.", data);
	}
	return (SUCCESS);
}

int password(char **tab, t_data *data)
{
	if (data->connected != true) {
		if (data->username == NULL) {
			send_message(503, E_PASS, data);
			return (SUCCESS);
		} else if (strcasecmp(data->username, "anonymous") != 0) {
			send_message(530, E_BLOGIN, data);
			return (SUCCESS);
		}
		data->password = "";
		data->connected = true;
		send_message(230, "Login successful.", data);
		printf("user : %s login success.\n", data->username);
	} else {
		send_message(230, "Already logged in.", data);
	}
	return (SUCCESS);
}
