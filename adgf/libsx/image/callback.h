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

void cmd_revert(Widget w, void *data);
void cmd_histogram(Widget w, void *data);
void cmd_threshold(Widget w, void *data);
void cmd_brighten(Widget w, void *data);
void cmd_color2grey(Widget w, void *data);
void cmd_negative(Widget w, void *data);
void cmd_median(Widget w, void *data);
void cmd_blur(Widget w, void *data);
void cmd_sharpen(Widget w, void *data);
void cmd_edge_detect(Widget w, void *data);

void opt_dump_database(Widget w, void *data);
void opt_status(Widget w, void *data);

void redisplay(Widget w, int new_width, int new_height, void *data);
void button_down(Widget w, int which_button, int x,int y, void *data);
void button_up(Widget w, int which_button, int x, int y, void *data);
void keypress(Widget w, char *input, int up_or_down, void *data);
void motion(Widget w, int x, int y, void *data);

void redisplay_hist(Widget w, int new_width, int new_height, void *data);

void redisplay_lut(Widget w, int new_width, int new_height, void *data);


#endif /* _CALLBACK_H */
