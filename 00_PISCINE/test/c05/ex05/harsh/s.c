









int 	ft_sqrt(int n)
{
	int 	i;

	i = 1;
	while ( i * i <= n)
		i++;
	i--;
	if( i * i == n)
		return i;
	else
		return 0;
}


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
	k = (unsigned int)t;
	buf = (double)k;
	t - buf;
	if ((t - buf) == 0 || (t - buf) <= 1.0)
    	return (int)t;
	else
		return (0);
}