/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:24:27 by minkim            #+#    #+#             */
/*   Updated: 2022/04/16 17:58:55 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void print_cmd(Node *ahead, int cmd)
{
    //1 sa
    //2 sb
    //3 ra
    //4 rb

    //5 pa
    //6 pb
    //7 rra
    //8 rrb
    //9 rrr


    if (ahead->data == 1 && cmd == 2)
    {
        ahead->data = 0;
        write(1, "ss\n", 3);     
    }
    else if (ahead->data == 2 && cmd == 1)
    {
        ahead->data = 0;
        write(1, "ss\n", 3);     
    }
    else if (ahead->data == 3 && cmd == 4)
    {
        ahead->data = 0;
        write(1, "rr\n", 3);     
    }
    else if (ahead->data == 4 && cmd == 3)
    {
        ahead->data = 0;
        write(1, "rr\n", 3);     
    }
    else if (ahead->data == 1 && cmd == 1)
        ahead->data = 0;
    else if (ahead->data == 2 && cmd == 2)
        ahead->data = 0;
    else if (ahead->data == 5 && cmd == 6)
        ahead->data = 0;
    else if (ahead->data == 6 && cmd == 5)
        ahead->data = 0;
    else if (ahead->data == 3 && cmd == 7)
        ahead->data = 0;
    else if (ahead->data == 4 && cmd == 8)
        ahead->data = 0;
    else
    {
        if (ahead->data == 1)
            write(1, "sa\n", 3);     
        if (ahead->data == 2)
            write(1, "sb\n", 3);
        if (ahead->data == 3)
            write(1, "ra\n", 3);     
        if (ahead->data == 4)
            write(1, "rb\n", 3);
        if (ahead->data == 5)
            write(1, "pa\n", 3);     
        if (ahead->data == 6)
            write(1, "pb\n", 3);
        if (ahead->data == 7)
            write(1, "rra\n", 4);
        if (ahead->data == 8)
            write(1, "rrb\n", 4);
        if (ahead->data == 9)
            write(1, "rrr\n", 4);
        ahead->data = cmd;
    }
}