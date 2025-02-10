#include "minishell.h"
#include "libft.h"

e_type	ft_optcmp(char *str)
{
	if (ft_strncmp(str, "(", 1) == 0)
		return (SUB);
	else if (ft_strncmp(str, ")", 1) == 0)
		return (SUB);
	else if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (INPUT);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (INPUT);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (OUTPUT);
	else if (ft_strncmp(str, ">>", 2) == 0)
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

void	ft_printtree(t_node *tree)
{
	if (!tree)
		return;
	ft_printtree(tree->left);
	ft_printf("%s\n", tree->str);
	ft_printtree(tree->right);
}
