#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - this is the custom Printf function
 * @format: this is the format to be passed to the function
 * Return: this function will return all the printed characters
 */

int _printf(const char *format, ...)
{
    /*data declaration block*/
	int counter;
    
    /*Variables to be mapped from macros*/
	int get_flags;
    int get_width;
    int get_precision;
    int get_size;

    /*declaration and initialising the variables*/
    int printed = 0;
    int prnt_characters = 0;
    int buffer_ind = 0;

	va_list list;

	char buffer[GET_SIZE_OF_BUFFER];

    /*valiadate to make sure that the import parameter is not empty*/
	if (format == NULL)
        return (-1);

    /*va_start is a macro -- initialise the list before we use it*/
    va_start(list, format);

	for (counter = 0; format && format[counter] != '\0'; counter++)
	{
		if (format[counter] != '%')
		{
			buffer[buffer_ind++] = format[counter];

			if (buffer_ind == GET_SIZE_OF_BUFFER)
				print_buffer(buffer, &buffer_ind);

			prnt_characters++;
		}
		else
		{
			print_buffer(buffer, &buffer_ind);
            /*calling the macros*/
			get_flags = get_flags(format, &counter);

			get_width = get_width(format, &counter, list);

			get_precision = get_precision(format, &counter, list);

			get_size = get_size(format, &counter);

			++counter;

			printed = handle_print(format, &counter, list, buffer,
				get_flags,get_width, get_precision, get_size);

			if (printed == -1)
				return (-1);

			prnt_characters = prnt_characters + printed;

		}
	}

	print_buffer(buffer, &buff_ind);

/*clear the macro*/
	va_end(list);

	return (prnt_characters);
}

/**
 * print_buffer - This function prints the contents of the buffer
 * if they  exist
 * @buffer: This is the buffer of array of character
 * @buff_ind: The index at which to add the characters
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)

		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
