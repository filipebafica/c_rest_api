#include "server.h"

static void	book_route(struct mg_connection *c, struct mg_http_message *hm)
{
	t_query	query;
	t_node	*head;
	cJSON	*object;
	char	*user_query;
	char	*json_str;

	user_query = get_user_query(hm);
	if (!user_query)
	{
		mg_http_reply(c, 500, "Content-Type: application/json\r\n", "%s\n", "invalid query");
		return ;
	}
	init_list(&query);
	query_an_item(&query, user_query);
	if (!query.head)
	{
		mg_http_reply(c, 500, "Content-Type: application/json\r\n", "%s\n", "id not found");
		return ;
	}
	head = query.head;
	while (head)
	{
		object = cJSON_CreateObject();
		cJSON_AddStringToObject(object, "id", head->id);
		cJSON_AddStringToObject(object, "book_title", head->book_title);
		cJSON_AddStringToObject(object, "author", head->author);
		head = head->next;
	}
	json_str = cJSON_Print(object);
	mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s\n", json_str);
	cJSON_Delete(object);
	free(json_str);
	free_list(&query.head);
	free(user_query);
}

static void	root_route(struct mg_connection *c, struct mg_http_message *hm)
{
	t_query	query;
	t_node	*head;
	cJSON	*arr;
	cJSON	*object;
	char	*json_str;

	init_list(&query);
	query_all(&query);
	arr = cJSON_CreateArray();
	head = query.head;
	while (head)
	{
		object = cJSON_CreateObject();
		cJSON_AddStringToObject(object, "id", head->id);
		cJSON_AddStringToObject(object, "book_title", head->book_title);
		cJSON_AddStringToObject(object, "author", head->author);
		cJSON_AddItemToArray(arr, object);
		head = head->next;
	}
	json_str = cJSON_Print(arr);
	mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s\n", json_str);
	cJSON_Delete(arr);
	free(json_str);
	free_list(&query.head);
}

void	get_route(struct mg_connection *c, struct mg_http_message *hm)
{
	char	**request_tokens;

	request_tokens = ft_split(hm->method.ptr, ' ');
	if (mg_http_match_uri(hm, "/") && !ft_strcmp(request_tokens[0], "GET"))
		root_route(c, hm);
	else if (mg_http_match_uri(hm, "/book") && !ft_strcmp(request_tokens[0], "GET"))
		book_route(c, hm);
	else
		mg_http_reply(c, 500, NULL, "%s", "bad request :(");
	free_tokens(request_tokens);
}