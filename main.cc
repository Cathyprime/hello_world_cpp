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

	String moved_in;
	moved_in += "Hello Gaymer";

	String copied;
	copied = moved_in;

	printf("1: %s\n", new_str.c_str());
	printf("2: %s\n", str.c_str());
	printf("3: %s\n", third_str.c_str());
	printf("4: %c\n", third_str[3]);
	printf("5: %s\n", moved_in.c_str());
	printf("6: %s\n", copied.c_str());
	return 0;
}
