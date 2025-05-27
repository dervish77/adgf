/* This file contains prototypes for the functions in callbacks.c.  It is
 * included by main.c so that when you create a new widget, you can tie
 * its callback function to something that has been defined (otherwise the
 * compiler will give you and error).
 *
 * If you add any functions to callbcks.c, you should put a corresponding 
 * function prototype in here.
 */

#ifndef _CALLBCKS_H
#define _CALLBCKS_H


/* callback protos */
void file_open(Widget w, void *data);
void file_save(Widget w, void *data);
void file_save_as(Widget w, void *data);
void file_close(Widget w, void *data);
void file_about(Widget w, void *data);
void file_help(Widget w, void *data);
void file_quit(Widget w, void *data);

void icon_setup(Widget w, void *data);
void icon_clear(Widget w, void *data);
void palette_clear(Widget w, void *data);
void flip_vert(Widget w, void *data);
void flip_horiz(Widget w, void *data);
void rot_left(Widget w, void *data);
void rot_right(Widget w, void *data);

void edit_color(Widget w, void *data);

void color_1_sel(Widget w, void *data);
void color_2_sel(Widget w, void *data);
void color_3_sel(Widget w, void *data);
void color_4_sel(Widget w, void *data);
void color_5_sel(Widget w, void *data);
void color_6_sel(Widget w, void *data);
void color_7_sel(Widget w, void *data);
void color_8_sel(Widget w, void *data);

void redisplay(Widget w, int new_width, int new_height, void *data);
void redisplay_preview(Widget w, int new_width, int new_height, void *data);

void button_down(Widget w, int which_button, int x,int y, void *data);
void button_up(Widget w, int which_button, int x, int y, void *data);
void keypress(Widget w, char *input, int up_or_down, void *data);
void motion(Widget w, int x, int y, void *data);



#endif /* _CALLBCKS_H */
