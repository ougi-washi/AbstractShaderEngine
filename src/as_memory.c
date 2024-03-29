// Abstract Shader Engine - Jed Fakhfekh - https://github.com/ougi-washi

#include "as_memory.h"
#include "stdlib.h"

u32 allocations_count = 0;
u64 allocated_memory = 0;
as_allocation allocations[MAX_ALLOCATIONS_COUNT] = { 0 };

void* as_malloc_fn(const size_t _size, const char* _file, const u32 _line, const char* _type)
{
	void* new_ptr = malloc(_size);
	AS_ASSERT(new_ptr, "Could not allocate memory.");

	strcpy(allocations[allocations_count].file, _file);
	strcpy(allocations[allocations_count].type, _type);
	allocations[allocations_count].line = _line;
	allocations[allocations_count].size = _size;
	allocations[allocations_count].ptr = new_ptr;
	if (allocations[allocations_count].ptr)
	{
		memset(allocations[allocations_count].ptr, 0, _size);
	}
	allocated_memory += _size;
	allocations_count++;
	//void* out_ptr = allocations[allocations_count - 1].ptr;
	return new_ptr;
}

void* as_realloc_fn(void* _ptr, const size_t _size, const char* _file, const u32 _line)
{
	if (allocations && _ptr)
	{
		for (u32 i = 0; i < allocations_count; i++)
		{
			if (allocations[i].ptr == _ptr)
			{
				_ptr = realloc(_ptr, _size);
				allocated_memory -= allocations[i].size;
				allocated_memory += _size;

				strcpy(allocations[i].file, _file);
				allocations[i].line = _line;
				allocations[i].ptr = _ptr;
				allocations[i].size = _size;
				return _ptr;
			}
		}
	}
	return as_malloc_fn(_size, _file, _line, "");
}

void as_free_fn(void* _ptr)
{
	if (!_ptr) { return; };
	i64 removed_index = -1;
	for (u32 i = 0; i < allocations_count; i++)
	{
		if (removed_index == -1 && allocations[i].ptr == _ptr)
		{
			free(_ptr);
			_ptr = NULL;
			allocated_memory -= allocations[i].size;
			removed_index = i;
		}
		else if (removed_index >= 0 && i > 0)
		{
			allocations[i - 1] = allocations[i];
		}
	}
	if (allocations_count > 0 && removed_index >= 0)
	{
		allocations_count--;
	}
	//if (_ptr)
	//{
	//	free(_ptr);
	//	_ptr = NULL;
	//}
}

char* as_allocation_to_string(as_allocation* _allocation) 
{
	if (_allocation) {
		char* str = (char*)malloc(256);
		if (str) {
			snprintf(str, 256, "ptr=%p, size=%zu, file=%s, line=%d",
				_allocation->ptr, _allocation->size, _allocation->file, _allocation->line);
			return str;
		}
	}
	return NULL;
}

void as_log_memory() 
{
	char log_buffer[4096];

	snprintf(log_buffer, sizeof(log_buffer), "Total allocated memory = %zu\n", allocated_memory);
	for (u32 i = 0; i < allocations_count; i++) 
	{
		char* str = as_allocation_to_string(&allocations[i]);
		strncat(log_buffer, str, sizeof(log_buffer) - strlen(log_buffer) - 1);
		free(str);
		strncat(log_buffer, "\n", sizeof(log_buffer) - strlen(log_buffer) - 1);
	}
	AS_LOG(LV_LOG, log_buffer);
}