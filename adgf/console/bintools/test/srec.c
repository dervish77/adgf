
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* |                                                          | */
/* |  FileName:   out.c                                       | */
/* |  Input File: test/srec.txt                               | */
/* |                                                          | */
/* |  Creation:   Thu Jul 28 18:42:46 2022                    | */
/* |                                                          | */
/* |  DESCRIPTION:                                            | */
/* |  C Language Array contains pointers to Motorola Srecords,| */
/* |  enabling srecord download at runtime.                   | */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */




unsigned char *mydata[] = {
"S11F00007C0802A6900100049421FFF07C6C1B787C8C23783C6000003863000026",
"S11F001C4BFFFFE5398000007D83637880010014382100107C0803A64E800020E9",
"S111003848656C6C6F20776F726C642E0A0042",
"S5030003F9",
"S9030000FC"
};


/* ***********************************************************
 * Total Number of Srecord Chars: 190
 * Number of Srecord Lines:       5
 * Longest Srecord Line:          66 chars
 * ***********************************************************
 */


