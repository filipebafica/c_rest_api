#include "cli.h"

static void	print_methods_count(int *methods_count)
{
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("%s %8s %5s %10s %5s\n", "┃","METHOD", "┃", "REQUESTS", "┃");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("%s %8s %5s %7d %8s\n", "┃", "GET", "┃", methods_count[GET], "┃");
	printf("%s %8s %5s %7d %8s\n", "┃", "POST", "┃", methods_count[POST], "┃");
	printf("%s %8s %5s %7d %8s\n", "┃", "PUT", "┃", methods_count[PUT], "┃");
	printf("%s %8s %5s %7d %8s\n", "┃", "DELETE", "┃", methods_count[DELETE], "┃");
	printf("%s %8s %5s %7d %8s\n", "┃", "PATCH", "┃", methods_count[PATCH], "┃");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

}

static int *get_methods_count(char **methods)
{
	int	*methods_count;
	int	i;

	methods_count = ft_calloc(5, sizeof(int));
	i = 0;
	while(methods[i])
	{
		if (!ft_strcmp(methods[i], "GET"))
			methods_count[GET] += 1;
		else if (!ft_strcmp(methods[i], "POST"))
			methods_count[POST] += 1;
		else if (!ft_strcmp(methods[i], "PUT"))
			methods_count[PUT] += 1;
		else if (!ft_strcmp(methods[i], "DELETE"))
			methods_count[DELETE] += 1;
		else if (!ft_strcmp(methods[i], "PATCH"))
			methods_count[PATCH] += 1;
		++i;
	}
	return (methods_count);
}

static void	update_file_content(char **file_content, char *buffer)
{
	char	*tmp;

	tmp = ft_strdup(*file_content);
	free(*file_content);
	*file_content = ft_strjoin(tmp, buffer);
	free(tmp);
}

static char	**get_file_tokens(int fd)
{
	char	*buffer;
	char	*file_content;
	char	**file_tokens;
	int		bytes;

	file_content = ft_calloc(1, 1);
	bytes = 1;
	while (bytes > 0)
	{
		buffer = malloc(100);
		bytes = read(fd, buffer, 99);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			update_file_content(&file_content, buffer);
		}
		free(buffer);
	}
	file_tokens = ft_split(file_content, '\n');
	free(file_content);
	return (file_tokens);
}

int	main(void)
{
	int		fd;
	char	**methods;
	int		*methods_count;

	fd = open(LOG_FILE, O_RDONLY, 0777);
	methods = get_file_tokens(fd);
	close(fd);
	methods_count = get_methods_count(methods);
	free_tokens(methods);
	print_methods_count(methods_count);
	free(methods_count);
	return (0);
}
