/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:58:22 by minkim            #+#    #+#             */
/*   Updated: 2021/02/16 15:07:54 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void    ft_sort_int_tab(int *tab, int size)
{
	int temp;
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
            if (tab[j] > tab[j + 1])          // 현재 요소의 값과 다음 요소의 값을 비교하여
            {                                 // 큰 값을
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;            // 다음 요소로 보냄
            }
			j++;
		}
		i++;
	}
}

void    bubble_sort(int arr[], int count)    // 매개변수로 정렬할 배열과 요소의 개수를 받음
{
    int temp;

    for (int i = 0; i < count; i++)    // 요소의 개수만큼 반복
    {
        for (int j = 0; j < count - 1; j++)   // 요소의 개수 - 1만큼 반복
        {
            if (arr[j] > arr[j + 1])          // 현재 요소의 값과 다음 요소의 값을 비교하여
            {                                 // 큰 값을
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;            // 다음 요소로 보냄
            }
        }
    }
}

int		main(void)
{
	int a[5] = { 5, 1, 4, 3, 2 };
	printf("%d, %d, %d, %d, %d\n", a[0], a[1], a[2], a[3], a[4]);
	ft_sort_int_tab(a, 5);
	printf("%d, %d, %d, %d, %d", a[0], a[1], a[2], a[3], a[4]);
}
