#include "server.h"

void	create_log(struct mg_http_message *hm)
{
	int		fd;
	char	**log_tokens;

	fd = open(LOG_FILE, O_RDWR | O_CREAT | O_APPEND, 0777);
	log_tokens = ft_split(hm->method.ptr, ' ');
	if (ft_strcmp(log_tokens[1], "/favicon.ico"))
		ft_putendl_fd(log_tokens[0], fd);
	free_tokens(log_tokens);
	close(fd);
}
