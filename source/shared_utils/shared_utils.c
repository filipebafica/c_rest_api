#include "shared.h"

static int	get_tokens_len(char **tokens)
{
	int	i;

	i = 0;
	while (*tokens)
	{
		++i;
		++tokens;
	}
	return (i);
}

void	free_tokens(char **tokens)
{
	int	i;
	int	len;

	if (!tokens)
		return ;
	i = 0;
	len = get_tokens_len(tokens);
	while (i < len)
	{
		free(tokens[i]);
		++i;
	}
	if (tokens)
		free(tokens);
}
