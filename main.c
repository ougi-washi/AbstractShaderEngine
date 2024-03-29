// Abstract Shader Engine - Jed Fakhfekh - https://github.com/ougi-washi

#include "as_editor.h"
#include "core/as_render.h"
#include "as_engine.h"

i32 main()
{
	as_engine_init();

#if AS_EDITOR
	as_editor_set_default_scene();
#endif

#if AS_EDITOR
	while (as_editor_should_loop())
#else
	while (as_engine_should_loop())
#endif
	{
		as_engine_draw();
	}

	as_engine_clear();
}
