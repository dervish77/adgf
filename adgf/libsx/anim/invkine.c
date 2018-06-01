/***********************************************************************

   File:  	invkine.c

   Author: 	Brian Lingard

   Date:	4/8/95

 Code for manipulating and animating articulated linked structures
 using the techniques of inverse kinematics.

 All links have the same length.  Assume that 'dt' (or time interval) 
 is equal to one time unit. Thus all calculations of positional 
 velocities and rotational velocities can be easily converted back 
 into positions and rotations.


 Link chains are defined as follows:

                               O
 	                      / end effector here, at end of link 3
 	                     /
 	                    /
      end of link1 ________/ end of link2 and start of link3
 	          /
 	         /
 	        / \
 	       /   \ rotation of link1
start of link1 


 A link's u vector lies along the link itself.  A link's v vector is 
 orthogonal to its u vector.  A link's n vector is orthogonal to both
 the u and v vectors.  Thus the u, v and n vectors form a coordinate
 system local to the given link.



 NOTE:  The current implimentation is only in 2 dimensions, thus the 
 	z-coordinate values are not used.  The view presented is always
	a projection of the x,y plane.

***********************************************************************/


/*  include necessary files 
 */
#include <stdio.h>
#include "libsx.h"
#include "main.h"
#include "callbcks.h"



/* #define INVKINE_DEBUG 1
*/


