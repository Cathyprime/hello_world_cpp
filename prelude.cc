#include "prelude.hh"
#include <stdlib.h>

void operator delete[](void* p) noexcept
{
	free(p);
}

void operator delete(void* p) noexcept
{
	free(p);
}

void* operator new[](size_t size)
{
	return malloc(size);
}

void* operator new(size_t size)
{
	return malloc(size);
}

extern "C" int main();

extern "C" void exit(int status)
{
	asm volatile (
		"movl %0, %%ebx\n"
		"movl $1, %%eax\n"
		"int $0x80\n"
		:
		: "r" (status)
		: "%eax", "%ebx"
	);

	while(true);
}

extern "C" void _start()
{
	exit(main());
}
