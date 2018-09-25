/*
** EPITECH PROJECT, 2018
** cpp
** File description:
** cpp
*/

#include <stdlib.h>
#include <string.h>

#include "server.h"

int count_words(char *str, char sep)
{
	int words = 1;
	int i = 0;

	while (str[0] == sep)
		str = str + 1;
	while (str[i] != '\0') {
		if (str[i] == sep) {
			while (str[i] == sep)
				i = i + 1;
			words = words + 1;
		}
		if (str[i] != '\0')
			i = i + 1;
	}
	if (i != 0 && str[i - 1] == sep)
		words = words - 1;
	return (words);
}

char *alloc_line(char *str, char sep, int *i)
{
	char *line;
	int tmp = *i;
	int len = 0;

	while (str[*i] != '\0' && str[*i] != sep) {
		*i = *i + 1;
		len = len + 1;
	}
	line = malloc(sizeof(char) * (len + 1));
	if (line == NULL)
		return (NULL);
	len = 0;
	while (tmp < *i)
		line[len++] = str[tmp++];
	line[len] = '\0';
	if (str[*i] != '\0')
		*i = *i + 1;
	return (line);
}

char **my_str_to_wordtab(char *str, char sep)
{
	char **tab;
	int words;
	int i = 0;
	int j = 0;

	str = clear_cmd(str);
	words = count_words(str, sep);
	tab = malloc(sizeof(char *) * (words + 1));
	if (tab == NULL)
		return (NULL);
	while (i < words) {
		while (str[j] == sep)
			j = j + 1;
		tab[i] = alloc_line(str, sep, &j);
		if (tab[i] == NULL)
			return (NULL);
		i = i + 1;
	}
	tab[i] = NULL;
	return (tab);
}