/***********************************************************************

  LoadAnimFile() - this function loads the definition input file which
		describes the link hierarchy.  This function also 
		precomputes the initial link data.  The format of the file
		is as follows:

  format:
	num_links
	type_link ox oy oz tl vl rx ry rz 
	end_type 
	motion_type
	num_frames_per_cycle
	l1_zrot ... ln_zrot

  where
	num_links	- total number of links in hierarchy (int)
	type_link	- 4 character keyword (root, link, or brch)
	ox, oy, oz	- origin of link (only valid if root) (float triplet)
	tl		- total length of link (float)
	vl		- visible length of link (float)
	rx, ry, rz	- rotation about each axis (float degrees)
	end_type	- 6 character keyword (square, circle, or triang)
	motion_type	- 6 character keyword (manual, linear, circle, or random)
	num_frames	- number of frames per animation cycle (0 = no table)
	ln_zrot		- z axis rotation for nth link (one value per link)

  example:
	4
	root -20.0 0 0 10.0 10.0 0 0 0.0
	link 0 0 0 10.0 10.0 0 0 10.0
	link 0 0 0 10.0 10.0 0 0 20.0
	link 0 0 0 10.0 10.0 0 0 30.0
	square
	manual
	6
	0.0 10.0 20.0 30.0
	2.0 14.0 26.0 38.0
	4.0 18.0 32.0 46.0
	6.0 22.0 38.0 54.0
	4.0 18.0 32.0 46.0
	2.0 14.0 26.0 38.0

  This specifies a single branch hierarchy of 4 links where each link is
  the same length, each link is fully visible, and each link is only rotated 
  about the z axis by a relative amount of 10 degrees.  The end effector is 
  a square and will be manually manipulated.  A predefined animation cycle
  will consist of 6 frames, which will generate a wagging effect.

***********************************************************************/
int 
LoadAnimFile(char *filename, MyProgram *data)
{
   FILE *infile;
   int i, parse_count;
   int n;				/* number of links in hierarchy */
   int nfpc;				/* number frames per cycle */
   char tempbuf[MAX_BUF_LEN];		/* temporary text buffer */
   char *buf;				/* pointer to primitive string */
   char *parm_array[NUM_LINK_PARMS];	/* array of parameter strings */
   char linktype[4];
   float parms[8];

   pointType MapWPointToScreen();


   /*  open the input file
    */
   infile = fopen(filename, "r");
   if (infile == (FILE *) NULL) {
      fprintf(stderr, "LoadAnimFile: couldn't open input file\n");
      return(1);
   }


   /*  get number of links 
    */
   fscanf(infile, "%d\n", &n);
   data->num_links = n;

printf("read n = %d\n", n);

   /*  read in all the links
    */
   for (i = 0; i < n; i++) {
      buf = fgets(tempbuf, MAX_BUF_LEN, infile); /* read line from file */

      data->links[i].type = LINK_UNKN;

      /* determine link type */
      if (strncmp(buf, "root", 4) == 0)		/* root link */
         data->links[i].type = LINK_ROOT;
      if (strncmp(buf, "link", 4) == 0)		/* normal link */
         data->links[i].type = LINK_LINK;
      if (strncmp(buf, "brch", 4) == 0)		/* branch link */
         data->links[i].type = LINK_BRCH;

      if (data->links[i].type != LINK_UNKN) {
         /* parse buffer for link parameters */
/*         parse_count = ParseString(buf, parm_array);
*/

         sscanf(buf, "%4c %f %f %f %f %f %f %f %f %f\n", linktype, &parms[0], 
		&parms[1], &parms[2], &parms[3], &parms[4], &parms[5], 
		&parms[6], &parms[7]);

         data->links[i].w_start.x = parms[0];
         data->links[i].w_start.y = parms[1];
         data->links[i].w_start.z = parms[2];

         data->links[i].total_length = parms[3];
         data->links[i].visible_length = parms[4];

         data->links[i].xrot_deg = parms[5];
         data->links[i].yrot_deg = parms[6];
         data->links[i].zrot_deg = parms[7];


         /* save link parameters for this link */
/*         if (parse_count != NUM_LINK_PARMS) {
            data->links[i].w_start.x = atof(parm_array[1]);
            data->links[i].w_start.y = atof(parm_array[2]);
            data->links[i].w_start.z = atof(parm_array[3]);

            data->links[i].total_length = atof(parm_array[4]);
            data->links[i].visible_length = atof(parm_array[5]);

            data->links[i].xrot_deg = atof(parm_array[6]);
            data->links[i].yrot_deg = atof(parm_array[7]);
            data->links[i].zrot_deg = atof(parm_array[8]);
         }
         else {
            fprintf(stderr, "LoadAnimFile: incorrect number of parameters\n");
            return(1);
         }
*/

         /* compute other needed parameters for this link */
         ComputeInitLink(i, data);
      }
      else {
         fprintf(stderr, "LoadAnimFile: unknown link type read\n");
         return(1);
      }
   }


   /*  read in and determine the end effector type
    */
   buf = fgets(tempbuf, MAX_BUF_LEN, infile); 	/* read line from file */

   if (strncmp(buf, "square", 6) == 0)		/* square end effector */
      data->end_effect.type = ENDEFF_SQUARE;
   else if (strncmp(buf, "circle", 6) == 0)	/* circle end effector */
      data->end_effect.type = ENDEFF_CIRCLE;
   else if (strncmp(buf, "triang", 6) == 0)	/* triangle end effector */
      data->end_effect.type = ENDEFF_TRIANGLE;
   else {
      data->end_effect.type = ENDEFF_UNKNOWN;
      fprintf(stderr, "LoadAnimFile: unknown end effector type read\n");
      return(1);
   }
      

   /*  read in the end effector motion type 
    */
   buf = fgets(tempbuf, MAX_BUF_LEN, infile); 	/* read line from file */

   if (strncmp(buf, "manual", 6) == 0)		/* manual motion type */
      data->end_effect.motion = ENDMOT_MANUAL;
   else if (strncmp(buf, "linear", 6) == 0)	/* linear motion type */
      data->end_effect.motion = ENDMOT_LINEAR;
   else if (strncmp(buf, "circle", 6) == 0)	/* circle motion type */
      data->end_effect.motion = ENDMOT_CIRCLE;
   else if (strncmp(buf, "random", 6) == 0)	/* random motion type */
      data->end_effect.motion = ENDMOT_RANDOM;
   else {
      data->end_effect.motion = ENDMOT_UNKNOWN;
      fprintf(stderr, "LoadAnimFile: unknown end effector motion read\n");
      return(1);
   }

   /*  read in number of frames per cycle
    */
   fscanf(infile, "%d\n", &nfpc);
   data->anim.num_frames_per_cycle = nfpc;

   /*  if table exists, read it in
    */
   if (nfpc > 0) {
      for (i = 0; i < nfpc; i++) {

         buf = fgets(tempbuf, MAX_BUF_LEN, infile);

         sscanf(buf, "%f %f %f %f\n", &parms[0], &parms[1], &parms[2], &parms[3]);

         data->anim.table[i][0] = parms[0];  /* currently, assume only 4 links */
         data->anim.table[i][1] = parms[1];
         data->anim.table[i][2] = parms[2];
         data->anim.table[i][3] = parms[3];
      }
   }

   /*  compute end effector related stuff
    */
   ComputeInitEndEffector(data);

   /*  draw initial state of links
    */
   ClearDrawArea();
   DrawLinks(data);

   /*  close the input file
    */
   fclose(infile);

   /*  set data loaded flag
    */
   data->dataloaded = TRUE;

   return(0);
} /* end of LoadAnimFile() */


