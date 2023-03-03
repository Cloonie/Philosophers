#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

void print_s(char *str, int *length)
{
	if (!str)
		str = "(null)";
	while (*str)
		*length += write(1, str++, 1);
}

void print_d_x(long long int num, int base, int *length)
{
	char *hex = "0123456789abcdef";

	if (num < 0)
	{
		num *= -1;
		*length += write(1, "-", 1);
	}
	if (num >= base)
		print_d_x((num / base), base, length);
	*length += write(1, &hex[num % base], 1);
}

int	ft_printf(const char *format, ...)
{
	int length;

	va_list pointer;
	va_start(pointer, format);

	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			if (*format == 's')
				print_s(va_arg(pointer, char *), &length);
			else if (*format == 'd')
				print_d_x((long long int)va_arg(pointer, int), 10, &length);
			else if (*format == 'x')
				print_d_x((long long int)va_arg(pointer, unsigned int), 16, &length);
		}
		else
			length += write(1, format, 1);
		format++;
	}
	va_end(pointer);
	return (length);
}

int main()
{
	ft_printf("string: %s num: %d hex: %x\n", "hello world!", -674832914, -1);
}