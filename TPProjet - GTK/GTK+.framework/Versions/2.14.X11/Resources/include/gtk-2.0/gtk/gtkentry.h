/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/.
 */

#if defined(GTK_DISABLE_SINGLE_INCLUDES) && !defined (__GTK_H_INSIDE__) && !defined (GTK_COMPILATION)
#error "Only <gtk/gtk.h> can be included directly."
#endif

#ifndef __GTK_ENTRY_H__
#define __GTK_ENTRY_H__


#include <gdk/gdk.h>
#include <gtk/gtkeditable.h>
#include <gtk/gtkimcontext.h>
#include <gtk/gtkmenu.h>
#include <gtk/gtkentrycompletion.h>
#include <pango/pango.h>

G_BEGIN_DECLS

#define GTK_TYPE_ENTRY                  (gtk_entry_get_type ())
#define GTK_ENTRY(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ENTRY, GtkEntry))
#define GTK_ENTRY_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ENTRY, GtkEntryClass))
#define GTK_IS_ENTRY(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ENTRY))
#define GTK_IS_ENTRY_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ENTRY))
#define GTK_ENTRY_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ENTRY, GtkEntryClass))


typedef struct _GtkEntry       GtkEntry;
typedef struct _GtkEntryClass  GtkEntryClass;

struct _GtkEntry
{
  GtkWidget  widget;

  gchar       *GSEAL (text);

  guint        GSEAL (editable) : 1;
  guint        GSEAL (visible)  : 1;
  guint        GSEAL (overwrite_mode) : 1;
  guint        GSEAL (in_drag) : 1;	            /* FIXME: Should be private?
                                                       Dragging within the selection */

  guint16      GSEAL (text_length);	            /* length in use, in chars */
  guint16      GSEAL (text_max_length);

  /*< private >*/
  GdkWindow    *GSEAL (text_area);
  GtkIMContext *GSEAL (im_context);
  GtkWidget    *GSEAL (popup_menu);

  gint          GSEAL (current_pos);
  gint          GSEAL (selection_bound);

  PangoLayout  *GSEAL (cached_layout);

  guint         GSEAL (cache_includes_preedit) : 1;
  guint         GSEAL (need_im_reset)          : 1;
  guint         GSEAL (has_frame)              : 1;
  guint         GSEAL (activates_default)      : 1;
  guint         GSEAL (cursor_visible)         : 1;
  guint         GSEAL (in_click)               : 1; /* Flag so we don't select all when clicking in entry to focus in */
  guint         GSEAL (is_cell_renderer)       : 1;
  guint         GSEAL (editing_canceled)       : 1; /* Only used by GtkCellRendererText */ 
  guint         GSEAL (mouse_cursor_obscured)  : 1;
  guint         GSEAL (select_words)           : 1;
  guint         GSEAL (select_lines)           : 1;
  guint         GSEAL (resolved_dir)           : 4; /* PangoDirection */
  guint         GSEAL (truncate_multiline)     : 1;

  guint         GSEAL (button);
  guint         GSEAL (blink_timeout);
  guint         GSEAL (recompute_idle);
  gint          GSEAL (scroll_offset);
  gint          GSEAL (ascent);	                    /* font ascent in pango units  */
  gint          GSEAL (descent);	            /* font descent in pango units */

  guint16       GSEAL (text_size);	            /* allocated size, in bytes */
  guint16       GSEAL (n_bytes);	            /* length in use, in bytes */

  guint16       GSEAL (preedit_length);	            /* length of preedit string, in bytes */
  guint16       GSEAL (preedit_cursor);	            /* offset of cursor within preedit string, in chars */

  gint          GSEAL (dnd_position);		    /* In chars, -1 == no DND cursor */

  gint          GSEAL (drag_start_x);
  gint          GSEAL (drag_start_y);

  gunichar      GSEAL (invisible_char);

  gint          GSEAL (width_chars);
};

struct _GtkEntryClass
{
  GtkWidgetClass parent_class;

  /* Hook to customize right-click popup */
  void (* populate_popup)   (GtkEntry       *entry,
                             GtkMenu        *menu);

  /* Action signals
   */
  void (* activate)           (GtkEntry       *entry);
  void (* move_cursor)        (GtkEntry       *entry,
			       GtkMovementStep step,
			       gint            count,
			       gboolean        extend_selection);
  void (* insert_at_cursor)   (GtkEntry       *entry,
			       const gchar    *str);
  void (* delete_from_cursor) (GtkEntry       *entry,
			       GtkDeleteType   type,
			       gint            count);
  void (* backspace)          (GtkEntry       *entry);
  void (* cut_clipboard)      (GtkEntry       *entry);
  void (* copy_clipboard)     (GtkEntry       *entry);
  void (* paste_clipboard)    (GtkEntry       *entry);
  void (* toggle_overwrite)   (GtkEntry       *entry);

