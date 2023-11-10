/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:17:32 by aschmitt          #+#    #+#             */
/*   Updated: 2023/11/10 01:35:42 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i ++;
	return (i);
}

int	check_nl(char *stack)
{
	size_t	i;

	i = -1;
	while (stack[++i])
		if (stack[i] == '\n')
			return (i);
	return (0);	
}

/*char	*add_check_stack(char *stack, char *buff)
{
	char *result;
	size_t	i;
	size_t	a;

	a = -1;
	i = -1;
	if (!stack)
	{
		result = malloc(sizeof(char) * (ft_strlen(buff) + 1));
		if (!result)
			return (NULL);
		while (buff[++i])
			result[i] = buff[i];
		result[i] = 0;
	}
	else
	{
		result = malloc(sizeof(char) * (ft_strlen((*stack)) + ft_strlen(buff) + 1));
		if (!result)
			return (NULL);
		while (stack[++i])
			result[i] = stack[i];
		while (buff[++a])
			result[i++] = buff[a];
		result[i] = 0;
	}
	free(stack);
	return (result);
}*/
char	*add_to_stack(char *stack, char *buff)
{
	char	*result;
	size_t	i;
	size_t	a;

	a = -1;
	i = -1;
	result = malloc(sizeof(char) * (ft_strlen(stack) + ft_strlen(buff) + 1));
	if (!result)
		return (NULL);
	while (stack[++i])
		result[i] = stack[i];
	while (buff[++a])
		result[i++] = buff[a];
	result[i] = 0;
	free(stack);
	return (result);
}
char	*new_stack(char *buff)
{
	char *result;
	size_t	i;

	i = -1;
	result = malloc(sizeof(char) * (ft_strlen(buff) + 1));
	if (!result)
		return (NULL);
	while (buff[++i])
		result[i] = buff[i];
	result[i] = 0;
	return (result);
}


char	*find_line(char *stack, char *buff, int fd)
{
	int res;

	res = read(fd, buff, BUFFER_SIZE);
	while (res > 0 && check_nl(stack))
	{
		buff[res] = 0;
		if (!stack)
			stack = new_stack(buff);
		else
			stack = add_to_stack(stack, buff);
	}
	if (res < 0)
	{
		if (stack)
			free(stack);
		free(buff);
		return (NULL);
	}
	free(buff);
	return (stack);
}

char	*ft_linator(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	line[i] = '\0';
	i = 0;
	while (buffer[i])
	{
		line[i] = buffer[i];
		i++;
		if (buffer[i - 1] == '\n')
			break ;
	}
	return (line);
}

char	*ft_buffinator(char *buffer)
{
	size_t	malloc_len;
	size_t	i;
	char	*temp;

	malloc_len = 0;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] && buffer[1 + i])
	{
		while (buffer[malloc_len + i])
			malloc_len++;
	}
	if (malloc_len > 0)
	{
		temp = malloc(sizeof(char) * (malloc_len));
		if (!temp)
			return (NULL);
		strcpy(temp, buffer + i + 1);
	}
	else
		temp = NULL;
	free(buffer);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*stack;
	char		*buff;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	stack = find_line(stack, buff, fd);
	if (!stack)
		return (0);
	line = ft_linator(stack);
	stack = ft_buffinator(stack);
	return (line);
}
