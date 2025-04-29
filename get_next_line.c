/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tripham <tripham@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 03:48:08 by tripham           #+#    #+#             */
/*   Updated: 2025/04/29 05:01:15 by tripham          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static char buffer[720000];
	static int index = 0;
	static int bytes_read = 1;
	int size = 0;
	char *line;
	
	if (index == 0)
	{
		int i = 0;
		while ((bytes_read = read(fd, buffer + i, BUFFER_SIZE)) > 0)
		{
			i += bytes_read;
		}
	}
	if (bytes_read < 0 || buffer[size + index] == '\0')
		return (NULL);
	line = malloc(720000);
	if (!line)
		return NULL;

	while (buffer[size + index] != '\n' && buffer[size + index] != '\0')
	{
		line[size] = buffer[size + index];
		size++;
	}
	if (buffer[size + index] == '\n')
	{
		line[size] = '\n';
		size++;
	}
	line[size] = '\0';
	index += size;
	return line;
}

#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd = open("text.txt", O_RDONLY);
	char *line;
	while((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}