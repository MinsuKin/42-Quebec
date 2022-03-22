/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:50:57 by minkim            #+#    #+#             */
/*   Updated: 2021/02/25 15:12:08 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

int		ft_is_prime(int nb)
{
	int i;

	if (nb < 0)
		return (0);
	if (nb == 0 || nb == 1)
		return (0);
	if (nb == 2 || nb == 3)
		return (1);
	else
	{
		i = 2;
		if (nb % 2 == 0)
			return (0);
		i = 3;
		while (i <= nb / 3)
		{
			if (nb % i == 0)
				return (0);
			i = i + 2;
		}
	}
	return (1);
}

int		ft_find_next_prime(int nb)
{
	if (nb < 3)
		return (2);
	else
	{
		while (ft_is_prime(nb) == 0)
			nb++;
		return (nb);
	}
}

int		main(void)
{
        printf("%d -> %d\n", -2845, ft_find_next_prime(-2845));
        printf("%d -> %d\n", 0, ft_find_next_prime(0));
        printf("%d -> %d\n", 1, ft_find_next_prime(1));
        printf("%d -> %d\n", 2, ft_find_next_prime(2));
        printf("%d -> %d\n", 7853, ft_find_next_prime(7853));
        printf("%d -> %d\n", 78989, ft_find_next_prime(78989));
        printf("%d -> %d\n", 2147483643, ft_find_next_prime(2147483643));
        printf("%d -> %d\n", 2147483645, ft_find_next_prime(2147483645));
        printf("%d -> %d\n", 2147483646, ft_find_next_prime(2147483646));
        printf("%d -> %d\n", 2147483647, ft_find_next_prime(2147483647));
        printf("%d -> %d\n", 122893, ft_find_next_prime(122893));
        printf("%d -> %d\n", 260124, ft_find_next_prime(260124));
        printf("%d -> %d\n", 369693, ft_find_next_prime(369693));
        printf("%d -> %d\n", 135724, ft_find_next_prime(135724));
        printf("%d -> %d\n", 126000, ft_find_next_prime(126000));
        printf("%d -> %d\n", 152499, ft_find_next_prime(152499));
        printf("%d -> %d\n", 276536, ft_find_next_prime(276536));
        printf("%d -> %d\n", 47166, ft_find_next_prime(47166));
        printf("%d -> %d\n", 21060, ft_find_next_prime(21060));
        printf("%d -> %d\n", 34885, ft_find_next_prime(34885));
        printf("%d -> %d\n", 148040, ft_find_next_prime(148040));
        printf("%d -> %d\n", 159311, ft_find_next_prime(159311));
        printf("%d -> %d\n", 299093, ft_find_next_prime(299093));
        printf("%d -> %d\n", 139872, ft_find_next_prime(139872));
        printf("%d -> %d\n", 3515, ft_find_next_prime(3515));
        printf("%d -> %d\n", 78959, ft_find_next_prime(78959));
        printf("%d -> %d\n", 278137, ft_find_next_prime(278137));
        printf("%d -> %d\n", 230013, ft_find_next_prime(230013));
        printf("%d -> %d\n", 167052, ft_find_next_prime(167052));
        printf("%d -> %d\n", 97936, ft_find_next_prime(97936));
        printf("%d -> %d\n", 387735, ft_find_next_prime(387735));
        printf("%d -> %d\n", 187549, ft_find_next_prime(187549));
        printf("%d -> %d\n", 80543, ft_find_next_prime(80543));
        printf("%d -> %d\n", 314736, ft_find_next_prime(314736));
        printf("%d -> %d\n", 169, ft_find_next_prime(169));
        printf("%d -> %d\n", 378538, ft_find_next_prime(378538));
        printf("%d -> %d\n", 368811, ft_find_next_prime(368811));
        printf("%d -> %d\n", 408757, ft_find_next_prime(408757));
        printf("%d -> %d\n", 267447, ft_find_next_prime(267447));
        printf("%d -> %d\n", 364227, ft_find_next_prime(364227));
        printf("%d -> %d\n", 412868, ft_find_next_prime(412868));
        printf("%d -> %d\n", 239303, ft_find_next_prime(239303));
        printf("%d -> %d\n", 50895, ft_find_next_prime(50895));
        printf("%d -> %d\n", 307925, ft_find_next_prime(307925));
        printf("%d -> %d\n", 80088, ft_find_next_prime(80088));
        printf("%d -> %d\n", 407772, ft_find_next_prime(407772));
        printf("%d -> %d\n", 69853, ft_find_next_prime(69853));
        printf("%d -> %d\n", 404193, ft_find_next_prime(404193));
        printf("%d -> %d\n", 239846, ft_find_next_prime(239846));
        printf("%d -> %d\n", 352551, ft_find_next_prime(352551));
		printf("%d -> %d\n", 395500, ft_find_next_prime(395500));
        printf("%d -> %d\n", 277939, ft_find_next_prime(277939));
        printf("%d -> %d\n", 154870, ft_find_next_prime(154870));
        printf("%d -> %d\n", 397048, ft_find_next_prime(397048));
        printf("%d -> %d\n", 87292, ft_find_next_prime(87292));
        printf("%d -> %d\n", 31999, ft_find_next_prime(31999));
        printf("%d -> %d\n", 354051, ft_find_next_prime(354051));
        printf("%d -> %d\n", 211732, ft_find_next_prime(211732));
        printf("%d -> %d\n", 291605, ft_find_next_prime(291605));
        printf("%d -> %d\n", 13594, ft_find_next_prime(13594));
        printf("%d -> %d\n", 273183, ft_find_next_prime(273183));
        printf("%d -> %d\n", 164400, ft_find_next_prime(164400));
        printf("%d -> %d\n", 309029, ft_find_next_prime(309029));
        printf("%d -> %d\n", 19751, ft_find_next_prime(19751));
        printf("%d -> %d\n", 353066, ft_find_next_prime(353066));
        printf("%d -> %d\n", 193838, ft_find_next_prime(193838));
        printf("%d -> %d\n", 344880, ft_find_next_prime(344880));
        printf("%d -> %d\n", 359737, ft_find_next_prime(359737));
        printf("%d -> %d\n", 365882, ft_find_next_prime(365882));
        printf("%d -> %d\n", 389437, ft_find_next_prime(389437));
        printf("%d -> %d\n", 163646, ft_find_next_prime(163646));
        printf("%d -> %d\n", 292161, ft_find_next_prime(292161));
        printf("%d -> %d\n", 389450, ft_find_next_prime(389450));
        printf("%d -> %d\n", 200015, ft_find_next_prime(200015));
        printf("%d -> %d\n", 276822, ft_find_next_prime(276822));
        printf("%d -> %d\n", 114008, ft_find_next_prime(114008));
        printf("%d -> %d\n", 194397, ft_find_next_prime(194397));
        printf("%d -> %d\n", 20318, ft_find_next_prime(20318));
        printf("%d -> %d\n", 242661, ft_find_next_prime(242661));
        printf("%d -> %d\n", 238945, ft_find_next_prime(238945));
        printf("%d -> %d\n", 16738, ft_find_next_prime(16738));
        printf("%d -> %d\n", 102249, ft_find_next_prime(102249));
        printf("%d -> %d\n", 173936, ft_find_next_prime(173936));
        printf("%d -> %d\n", 281459, ft_find_next_prime(281459));
        printf("%d -> %d\n", 205684, ft_find_next_prime(205684));
        printf("%d -> %d\n", 177027, ft_find_next_prime(177027));
        printf("%d -> %d\n", 177545, ft_find_next_prime(177545));
        printf("%d -> %d\n", 205203, ft_find_next_prime(205203));
        printf("%d -> %d\n", 242071, ft_find_next_prime(242071));
        printf("%d -> %d\n", 254364, ft_find_next_prime(254364));
        printf("%d -> %d\n", 390558, ft_find_next_prime(390558));
        printf("%d -> %d\n", 32837, ft_find_next_prime(32837));
        printf("%d -> %d\n", 54182, ft_find_next_prime(54182));
        printf("%d -> %d\n", 339369, ft_find_next_prime(339369));
        printf("%d -> %d\n", 418734, ft_find_next_prime(418734));
        printf("%d -> %d\n", 362931, ft_find_next_prime(362931));
        printf("%d -> %d\n", 96695, ft_find_next_prime(96695));
        printf("%d -> %d\n", 266911, ft_find_next_prime(266911));
        printf("%d -> %d\n", 374725, ft_find_next_prime(374725));
        printf("%d -> %d\n", 355277, ft_find_next_prime(355277));
        printf("%d -> %d\n", 14799, ft_find_next_prime(14799));
        printf("%d -> %d\n", 127964, ft_find_next_prime(127964));
        printf("%d -> %d\n", 192480, ft_find_next_prime(192480));
        printf("%d -> %d\n", 281573, ft_find_next_prime(281573));
        printf("%d -> %d\n", 355302, ft_find_next_prime(355302));
        printf("%d -> %d\n", 98282, ft_find_next_prime(98282));
        printf("%d -> %d\n", 368630, ft_find_next_prime(368630));
        printf("%d -> %d\n", 189943, ft_find_next_prime(189943));
        printf("%d -> %d\n", 193020, ft_find_next_prime(193020));
        printf("%d -> %d\n", 272383, ft_find_next_prime(272383));
}
