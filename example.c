#include "raylib.h"
#include "vibrant_logs.h"
#include "phosphorus_gui.h"

int main(void)
{
	vl_init();
	phos_gui_init();

	InitWindow(720, 720, "Test");
	SetTargetFPS(60);

	phos_gui gui = {0};
	gui.num_elems = 0;

	phos_gui_elem elem = { .id = "<auto-gen>", .pos = (Vector2) { 20, 20 }, .size = (Vector2) { 100, 50 } };

	phos_gui_add_elem(&gui, &elem);

	vl_log(VL_DEBUG, "elem.id = '%s'\n", elem.id);

	while(!WindowShouldClose())
	{
		float dt = GetFrameTime();

		// update:
		vl_update(dt);


		// render stage:
		BeginDrawing();
		ClearBackground(RAYWHITE);

		// render here:
		EndDrawing();
	}

	phos_gui_shutdown();

	CloseWindow();

	return 0;
}
