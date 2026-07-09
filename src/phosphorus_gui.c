#include "dynamic_array_spellbook.h"
#include "vibrant_logs.h"
#include "phosphorus_gui.h"

// registry of elems and UI contexts:
typedef struct phos_gui_elem_arr
{
	// holds the actual ui elements
	phos_gui_elem **data;
	size_t size, capacity;
} phos_gui_elem_arr;

static bool phos_gui_is_init = false;
static phos_gui_elem_arr phos_gui_elem_registry;


void phos_gui_init()
{
	if(phos_gui_is_init)
	{
		vl_log(VL_ERROR, "Cannot re-initialize PhosphorusGUI!\n");
		return;
	}

	dynas_init(&phos_gui_elem_registry);

	phos_gui_is_init = true;
}
void phos_gui_shutdown()
{
	if(!phos_gui_is_init)
	{
		vl_log(VL_ERROR, "PhosphorusGUI was never initialized, cannot shutdown!\n");
		return;
	}

	dynas_free(&phos_gui_elem_registry);

	phos_gui_is_init = false;
}

void phos_gui_center_elem(phos_gui_elem *elem, Vector2 origin, Vector2 size)
{
	if(!elem)
	{
		vl_log(VL_ERROR, "Cannot center a null UI element!\n");
		return;
	}

	Vector2 elem_size = elem -> size;
	Vector2 container_center = { origin.x + size.x / 2.0f, origin.y + size.y / 2.0f };
	Vector2 elem_centered = { container_center.x - elem_size.x / 2.0f, container_center.y - elem_size.y / 2.0f };

	elem -> pos = elem_centered;
}

static int phos_gui_auto_id = 0;

PHOS_GUI_API int phos_gui_register_elem(phos_gui_elem *elem)
{
	if(!elem)
	{
		vl_log(VL_ERROR, "Cannot register null UI element!\n");
		return 0;
	}
	if(!phos_gui_is_init)
	{
		vl_log(VL_ERROR, "Cannot register element, phos_gui_init() was never called!\n");
		return 0;
	}

	// first auto-generate element's ID if it is set to "<auto-gen>"
	if(strcmp(elem -> id, "<auto-gen>") == 0)
	{
		sprintf(elem -> id, "elem_#%d", phos_gui_auto_id++);
	}

	// find duplicate pointers and IDs:
	for(size_t i = 0; i < phos_gui_elem_registry.size; ++i)
	{
		phos_gui_elem *e = phos_gui_elem_registry.data[i];

		if(e)
		{
			if(e == elem)
			{
				vl_log(VL_ERROR, "Duplicate UI element pointer found: %p!\n", e);
				return 0;
			}
			if(strcmp(e -> id, elem -> id) == 0)
			{
				vl_log(VL_ERROR, "Duplicate ID found: '%s'!\n", e -> id);
				return 0;
			}
		}
	}

	// no duplicate, the elem can be registered
	dynas_add(&phos_gui_elem_registry, elem);

	return 1;
}
int phos_gui_add_elem(phos_gui *gui, phos_gui_elem *elem)
{
	if(!gui || !elem)
	{
		vl_log(VL_ERROR, "Failed to add UI element. Make sure 'gui' and 'elem' are not NULL!\n");
		return 0;
	}

	// try to register 'elem'
	if(phos_gui_register_elem(elem) == 0)
	{
		vl_log(VL_ERROR, "Failed to register the given UI element!\n");
		return 0;
	}

	// add 'elem' to 'curr_elems' in the given phos_gui
	if(gui -> num_elems >= PHOS_GUI_MAX_ELEMS)
	{
		vl_log(VL_WARNING, "No more elements can be added to this phos_gui: %p\n", gui);
		return 0;
	}
	*(gui -> elems + (gui -> num_elems++)) = *elem;

	return 1;
}
phos_gui_elem *phos_gui_get_elem(const char *ID)
{
	if(!ID)
	{
		vl_log(VL_ERROR, "Cannot obtain UI element with null ID!\n");
		return NULL;
	}
	if(!phos_gui_is_init)
	{
		vl_log(VL_ERROR, "Cannot obtain UI element, phos_gui_init() was never called!\n");
		return NULL;
	}

	for(size_t i = 0; i < phos_gui_elem_registry.size; ++i)
	{
		phos_gui_elem *e = phos_gui_elem_registry.data[i];

		if(e)
			if(strcmp(e -> id, ID) == 0)
				return e;
	}

	vl_log(VL_ERROR, "No UI element found with the ID: '%s'\n", ID);
	return NULL;
}
