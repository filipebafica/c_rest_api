#include "server.h"

static void	fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	struct mg_http_message	*hm;

	if (ev == MG_EV_HTTP_MSG)
	{
		hm = (struct mg_http_message *) ev_data;
		create_log(hm);
		get_route(c, hm);
	}
}

int	main(void)
{
	struct mg_mgr	mgr;
	int				fd;

	fd = open(LOG_FILE, O_RDWR | O_CREAT | O_TRUNC, 0777);
	close(fd);
	mg_mgr_init(&mgr);
	mg_http_listen(&mgr, "0.0.0.0:8000", fn, NULL);
	printf("%s\n%s\n", "Server listening on port 8000", "Press Ctrl + C to stop the server");
	for (;;) mg_mgr_poll(&mgr, 1000);
}
