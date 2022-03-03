#include "server.h"

void	free_list(t_node **head)
{
	t_node	*tmp;

	if (*head == NULL)
		return ;
	while (*head != NULL)
	{
		tmp = (*head)->next;
		free ((*head)->id);
		free ((*head)->book_title);
		free ((*head)->author);
		free (*head);
		*head = tmp;
	}
}

void	init_list(t_query *query)
{
	query->head = NULL;
	query->count = 0;
}

static int	is_digit(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		++s;
	}
	return (1);
}

char	*get_user_query(struct mg_http_message *hm)
{
	char	*user_query;
	char	**split_by_space;
	char	**split_by_equal;

	if (!hm->query.ptr)
		return (NULL);
	split_by_space = ft_split(hm->query.ptr, ' ');
	split_by_equal = ft_split(split_by_space[0], '=');
	if (split_by_equal && !ft_strcmp(split_by_equal[0], "id") && is_digit(split_by_equal[1]))
		user_query = ft_strdup(split_by_equal[1]);
	else
		user_query = NULL;
	free_tokens(split_by_space);
	free_tokens(split_by_equal);
	return (user_query);
}
