#include<stdio.h>

int pow10OfLen(int num)
{
	int n = 1;
	while (num != 0)
	{
		n *= 10;
		num /= 10;
	}
	return n / 10;
}
void compress(char *s)
{
	int count, write = 0, read = 0, n;
	char cur_char;
	while (s[read] != '\0')
	{
		count = 0;
		cur_char = s[read];
		while (cur_char == s[read])
		{
			read++;
			count++;
		}
		s[write++] = cur_char;
		if (count != 1){
			n = pow10OfLen(count);
			while (n != 0)
			{
				s[write++] = (count / n) + '0';
				count = count % n;
				n = n / 10;
			}
		}
	}
	s[write] = '\0';
}
int strcompress_main()
{
	//char s[] = "aaabbccc";
	//char s[] = "abbccc";
	//char s[] = "a";
	char s[] = "aaaaaaaab  bbbbAAAAAAAAAAa";
	compress(s);
	printf("%s", s);
	return 0;
}