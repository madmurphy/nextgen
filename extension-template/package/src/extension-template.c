/*  -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */

/*\
|*|
|*| nautilus-__REPL_IDCASE_EXTNAME__.c
|*|
|*| https://gitlab.gnome.org/__REPL_AUTHOR_NICKNAME__/nautilus-__REPL_IDCASE_EXTNAME__
|*|
|*| Copyright (C) __REPL_PACKAGE_YEAR__ __REPL_AUTHOR_NAME__ <__REPL_AUTHOR_EMAIL__>
|*|
|*| **__REPL_PACKAGE_NAME__** is free software: you can redistribute it and/or
|*| modify it under the terms of the GNU General Public License as published by
|*| the Free Software Foundation, either version 3 of the License, or (at your
|*| option) any later version.
|*|
|*| **__REPL_PACKAGE_NAME__** is distributed in the hope that it will be useful,
|*| but WITHOUT ANY WARRANTY; without even the implied warranty of
|*| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
|*| Public License for more details.
|*|
|*| You should have received a copy of the GNU General Public License along
|*| with this program. If not, see <http://www.gnu.org/licenses/>.
|*|
\*/



#ifdef HAVE_CONFIG_H
#include "config.h"
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
	bindtextdomain(GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
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
} Nautilus__REPL_TITLECASE_EXTNAME__;

typedef struct {
	GObjectClass parent_slot;
} Nautilus__REPL_TITLECASE_EXTNAME__Class;

static GType provider_types[1];
static GType nautilus___REPL_LOWERCASE_EXTNAME___type;
static GObjectClass * parent_class;



/*\
|*|
|*| FUNCTIONS
|*|
\*/
/*@@@@@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_FILE_MENU)! @@@@@@@@@@@@@@@@@@*/


static void on_do_stuff_selected_menuitem_activate (
	NautilusMenuItem * const menu_item,
	gpointer const user_data
) {

	/*

		This is the function that is invoked when the user clicks on the "Do
		something" menu entry.

	*/

	gchar * file_uri;

	GList * const file_selection = g_object_get_data(
		G_OBJECT(menu_item),
		"nautilus___REPL_LOWERCASE_EXTNAME___files"
	);

	for (GList * iter = file_selection; iter; iter = iter->next) {

		/*  Launch Nautilus from a terminal to see this  */

		file_uri = nautilus_file_info_get_uri(NAUTILUS_FILE_INFO(iter->data));
		g_message(_("Doing something with %s ..."), file_uri);
		g_free(file_uri);

	}

}
/*@@@@@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_FILE_MENU)! @@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_BACKGROUND_MENU)! @@@@@@@@@@@@@@@@*/


static void on_do_stuff_background_menuitem_activate (
	NautilusMenuItem * const menu_item,
	gpointer const user_data
) {

	/*

		This is the function that is invoked when the user clicks on the "Do
		something" menu entry. Good coding! ;)

	*/

	gchar * file_uri;

	NautilusFileInfo * const background_item = g_object_get_data(
		G_OBJECT(menu_item),
		"nautilus___REPL_LOWERCASE_EXTNAME___background_items"
	);


	file_uri = nautilus_file_info_get_uri(background_item);
	g_message(_("Doing something with background item %s ..."), file_uri);
	g_free(file_uri);

}
/*@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_BACKGROUND_MENU)! @@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_FILE_MENU)! @@@@@@@@@@@@@@@@@@*/


static GList * nautilus___REPL_LOWERCASE_EXTNAME___get_file_items (
	NautilusMenuProvider * const menu_provider,
	GtkWidget * const nautilus_window,
	GList * const file_selection
) {

	/*

	Uncomment the following block if you want the "Do something" menu entry not
	to be shown if a directory is found among the selected files.

	If you want instead to show the menu entry only when a particular mimetype
	is selected, use as condition:
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
		"Nautilus__REPL_TITLECASE_EXTNAME__::do_stuff_selected",
		_("Do something 1"),
		_("Some longer description of what you do"),
		NULL /* icon name or `NULL` */
	);

	g_signal_connect(
		menu_item,
		"activate",
		G_CALLBACK(on_do_stuff_selected_menuitem_activate),
		NULL /* or any custom user data */
	);

	g_object_set_data_full(
		G_OBJECT(menu_item),
		"nautilus___REPL_LOWERCASE_EXTNAME___files",
		nautilus_file_info_list_copy(file_selection),
		(GDestroyNotify) nautilus_file_info_list_free
	);

	return g_list_append(NULL, menu_item);

}
/*@@@@@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_FILE_MENU)! @@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_BACKGROUND_MENU)! @@@@@@@@@@@@@@@@*/


