// Abstract Shader Engine - Jed Fakhfekh - https://github.com/ougi-washi

#pragma once

#include "as_types.h"

#define AS_SHADER_TYPE_VERTEX	0
#define AS_SHADER_TYPE_FRAGMENT	1
#define AS_MAX_SHADER_SOURCE_SIZE 4096
#define AS_MAX_SHADER_BINARY_SIZE 8192

typedef u8 as_shader_type;

typedef struct as_shader_binary
{
	char source[AS_MAX_SHADER_SOURCE_SIZE];
	sz source_size;
	u32 binaries[AS_MAX_SHADER_BINARY_SIZE];
	sz binaries_size;
} as_shader_binary;

extern i32 as_shader_compile(as_shader_binary* binary, const char* source, const char* entry_point, const as_shader_type shader_type);
extern as_shader_binary* as_shader_read_code(const char* filename, const as_shader_type shader_type);
extern void as_shader_destroy_binary(as_shader_binary* shader_bin, const bool is_ptr);

extern void as_shader_binary_serialize(const as_shader_binary* data, const char* filename);
as_shader_binary* as_shader_binary_deserialize(const char* filename);
