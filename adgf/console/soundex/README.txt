README for Soundex Translator Program
-------------------------------------


Soundex is a system for phonetically indexing federal census data.  It was
first applied to the 1880 federal census.  It codes surnames (last names)
based on the way the name sounds rather than how it is spelled.  This program
simplifies the coding of surnames into their Soundex codes.  


----------------------------------------------------------------------------

Files within this directory:

	README.txt	    - this file
	CHANGES.txt	    - revision history
	LICENSE.txt	    - copying/license terms

	main.c		    - main program function
	main.h

	file.c	        - file routines
	file.h

	soundex.c	    - soundex routines
	soundex.h

    soundex.cbp     - CodeBlocks IDE project file
    soundex.layout

	soundex.man	    - man page for soundex program

	Makefile	    - makefile to make target 'soundex' for Unix systems

	list		    - sample surname list (used by unit test)

----------------------------------------------------------------------------

To unpack distribution file:

	gunzip soundex_0.4.tar.gz

	tar xvf soundex_0.4.tar
	
----------------------------------------------------------------------------

To make soundex executable:

	cd soundex
	
	make

----------------------------------------------------------------------------

To make and run unit test:

	cd soundex
	
	make test

----------------------------------------------------------------------------

To make and install soundex executable and man page:

	cd soundex

	<edit makefile to change installed directory if desired>
	
	make all

----------------------------------------------------------------------------

To use soundex:

	soundex [<surname string> | [-f surname_file]|[-h]|[-v]]

----------------------------------------------------------------------------

Examples:  (single surnames)

	% soundex Eberhard

	Soundex output:
	    Eberhard     b, r, r      E-166


	% soundex Hildebrand

	Soundex output:
	    Hildebrand     l, d, b      H-431


	% soundex Zita

	Soundex output:
	    Zita     t      Z-300


Examples:  (list of surnames)

	% soundex -f mylist

	Soundex output:
	    Eberhard     b, r, r      E-166
	    Hildebrand     l, d, b      H-431
	    Zita     t      Z-300


Note that the list file must contain more than one surname.  The format of 
the file is as follows:

3
jones
smithson
zeman

The number is the number of surnames in the list file.  The remaining
entries are surnames listed in any order.  But each entry must have a
<CR> at the end of the line.

----------------------------------------------------------------------------


Notes from:

THE 1790-1890 FEDERAL POPULATION CENSUSES:
CATALOG OF NATIONAL ARCHIVES MICROFILM
(PART 1)


National Archives Trust Fund Board
National Archives and Records Administration
Washington, DC
1993


Step 1:  Code Surname

     To use Soundex, researchers must first code the surname of
the person or family in which they are interested. Every Soundex
code consists of a letter and three numbers, such as B-536,
representing names such as Bender. The letter is always the first
letter of the surname, whether it is a vowel or a consonant.
     Disregard the remaining vowels (A, E, I, O, and U) as well
as W, Y, and H. Assign numbers to the next three consonants of
the surname according to the coding guide included in table 1,
but note the exceptions discussed later. Disregard any remaining
consonants. If there are not three consonants following the
initial letter, use zeroes to complete the three-digit code. A
name yielding no code number, such as Lee, would thus be L-000. 
A name with only one code number, such as Cook, would be C-200. 
Further discussion will use this name and code as examples.
     Most surnames can be coded using the guide. The next
discussions explain exceptions.

TABLE 1: SOUNDEX CODING GUIDE

After retaining the first letter of the surname and disregarding
the next letters if they are A, E, I, O, U, W, Y, and H, then:

     The number               Represents the letters
          1                    B, P, F, V     
          2                    C, S, K, G, J, Q, X, Z     
          3                    D, T     
          4                    L     
          5                    M, N     
          6                    R    

Prefixes 
     If the surname has a prefix, such as D', De, dela, Di, du,
Le, van, or Von, code it both with and without the prefix because
it might be listed under either code. The surname vanDevanter,
for example, could be V-531 or D-153. Mc and Mac are not
considered to be prefixes and should be coded like other
surnames.

Double Letters
     If the surname has any double letters, they should be
treated as one letter. Thus, in the surname Lloyd, the second l
should be crossed out. In the surname Gutierrez, the second r
should be disregarded.

Side-by-Side Letters 
     A surname may have different side-by-side letters that
receive the same number on the Soundex coding guide.  For
example, the c, k, and s in Jackson all receive a number 2 code.
These letters with the same code should be treated as only one
letter. In the name Jackson, the k and s should be disregarded.
This rule also applies to the first letter of a surname, even
though it is not coded. For example, Pf in Pfister would receive
a number 1 code for both the P and f.  Thus in this name the
letter f should be crossed out, and the code is P-236.

American Indian and Asian Names 
     A phonetically spelled American Indian or Asian name was
sometimes coded as if it were one continuous name. If a
distinguishable surname was given, the name may have been coded
in the normal manner. For example, Dances with Wolves might have
been coded as Dances (D-522) or as Wolves (W-412), or the name
Shinka-Wa-Sa may have been coded as Shinka (S-520) or Sa (S-000).

If Soundex cards do not yield expected results, researchers
should consider other surname spellings or variations on coding
names.

Female Religious Figures 
     Nuns or other female religious figures with names such as
Sister Veronica may have been members of households or heads of
households or institutions where a child or children age 10 or
under resided. Because many of these religious figures do not use
a surname, the Soundexes for the post-1880 censuses frequently
use the code S-236, for Sister, whether or not a surname exists.
So far as can be determined, though, the Soundex for the 1880
census does not use the code S-236 for this purpose.
     Because of the limitations of the 1880 Soundex, the number
of cards mentioning a nun or comparable person is likely to be
very small. If this person was the head of a household or
institution with children, indexers may have coded the head's
surname. If no surname existed, the indexers may have used the
Not Reported (NR) surname option discussed later. In either case,
if the household or institution headed by a female religious
figure included a child under 10, the researcher also can code
the child's surname and seek an Individual Card. No Individual
Card, though, applies to a nun or any other person 10 years or
older.

Single-Term Names 
     In 1880 many individuals, especially in Alaska or areas with
many Native Americans, may have used only a single-term name such
as Loksi or Hiawatha. Perhaps not until the 1900s did their
descendants use a surname. Some researchers, therefore, may need
to code a single-term name as though it was a surname. If this
rule applies to the head of a family and other family members
have different names, Individual Cards will also pertain to those
members age 10 or younger.

TABLE 2: EXAMPLES OF SOUNDEX CODING

     Name                Letters Coded       Coding

     Allricht            l, r, c             A-462 
     Eberhard            b, r, r             E-166 
     Engebrethson        n, g, b             E-521 
     Heimbach            m, b, c             H-512 
     Hanselmann          n, s, l             H-524 
     Henzelmann          n, z, l             H-524 
     Hildebrand          l, d, b             H-431 
     Kavanagh            v, n, g             K-152 
     Lind, Van           n, d                L-530 
     Lukaschowsky        k, s, s             L-222 
     McDonnell           c, d, n             M-235 
     McGee               c                   M-200 
     O'Brien             b, r, n             O-165 
     Opnian              p, n, n             O-155 
     Oppenheimer         p, n, m             O-155 
     Riedemanas          d, m, n             R-355 
     Zita                t                   Z-300 
     Zitzmeinn           t, z, m             Z-325

----------------------------------------------------------------------------
last update: March 23, 2011

