/*****************************************************************************
 *
 *	Room file for Dungeons of Thuria.
 *
 *	File:	room.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	12/04/96
 *
 *	Revs:
 *	  0.1	02/13/98  converted to "c" file
 *	  0.0 	12/04/96  originated
 *
 *****************************************************************************/


#ifndef MAIN_H
#include "main.h"
#endif


/* 
# room description file for Dungeons of Thuria
#
# Format:  Room #, Line #, Text
#
*/

ROOM_S_T room[] = {
 0, 1, "A small entrance chamber with debris",
 0, 2, "scattered.  A passageway leads north.",
 0, -1, " ",

 1, 1, "A small antechamber behind the throne.",
 1, 2, "Several tapestries hang on the walls.",
 1, -1, " ",

 2, 1, "Ornate throne sits in center of room.",
 2, 2, "Heavy green draperies cover the wall",
 2, 3, "to the west behind the throne.  The",
 2, 4, "only exit appears to be east.",
 2, -1, " ",

 3, 1, "Long corridor with doorways to the",
 3, 2, "east, west, and south.",
 3, -1, " ",

 4, 1, "Castle's dining hall. Tables covered",
 4, 2, "with food scraps, and broken dishes.",
 4, 3, "Swinging doors are to the east.",
 4, -1, " ",

 5, 1, "Decent sized kitchen. Fire pit sits",
 5, 2, "to one side.  Yet more food scraps.",
 5, -1, " ",

 6, 1, "Very small room, six feet square.",
 6, 2, "Broken lumber is piled in one corner.",
 6, -1, " ",
 
 7, 1, "Large hall with exits on all sides.",
 7, 2, "Antique oak walls are varnished. An",
 7, 3, "elaborate chandelier is above you.",
 7, -1, " ",

 8, 1, "Damp grey mist swirls around your",
 8, 2, "feet. Stairs lead downward into",
 8, 3, "darkness. An exit is to the west.",
 8, -1, " ",

 9, 1, "You see the largest beaver dam you",
 9, 2, "have ever seen. A marvelous work of",
 9, 3, "engineering.  A trail heads south",
 9, 3, "and a path winds north around pond.",
 9, -1, " ",

10, 1, "You climbed high above the valley",
10, 2, "floor and are next to narrow river",
10, 3, "with swiftly moving current. A trail",
10, 4, "winds north. A wider path leads east.",
10, -1, " ",

11, 1, "You are next to a beaver pond. There",
11, 2, "are beavers nearby.  You can only",
11, 3, "travel south.",
11, -1, " ",

12, 1, "A long valley, filled with mist.",
12, 2, "Impassable mountains to the north",
12, 3, "and south prohibit travel.  A narrow",
12, 4, "leads west.  A road leads east.",
12, -1, " ",

13, 1, "You are outside a modest castle.  A", 
13, 2, "road leads west and east.  A massive",
13, 3, "wooden door is facing you.",
13, -1, " ",

14, 1, "Babbling brook interrupts the trail.",
14, 2, "The trail continues east but looks",
14, 3, "kind of swampy and foreboding.",
14, -1, " ",

15, 1, "Stairs lead up from the eastern wall.",
15, 2, "Doorways lead north and south. A",
15, 3, "statue of a native american indian",
15, 4, "stands across from the stairs.",
15, -1, " ",

#if 0
16, 1, "A dank, musty odor fills the air.  A very dark passageway leads west.",
16, 2, "The deep gloom nearly conceals a narrow set of stairs which lead down.", 
16, -1, " ",

17, 1, "You are in a small alcove above a room filled with pillows.  A",
17, 2, "steeply sloped passage leads back down.",
17, -1, " ",

18, 1, "You are in a narrow north-south passage.  Indecipherable markings",
18, 2, "cover both walls.",
18, -1, " ",

19, 1, "Several dozen pillows cover the entire floor of this room.  Each",
19, 2, "pillow is richly embroidered with a pattern of many different",
19, 3, "colors.  A single doorway lies to the south, and a steeply sloped",
19, 4, "passage leads up.  It does appear climbable.",
19, -1, " ",

20, 1, "A massive granite pillar sits squarely in the middle of this room.  A",
20, 2, "pair of ornate doorways lead south and east.", 
20, -1, " ",

21, 1, "This room is perfectly round and the walls have no visible markings.",
21, 2, "Only the western and northern exits disturb the perfect symmetry of",
21, 3, "the curvature of the walls.",
21, -1, " ",

22, 1, "The darkness of this room swallows the glow from your lantern.  From",
22, 2, "somewhere just beyond your sight a hollow voice says \"plugh\".  After",
22, 3, "groping around in the darkness you find the only exit is to the east.",
22, -1, " ",

23, 1, "You are in the west end of a large hall.  The hall extends to the",
23, 2, "east.  Doorways lead north and south.  Obviously, it was a place used",
23, 3, "for entertaining visitors to the castle.  Several large paintings",
23, 4, "line the walls well out of reach.  A narrow set of stairs lead up.",
23, -1, " ",

24, 1, "You are in the east end of a large hall.  The hall extends to the",
24, 2, "west.  A single doorway leads north.",
24, -1, " ",

25, 1, "The walls of this room are painted glossy black.  A single exit",
25, 2, "leads back north.",
25, -1, " ",

26, 1, "You are in a dimly lit room.  The only illumination appears to be",
26, 2, "coming from a narrow slit in the wall to the east.",
26, -1, " ",

27, 1, "A strange green glow fills this room.  A straw nest lies in the center",
27, 2, "of room.  An odd squawking sound seems to be coming from somewhere.",
27, -1, " ",

28, 1, "You are in a narrow crevice overlooking a library.  The only other",
28, 2, "exit is to the south.",
28, -1, " ",

29, 1, "This is a very tastefully decorated room with several nice oriental", 
29, 2, "carpets laying on the floor.", 
29, -1, " ",

30, 1, "You are on a narrow ledge on the northern side a bottomless fissure.",
30, 2, "The fissure is spanned by a crystal bridge.",
30, -1, " ",

31, 1, "Engraved on the eastern wall are some more indecipherable writings.",
31, 3, "A single exit leads back west.",
31, -1, " ",

32, 1, "You are in a small room high above a strange room below.  A tight",
32, 2, "opening leads north.  A small hole in the wall is nearby.",
32, -1, " ",

33, 1, "This is obviously a library full of books.  A large table lies in",
33, 2, "center of the room.  The books seem to cover a range of subjects from",
33, 3, "science and history, to religion and politics.",
33, -1, " ",

34, 1, "You are in a large cave with exits to the west and south.  A ",
34, 2, "bottomless fissure lies to the north.  There appears to be a narrow",
34, 3, "ledge on the other side of the fissure.",
34, -1, " ",

35, 1, "You are in a strange little room.  Exits lie to the south and east.",
35, 2, "A small hole in the wall lies far above a basket of rope.",
35, -1, " ",

36, 1, "You are in a small cave filled with many large boulders.  Exits lie",
36, 2, "to the north, west and east.",
36, -1, " ",

37, 1, "You are standing on a narrow beach on the northern side of a vast",
37, 2, "underground lake.  There appears to be no way to walk around the",
37, 3, "perimeter of the lake.  A small passage leads back to the west.",
37, -1, " ",

38, 1, "You are standing on a wide beach on the southern side of a vast",
38, 2, "underground lake.  A twisting passageway leads off the east.",
38, -1, " ",

39, 1, "This is a small cave which at first seemed to be vacant.  A strange",
39, 2, "little man is sitting in a chair near the doorway to the north.  He",
39, 3, "is holding a fierce looking weapon with a long curved blade at the",
39, 4, "end of a pole.",
39, -1, " ",

40, 1, "This a pyramid shaped room, but from the inside perspective.  A",
40, 2, "twisting passageway leads south.",
40, -1, " ",

41, 1, "You are standing in your kitchen still holding your morning paper",
41, 2, "clutched in your left hand.  An empty coffee cup lies at your feet.",
41, 3, "Apparently, you either had a bad dream or too much caffienne.  You",
41, 4, "hear the rumble of a tow truck pulling into your driveway.  Maybe",
41, 5, "you'll finally make it into work this morning afterall.", 
41, -1, " ",

42, 1, "You are lost in the swamp.",
42, -1, " ",

43, 1, "You are hopelessly lost in the swamp.",
43, -1, " ",

44, 1, "You are hopelessly lost in the swamp.",
44, -1, " ",

45, 1, "You are hopelessly lost in the swamp.",
45, -1, " ",

46, 1, "You are hopelessly lost in the swamp.",
46, -1, " ",

47, 1, "You are hopelessly lost in the swamp.",
47, -1, " ",

48, 1, "You are lost in the swamp.",
48, -1, " ",

49, 1, "You are hopelessly lost in the swamp.",
49, -1, " ",

50, 1, "You are hopelessly lost in the swamp.",
50, -1, " ",
#endif

-1, 0, " ",
};