static GList * nautilus___REPL_LOWERCASE_EXTNAME___get_background_items (
	NautilusMenuProvider * const menu_provider,
	GtkWidget * const nautilus_window,
	NautilusFileInfo * const current_folder
) {

	NautilusMenuItem * const menu_item = nautilus_menu_item_new(
		"Nautilus__REPL_TITLECASE_EXTNAME__::do_stuff_background",
		_("Do something 2"),
		_("Some longer description of what you do"),
		NULL    /*  icon name or `NULL`  */
	);

	g_signal_connect(
		menu_item,
		"activate",
		G_CALLBACK(on_do_stuff_background_menuitem_activate),
		NULL    /*  or any custom user data  */
	);

	g_object_ref(current_folder);

	g_object_set_data_full(
		G_OBJECT(menu_item),
		"nautilus___REPL_LOWERCASE_EXTNAME___background_items",
		current_folder,
		(GDestroyNotify) g_object_unref
	);

	return g_list_append(NULL, menu_item);

}
/*@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_BACKGROUND_MENU)! @@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_COLUMNS_OR_FILE_INFO)! @@@@@@@@@@@@@*/


static NautilusOperationResult nautilus___REPL_LOWERCASE_EXTNAME___update_file_info (
	NautilusInfoProvider * const info_provider,
	NautilusFileInfo * const nautilus_file,
	GClosure * const update_complete,
	NautilusOperationHandle ** const operation_handle
) {
/*@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_COLUMNS_OR_FILE_INFO)! @@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_FILE_INFO)! @@@@@@@@@@@@@@@@@@@*/

	/*  Emblem example  */

	/*
	As a simple example of what this function can do, we are going to add a
	"favorite" emblem to all files modified in the last hour...
	*/

	GFile * location = nautilus_file_info_get_location(nautilus_file);

	GFileInfo * const finfo = g_file_query_info(
		location,
		G_FILE_ATTRIBUTE_TIME_MODIFIED,
		G_FILE_QUERY_INFO_NONE,
		NULL,
		NULL
	);

	g_object_unref(location);

	if (!finfo) {

		return NAUTILUS_OPERATION_FAILED;

	}

	if (
		(guint64) g_file_info_get_attribute_uint64(
			finfo,
			G_FILE_ATTRIBUTE_TIME_MODIFIED
		) + 3600 > (guint64) time(NULL)
	) {

		nautilus_file_info_add_emblem(nautilus_file, "emblem-favorite");

	}

	g_object_unref(finfo);

	/*  End of emblem example  */
/*@@@@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_FILE_INFO)! @@@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_COLUMNS)! @@@@@@@@@@@@@@@@@@@@*/

	/*
	The following code populates our column with a simple "Hello world" text...
	*/

    nautilus_file_info_add_string_attribute(
		nautilus_file,
		"Nautilus__REPL_TITLECASE_EXTNAME__::my_attribute",
		"Hello world"
	);
/*@@@@@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_COLUMNS)! @@@@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_COLUMNS_OR_FILE_INFO)! @@@@@@@@@@@@@*/

	return NAUTILUS_OPERATION_COMPLETE;

}
/*@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_COLUMNS_OR_FILE_INFO)! @@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_PROPERTY_PAGES)! @@@@@@@@@@@@@@@@*/


static GList * nautilus___REPL_LOWERCASE_EXTNAME___get_pages (
	NautilusPropertyPageProvider * const page_provider,
	GList * const file_selection
) {

	/*

	Uncomment the following block if you want the "My property page" property
	not to be shown if a directory is found among the selected files.

	If you want instead to show the property page only when a particular mime
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

	GtkWidget * my_page_label = gtk_label_new_with_mnemonic(
		_("_My property page")
	);

	/*
	We are going to place a simple `GtkLabel` as a direct child of the property
	page, but in real life you will want to append a more composite content...
	*/
	GtkWidget * const my_page_content = gtk_label_new(
		_("Property page's content")
	);

	gtk_widget_show(my_page_label);
	gtk_widget_show_all(my_page_content);

	return g_list_append(
		NULL,
		nautilus_property_page_new(
			"my-property-page",
			my_page_label,
			my_page_content
		)
	);

}
/*@@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_PROPERTY_PAGES)! @@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_LOCATION_WIDGET)! @@@@@@@@@@@@@@@@*/