/***********************************************************************

  ComputeInitLink() - this function computes the initial end points, 
		u,v,n vectors, and rotation matrix for the specified link.

  for the given link
	set visible end to origin + vislen
	set actual end to origin + totlen
	rotate both points by theta about z axis
	translate both points to actual end of previous link
	compute u,v,n vectors
	map end points to screen coordinates

***********************************************************************/
int 
ComputeInitLink(int link, MyProgram *data)
{
   vectorType	o2, o2prime, o3, o3prime;
   vectorType	p1, p2, p3;
   vectorType	u, v, vprime, n;

   double	world[4];
   double	screen[4];

   matrixType 	translation;
   matrixType	rotation;
   matrixType	screen_map;

   pointType MapWPointToScreen(wpointType *p, matrixType *map);


   /*  set actual end to origin + totlen
    */
   o3.x = data->links[link].total_length;
   o3.y = 0.0;
   o3.z = 0.0;

   /* set visible end to origin + vislen
    */
   o2.x = data->links[link].visible_length;
   o2.y = 0.0;
   o2.z = 0.0;

   /*  make rotation matrix
    */
   rotation = MakeRotationMatrix('z', data->links[link].zrot_deg);

   MatrixCopy(&rotation, &data->links[link].rot_mat);

   /*  rotate actual and visible end points around z axis
    */
   o3prime = TransformVector(&o3, &rotation);    /* o3prime = o3 * Rz(theta) */
   o2prime = TransformVector(&o2, &rotation);    /* o2prime = o2 * Rz(theta) */

   /*  set start of link to actual end of previous link if not root link 
    */
   if (data->links[link].type == LINK_ROOT) {	/* root link */
      p1.x = data->links[link].w_start.x;
      p1.y = data->links[link].w_start.y;
      p1.z = data->links[link].w_start.z;
   }
   else {					/* normal link */
      p1.x = data->links[link - 1].w_end.x;
      p1.y = data->links[link - 1].w_end.y;
      p1.z = data->links[link - 1].w_end.z;
   }

   /*  make translation matrix
    */
   translation = MakeTranslationMatrix(p1.x, p1.y, p1.z);

   /*  translate actual end and visible end to final locations
    */
   p3 = TransformVector(&o3prime, &translation); /* p3 = o3prime * T(ox,oy,oz) */
   p2 = TransformVector(&o2prime, &translation); /* p2 = o2prime * T(ox,oy,oz) */

   /*  copy final end locations to link data
    */
   data->links[link].w_end.x = p3.x;		/* actual end */
   data->links[link].w_end.y = p3.y;
   data->links[link].w_end.z = p3.z;
   data->links[link].w_visend.x = p2.x;		/* visible end */
   data->links[link].w_visend.y = p2.y;
   data->links[link].w_visend.z = p2.z;
   data->links[link].w_start.x = p1.x;		/* start point */
   data->links[link].w_start.y = p1.y;
   data->links[link].w_start.z = p1.z;

   /*  compute u vector
    */
   u = VecSub(&p1, &p3);		/* u = p3 - p1 */
   VecNormalize(&u);			/* u = u / mag(u) */

   /*  compute n vector 
    */
   vprime.x = 0.0;
   vprime.y = 1.0;
   vprime.z = 0.0;
   n = VecCrossproduct(&u, &vprime);	/* n = u X vprime */

   /*  compute v vector
    */
   v = VecCrossproduct(&n, &u);		/* v = n X u */

   /*  copy u,v,n vectors to link data
    */
   data->links[link].u_vec.x = u.x;
   data->links[link].u_vec.y = u.y;
   data->links[link].u_vec.z = u.z;

   data->links[link].v_vec.x = v.x;
   data->links[link].v_vec.y = v.y;
   data->links[link].v_vec.z = v.z;

   data->links[link].n_vec.x = n.x;
   data->links[link].n_vec.y = n.y;
   data->links[link].n_vec.z = n.z;

   /*  map start and end points to screen coordinates
    */
   world[0] = WB_MINX;
   world[1] = WB_MINY;
   world[2] = WB_MAXX;
   world[3] = WB_MAXY;
   screen[0] = 0.0;
   screen[1] = 0.0;
   screen[2] = SCREEN_X_SIZE;
   screen[3] = SCREEN_Y_SIZE;
   screen_map = MakeMappingMatrix(world, screen);

   data->links[link].start = MapWPointToScreen( &data->links[link].w_start, &screen_map);
   data->links[link].end = MapWPointToScreen( &data->links[link].w_end, &screen_map);
   data->links[link].visend = MapWPointToScreen( &data->links[link].w_visend, &screen_map);


#ifdef INVKINE_DEBUG
   OutputLink(stdout, data, link);
#endif

   return(0);
} /* end of ComputeInitLink() */


