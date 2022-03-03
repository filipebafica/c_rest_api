#ifndef SERVER_H
# define SERVER_H
# include "shared.h"
# include "mongoose.h"
# include "cJSON.h"
# include "sqlite3.h"

typedef struct s_node
{
	char			*id;
	char			*book_title;
	char			*author;
	struct s_node	*next;
	struct s_node	*previous;
}	t_node;

typedef struct s_query
{
	t_node	*head;
	int		count;
}	t_query;

void	query_all(t_query *query);
void	query_an_item(t_query *query, char *id);
void	init_list(t_query *query);
void	free_list(t_node **head);
void	create_log(struct mg_http_message *hm);
void	get_route(struct mg_connection *c, struct mg_http_message *hm);
char	*get_user_query(struct mg_http_message *hm);
#endif