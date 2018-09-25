/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** cpp
*/

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "server.h"

int client_fork(t_data *data)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (84);
	if (pid == 0) {
		run(data);
	}
	return (SUCCESS);
}

int create_client(char **av, int s_fd)
{
	t_data *data;

	data = init(av);
	if (data == NULL || connect_to_server(data, s_fd) == ERROR
		|| client_fork(data) == ERROR)
		return (ERROR);
	if (close(data->c_fd) == -1) {
		printf("%s\n", E_CLOSE);
		return (SUCCESS);
	}
	clear(data);
	return (SUCCESS);
}

int create_server(char **av)
{
	struct sockaddr_in s_in;
	int fd = socket(AF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
	int value = 1;

	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(atoi(av[1]));
	s_in.sin_addr.s_addr = INADDR_ANY;
	if ((fd == -1) ||
		((bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in))) == -1)
		|| (((listen(fd, 3)) == -1))) {
		printf("Socket Error.\n");
		return (-1);
	}
	return (fd);
}

int main(int ac, char **av)
{
	int fd;

	srand(time(NULL));
	if (check_usage(ac, av) == ERROR)
		return (SUCCESS);
	printf("Port : [%s] et Path : [%s]\n", av[1], av[2]);
	printf("Waiting for connexion...\n");
	fd = create_server(av);
	if (fd == -1)
		return (ERROR);
	while (1) {
		if (create_client(av, fd) == ERROR) {
			return (ERROR);
		}
	}
	return (SUCCESS);
}
