/***********************************************************************

   File:  	invkine.h

   Author: 	Brian Lingard

   Date:	4/8/95

 Header file for inverse kinematics demo program.  This file contains
 definitions and typedefs for useful structures when defining chains
 of articulated links.

 All links have the same length.  Assume that 'dt' (or time interval) 
 is equal to one time unit. Thus all calculations of positional 
 velocities and rotational velocities can be easily converted back 
 into positions and rotations.


 Link chains are defined as follows:

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

#ifndef _INVKINE_H
#define _INVKINE_H

#include "vecmath.h"

#define SCREEN_X_SIZE   800
#define SCREEN_Y_SIZE	800

#define InvertY(y)	(SCREEN_Y_SIZE - y)

#define MAX_BUF_LEN	80
#define NUM_LINK_PARMS	9

#define MAX_NUM_LINKS	10		/* link parameters */
#define LINK_LENGTH	1

#define LINK_UNKN	0
#define LINK_ROOT	1		/* link types */
#define LINK_LINK	2
#define LINK_BRCH	3

#define ENDEFF_SIZE	10		/* end effector size in pixels */
#define ENDEFF_GRABSIZE 20

#define ENDEFF_UNKNOWN	0
#define ENDEFF_SQUARE	1		/* shapes of end effector */
#define ENDEFF_CIRCLE	2
#define ENDEFF_TRIANGLE 3

#define ENDMOT_UNKNOWN	0
#define ENDMOT_MANUAL	1		/* end effector motion types */
#define ENDMOT_LINEAR	2
#define ENDMOT_CIRCLE	3
#define ENDMOT_RANDOM	4
#define ENDMOT_FW_TABLE 5
#define ENDMOT_FW_RANDOM 6

#define MAX_NFPC	20		/* max number frames per cycle */

#define ANIM_LIN_VELX	((float) 0.1)	/* linear velocity */
#define ANIM_LIN_VELY	((float) -0.1)
#define ANIM_LIN_VELZ	((float) 0.0)
#define ANIM_LIN_NF	50		/* linear number of frames */

#define WB_MINX		-20.0		/* define world bounds */
#define WB_MAXX		20.0
#define WB_MINY		-20.0
#define WB_MAXY		20.0
#define WB_MINZ		-20.0
#define WB_MAXZ		20.0

#define VEC_SIZE	3		/* vector/matrix parameters */
#define HGVEC_SIZE	4
#define MAT_SIZE	4

#define BUTTON_UP	0		/* left button state */
#define BUTTON_DOWN	1

typedef struct {
   pointType bl;			/* bottom left of rectangle */
   pointType tr;			/* top right of rectangle */
} rectType;


/*  link structure 
 */
typedef struct {
   int 		id;			/* unique id of this link */
   int		linkto;			/* id of previous link, -1 if start */
   int		type;			/* link type */
   wpointType	w_start;
   wpointType	w_end;
   wpointType	w_visend;
   float 	total_length;
   float	visible_length;
   float	xrot_deg;		/* init rotation about x axis */
   float	yrot_deg;		/* init rotation about y axis */
   float	zrot_deg;		/* init rotation about z axis */
   vectorType	u_vec;			/* normalized u axis vector */
   vectorType	v_vec;			/* normalized v axis vector */
   vectorType	n_vec;			/* normalized n axis vector */
   matrixType	rot_mat;		/* combined rotation matrix */
   pointType	start;
   pointType	end;
   pointType	visend;			/* visible end, if not same as end */
} linkType;


/*  end effector structure
 */
typedef struct {
   int		link_id;		/* which link this is end of */
   int		type;			/* end effector type */
   int 		motion;			/* end effector motion type */
   pointType	center;			/* end effector center */
   rectType	extent;			/* extent of end effector */
   rectType	square;			/* square end effector */
   int		radius;			/* radius of circle in pixels */
   int		diameter;		/* diameter of circle in pixels */
   pointType	polyverts[3];		/* vertices of triangle */
} endType;


/*  animation structure
 */
typedef struct {
   wpointType	new_position;		/* new position of last link's actual end */
   vectorType	linear_vel;		/* linear velocity */
   int		linear_num_frames;	/* number of frames to travel */
   wpointType	circle_center;
   float	circle_radius;
   float	circle_angular_vel;	/* radians per frame */
   int		circle_num_frames;	/* number of frames to travel */
   vectorType	random_vel;		/* random velocity */
   int		num_frames_per_cycle;
   float	table[MAX_NFPC][MAX_NUM_LINKS];	/* table of zrot for each frame */
   int		start_time;
   int		stop_time;
} animType;

#endif /* _INVKINE_H */
/* end of invkine.h */
