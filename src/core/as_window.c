// Abstract Shader Engine - Jed Fakhfekh - https://github.com/ougi-washi

#include "core/as_window.h"
#include <GLFW/glfw3.h>

void* as_display_context_create(const i32 x, const i32 y, const char* title, void key_callback(void*, i32, i32, i32, i32))
{
	if (!glfwInit())
	{
		return NULL;
	}
	GLFWwindow* display_context = glfwCreateWindow(x, y, title, NULL, NULL);
	if (display_context)
	{
		glfwSetKeyCallback(display_context, key_callback);
	}
	return display_context;
}

void as_display_context_destroy(void* display_context)
{
	glfwDestroyWindow(display_context);
}

bool as_display_context_should_close(void* display_context)
{
	return glfwWindowShouldClose(display_context);
}

void as_display_context_poll_event()
{
	glfwPollEvents();
}

void as_display_context_terminate()
{
	glfwTerminate();
}