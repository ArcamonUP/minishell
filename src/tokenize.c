#include "minishell.h"
#include "libft.h"

t_node	*ft_new_cmd(char *str);
e_type	get_type(char *shell);

t_node	*ft_new_and(char **token, int index)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->type = AND;
	new->str = token[index];
	new->left = ;
	new->right = NULL;
	return (new);
}

t_node	*ft_parse(char **token)
{
	int i;

	i = 0;
	while (token[i])
	{
		ft_printf("%s\n", token[i]);
		if (get_type(token[i]) == AND)
			ft_new_and(token, i);
		else if (get_type(token[i]) == OR)
			
		else if (get_type(token[i]) == CMD)

		i++;
	}
}