/***********************************************************************

  MapWPointToScreen() - maps the given world point to screen coordinates

***********************************************************************/
pointType
MapWPointToScreen(wpointType *p, matrixType *map)
{
   pointType sp;
   vectorType pvec;
   matrixType pmat, pmat_res;

   pvec = WPoint2Vector( p );
   pmat = Vector2Matrix( &pvec, 3);	/* since map is a 3x3 matrix */

   pmat_res = MatrixMultiply( map, &pmat);

   pvec = Matrix2Vector( &pmat_res );

   sp.x = pvec.x;
   sp.y = pvec.y;
   
   return(sp);
} /* end of MapWPointToScreen() */


/***********************************************************************

  ComputeInitEndEffector() - computes initial end effector stuff

***********************************************************************/
int
ComputeInitEndEffector(MyProgram *data)
{
   
   /*  set center of end effector to actual end of last link
    */
   data->end_effect.center.x = data->links[data->num_links - 1].end.x;
   data->end_effect.center.y = data->links[data->num_links - 1].end.y;

   /*  compute bounding extent of end effector -- used for grabbing
    */
   data->end_effect.extent.bl.x = data->end_effect.center.x - (ENDEFF_GRABSIZE / 2);
   data->end_effect.extent.bl.y = data->end_effect.center.y - (ENDEFF_GRABSIZE / 2);
   data->end_effect.extent.tr.x = data->end_effect.center.x + (ENDEFF_GRABSIZE / 2);
   data->end_effect.extent.tr.y = data->end_effect.center.y + (ENDEFF_GRABSIZE / 2);

   /*  compute necessary info for drawing end effector
    */
   switch(data->end_effect.type) {
      case ENDEFF_SQUARE:
         data->end_effect.square.bl.x = data->end_effect.center.x - (ENDEFF_SIZE / 2);
         data->end_effect.square.bl.y = data->end_effect.center.y - (ENDEFF_SIZE / 2);
         data->end_effect.square.tr.x = data->end_effect.center.x + (ENDEFF_SIZE / 2);
         data->end_effect.square.tr.y = data->end_effect.center.y + (ENDEFF_SIZE / 2);
         break;
      case ENDEFF_CIRCLE:
         data->end_effect.radius = ENDEFF_SIZE / 2;
         data->end_effect.diameter = ENDEFF_SIZE;
         break;
      case ENDEFF_TRIANGLE:
         break;
      default:
         break;
   }

   /*  assign predetermined paths for end effector motion
    */
   switch(data->end_effect.motion) {
      case ENDMOT_LINEAR:
         data->anim.linear_vel.x = ANIM_LIN_VELX;
         data->anim.linear_vel.y = ANIM_LIN_VELY;
         data->anim.linear_vel.z = ANIM_LIN_VELZ;
         data->anim.linear_num_frames = ANIM_LIN_NF;
         break;
      case ENDMOT_CIRCLE:
         break;
      case ENDMOT_RANDOM:
         break;
      default:
         break;
   }

   return(0);
} /* end of ComputeInitEndEffector() */


