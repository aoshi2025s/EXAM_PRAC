#include <unistd.h>

void	print_bits(unsigned char octet)
{
	char bits[] = "00000000";

	for (int i = 0; i < 8; i++)
	{
		if (octet & (1 << i))
		{
			bits[i] = '1';
		}
		else
		{
			bits[i] = '0';
		}
	}
	for (int i = 7; i >= 0; i--)
	{
		write(1, &bits[i], 1);
	}
}
