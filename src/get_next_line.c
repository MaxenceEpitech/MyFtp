/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** cpp
*/

#define READ_SIZE 1024

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

char *re_alloc(char *str)
{
	char *restr;
	int i = 0;

	restr = malloc((sizeof(char) * strlen(str) + 2));
	if (restr == NULL)
		return (NULL);
	while (str[i] != '\0') {
		restr[i] = str[i];
		i = i + 1;
	}
	restr[i + 1] = '\0';
	free(str);
	return (restr);
}

char *get_next_line(const int fd)
{
	static char buff[READ_SIZE];
	char *str;
	int i = 0;
	int j = 0;

	str = malloc(sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	while ((j = read(fd, buff, 1)) > 0
	       && buff[0] != '\n') {
		str = re_alloc(str);
		str[i] = buff[0];
		i = i + 1;
	}
	if (j == 0 && i == 0)
		return (NULL);
	return (str);
}
