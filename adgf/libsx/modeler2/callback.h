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
void file_open(Widget w, void *data);
void file_save(Widget w, void *data);
void file_save_as(Widget w, void *data);
void file_close(Widget w, void *data);
void file_export_raw(Widget w, void *data);
void file_export_vrml(Widget w, void *data);
void file_about(Widget w, void *data);
void file_help(Widget w, void *data);
void file_quit(Widget w, void *data);

void cmd_add_prim(Widget w, void *data);
void cmd_del_prim(Widget w, void *data);
void cmd_edit_prim(Widget w, void *data);
void cmd_edit_camera(Widget w, void *data);
void cmd_edit_light(Widget w, void *data);
void cmd_edit_anim(Widget w, void *data);

void opt_setup_defaults(Widget w, void *data);
void opt_dump_database(Widget w, void *data);
void opt_status(Widget w, void *data);
void opt_toggle_color(Widget w, void *data);

void view_all(Widget w, void *data);
void view_xy(Widget w, void *data);
void view_zy(Widget w, void *data);
void view_xz(Widget w, void *data);
void view_camera(Widget w, void *data);

void rend_wire(Widget w, void *data);
void rend_solid(Widget w, void *data);
void rend_flat(Widget w, void *data);

void anim_stop(Widget w, void *data);
void anim_run_forward(Widget w, void *data);
void anim_run_reverse(Widget w, void *data);
void anim_loop(Widget w, void *data);
void anim_ping(Widget w, void *data);
void anim_step_forward(Widget w, void *data);
void anim_step_reverse(Widget w, void *data);
void anim_first(Widget w, void *data);
void anim_last(Widget w, void *data);

void zoom_in(Widget w, void *data);
void zoom_normal(Widget w, void *data);
void zoom_out(Widget w, void *data);

void redisplay(Widget w, int new_width, int new_height, void *data);
void button_down(Widget w, int which_button, int x,int y, void *data);
void button_up(Widget w, int which_button, int x, int y, void *data);
void keypress(Widget w, char *input, int up_or_down, void *data);
void motion(Widget w, int x, int y, void *data);



#endif /* _CALLBACK_H */
