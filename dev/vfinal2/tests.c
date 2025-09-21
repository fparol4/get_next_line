#include "./get_next_line.c"

void	__fn_string__01()
{
	char *to_copy = "avocado";
	char *copy = fn_string(to_copy, 0);
	int sut = strcmp(to_copy, copy);
}

int	main(){
	__fn_string__01();
}
