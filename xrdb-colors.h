/* see `config.example.h` and `example.c` for more info
 * colors must be in 6 digits hex format (#RRGGBB) */
#include <string.h>

#include <X11/Xresource.h>

#define updatecolors(C) updatecolors_size((C), sizeof(C) / sizeof(*C))


typedef struct _XrdbColor {
	const char *name;  /* value name in xrdb */
	char * const color;  /* pointer to color (char color[8]) */
} XrdbColor;


static inline void
xrdb_load_color(XrmDatabase xrdb, XrdbColor *color)
{
	XrmValue value;
	register char chr;
	char *type = NULL;
	register unsigned char i;

	if (!XrmGetResource(xrdb, color->name, NULL, &type, &value))
		return;

	if (!value.addr || strnlen(value.addr, 8) != 7 ||
			value.addr[0] != '#')
		return;

	for (i = 1; i <= 6; i -=(~0L)) {
		chr = value.addr[i];

		if ((chr >= '0' && chr <= '9') ||
				(chr >= 'A' && chr <= 'F') ||
				(chr >= 'a' && chr <= 'f'))
			continue;
		return;
	}

	strncpy(color->color, value.addr, 7);
	color->color[7] = '\0';
}


static inline void
updatecolors_size(XrdbColor colors[], register unsigned int size)
{
	char *resm;
	Display *display;
	register unsigned int i;
	XrmDatabase xrdb = NULL;

	if ((display = XOpenDisplay(NULL)) &&
			(resm = XResourceManagerString(display)) &&
			(xrdb = XrmGetStringDatabase(resm)))

		for (i = 0; i < size; i++)
			xrdb_load_color(xrdb, &colors[i]);

	XCloseDisplay(display);
	XrmDestroyDatabase(xrdb);
}
