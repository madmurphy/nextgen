/*  -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */

/*\
|*|
|*| nautilus-__REPL_IDCASE_PACKAGENAME__.c
|*|
|*| https://gitlab.gnome.org/__REPL_AUTHOR_NICKNAME__/nautilus-__REPL_IDCASE_PACKAGENAME__
|*|
|*| Copyright (C) __REPL_PACKAGE_YEAR__ __REPL_AUTHOR_NAME__ <__REPL_AUTHOR_EMAIL__>
|*|
|*| **nautilus-__REPL_IDCASE_PACKAGENAME__** is free software: you can redistribute it and/or
|*| modify it under the terms of the GNU General Public License as published by
|*| the Free Software Foundation, either version 3 of the License, or (at your
|*| option) any later version.
|*|
|*| **nautilus-__REPL_IDCASE_PACKAGENAME__** is distributed in the hope that it will be useful,
|*| but WITHOUT ANY WARRANTY; without even the implied warranty of
|*| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
|*| Public License for more details.
|*|
|*| You should have received a copy of the GNU General Public License along
|*| with this program. If not, see <http://www.gnu.org/licenses/>.
|*|
\*/



#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib.h>
#include <nautilus-extension.h>



/*\
|*|
|*| BUILD SETTINGS
|*|
\*/


#ifdef ENABLE_NLS
#include <glib/gi18n-lib.h>
#define I18N_INIT() \
	bindtextdomain(GETTEXT_PACKAGE, NAUTILUS___REPL_UPPERCASE_PACKAGENAME___LOCALEDIR);
#else
#define _(STRING) ((char * ) STRING)
#define I18N_INIT()
#endif



/*\
|*|
|*| GLOBAL TYPES AND VARIABLES
|*|
\*/


typedef struct {
	GObject parent_slot;
} Nautilus__REPL_TITLECASE_PACKAGENAME__;

typedef struct {
	GObjectClass parent_slot;
} Nautilus__REPL_TITLECASE_PACKAGENAME__Class;

static GType provider_types[1];
static GType nautilus___REPL_LOWERCASE_PACKAGENAME___type;
static GObjectClass * parent_class;



/*\
|*|
|*| FUNCTIONS
|*|
\*/


static void nautilus___REPL_LOWERCASE_PACKAGENAME___helloworld (
	NautilusMenuItem * const menu_item,
	gpointer const user_data
) {

	/*

		This is the function that is invoked when the user clicks on the "Do
		something" menu entry. Good coding! ;)

	*/

	gchar * file_uri;

	GList * const file_selection = g_object_get_data(
		G_OBJECT(menu_item),
		"nautilus___REPL_LOWERCASE_PACKAGENAME___files"
	);

	for (GList * iter = file_selection; iter; iter = iter->next) {

		/*  Launch Nautilus from a terminal to see this  */

		file_uri = nautilus_file_info_get_uri(NAUTILUS_FILE_INFO(iter->data));
		printf(_("Doing something with %s ...\n"), file_uri);
		g_free(file_uri);

	}

}


static GList * nautilus___REPL_LOWERCASE_PACKAGENAME___get_file_items (
	NautilusMenuProvider * const provider,
	GtkWidget * const window,
	GList * const file_selection
) {

	/*

		Uncomment the following block if you want the "Do something" menu entry
		not to be shown if a directory is found among the selected files.

		If you want instead to show the menu entry only when a particular mime
		type is selected, use as condition:
		`!nautilus_file_is_mime_type(NAUTILUS_FILE_INFO(iter->data), "application/x-[MIME TYPE]")`

		For further information see the `NautilusFileInfo` interface at:
		https://developer.gnome.org/libnautilus-extension/stable/NautilusFileInfo.html

	*/

	/*

	for (GList * iter = file_selection; iter; iter = iter->next) {

		if (nautilus_file_info_is_directory(NAUTILUS_FILE_INFO(iter->data))) {

			return NULL;

		}

	}

	*/

	NautilusMenuItem * const menu_item = nautilus_menu_item_new(
		"Nautilus__REPL_TITLECASE_PACKAGENAME__::do_stuff",
		_("Do something"),
		_("Some longer description of what you do"),
		NULL /* icon name or `NULL` */
	);

	g_signal_connect(
		menu_item,
		"activate",
		G_CALLBACK(nautilus___REPL_LOWERCASE_PACKAGENAME___helloworld),
		NULL /* or any custom user data */
	);

	g_object_set_data_full(
		G_OBJECT(menu_item),
		"nautilus___REPL_LOWERCASE_PACKAGENAME___files",
		nautilus_file_info_list_copy(file_selection),
		(GDestroyNotify) nautilus_file_info_list_free
	);

	return g_list_append(NULL, menu_item);

}


static void nautilus___REPL_LOWERCASE_PACKAGENAME___menu_provider_iface_init (
	NautilusMenuProviderIface * const iface,
	gpointer const iface_data
) {

	iface->get_file_items = nautilus___REPL_LOWERCASE_PACKAGENAME___get_file_items;

}


static void nautilus___REPL_LOWERCASE_PACKAGENAME___class_init (
	Nautilus__REPL_TITLECASE_PACKAGENAME__Class * const nautilus___REPL_LOWERCASE_PACKAGENAME___class,
	gpointer class_data
) {

	parent_class = g_type_class_peek_parent(nautilus___REPL_LOWERCASE_PACKAGENAME___class);

}


static void nautilus___REPL_LOWERCASE_PACKAGENAME___register_type (
	GTypeModule * const module
) {

	static const GTypeInfo info = {
		sizeof(Nautilus__REPL_TITLECASE_PACKAGENAME__Class),
		(GBaseInitFunc) NULL,
		(GBaseFinalizeFunc) NULL,
		(GClassInitFunc) nautilus___REPL_LOWERCASE_PACKAGENAME___class_init,
		(GClassFinalizeFunc) NULL,
		NULL,
		sizeof(Nautilus__REPL_TITLECASE_PACKAGENAME__),
		0,
		(GInstanceInitFunc) NULL,
		(GTypeValueTable *) NULL
	};

	static const GInterfaceInfo menu_provider_iface_info = {
		(GInterfaceInitFunc) nautilus___REPL_LOWERCASE_PACKAGENAME___menu_provider_iface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	nautilus___REPL_LOWERCASE_PACKAGENAME___type = g_type_module_register_type(
		module,
		G_TYPE_OBJECT,
		"Nautilus__REPL_TITLECASE_PACKAGENAME__",
		&info,
		0
	);

	g_type_module_add_interface(
		module,
		nautilus___REPL_LOWERCASE_PACKAGENAME___type,
		NAUTILUS_TYPE_MENU_PROVIDER,
		&menu_provider_iface_info
	);

}


GType nautilus___REPL_LOWERCASE_PACKAGENAME___get_type (void) {

	return nautilus___REPL_LOWERCASE_PACKAGENAME___type;

}


void nautilus_module_shutdown (void) {

	/*  Any module-specific shutdown  */

}


void nautilus_module_list_types (
	const GType ** const types,
	int * const num_types
) {

	*types = provider_types;
	*num_types = G_N_ELEMENTS(provider_types);

}


void nautilus_module_initialize (
	GTypeModule * const module
) {

	I18N_INIT();
	nautilus___REPL_LOWERCASE_PACKAGENAME___register_type(module);
	*provider_types = nautilus___REPL_LOWERCASE_PACKAGENAME___get_type();

}


/*  EOF  */

