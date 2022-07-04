#include "includes/libft.h"

t_iarray	*ft_add_to_iarray(t_iarray *array, int insert)
{
	int	*new_array;
	int	i;

	if (insert > INT_MAX || insert < INT_MIN)
		ft_error("Not within INT values.", __FILE__, __func__, __LINE__);
	new_array = NULL;
	if (array)
	{
		new_array = ft_calloc(array->size + 1, sizeof(int));
		i = -1;
		while (++i < array->size)
			new_array[i] = array->array[i];
		new_array[i] = insert;
		array->size++;
		free(array->array);
		array->array = new_array;	
	}
	else
	{
		array = ft_calloc(1, sizeof(t_iarray));
		new_array = ft_calloc(1, sizeof(int));
		new_array[0] = insert;
		array->array = new_array;
		array->size = 1;
	}
	return (array);
}
