#include<unistd.h>

void	write_num(int fd, long n, int div, int leading)
{
	long	num;
	char	c;

	if (div == 0)
		return ;
	num = n / div;
	if (num)
		leading = 0;
	if (!leading)
	{
		c = num + '0';
		write(fd, &c, 1);
	}
	write_num(fd, n % div, div / 10, leading);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nl;

	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	nl = n;
	if (nl < 0)
	{
		write(fd, "-", 1);
		nl *= -1;
	}
	write_num(fd, nl, 1000000000, 1);
}
