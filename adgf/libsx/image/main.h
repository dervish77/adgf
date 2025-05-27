/* This file contains the various things related to the main body of the 
 * program.  It is pretty sparse, and really shouldn't be too cluttered
 * up.
 *
 */

#ifndef _MAIN_H
#define _MAIN_H


#ifndef _IMAGE_H
#include "image.h"
#endif


/* define widget indices */
#define FILE_MENU_IDX		0
#define CMD_MENU_IDX		1
#define OPT_MENU_IDX		2
#define LABEL_IDX		3
#define DRAW_AREA_IDX		4
#define HIST_LABEL_IDX		5
#define HIST_AREA_IDX		6
#define LUT_LABEL_IDX		7
#define LUT_AREA_IDX		8
#define FILE_OPEN_IDX		9
#define FILE_SAVE_IDX		10
#define FILE_SAVE_AS_IDX	11
#define FILE_CLOSE_IDX		12
#define FILE_ABOUT_IDX		13
#define FILE_HELP_IDX		14
#define FILE_QUIT_IDX		15
#define CMD_REVERT_IDX		16
#define CMD_HISTOGRAM_IDX	17
#define CMD_THRESHOLD_IDX	18
#define CMD_BRIGHTEN_IDX	19
#define CMD_COL2GREY_IDX	20
#define CMD_NEGATIVE_IDX	21
#define CMD_MEDIAN_IDX		22
#define CMD_BLUR_IDX		23
#define CMD_SHARPEN_IDX		24
#define CMD_EDGE_IDX		25
#define OPT_DUMP_DATA_IDX	26
#define OPT_STATUS_IDX		27
#define MAX_WIDGETS		28



/* This structure contains information relevant to your program.
 * You should fill it in with information that you need.
 *
 */
typedef struct MyProgram
{
   BOOLEAN_T		project_loaded;	
   BOOLEAN_T		project_saved;
   FILE_STRING_T	load_file_name;
   FILE_STRING_T	save_file_name;
   FILE			*load_file;
   FILE			*save_file;
   DATA_S_T		data;
}MyProgram;


/* protos */
void init_display(int argc, char **argv, MyProgram *me);

extern Widget drawarea_widget;
extern Widget histarea_widget;
extern Widget lutarea_widget;

extern void InitDatabase(MyProgram *data);
extern void DumpDatabase(MyProgram *data);
extern void LoadImage(MyProgram *data);
extern void SaveImage(MyProgram *data);

extern void InitializeLUT(MyProgram *data);
extern void SetNegate(MyProgram *data);
extern void SetBWThreshold(MyProgram *data, int threshold);
extern void SetBrightnessFactor(MyProgram *data, int factor);

extern void ClearImageBuff(IMAGE_S_T *buffer);
extern void CopyImageBuff(IMAGE_S_T *src, IMAGE_S_T *dst);

extern void GenerateHistogram(MyProgram *data);
extern void Color2GreyImageBuff(MyProgram *data);
extern void PointProcessImageBuff(MyProgram *data);
extern void MedianFilterImageBuff(MyProgram *data);
extern void SetDefaultBlurFilter(MyProgram *data);
extern void BlurImageBuff(MyProgram *data);
extern void SetDefaultSharpenFilter(MyProgram *data);
extern void SharpenImageBuff(MyProgram *data);

extern void UpdateDisplay(MyProgram *data);

extern void Convolve(FILTER_S_T *filter, int maxr, int maxc, COLOR_S_T *src_p, COLOR_S_T *dst_p);

extern void DrawImageBuffer(MyProgram *data);
extern void DrawHistogram(MyProgram *data);
extern void DrawLUT(MyProgram *data);

extern void UpdateDisplay(MyProgram *data);

extern void ClearColorMap();


#ifndef TRUE
#define TRUE  ((BOOLEAN_T) 1)
#define FALSE ((BOOLEAN_T) 0)
#endif


#endif /* _MAIN_H */
/* end of main.h */
