/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:41:58 by minkim            #+#    #+#             */
/*   Updated: 2022/04/14 15:53:56 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void ft_two_b(Node *bhead)
{
	if (bhead->next->data > bhead->next->next->data)
		swap_b(bhead);
}

void ft_three_a(Node *ahead, Node *bhead)
{
	if (ahead->next->data > ahead->next->next->data) // 2 > 1  //@ 3 > 2  //# 3 > 1
	{
		if (ahead->next->next->data < ahead->next->next->next->data)  // 1 < 3  //# 1 < 2
		{
			if (ahead->next->data > ahead->next->next->next->data)  //#  3 > 2
			{
				swap_a(ahead); // 1 3 2
				push_b(ahead, bhead); // 3 2    1
				swap_a(ahead); // 2 3     1
				push_a(ahead, bhead); // 1 2 3
			}
			else// if (ahead->next->data < ahead->next->next->next->data)  //  2 < 3
			{
				swap_a(ahead);
			}
		}
		else// if (ahead->next->next->data > ahead->next->next->next->data)  //@ 2 > 1
		{
			if (ahead->next->data > ahead->next->next->next->data)  //@  3 > 1
			{
				swap_a(ahead); // 2 3 1
				push_b(ahead, bhead); // 3 1     2
				swap_a(ahead); // 1 3     2
				push_a(ahead, bhead); // 2 1 3
				swap_a(ahead); // 1 2 3
			}
		}
	}
	else// if (ahead->next->data < ahead->next->next->data) // 1 < 3 2  //@ 2 < 3 1
	{
		if (ahead->next->next->data > ahead->next->next->next->data) // 1 3 > 2  //@ 2 3 > 1
		{
			if (ahead->next->data < ahead->next->next->next->data) // 1 < 2
			{
				push_b(ahead, bhead); // 3 2   1
				swap_a(ahead); // 2 3   1
				push_a(ahead, bhead); // 1 2 3
			}
			else// if (ahead->next->data > ahead->next->next->next->data) // 2 > 1
			{
				push_b(ahead, bhead); // 3 1     2
				swap_a(ahead); // 1 3     2
				push_a(ahead, bhead); // 2 1 3
				swap_a(ahead); // 1 2 3
			}
		}
	}
}

void ft_three_b(Node *ahead, Node *bhead)
{
	if (bhead->next->data > bhead->next->next->data) 
	{
		if (bhead->next->next->data < bhead->next->next->next->data)  
		{
			if (bhead->next->data > bhead->next->next->next->data)  // 3 1 2
			{
				push_a(ahead, bhead); // 3   1 2
				swap_b(bhead); // 3   2 1
				push_a(ahead, bhead); // 2 3   1
				push_a(ahead, bhead); // 1 2 3
			}
			else// if (bhead->next->data < bhead->next->next->next->data)  // 2 1 3
			{
				push_a(ahead, bhead); // 2   1 3
				swap_b(bhead); // 2   3 1
				push_a(ahead, bhead); // 3 2   1
				swap_a(ahead); // 2 3   1
				push_a(ahead, bhead); // 1 2 3
			}
		}
		else// if (bhead->next->next->data > bhead->next->next->next->data)  
		{
			if (bhead->next->data > bhead->next->next->next->data)  // 3 2 1
			{
				push_a(ahead, bhead);
				push_a(ahead, bhead);
				push_a(ahead, bhead);
			}
		}
	}
	else// if (bhead->next->data < bhead->next->next->data) 
	{
		if (bhead->next->next->data > bhead->next->next->next->data) 
		{
			if (bhead->next->data < bhead->next->next->next->data) // 1 3 2
			{
				swap_b(bhead); // 3 1 2
				push_a(ahead, bhead); // 3   1 2
				swap_b(bhead); // 3   2 1
				push_a(ahead, bhead); // 2 3   1
				push_a(ahead, bhead); // 1 2 3
			}
			else// if (bhead->next->data > bhead->next->next->next->data) // 2 3 1
			{
				swap_b(bhead);
				push_a(ahead, bhead); 
				push_a(ahead, bhead); 
				push_a(ahead, bhead); 
			}
		}
		else //if (bhead->next->next->data < bhead->next->next->next->data) 
		{
			// if (bhead->next->data < bhead->next->next->next->data) // 1 2 3
			// {
				swap_b(bhead); //      2 1 3
				push_a(ahead, bhead); // 2   1 3
				swap_b(bhead); // 2   3 1
				push_a(ahead, bhead); // 3 2   1
				swap_a(ahead); // 2 3   1
				push_a(ahead, bhead); // 1 2 3
			// }
		}
	}
}
