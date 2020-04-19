#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

int unum_size(unsigned int num)
{
    int count;

    count = 0;
    if (num >= 0 && num <= 9)
        return (1);
    while (num > 9)
    {
        num /= 10;
        count++;
    }
    return (count);
}

/*
char    *ft_utoa(unsigned int num, int base)
{
    int bytes;
    char str[unum_size(bytes) + 1];

    
}*/


// inline function to swap two numbers
void swap(char *x, char *y) {
	char t = *x; *x = *y; *y = t;
}

// function to reverse buffer[i..j]
char* reverse(char *buffer, int i, int j)
{
	while (i < j)
		swap(&buffer[i++], &buffer[j--]);

	return buffer;
}

// Iterative function to implement itoa() function in C
char* ft_utoa(unsigned int value, char* buffer, int base)
{
	// invalid input
	if (base < 2 || base > 32)
		return buffer;

	// consider absolute value of number
	unsigned int n = value;//abs(value);

	int i = 0;
	while (n)
	{
		unsigned int r = n % base;

		if (r >= 10) 
			buffer[i++] = 65 + (r - 10);
		else
			buffer[i++] = 48 + r;

		n = n / base;
	}

	// if number is 0
	if (i == 0)
		buffer[i++] = '0';

	// If base is 10 and value is negative, the resulting string 
	// is preceded with a minus sign (-)
	// With any other base, value is always considered unsigned
	if (value < 0 && base == 10)
		buffer[i++] = '-';

	buffer[i] = '\0'; // null terminate string

	// reverse the string and return it
	return reverse(buffer, 0, i - 1);
}


void printout(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

int ft_printf(const char *str, ...)
{
    int i = 0, j = 0, num = 0;
    char buffer[1000], c;
    va_list arg;

    va_start(arg, str);
    while (str[i])
    {
        if (str[i] == '%')
        {
            if (str[i] == '.')
            {
                i++;
                
            }
            i++;
            if (str[i] == 'c')
            {
                buffer[j] = (char)va_arg(arg, int);
                j++;
            }
            else if (str[i] == 's')
            {
                const char* argString = va_arg(arg, const char*);
                strcat(buffer, argString);
                j = strlen(buffer);
            }
            else if (str[i] == 'd' || str[i] == 'i')
            {
                num = va_arg(arg, int);
                char argNum[200];
                itoa(num, argNum, 10);
                strcat(buffer, argNum);
                j = strlen(buffer);
            }
            else if (str[i] == 'p')
            {
                int p = va_arg(arg, int);
                char argP[200];
                itoa(p, argP, 16);
                strcat(buffer, argP);
                j = strlen(buffer);
            }
            else if (str[i] == 'x' || str[i] == 'X')
            {
                unsigned int x = va_arg(arg, unsigned int);
                char argx[200];
                itoa(x, argx, 16);
                if (str[i] == 'X')
                    {
                        int e = 0;
                        while (argx[e])
                        {
                            argx[e] = ft_toupper(argx[e]);
                            e++;
                        }
                    }
                strcat(buffer, argx);
                j = strlen(buffer);
            }
            else if (str[i] == 'u')
            {
                unsigned int u = va_arg(arg, unsigned int);
                printf("%u\n", u);
                char argu[200];
                ft_utoa(u, argu, 10);
                printf("%s\n", argu);
                strcat(buffer, argu);
                j = strlen(buffer);
            }
            }
        else
        {
            buffer[j] = str[i];
            j++;
        }
        buffer[j] = '\0';
        i++;
    }
    va_end(arg);
    printout(buffer);
    return (j);
}

int main()
{
    char c[20] = "last test";
    int d;

    d = -30;

    ///c = "hello world";
    ft_printf("can you print this shit out [%X] or naw?", d);
    printf("can you print this shit out [%-.0X] or naw?", d);
    return (0);
}
