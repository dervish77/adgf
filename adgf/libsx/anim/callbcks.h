/* This file contains prototypes for the functions in callbacks.c.  It is
 * included by main.c so that when you create a new widget, you can tie
 * its callback function to something that has been defined (otherwise the
 * compiler will give you and error).
 *
 * If you add any functions to callbacks.c, you should put a corresponding 
 * function prototype in here.
 */


/* callback protos */
void quit(Widget w,    void *data);
void open_file(Widget w, void *data);
void run_anim(Widget w, void *data);
void stop_anim(Widget w, void *data);
void toggle_redraw(Widget w, void *data);
void about(Widget w, void *data);
void help(Widget w, void *data);
void next_frame(void *data, XtIntervalId *id);
void frame_rate(Widget w, float new_fr, void *data);

void mode_manual(Widget w, void *data);
void mode_linear(Widget w, void *data);
void mode_circle(Widget w, void *data);
void mode_random(Widget w, void *data);
void mode_fw_table(Widget w, void *data);
void mode_fw_random(Widget w, void *data);

void redisplay(Widget w, int new_width, int new_height, void *data);
void button_down(Widget w, int which_button, int x,int y, void *data);
void button_up(Widget w, int which_button, int x, int y, void *data);
void keypress(Widget w, char *input, int up_or_down, void *data);
void motion(Widget w, int x, int y, void *data);

/* other protos */
int LoadAnimFile(char *filename, MyProgram *data);
int DrawLinks(MyProgram *data);
int HandleButton(MyProgram *data);
int HandleMoveStructure(MyProgram *data);
int ComputeNextFrame(MyProgram *data);