/***********************************************************************

  DrawLinks() - this function draws the current link hierarchy as stated 
		in the data structure 'data'.

***********************************************************************/
int 
DrawLinks(MyProgram *data)
{
   int i;

   if (data->redraw == TRUE)
      SetDrawMode(SANE_XOR);

   /*  draw each link 
    */
   for (i = 0; i < data->num_links; i++)
      DrawLine(data->links[i].start.x, InvertY(data->links[i].start.y), 
		data->links[i].visend.x, InvertY(data->links[i].visend.y));

   /*  draw end effector
    */
   switch(data->end_effect.type) {
      case ENDEFF_SQUARE:
         DrawFilledBox(data->end_effect.center.x, 
			InvertY(data->end_effect.center.y),
			ENDEFF_SIZE, ENDEFF_SIZE);
         break;
      case ENDEFF_CIRCLE:
         DrawFilledArc(data->end_effect.center.x, 
			InvertY(data->end_effect.center.y),
			ENDEFF_SIZE, ENDEFF_SIZE, 0, 360);
         break;
      case ENDEFF_TRIANGLE:
         break;
      default:
         break;
   }

   SetDrawMode(GXcopy);

   return(0);
} /* end of DrawLinks() */


/******************************************************************

  PointInBox() -- This function determines if a point is within the 
		bounding rectangle.

******************************************************************/
int
PointInBox(pointType p, rectType r)
{
printf("point is at - %d %d\n", p.x, p.y);
printf("extent bl at - %d %d\n", r.bl.x, r.bl.y);
printf("extent tr at - %d %d\n", r.tr.x, r.tr.y);

   if ((p.x < r.bl.x) || (r.tr.x < p.x))
      return(FALSE);

   if ((p.y < r.tr.y) || (r.bl.y < p.y))
      return(FALSE);

   return(TRUE);
} /* end of PointInBox() */


/***********************************************************************

  HandleButton() - this function determines if the end effector of the 
		structure has been grabbed or not.

***********************************************************************/
int 
HandleButton(MyProgram *data)
{
   pointType curr_p;

   curr_p.x = data->curr_mousx;
   curr_p.y = InvertY(data->curr_mousy);

   if (data->button_state == BUTTON_DOWN)  /* check if actually grabbed */

      if (PointInBox(curr_p, data->end_effect.extent) == TRUE) {
         data->endgrabbed = TRUE;
         printf("end effector was grabbed\n");
      }
      else
         data->endgrabbed = FALSE;

   else
      return(1);			/* error, unknown button state */
   
   return(0);
} /* end of HandleButton() */


/***********************************************************************

  HandleMoveStructure() - this function computes the new positions of all
		the links in the hierarchy using the inverse kinematic 
		approach.

***********************************************************************/
int 
HandleMoveStructure(MyProgram *data)
{

   /*  compute positional and angular velocities of end effector
    */


   /*  propagate velocities down the hierarchy
    */


   /*  redraw the link hierarchy
    */
   DrawLinks(data);

   return(0);
} /* end of HandleMoveStructure() */


/***********************************************************************

  ComputeNextFrame() - this function moves the end effector along a 
		predefined path, calls HandleMoveStructure to
		recompute the joint angles and redraw the structure.

***********************************************************************/
int 
ComputeNextFrame(MyProgram *data)
{
   matrixType translation;
   int last_link, f, i;

   last_link = data->num_links - 1;

   /*  move end effector along predefined path based on motion type
    */
   switch(data->end_effect.motion) {
      case ENDMOT_LINEAR:
         translation = MakeTranslationMatrix(data->anim.linear_vel.x, 
					data->anim.linear_vel.y,
					data->anim.linear_vel.z);

         data->anim.new_position = TransformWPoint(&data->links[last_link].w_end, &translation);
         /* recompute joint angles and redraw */
         HandleMoveStructure(data);
         break;

      case ENDMOT_CIRCLE:
         /* recompute joint angles and redraw */
         HandleMoveStructure(data);
         break;

      case ENDMOT_RANDOM:
         data->anim.random_vel.x = nrand();
         data->anim.random_vel.y = nrand();
         data->anim.random_vel.z = 0.0;

         /* recompute joint angles and redraw */
         HandleMoveStructure(data);
         break;

      case ENDMOT_FW_TABLE:	/* forward kinematics example */
         /* erase previous drawing of links */
         if (data->redraw == TRUE)
            DrawLinks(data);

         f = data->frame_count % data->anim.num_frames_per_cycle;
         /* read new state vector from table */
         for (i = 0; i < data->num_links; i++) {
            data->links[i].zrot_deg = data->anim.table[f][i];
            ComputeInitLink(i, data);
         }
         ComputeInitEndEffector(data);

         /* draw new links */
         DrawLinks(data);
         break;

      case ENDMOT_FW_RANDOM:	/* forward kinematics example */
         /* erase previous drawing of links */
         if (data->redraw == TRUE)
            DrawLinks(data);

         /* generate a randomized state vector */
         for (i = 0; i < data->num_links; i++) {
            data->links[i].zrot_deg = data->links[i].zrot_deg + (5 * nrands());
            ComputeInitLink(i, data);
         }
         ComputeInitEndEffector(data);

         /* draw new links */
         DrawLinks(data);
         break;

      default:
         break;
   }

   /*  increment frame count
    */
   data->frame_count++;

   return(0);
} /* end of ComputeNextFrame() */


