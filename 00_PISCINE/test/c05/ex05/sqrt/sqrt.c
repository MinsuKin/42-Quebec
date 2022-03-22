#include <stdio.h>
#include <math.h>
double ft_sqrt(unsigned int src)
{
    unsigned int k;
    double t;
    double buf = (double)src;
	k = 0;
	t = buf;
	while (k < 20)
	{
        if(t<1.0)
            break;
        t = (t*t+buf)/(2.0*t);
		k++;
	}
    printf("%f\n", t);
	k = (int)t;
    printf("%d\n", k);
	buf = (double)k;
    printf("%f\n", buf);
	t = t - buf;
    printf("%f\n", t);
    return t;
}

int		main(void)
{
        // printf("sqrt of %d is %f\n", -2576, ft_sqrt(-2576));
        // printf("sqrt of %d is %f\n", 0, ft_sqrt(0));
        // printf("sqrt of %d is %f\n", 1, ft_sqrt(1));
        // printf("sqrt of %d is %f\n", 2, ft_sqrt(2));
        // printf("sqrt of %d is %f\n", 1640045925, ft_sqrt(1640045925));
        // printf("sqrt of %d is %f\n", 2147395600, ft_sqrt(2147395600));
        // printf("sqrt of %d is %f\n", 2147483646, ft_sqrt(2147483646));
        // printf("sqrt of %d is %f\n", 252937216, ft_sqrt(252937216));
        // printf("sqrt of %d is %f\n", 1999266440, ft_sqrt(1999266440));
        // printf("sqrt of %d is %f\n", 2068430400, ft_sqrt(2068430400));
        // printf("sqrt of %d is %f\n", 866618250, ft_sqrt(866618250));
        printf("sqrt of %d is %f\n", 1070336656, ft_sqrt(1070336656));
        // printf("sqrt of %d is %f\n", 30403578, ft_sqrt(30403578));
        // printf("sqrt of %d is %f\n", 4761, ft_sqrt(4761));
        // printf("sqrt of %d is %f\n", 35934310, ft_sqrt(35934310));
        // printf("sqrt of %d is %f\n", 2126132100, ft_sqrt(2126132100));
        // printf("sqrt of %d is %f\n", 132646863, ft_sqrt(132646863));
}