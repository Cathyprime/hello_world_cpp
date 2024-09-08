#pragma once

typedef unsigned long size_t;

// TODO: implement malloc
// TODO: implement free
// TODO: implement realloc

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