static GtkWidget * nautilus___REPL_LOWERCASE_EXTNAME___get_widget (
	NautilusLocationWidgetProvider * const widget_provider,
	const char * const folder_uri,
	GtkWidget * const nautilus_window
) {

	/*  We are going to place a `GtkInfoBar` into the location widget  */

	GtkWidget
		* title_label = gtk_label_new(NULL),
		* message_label = gtk_label_new("This is an example message"),
		* location_vbox = gtk_box_new(
			GTK_ORIENTATION_VERTICAL,
			0
		),
		* location_infobar = gtk_info_bar_new_with_buttons(
			"This is an example button",
			NULL
		);

	gtk_label_set_markup(
		GTK_LABEL(title_label),
		"<b>This is an example title</b>"
	);

	gtk_label_set_xalign(GTK_LABEL(title_label), 0.0);
	gtk_label_set_xalign(GTK_LABEL(message_label), 0.0);

	gtk_box_pack_start(GTK_BOX(location_vbox), title_label, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(location_vbox), message_label, TRUE, TRUE, 0);

	gtk_container_add(
		GTK_CONTAINER(
			gtk_info_bar_get_content_area(GTK_INFO_BAR(location_infobar))
		),
		location_vbox
	);

	gtk_widget_show_all(location_infobar);
	return location_infobar;

}
/*@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_LOCATION_WIDGET)! @@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_COLUMNS)! @@@@@@@@@@@@@@@@@@@@*/


static GList * nautilus___REPL_LOWERCASE_EXTNAME___get_columns (
	NautilusColumnProvider * const column_provider
) {

	NautilusColumn * column = nautilus_column_new(
		"Nautilus__REPL_TITLECASE_EXTNAME__::my_column",
		"Nautilus__REPL_TITLECASE_EXTNAME__::my_attribute",
		_("My column"),
		_("Some longer description of what your column is")
	);

	/*
	We are returning a `GList` composed of only one column, but you can add as
	many columns as you want.
	*/
	return g_list_append(NULL, column);

}
/*@@@@@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_COLUMNS)! @@@@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_CONTEXT_MENUS)! @@@@@@@@@@@@@@@@@*/


static void nautilus___REPL_LOWERCASE_EXTNAME___menu_provider_iface_init (
	NautilusMenuProviderIface * const iface,
	gpointer const iface_data
) {

/*@@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_CONTEXT_MENUS)! @@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_FILE_MENU)! @@@@@@@@@@@@@@@@@@*/
	iface->get_file_items = nautilus___REPL_LOWERCASE_EXTNAME___get_file_items;
/*@@@@@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_FILE_MENU)! @@@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_BACKGROUND_MENU)! @@@@@@@@@@@@@@@@*/
	iface->get_background_items = nautilus___REPL_LOWERCASE_EXTNAME___get_background_items;
/*@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_BACKGROUND_MENU)! @@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_CONTEXT_MENUS)! @@@@@@@@@@@@@@@@@*/

}
/*@@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_CONTEXT_MENUS)! @@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_COLUMNS_OR_FILE_INFO)! @@@@@@@@@@@@@*/


static void nautilus___REPL_LOWERCASE_EXTNAME___type_info_provider_iface_init (
	NautilusInfoProviderIface * const iface,
	gpointer const iface_data
) {

	iface->update_file_info = nautilus___REPL_LOWERCASE_EXTNAME___update_file_info;

}
/*@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_COLUMNS_OR_FILE_INFO)! @@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_PROPERTY_PAGES)! @@@@@@@@@@@@@@@@*/


static void nautilus___REPL_LOWERCASE_EXTNAME___property_page_provider_iface_init (
	NautilusPropertyPageProviderIface * const iface
) {

	iface->get_pages = nautilus___REPL_LOWERCASE_EXTNAME___get_pages;

}
/*@@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_PROPERTY_PAGES)! @@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_LOCATION_WIDGET)! @@@@@@@@@@@@@@@@*/


static void nautilus___REPL_LOWERCASE_EXTNAME___location_widget_provider_iface_init (
	NautilusLocationWidgetProviderIface * const iface,
	gpointer const iface_data
) {

	iface->get_widget = nautilus___REPL_LOWERCASE_EXTNAME___get_widget;

}
/*@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_LOCATION_WIDGET)! @@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_COLUMNS)! @@@@@@@@@@@@@@@@@@@@*/


static void nautilus___REPL_LOWERCASE_EXTNAME___column_provider_iface_init (
	NautilusColumnProviderIface * const iface,
	gpointer const iface_data
) {

	iface->get_columns = nautilus___REPL_LOWERCASE_EXTNAME___get_columns;

}
/*@@@@@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_COLUMNS)! @@@@@@@@@@@@@@@@@@@@@*/


static void nautilus___REPL_LOWERCASE_EXTNAME___class_init (
	Nautilus__REPL_TITLECASE_EXTNAME__Class * const nautilus___REPL_LOWERCASE_EXTNAME___class,
	gpointer class_data
) {

	parent_class = g_type_class_peek_parent(nautilus___REPL_LOWERCASE_EXTNAME___class);

}


