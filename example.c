#include "vibrant_logs.h"
#include "phosphorus_gui.h"

int main(void)
{
	vl_init();
	phos_gui_init();

	InitWindow(1280, 720, "Test");
	SetTargetFPS(60);

	// TODO 'scale' field in the gui struct?
	phos_gui gui = {0};
	phos_gui_set_id(&gui, "<auto-gen>");
	phos_gui_set_gui(&gui);

	while(!WindowShouldClose())
	{
		float dt = GetFrameTime();

		// update:
		vl_update(dt);

		// update gui
		phos_gui_update(dt);

		// toggle debug mode on/off
		if(IsKeyPressed(KEY_F1))
			phos_gui_toggle_debug_mode();


		// render stage:
		BeginDrawing();
		ClearBackground(GRAY);

		// render here:
		phos_gui_render();

		EndDrawing();
	}

	phos_gui_shutdown();

	CloseWindow();

	return 0;
}
