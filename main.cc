#include <stdio.h>
#include "etl_type_traits.h"
#include "string.hh"
#include "prelude.hh"

int main()
{
	String str{"Hello"};
	str += ',';
	str += ' ';
	str += "World!";

	String new_str{};
	new_str = etl::move(str);

	String some_str{"hi"};

	String third_str = some_str + " " + new_str;

	printf("1: %s\n", (char*)new_str);
	printf("2: %s\n", (char*)str);
	printf("3: %s\n", (char*)third_str);
	printf("4: %c\n", third_str[3]);
	return 0;
}
