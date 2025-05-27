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
void file_about(Widget w, void *data);
void file_help(Widget w, void *data);
void file_quit(Widget w, void *data);

void edit_copy(Widget w, void *data);
void edit_paste(Widget w, void *data);
void edit_cut(Widget w, void *data);

void render_wire(Widget w, void *data);
void render_flat(Widget w, void *data);
void render_gouraud(Widget w, void *data);
void render_phong(Widget w, void *data);

void view_orth_xy(Widget w, void *data);
void view_orth_zy(Widget w, void *data);
void view_orth_xz(Widget w, void *data);
void view_para(Widget w, void *data);
void view_pers(Widget w, void *data);

void long_scroll(Widget w, float longitude, void *data);
void lat_scroll(Widget w, float latitude, void *data);
void zoom_scroll(Widget w, float zoom, void *data);

void redisplay(Widget w, int new_width, int new_height, void *data);
void button_down(Widget w, int which_button, int x,int y, void *data);
void button_up(Widget w, int which_button, int x, int y, void *data);
void keypress(Widget w, char *input, int up_or_down, void *data);
void motion(Widget w, int x, int y, void *data);



#endif /* _CALLBACKS_H */
