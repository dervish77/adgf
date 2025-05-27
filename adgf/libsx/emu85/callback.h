/* This file contains prototypes for the functions in callbacks.c.  It is
 * included by main.c so that when you create a new widget, you can tie
 * its callback function to something that has been defined (otherwise the
 * compiler will give you and error).
 *
 * If you add any functions to callback.c, you should put a corresponding 
 * function prototype in here.
 */

#ifndef _CALLBACK_H
#define _CALLBACK_H


/* callback protos */
void file_new(Widget w, void *data);
void file_load(Widget w, void *data);
void file_save(Widget w, void *data);
void file_quit(Widget w, void *data);

void options_rom_setup(Widget w, void *data);
void options_ram_setup(Widget w, void *data);
void options_clock_setup(Widget w, void *data);
void options_status(Widget w, void *data);

void display_mpu(Widget w, void *data);
void display_system(Widget w, void *data);
void display_both(Widget w, void *data);
void display_image(Widget w, void *data);

void control_reset(Widget w, void *data);
void control_step(Widget w, void *data);
void control_go(Widget w, void *data);
void control_halt(Widget w, void *data);

void help_about(Widget w, void *data);
void help_menu(Widget w, void *data);
void help_keys(Widget w, void *data);
void help_rules(Widget w, void *data);

void redisplay_status(Widget w, int new_width, int new_height, void *data);

void redisplay(Widget w, int new_width, int new_height, void *data);
void button_down(Widget w, int which_button, int x,int y, void *data);
void button_up(Widget w, int which_button, int x, int y, void *data);
void keypress(Widget w, char *input, int up_or_down, void *data);
void motion(Widget w, int x, int y, void *data);



#endif /* _CALLBACK_H */
