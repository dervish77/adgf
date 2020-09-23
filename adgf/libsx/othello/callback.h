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

void options_single(Widget w, void *data);
void options_two(Widget w, void *data);
void options_net(Widget w, void *data);
void options_demo(Widget w, void *data);
void options_board8(Widget w, void *data);
void options_board10(Widget w, void *data);
void options_board12(Widget w, void *data);
void options_status(Widget w, void *data);

void skill_none(Widget w, void *data);
void skill_random(Widget w, void *data);
void skill_corners(Widget w, void *data);
void skill_maxflip(Widget w, void *data);
void skill_ai(Widget w, void *data);

void help_about(Widget w, void *data);
void help_menu(Widget w, void *data);
void help_keys(Widget w, void *data);
void help_rules(Widget w, void *data);

void pass_button(Widget w, void *data);
void hint_button(Widget w, void *data);

void redisplay_score(Widget w, int new_width, int new_height, void *data);

void redisplay(Widget w, int new_width, int new_height, void *data);
void button_down(Widget w, int which_button, int x,int y, void *data);
void button_up(Widget w, int which_button, int x, int y, void *data);
void keypress(Widget w, char *input, int up_or_down, void *data);
void motion(Widget w, int x, int y, void *data);



#endif /* _CALLBACK_H */
