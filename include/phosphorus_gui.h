#pragma once

#ifdef _WIN32
	#ifdef PHOS_GUI_EXPORTS
		#define PHOS_GUI_API __declspec(dllexport)
	#else
		#define PHOS_GUI_API __declspec(dllimport)
	#endif
#else
	#define PHOS_GUI_API
#endif


#include <string.h>
#include "raylib.h"



// UTILS:







// BUILDING GUI ELEMENTS WITH DYNAMIC COMPONENTS:


/**
  A background texture component.
*/
#define PHOS_GUI_BG_TEXTURE_COMPONENT(name) \
	Texture2D name

/**
  A click callback component. Click callbacks provide
  elements with actions upon being clicked.

  @param return_type The return type of the callback function.
  @param name The name of the callback function field inside
  the UI element.
  @param ... The argument types the callback function should expect
  when called.
*/
#define PHOS_GUI_CLICK_CALLBACK_COMPONENT(return_type, name, ...) \
	return_type (*name) (__VA_ARGS__)

/**
  A text component.
*/
#define PHOS_GUI_TEXT_COMPONENT(name, max_len) \
	char name[max_len]

/**
  A Vector2 component. Vector2 components hold 2 float values.
*/
#define PHOS_GUI_VEC2_COMPONENT(name) \
	Vector2 name

/**
  A color component.
*/
#define PHOS_GUI_COLOR_COMPONENT(name) \
	Color name

/**
  The standard components of any UI element: position and size.
*/
#define PHOS_GUI_STD_COMPONENTS \
	PHOS_GUI_VEC2_COMPONENT(pos); \
	PHOS_GUI_VEC2_COMPONENT(size)

/**
  The standard mouse state information on an interactable UI element.

  'has_focus' determines whether or not the element has been clicked
  and therefore is focused.

  'hovered' determines if the mouse if currently over the element.

  'clicked' determines if the mouse is currently hovered over
  the element AND the left mouse button was pressed once.

  'pressed' determines if the mouse is currently hovered over
  the element AND the left mouse button is being held down
  at the same time.
*/
#define PHOS_GUI_STD_MOUSE_INFO \
	bool has_focus; \
	bool hovered; \
	bool clicked; \
	bool pressed







// USING PRE-MADE ELEMENTS IN PhosphorusGUI:


/**
  The max number of elements within a single
  phos_gui instance.
*/
#define PHOS_GUI_MAX_ELEMS 64

/**
  The max length of an element's ID.
*/
#define PHOS_GUI_MAX_ID_LEN 32

/**
  A phos_gui_elem represents a single UI element.

  phos_gui_elems come with pre-configured UI components.
*/
typedef struct phos_gui_elem
{
	/**
	  This UI element's ID.

	  The ID should be unique.

	  @important If you assign the ID to
	  '<auto-gen>' then the library will
	  automatically generate an ID for
	  the element.
	*/
	char id[PHOS_GUI_MAX_ID_LEN + 1];
	/**
	  The element's position.
	*/
	Vector2 pos;
	/**
	  The element's size.
	*/
	Vector2 size;
} phos_gui_elem;

/**
  A phos_gui stores up to 64 UI elements.
*/
typedef struct phos_gui
{
	/**
	  The elements inside the GUI.
	*/
	phos_gui_elem elems[PHOS_GUI_MAX_ELEMS];
	/**
	  The current amount of elements inside this GUI.
	*/
	size_t num_elems;
} phos_gui;








// CORE FUNCTIONS:


/**
  The window's origin.
*/
#define PHOS_GUI_WIN_ORIGIN (Vector2) { 0.0f, 0.0f }
/**
  The window's current size.
*/
#define PHOS_GUI_WIN_SIZE (Vector2) { GetScreenWidth(), GetScreenHeight() }


/**
  Initializes the PhosphorusGUI library.
*/
PHOS_GUI_API void phos_gui_init(void);
/**
  Frees all resources used by the PhosphorusGUI library.
*/
PHOS_GUI_API void phos_gui_shutdown(void);


/**
  Centers a UI element inside the given bounds.

  @param elem The UI element to center.
  @param origin The origin of the container the element is being centered in.
  @param bounds The size of the container the element is being centered in.
*/
PHOS_GUI_API void phos_gui_center_elem(phos_gui_elem *elem, Vector2 origin, Vector2 size);


/**
  Registers a UI element using the element's ID.

  This function does check for duplicate IDs, as well
  as duplicate pointers.

  @return 1 on success, 0 on failure.
*/
PHOS_GUI_API int phos_gui_register_elem(phos_gui_elem *elem);
/**
  Adds a UI element to the given phos_gui instance.

  This automatically registers the element, and performs
  any other necessary actions to ensure the program works correctly.

  @param gui The phos_gui instance to add an element to.
  @param elem The element to add to the phos_gui.

  @return 1 on success, 0 on failure.
*/
PHOS_GUI_API int phos_gui_add_elem(phos_gui *gui, phos_gui_elem *elem);
/**
  Obtains a UI element with a specific ID.
*/
PHOS_GUI_API phos_gui_elem *phos_gui_get_elem(const char *ID);