/*****************************************************************
*  ParseString - parses list of strings into array of strings    *
******************************************************************/
int 
ParseString(char *string, char *args[])
{
   char c, *argstart;
   int arglen, argcount=0;
   
   argstart = string;

   for (; *string != '\0'; string++) {
      c = *string;
      if (isspace(c) || (c == '\0')) {
         args[argcount] = argstart;
         arglen = string - argstart;
         args[argcount][arglen] = '\0';
         argcount++;
         argstart = string + 1;
      }
   }

   return(argcount);
} /* end of ParseString() */


/***********************************************************************

  OutputLink() - this function is used to aid in debug, it outputs the
		specified link's information.

***********************************************************************/
int 
OutputLink(FILE *outfile, MyProgram *data, int link)
{
   int r;

   fprintf(outfile, "\nLINK ENTRY #%d:\n", link);   

   fprintf(outfile, "link id = %d\n", data->links[link].id);
   fprintf(outfile, "link type = %d\n", data->links[link].type);
   fprintf(outfile, "link wstart = %f %f %f\n", data->links[link].w_start.x, 
					data->links[link].w_start.y, 
					data->links[link].w_start.z);
   fprintf(outfile, "link wend = %f %f %f\n", data->links[link].w_end.x, 
					data->links[link].w_end.y, 
					data->links[link].w_end.z);
   fprintf(outfile, "link wvisend = %f %f %f\n", data->links[link].w_visend.x, 
					data->links[link].w_visend.y, 
					data->links[link].w_visend.z);
   fprintf(outfile, "link total len = %f\n", data->links[link].total_length);
   fprintf(outfile, "link visible len = %f\n", data->links[link].visible_length);
   fprintf(outfile, "link x rot = %f\n", data->links[link].xrot_deg);
   fprintf(outfile, "link y rot = %f\n", data->links[link].yrot_deg);
   fprintf(outfile, "link z rot = %f\n", data->links[link].zrot_deg);
   fprintf(outfile, "link u vec = %f %f %f\n", data->links[link].u_vec.x, 
					data->links[link].u_vec.y, 
					data->links[link].u_vec.z);
   fprintf(outfile, "link v vec = %f %f %f\n", data->links[link].v_vec.x, 
					data->links[link].v_vec.y, 
					data->links[link].v_vec.z);
   fprintf(outfile, "link n vec = %f %f %f\n", data->links[link].n_vec.x, 
					data->links[link].n_vec.y, 
					data->links[link].n_vec.z);

   fprintf(outfile, "combined rot matrix:\n");
   fprintf(outfile, "  num rows = %d\n", data->links[link].rot_mat.r);
   fprintf(outfile, "  num cols = %d\n", data->links[link].rot_mat.c);
   for (r = 0; r < data->links[link].rot_mat.r; r++)
      fprintf(outfile, "  %f %f %f %f\n", data->links[link].rot_mat.m[r][0], 
					data->links[link].rot_mat.m[r][1], 
					data->links[link].rot_mat.m[r][2], 
					data->links[link].rot_mat.m[r][3]);

   fprintf(outfile, "link start = %d %d\n", data->links[link].start.x, 
					data->links[link].start.y);
   fprintf(outfile, "link end = %d %d\n", data->links[link].end.x, 
					data->links[link].end.y);
   fprintf(outfile, "link visend = %d %d\n", data->links[link].visend.x, 
					data->links[link].visend.y);

   return(0);
} /* end of OutputLink() */


/* end of invkine.c */
