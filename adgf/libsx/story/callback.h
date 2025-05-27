/* This file contains prototypes for the functions in callbacks.c.  It is
 * included by main.c so that when you create a new widget, you can tie
 * its callback function to something that has been defined (otherwise the
 * compiler will give you and error).
 *
 * If you add any functions to callbacks.c, you should put a corresponding 
 * function prototype in here.
 */

#ifndef _CALLBACK_H
#define _CALLBACK_H


/* callback protos */
void file_new(Widget w, void *data);
void file_open(Widget w, void *data);
void file_save(Widget w, void *data);
void file_save_as(Widget w, void *data);
void file_print(Widget w, void *data);
void file_print_setup(Widget w, void *data);
void file_prefs(Widget w, void *data);
void file_close(Widget w, void *data);
void file_quit(Widget w, void *data);

void edit_undo(Widget w, void *data);
void edit_sel_all(Widget w, void *data);
void edit_copy(Widget w, void *data);
void edit_paste(Widget w, void *data);
void edit_cut(Widget w, void *data);

void view_all(Widget w, void *data);
void view_act(Widget w, void *data);
void view_scene(Widget w, void *data);
void view_hier(Widget w, void *data);
void view_frames(Widget w, void *data);
void view_slides(Widget w, void *data);

void func_add_act(Widget w, void *data);
void func_add_scene(Widget w, void *data);
void func_add_frame(Widget w, void *data);
void func_del_act(Widget w, void *data);
void func_del_scene(Widget w, void *data);
void func_del_frame(Widget w, void *data);
void func_edit_sel(Widget w, void *data);
void func_edit_frame(Widget w, void *data);
void func_rearrange(Widget w, void *data);

void tools_select(Widget w, void *data);
void tools_line(Widget w, void *data);
void tools_freehand(Widget w, void *data);
void tools_rectangle(Widget w, void *data);
void tools_circle(Widget w, void *data);
void tools_arc(Widget w, void *data);
void tools_fill_rect(Widget w, void *data);
void tools_fill_circle(Widget w, void *data);
void tools_fill_style(Widget w, void *data);
void tools_patt_style(Widget w, void *data);
void tools_import_bm(Widget w, void *data);
void tools_export_bm(Widget w, void *data);

void help_about(Widget w, void *data);
void help_brief(Widget w, void *data);
void help_search(Widget w, void *data);
void help_index(Widget w, void *data);

void redisplay(Widget w, int new_width, int new_height, void *data);
void button_down(Widget w, int which_button, int x,int y, void *data);
void button_up(Widget w, int which_button, int x, int y, void *data);
void keypress(Widget w, char *input, int up_or_down, void *data);
void motion(Widget w, int x, int y, void *data);


#endif /* end of _CALLBACK_H */
