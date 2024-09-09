#include <stdio.h>
#include "etl_type_traits.h"
#include "string.hh"
#include "prelude.hh"

int main()
{
	String str("Hello");
	str += ',';
	str += ' ';
	str += "World!";

	String new_str;
	new_str = etl::move(str);

	String some_str("hi");

	String third_str = some_str + " " + new_str;

	String empty_str;
	empty_str += "Hello Gaymer";

	printf("1: %s\n", new_str.c_str());
	printf("2: %s\n", str.c_str());
	printf("3: %s\n", third_str.c_str());
	printf("4: %c\n", third_str[3]);
	printf("5: %s\n", empty_str.c_str());
	return 0;
}
