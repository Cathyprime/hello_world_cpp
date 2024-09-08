#pragma once

typedef unsigned long size_t;

// TODO: implement malloc
// TODO: implement free
// TODO: implement realloc

void operator delete[](void* p) noexcept;
void operator delete(void* p) noexcept;

void* operator new[](size_t size);
void* operator new(size_t size);

extern "C" int main();