  /* hook to add other objects beside the entry (like in GtkSpinButton) */
  void (* get_text_area_size) (GtkEntry       *entry,
			       gint           *x,
			       gint           *y,
			       gint           *width,
			       gint           *height);

  /* Padding for future expansion */
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
};

GType      gtk_entry_get_type       		(void) G_GNUC_CONST;
GtkWidget* gtk_entry_new            		(void);
void       gtk_entry_set_visibility 		(GtkEntry      *entry,
						 gboolean       visible);
gboolean   gtk_entry_get_visibility             (GtkEntry      *entry);
void       gtk_entry_set_invisible_char         (GtkEntry      *entry,
                                                 gunichar       ch);
gunichar   gtk_entry_get_invisible_char         (GtkEntry      *entry);
void       gtk_entry_set_has_frame              (GtkEntry      *entry,
                                                 gboolean       setting);
gboolean   gtk_entry_get_has_frame              (GtkEntry      *entry);
void       gtk_entry_set_inner_border                (GtkEntry        *entry,
                                                      const GtkBorder *border);
G_CONST_RETURN GtkBorder* gtk_entry_get_inner_border (GtkEntry        *entry);
void       gtk_entry_set_overwrite_mode         (GtkEntry      *entry,
                                                 gboolean       overwrite);
gboolean   gtk_entry_get_overwrite_mode         (GtkEntry      *entry);
/* text is truncated if needed */
void       gtk_entry_set_max_length 		(GtkEntry      *entry,
						 gint           max);
gint       gtk_entry_get_max_length             (GtkEntry      *entry);
guint16    gtk_entry_get_text_length            (GtkEntry      *entry);
void       gtk_entry_set_activates_default      (GtkEntry      *entry,
                                                 gboolean       setting);
gboolean   gtk_entry_get_activates_default      (GtkEntry      *entry);

void       gtk_entry_set_width_chars            (GtkEntry      *entry,
                                                 gint           n_chars);
gint       gtk_entry_get_width_chars            (GtkEntry      *entry);

/* Somewhat more convenient than the GtkEditable generic functions
 */
void       gtk_entry_set_text                   (GtkEntry      *entry,
                                                 const gchar   *text);
/* returns a reference to the text */
G_CONST_RETURN gchar* gtk_entry_get_text        (GtkEntry      *entry);

PangoLayout* gtk_entry_get_layout               (GtkEntry      *entry);
void         gtk_entry_get_layout_offsets       (GtkEntry      *entry,
                                                 gint          *x,
                                                 gint          *y);
void       gtk_entry_set_alignment              (GtkEntry      *entry,
                                                 gfloat         xalign);
gfloat     gtk_entry_get_alignment              (GtkEntry      *entry);

void                gtk_entry_set_completion (GtkEntry           *entry,
                                              GtkEntryCompletion *completion);
GtkEntryCompletion *gtk_entry_get_completion (GtkEntry           *entry);

gint       gtk_entry_layout_index_to_text_index (GtkEntry      *entry,
                                                 gint           layout_index);
gint       gtk_entry_text_index_to_layout_index (GtkEntry      *entry,
                                                 gint           text_index);

/* For scrolling cursor appropriately
 */
void           gtk_entry_set_cursor_hadjustment (GtkEntry      *entry,
                                                 GtkAdjustment *adjustment);
GtkAdjustment* gtk_entry_get_cursor_hadjustment (GtkEntry      *entry);

/* Deprecated compatibility functions
 */

#ifndef GTK_DISABLE_DEPRECATED
GtkWidget* gtk_entry_new_with_max_length	(gint           max);
void       gtk_entry_append_text    		(GtkEntry      *entry,
						 const gchar   *text);
void       gtk_entry_prepend_text   		(GtkEntry      *entry,
						 const gchar   *text);
void       gtk_entry_set_position   		(GtkEntry      *entry,
						 gint           position);
void       gtk_entry_select_region  		(GtkEntry      *entry,
						 gint           start,
						 gint           end);
void       gtk_entry_set_editable   		(GtkEntry      *entry,
						 gboolean       editable);
#endif /* GTK_DISABLE_DEPRECATED */

G_END_DECLS

#endif /* __GTK_ENTRY_H__ */
