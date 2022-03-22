/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msauvage <msauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 08:42:05 by msauvage          #+#    #+#             */
/*   Updated: 2021/03/01 10:29:57 by msauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_input_to_tab(char *str)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (10 * result) - (str[i] - '0');
		i++;
	}
}

void	ft_find_char(char *str)
{
	
}
