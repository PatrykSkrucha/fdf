#include "libft/libft.h"

int main()
{
	char **d = ft_split("cos tam", ' ');
	free_splitted(d);
	return (0);
}