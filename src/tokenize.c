#include "minishell.h"
#include "libft.h"

t_node	*ft_new_cmd(char *str);
e_type	ft_optcmp(char *shell);

t_node	*ft_new_op(char *token, e_type op)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->type = op;
	new->str = token;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_node	*ft_parse_cmd(char ***token)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->str = **token;
	node->type = AND;
	node->left = NULL;
	node->right = NULL;
	(*token)++;
	return (node);
}

t_node	*ft_parse_and_or(char ***token)
{
	//echo number1 && echo hello || echo salut
	t_node	*previous;
	t_node	*current;
	t_node	*right;
	char	*str;

	previous = ft_parse_cmd(token);
	if (!previous)
		return (NULL);
	while (**token && (ft_optcmp(**token) == AND || ft_optcmp(**token) == OR))
	{
		str = **token;
		(*token)++;
		right = ft_parse_cmd(token);
		if (!right)
			return (NULL);
		current = (t_node *)malloc(sizeof(t_node));
		if (!current)
			return (NULL);
		current->str = str;
		current->type = ft_optcmp(str);
		current->left = previous;
		current->right = right;
		previous = current;
	}
	return (previous);
}
