#include "minishell.h"

e_type	get_type(char *shell)
{
	if (strncmp(shell, "(", 1) == 0)
		return (SUB);
	else if (strncmp(shell, ")", 1) == 0)
		return (SUB);
	else if (strncmp(shell, "&&", 2) == 0)
		return (AND);
	else if (strncmp(shell, "||", 2) == 0)
		return (OR);
	else if (strncmp(shell, "|", 1) == 0)
		return (PIPE);
	else if (strncmp(shell, "<", 1) == 0)
		return (INPUT);
	else if (strncmp(shell, "<<", 2) == 0)
		return (INPUT);
	else if (strncmp(shell, ">", 1) == 0)
		return (OUTPUT);
	else if (strncmp(shell, ">>", 2) == 0)
		return (OUTPUT);
	else
		return (CMD);
}

t_node	*ft_new_cmd(char *str)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->str = str;
	new->type = CMD;
	new->left = NULL;
	new->right = NULL;
	return (new);
}