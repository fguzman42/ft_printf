#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>



typedef struct s_flags
{
    int dot;
    int ast;
    int num;
    char* numstr;
}              t_flags;

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
    t_flags flag;
    va_list arg;
    int dotflag = 0;
    int wnum = 0;
    va_start(arg, str);
    while (str[i])
    {
        if (str[i] == '%')
        {
            i++;
            if (str[i] == '.' && dotflag == 0)            
            {
                i++;
                char width[100];
                int w = 0;
                while (str[i] >= '0' && str[i] <= '9')
                {
                    width[w] = str[i];
                    w++;
                    i++;
                }
                width[w] = '\0';
                wnum = atoi(width);
                dotflag = 1;
            }
            if (str[i] == 'c')
            {
                buffer[j] = (char)va_arg(arg, int);
                j++;
            }
            else if (str[i] == 's')
            {
                const char* argString = va_arg(arg, const char*);
                if (dotflag == 1)
                {
                    if (wnum < strlen(argString))
                    {
                        char spaces[100];
                        int p = 0;
                        while (p < wnum)
                        {
                            spaces[p] = argString[p];
                            p++;
                        }
                        spaces[p] = '\0';
                        strcat(buffer, spaces);
                        j = strlen(buffer);
                    }
                    else
                    {
                        strcat(buffer, argString);
                        j = strlen(buffer);
                    }
                }
                else
                {
                    strcat(buffer, argString);
                    j = strlen(buffer);
                }
            }
            else if (str[i] == 'd' || str[i] == 'i')
            {
                num = va_arg(arg, int);
                char argNum[200];
                itoa(num, argNum, 10);
                if (dotflag == 1)
                {
                    if (wnum > strlen(argNum))
                    {
                        char zeros[100];
                        int np = 0;
                        while (np < (wnum - strlen(argNum)))
                        {
                            zeros[np] = '0';
                            np++;
                        }
                        zeros[np] = '\0';
                        strcat(zeros, argNum);
                        strcat(buffer, zeros);
                        j = strlen(buffer);
                    }
                    else
                    {
                        strcat(buffer, argNum);
                        j = strlen(buffer);
                    }
                }
                else
                {
                    strcat(buffer, argNum);
                    j = strlen(buffer);
                }
            }
            else if (str[i] == 'p')
            {
                int p = va_arg(arg, int);
                char argP[200];
                itoa(p, argP, 16);
                if (dotflag == 1)
                {
                    if (wnum > strlen(argP))
                    {
                        char pzeros[100];
                        int pp = 0;
                        while (pp < (wnum - strlen(argP)))
                        {
                            pzeros[pp] = '0';
                            pp++;
                        }
                        pzeros[pp] = '\0';
                        strcat(pzeros, argP);
                        strcat(buffer, pzeros);
                        j = strlen(buffer);
                    }
                    else
                    {
                        strcat(buffer, argP);
                        j = strlen(buffer);
                    }
                }
                else
                {
                    strcat(buffer, argP);
                    j = strlen(buffer);
                }
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
                if (dotflag == 1)
                {
                    if (wnum > strlen(argx))
                    {
                        char xzeros[100];
                        int xp = 0;
                        while (xp < (wnum - strlen(argx)))
                        {
                            xzeros[xp] = '0';
                            xp++;
                        }
                        xzeros[xp] = '\0';
                        strcat(xzeros, argx);
                        strcat(buffer, xzeros);
                        j = strlen(buffer);
                    }
                    else
                    {
                        strcat(buffer, argx);
                        j = strlen(buffer);
                    }
                }
                else
                {
                    strcat(buffer, argx);
                    j = strlen(buffer);
                }
            }
            else if (str[i] == 'u')
            {
                unsigned int u = va_arg(arg, unsigned int);
                char argu[200];
                ft_utoa(u, argu, 10);
                if (dotflag == 1)
                {
                    if (wnum > strlen(argu))
                    {
                        char uzeros[100];
                        int up = 0;
                        while (up < (wnum - strlen(argu)))
                        {
                            uzeros[up] = '0';
                            up++;
                        }
                        uzeros[up] = '\0';
                        strcat(uzeros, argu);
                        strcat(buffer, uzeros);
                        j = strlen(buffer);
                    }
                    else
                    {
                        strcat(buffer, argu);
                        j = strlen(buffer);
                    }
                }
                else
                {
                    strcat(buffer, argu);
                    j = strlen(buffer);
                }
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
    unsigned int d;

    d = 30;

    
    ft_printf("can you print this shit out [%p] or naw?\n", d);
    printf("can you print this shit out [%p] or naw?\n", d);
    return (0);
}