static void nautilus___REPL_LOWERCASE_EXTNAME___register_type (
	GTypeModule * const module
) {

	static const GTypeInfo info = {
		sizeof(Nautilus__REPL_TITLECASE_EXTNAME__Class),
		(GBaseInitFunc) NULL,
		(GBaseFinalizeFunc) NULL,
		(GClassInitFunc) nautilus___REPL_LOWERCASE_EXTNAME___class_init,
		(GClassFinalizeFunc) NULL,
		NULL,
		sizeof(Nautilus__REPL_TITLECASE_EXTNAME__),
		0,
		(GInstanceInitFunc) NULL,
		(GTypeValueTable *) NULL
	};

	nautilus___REPL_LOWERCASE_EXTNAME___type = g_type_module_register_type(
		module,
		G_TYPE_OBJECT,
		"Nautilus__REPL_TITLECASE_EXTNAME__",
		&info,
		0
	);
/*@@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_CONTEXT_MENUS)! @@@@@@@@@@@@@@@@@*/

	static const GInterfaceInfo menu_provider_iface_info = {
		(GInterfaceInitFunc) nautilus___REPL_LOWERCASE_EXTNAME___menu_provider_iface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	g_type_module_add_interface(
		module,
		nautilus___REPL_LOWERCASE_EXTNAME___type,
		NAUTILUS_TYPE_MENU_PROVIDER,
		&menu_provider_iface_info
	);
/*@@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_CONTEXT_MENUS)! @@@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_COLUMNS_OR_FILE_INFO)! @@@@@@@@@@@@@*/

	static const GInterfaceInfo type_info_provider_iface_info = {
		(GInterfaceInitFunc)
			nautilus___REPL_LOWERCASE_EXTNAME___type_info_provider_iface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	g_type_module_add_interface(
		module,
		nautilus___REPL_LOWERCASE_EXTNAME___type,
		NAUTILUS_TYPE_INFO_PROVIDER,
		&type_info_provider_iface_info
	);
/*@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_COLUMNS_OR_FILE_INFO)! @@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_PROPERTY_PAGES)! @@@@@@@@@@@@@@@@*/

	static const GInterfaceInfo property_page_provider_iface_info = {
		(GInterfaceInitFunc)
			nautilus___REPL_LOWERCASE_EXTNAME___property_page_provider_iface_init,
		NULL,
		NULL
	};

	g_type_module_add_interface (
		module,
		nautilus___REPL_LOWERCASE_EXTNAME___type,
		NAUTILUS_TYPE_PROPERTY_PAGE_PROVIDER,
		&property_page_provider_iface_info
	);
/*@@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_PROPERTY_PAGES)! @@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_LOCATION_WIDGET)! @@@@@@@@@@@@@@@@*/

	static const GInterfaceInfo location_widget_provider_iface_info = {
		(GInterfaceInitFunc) nautilus___REPL_LOWERCASE_EXTNAME___location_widget_provider_iface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	g_type_module_add_interface(
		module,
		nautilus___REPL_LOWERCASE_EXTNAME___type,
		NAUTILUS_TYPE_LOCATION_WIDGET_PROVIDER,
		&location_widget_provider_iface_info
	);
/*@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_LOCATION_WIDGET)! @@@@@@@@@@@@@@@@@*/
/*@@@@@@@@@@@@@@@@@@@ !START_EXCEPTION(FEATURE_COLUMNS)! @@@@@@@@@@@@@@@@@@@@*/

	static const GInterfaceInfo column_provider_iface_info = {
		(GInterfaceInitFunc) nautilus___REPL_LOWERCASE_EXTNAME___column_provider_iface_init,
		(GInterfaceFinalizeFunc) NULL,
		NULL
	};

	g_type_module_add_interface(
		module,
		nautilus___REPL_LOWERCASE_EXTNAME___type,
		NAUTILUS_TYPE_COLUMN_PROVIDER,
		&column_provider_iface_info
	);
/*@@@@@@@@@@@@@@@@@@@@ !END_EXCEPTION(FEATURE_COLUMNS)! @@@@@@@@@@@@@@@@@@@@@*/

}


GType nautilus___REPL_LOWERCASE_EXTNAME___get_type (void) {

	return nautilus___REPL_LOWERCASE_EXTNAME___type;

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
	nautilus___REPL_LOWERCASE_EXTNAME___register_type(module);
	*provider_types = nautilus___REPL_LOWERCASE_EXTNAME___get_type();

}


/*  EOF  */

