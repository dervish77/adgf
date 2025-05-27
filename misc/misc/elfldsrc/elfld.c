#define COMPILE_FOR_UNIX
#define NEW_TOOLKIT
#define VERBOSE
#define IGNORE_SKIPPING

/* ******************************************************
 * General Flow here:
 *
 * 1. Read the elfheader:
 * 1.1 Determine whether the file is 'SANE'...
 *       The Magic# is OK and a real "ELF" formatted file 
 *	 for 32bit BigEndian PPC target.
 *
 * 2. Derive information about the rest of the headers.
 *       where the start of the section headers are.
 *       where the start of the program segment headers are.
 *
 * 3. Read the string table section header, then assign a pointer
 *    to this table.
 * 
 * String Table Section Header address =
 * (filebase + (e_shoff + (e_shstrndx * e_shentsize))
 *
 * We use this to print out the name of the section we're loading...
 *     i.e.: ".text", ".data", ".bss"
 *
 * 4. Read each Program Segment Header one at a time. For each
 *    Program Segment Header, read through the Section Header Table
 *    and determine which sections apply to the current Program Segment.
 *
 * 5. Load the valid Sections into memory based on their sh_addr and
 *    sh_size. Seek to the file offset using the sh_offset header info.
 *
 * 6. Print the ENTRY Pt address and jump to it. We may leave the
 *       jumping for later.
 * *******************************************************************
 */

#ifdef COMPILE_FOR_UNIX /* then native Sun4 compile */
#include <stdio.h>
#endif
#include <types.h>
#include <elfld.h>
#include <elf.h>
#include <elfcommon.h>
#include <unistd.h>     /* this comes from /usr/include/sys */

#ifndef COMPILE_FOR_UNIX
extern uint8_t _begin_bss, _end_bss;
#endif

bool_t read_elfhdr(FILE *fd_in, Elf32_External_Ehdr *elfhdr);

void print_elfhdr(Elf32_External_Ehdr *e_hdr);

bool_t check_elfhdr(Elf32_External_Ehdr  *e_hdr);

void print_scnhdr(Elf32_External_Shdr *scnhdr, int num, char *strtab, bool_t ldflag);
bool_t read_proghdr(FILE *fd_in, Elf32_External_Phdr *proghdr);
void print_proghdr(Elf32_External_Phdr *proghdr, int num);

Elf32_External_Shdr *read_scnhdr_ptr(FILE *fd_in);

uint8_t *read_strtab_ptr(FILE *fd_in, Elf32_External_Shdr *scnhdr);

bool_t elf_section_ok(Elf32_External_Shdr *scnhdr, Elf32_External_Phdr *proghdr, uint8_t *strtab);

bool_t load_elf_section(FILE *fd_in, Elf32_External_Shdr *scnhdr, uint8_t *strtab);

uint8_t *read_image_ptr(FILE *fd_in, Elf32_External_Shdr *scnhdr, uint8_t *strtab);

void check_bss_warning(Elf32_External_Shdr *scnhdr, uint8_t *strtab);

char *shstrtab = ".shstrtab";

bool_t elfld(FILE *fd_in, Elf32_External_Ehdr *elfhdr)
{
    /* The Program Segment Header data structure is allocated on the STACK */
    Elf32_External_Phdr proghdr; /* program header - read one at a time */
    
    /* the follow two variables will actually point to the FLASH device */
    register Elf32_External_Shdr *scnhdr; /* section header - read one at a time */  
    register uint8_t *strtab;    /* string table for lookup of section names */
    
    /* these are register variables */
    uint32_t start, offset, segsize, progsize, exp_addr, pad;
    int32_t i, j;
    strtab = 0;
    scnhdr = 0;

    /* -- Step 1 -- */

    /* It is not guaranteed that the elf header, program headers, 
     * and section headers are contiguous in the file. Read each one 
     * in separately, but not necessarily in order.
     */
    if (read_elfhdr(fd_in, elfhdr)==FAILED) return(FAILED);  

    /* print-out the elf-file header to the display */
    print_elfhdr(elfhdr);
    
    /* sanity check the section size field in the header */

    if (sizeof(Elf32_External_Shdr) != elfhdr->e_shentsize) {
	printf("\nError: Sect size specified in elf-hdr(%d) NOT= expected(%d)\n",
	       elfhdr->e_shentsize, sizeof(Elf32_External_Shdr));
	return(FAILED);
    }
    
    /* -- Step 2 -- */

    /* The "text" names for the sections are in a STRING TABLE. The
     * string table is described in a section header. Typically, it 
     * is the last section header... "who knows why"... but we look 
     * specifically for this section up front.
     */

    /* save the starting offset to the Section Headers */
    start = elfhdr->e_shoff;
    
    /* Sanity check that STRING SECTION index is < total NUM of SECTIONS */
    
    if (!(elfhdr->e_shstrndx < elfhdr->e_shnum)) {
	printf("\nError: String Section index(%d) NOT < Tot #of Sections(%d)\n",
	       elfhdr->e_shstrndx, elfhdr->e_shnum);
	return(FAILED);    /* FAILED */
    }
    
    /* The string table section header is the "e_shstrndx"th entry in the 
     * Section Header Table. Calculate the offset to this entry */
    
    offset = (elfhdr->e_shstrndx * elfhdr->e_shentsize);

    /* Now Position to the STRING SECTION HEADER */

    if (fseek(fd_in, start+offset, SEEK_SET)) {
	printf("\nError: Seek error for String section header @0x%x\n", 
	       start+offset);
	return(FAILED);
    }
    
    /* read in the STRING SECTION header here */
    if ((scnhdr = read_scnhdr_ptr(fd_in))==(Elf32_External_Shdr *)FAILED) {
	return(FAILED);
    }

#ifdef VERBOSE    
    printf("\n*** READING THE STRING SECTION HEADER ***\n");
#endif
    
    /* print the STRING SECTION header (strtab is passed =0 and ignored) */
    print_scnhdr(scnhdr, elfhdr->e_shstrndx, strtab, TRUE);
    
    /* -- Step 3 -- */
    
    /* Now, get init the "string table" pointer and index into it using 
     * the section header's "sh_name" index. If the name found there is 
     * NOT=".shstrtab", then something is seriously wrong!
     */

    if (fseek(fd_in, scnhdr->sh_offset, SEEK_SET)) {
	printf("\nError: Seek error for String Table.\n");
	return(FAILED);
    }
    
    /* init the pointer to the STRING TABLE here... */
    if ((strtab = read_strtab_ptr(fd_in, scnhdr))==(uint8_t *)FAILED)
	return(FAILED);
    
    /* verify the section name = ".shstrtab" */
    if(strcmp(&strtab[scnhdr->sh_name], &shstrtab[0])) {
	printf("\nError: Expect string table[%d] =: %s, but read %s instead!\n", 
	       &shstrtab[0], &strtab[scnhdr->sh_name]);
	return(FAILED);
    }
    
    /* -- Step 4 -- */

    /* Loop for each Program Segment Entry in the ELF file... */
    
    progsize = 0;

    for(i = 0; i < elfhdr->e_phnum; i++) {   
	
	start  = elfhdr->e_phoff;            /* get start of Program Segment Hdr Table */

	offset = (i * elfhdr->e_phentsize);  /* calc offset to i'th Prog Segment Hdr */
	
	/* Seek to the next PROGRAM SEGMENT HEADER */	
	if (fseek(fd_in, start+offset, SEEK_SET)) {
	    printf("\nError: Seek error for Program Segment headers.\n");
	    return(FAILED);
	}
	
	/* Read in the next PROGRAM SEGMENT HEADER into our buffer */
	if (read_proghdr(fd_in, &proghdr)==FAILED) 
	    return(FAILED);
	
	print_proghdr(&proghdr, i);
	
	/* -- Step 5 -- */

	/* Scan through each section header loading only the relavent ones */	

	segsize = 0;     /* clear count for this program segment size */

	exp_addr = 0;

	for (j=0; j<elfhdr->e_shnum; j++) {	
	    
	    /* Seek to the jth section header */

	    start  = elfhdr->e_shoff;
	    offset = (j * elfhdr->e_shentsize);
	    
	    if (fseek(fd_in, start+offset, SEEK_SET)) {
		printf("\nError: Seek error for section headers.\n");
		return(FAILED);
	    }

	    /* other section headers are read in here */   
	    if ((scnhdr = read_scnhdr_ptr(fd_in))==(Elf32_External_Shdr *)FAILED) 
		return(FAILED);
	    
	    /* -- Step 6 -- */
	   
	    /* Look for only valid program sections to load for this segment. */
	    
	    if (elf_section_ok(scnhdr, &proghdr, strtab) == TRUE) {

		/* print a warning if bss will be trashed */
		check_bss_warning(scnhdr, strtab);

		/* Print Loading... */
		print_scnhdr(scnhdr, j, strtab, TRUE);

		/* -- Step 7 -- */
		
		/* Copy the Section into system memory */
		
		if (load_elf_section(fd_in, scnhdr, strtab)==FAILED)
		    return(FAILED);
		
		/* segsize = sum of memory space requirements by program sections */

		pad = 0;   /* sections are not always contiguous... so consider pad*/

		/* are sections contiguous in memory ? */

		if (exp_addr != 0) {       /* if 1st section, nothing to check */
		    if (exp_addr != scnhdr->sh_addr)
			pad = (scnhdr->sh_addr - exp_addr); /* calculate padding */
		}
#ifdef VERBOSE
		if (pad) printf(", pad %d. bytes", pad);
#endif
		segsize += scnhdr->sh_size + pad;

		/* init exp_addr = next expected memory address to be loaded */
		
		exp_addr = scnhdr->sh_addr + scnhdr->sh_size;
	    } 
	           /* Make sure we initialize bss sections to zero during i=0 */
	    else if ((scnhdr->sh_type == SHT_NOBITS) && (i==0)) {

		/* Here we found a .BSS section... so force this memory to ZEROES */

		print_scnhdr(scnhdr, j, strtab, TRUE);
		
#ifndef COMPILE_FOR_UNIX
		bzero(scnhdr->sh_addr, scnhdr->sh_size);		
#endif

	    } 
#ifdef VERBOSE
	    else {

		print_scnhdr(scnhdr, j, strtab, FALSE);

	    }
#endif	    

	} /* next section header */
	
	printf("\n\nSegment %d Loaded: [%d. bytes]\n", i, segsize);

	if (segsize != proghdr.p_filesz) {
	    
	    printf("\n\nWarning: Program size loaded [0x%x] != proghdr.p_filesz [0x%x]\n",
		   segsize, proghdr.p_filesz);
	
	} else if (segsize > proghdr.p_memsz) {
	    
	    printf("\n\nWarning: Program size loaded [0x%x] > proghdr.p_memsz [0x%x]\n",
		   segsize, proghdr.p_memsz);
	}
	progsize += segsize;
	
    } /* next program header */


    printf("\nProgram Size: [%d. bytes]", progsize);

    printf("\nEntry Point = 0x%08x\n", elfhdr->e_entry);

    return(PASSED);
}


void print_elfhdr(Elf32_External_Ehdr *elfhdr)
{
#ifdef VERBOSE
    int i;
    printf("\n*** First - Elf32_External_Ehdr ***\n");
    printf("\nelfhdr->e_ident:  - this is the magic num:\n");
    
    for (i=0; i<16; i++) {
	printf("%02x ", elfhdr->e_ident[i]);
    }

    printf("\nelfhdr->e_type      = 0x%04x - obj filetype", elfhdr->e_type);
    printf("\nelfhdr->e_machine   = 0x%04x - req'd arch", elfhdr->e_machine);
    printf("\nelfhdr->e_version   = 0x%08x - objfile version", elfhdr->e_version);
    printf("\nelfhdr->e_entry     = 0x%08x - entry pt vir addr", elfhdr->e_entry);
    printf("\nelfhdr->e_phoff     = 0x%08x - prog hdr tbl file offset", elfhdr->e_phoff);
    printf("\nelfhdr->e_shoff     = 0x%08x - sect hdr tbl file offset", elfhdr->e_shoff);
    printf("\nelfhdr->e_flags     = 0x%08x - proc specific flags", elfhdr->e_flags);

    printf("\nelfhdr->e_ehsize    = 0x%04x - elf hdr sz", elfhdr->e_ehsize);

    printf("\nelfhdr->e_phentsize = 0x%04x - prog hdr tbl entry sz", elfhdr->e_phentsize);
    printf("\nelfhdr->e_phnum     = 0x%04x - prog hdr tbl entry ct", elfhdr->e_phnum);

    printf("\nelfhdr->e_shentsize = 0x%04x - sect hdr table entry sz", elfhdr->e_shentsize);
    printf("\nelfhdr->e_shnum     = 0x%04x - sect hdr tbl entry ct", elfhdr->e_shnum);
    printf("\nelfhdr->e_shstrndx  = 0x%04x - sect hdr string tbl index\n", elfhdr->e_shstrndx);
#endif
}



bool_t check_elfhdr(Elf32_External_Ehdr *elfhdr)
{

    /* Make sure we like the file header */
    
    /* elf magic number is 0x7f"ELF"; CLASS should indicate 32 bit file;
       DATA should indicate Big Endian; should be current version;
       type should be executable; and machine should be powerpc.
       The offset to the program and section
       header tables should not be 0, i.e. they must exist.
       */
    
    if(elfhdr->e_ident[EI_MAG0] != 0x7f || elfhdr->e_ident[EI_MAG1] != 'E' ||
       elfhdr->e_ident[EI_MAG2] != 'L' || elfhdr->e_ident[EI_MAG3] != 'F' ||
       elfhdr->e_ident[EI_CLASS] != ELFCLASS32 ||
       elfhdr->e_ident[EI_DATA] != ELFDATA2MSB ||
       elfhdr->e_ident[EI_VERSION] != EV_CURRENT || elfhdr->e_type != ET_EXEC ||
       elfhdr->e_version != EV_CURRENT ||
       /* only valid for Cygnus */ elfhdr->e_machine != EM_PPC ||
       elfhdr->e_phoff == 0 || elfhdr->e_shoff == 0)
	{
	    printf( "Error: Don't like the file header.\n");
#ifdef VERBOSE    
	    printf("%x:0x7f\n", (unsigned)elfhdr->e_ident[EI_MAG0]);
	    printf("%c:E\n", elfhdr->e_ident[EI_MAG1]);
	    printf("%c:L\n", elfhdr->e_ident[EI_MAG2]);
	    printf("%c:F\n", elfhdr->e_ident[EI_MAG3]);
	    printf("%u:%u\n", (unsigned)elfhdr->e_ident[EI_CLASS], ELFCLASS32);
	    printf("%u:%u\n", (unsigned)elfhdr->e_ident[EI_DATA], ELFDATA2MSB);
	    printf("%u:%u\n", (unsigned)elfhdr->e_ident[EI_VERSION], EV_CURRENT);
	    printf("%u:%u\n", (unsigned)elfhdr->e_type, ET_EXEC);
	    printf("%u:%u\n", (unsigned)elfhdr->e_version, EV_CURRENT);
	    printf("%u:%u\n", (unsigned)elfhdr->e_machine, EM_PPC);
	    printf("%u:!0\n", (unsigned)elfhdr->e_phoff);
	    printf("%u:!0\n", (unsigned)elfhdr->e_shoff);
#endif
	    return(FAILED);
	}
    
    return(PASSED);
}



bool_t read_elfhdr(FILE *fd_in, Elf32_External_Ehdr *elfhdr)
{
    int32_t size;

    size = sizeof(Elf32_External_Ehdr);

    if (fread((uint8_t *)elfhdr, 1, size, fd_in) != size) 	{
	printf("\nError: Error reading elf header.\n");
	return(FAILED);
    }

    if (check_elfhdr(elfhdr)==FAILED) return(FAILED);
    
    return(PASSED);
}


Elf32_External_Shdr *read_scnhdr_ptr(FILE *fd_in)
{
    Elf32_External_Shdr *scnhdr;
    int32_t size;
    
    size = sizeof(Elf32_External_Shdr);

#ifdef COMPILE_FOR_UNIX /* then native Sun4 compile */
    /* This is what we do when running this code under COMPILE_FOR_UNIX */
    scnhdr = (Elf32_External_Shdr *)malloc(size);
    
    if (scnhdr == NULL) {
	printf("\nError: Malloc failed to allocate for Section header.\n");
	return((Elf32_External_Shdr *)FAILED);
    }
    
    if (fread((uint8_t *)scnhdr, 1, size, fd_in) != size) {
	printf("\nError: Error reading section headers.\n");
	return((Elf32_External_Shdr *)FAILED);
    }
#else
    /* For embedded code, do NOT actually read from the file into a buffer.
     * Instead, just initialize the (char *) to the address of the desired 
     * file offset already loaded in memory (flash space).
     */
    if (fread_setptr((uint8_t **)&scnhdr, 1, size, fd_in) != size) 
	{
	    printf("\nError: Error reading Section Header Pointer.\n");
	    return((Elf32_External_Shdr *)FAILED);
	}
#endif

    return(scnhdr);
}


void print_scnhdr(Elf32_External_Shdr *scnhdr, 
		  int num, 
		  char *strtab, 
		  bool_t ldflag)
{
#ifdef VERBOSE
  
#ifdef IGNORE_SKIPPING
  
  if ((strtab) && (strcmp(".debug", &strtab[scnhdr->sh_name]) != 0))
    if (ldflag == FALSE) return;
#endif

  printf("\n\n *** %s Section Header #%d - Elf32_External_Shdr ***\n", ldflag ? "Loading" : "Skipping", num);   
  printf("\n scnhdr->sh_name      = %08x - Sect name", scnhdr->sh_name);
  
  if (strtab) {
    
    printf(" = %s", &strtab[scnhdr->sh_name]);
    
  } else if (scnhdr->sh_type == SHT_STRTAB) {
    
    printf(" = %s", &shstrtab[0]);
  }
  
  printf("\n scnhdr->sh_type      = %08x - Type of sect",scnhdr->sh_type);
  printf("\n scnhdr->sh_flags     = %08x - Misc sect attrib",scnhdr->sh_flags); 
  printf("\n scnhdr->sh_addr      = %08x - Sect virt addr at exec",scnhdr->sh_addr); 
  printf("\n scnhdr->sh_offset    = %08x - Sect file offset",scnhdr->sh_offset);
  printf("\n scnhdr->sh_size      = %08x - Size of section",scnhdr->sh_size);
  printf("\n scnhdr->sh_link      = %08x - Index of another sect",scnhdr->sh_link);
  printf("\n scnhdr->sh_info      = %08x - Additional sect info",scnhdr->sh_info);
  printf("\n scnhdr->sh_addralign = %08x - Sect alignment",scnhdr->sh_addralign);
  printf("\n scnhdr->sh_entsize   = %08x - Entry size",scnhdr->sh_entsize);

#else
  
  if (strtab) {
    printf("\n%s Section @ 0x%08x, size= 0x%08x\t%s",
           ldflag ? "Loading " : "Skipping", 
           scnhdr->sh_addr, scnhdr->sh_size, &strtab[scnhdr->sh_name]);
  }
  
#endif
}


bool_t read_proghdr(FILE *fd_in, Elf32_External_Phdr *proghdr)
{
    int32_t size;
    
    size = sizeof(Elf32_External_Phdr);
    
    if (fread((uint8_t *)proghdr, 1, size, fd_in) != size) {
	printf("\nError: Error reading program headers.\n");
	return(FAILED);
    }
    return(PASSED);
}

void print_proghdr(Elf32_External_Phdr *proghdr, int num)
{
#ifdef VERBOSE
    /* PROGRAM Header */
    printf("\n\n *** Loading Program Header #%d - Elf32_External_Phdr ***\n", num);   
    printf("\n proghdr->p_type      = %08x - Identifies prog seg", proghdr->p_type);
    printf("\n proghdr->p_offset    = %08x - Segment file offset", proghdr->p_offset);
    printf("\n proghdr->p_vaddr     = %08x - Segment virtual addr",  proghdr->p_vaddr);
    printf("\n proghdr->p_paddr     = %08x - Segment physical addr", proghdr->p_paddr); 
    printf("\n proghdr->p_filesz    = %08x - Segment size in file",  proghdr->p_filesz);
    printf("\n proghdr->p_memsz     = %08x - Segment size in memory",proghdr->p_memsz);
    printf("\n proghdr->p_flags     = %08x - Segment flags",          proghdr->p_flags);
    printf("\n proghdr->p_align     = %08x - Segment alignment",   proghdr->p_align);
#endif
}

/* read in the STRING TABLE here */

uint8_t *read_strtab_ptr(FILE *fd_in, Elf32_External_Shdr *scnhdr)
{
    uint8_t *strtab;
#ifdef COMPILE_FOR_UNIX  /* then native Sun4 compile */
    /* This is what we do when running this code under COMPILE_FOR_UNIX */

    strtab = (char *)malloc(scnhdr->sh_size);
    
    if (strtab == NULL) {
	printf("\nError: Malloc failed to allocate for string table\n");
	return((uint8_t *)FAILED);
    }
    
    if (fread(strtab, 1, scnhdr->sh_size, fd_in) != scnhdr->sh_size) {
        printf("\nError: Error reading string table into buffer.\n");
        return((uint8_t *)FAILED);
    }
#else
    /* For embedded code, do NOT actually read from the file into a buffer.
     * Instead, just initialize the (char *) to the address of the desired 
     * file offset already loaded in memory (flash space).
     */
    if (fread_setptr(&strtab, 1, scnhdr->sh_size, fd_in) 
	!= scnhdr->sh_size) 
	{
	    printf("\nError: Error reading string table pointer.\n");
	    return((uint8_t *)FAILED);
	}
#endif
    return(strtab);
}


bool_t load_elf_section(FILE *fd_in, Elf32_External_Shdr *scnhdr, uint8_t *strtab)
{
    register int32_t i;
    register uint8_t *from_data;
    register uint8_t *to_addr;

    /* seek to the section data */
    if (fseek(fd_in, scnhdr->sh_offset, SEEK_SET)) {
	
	printf("\nError: seeking to file offset 0x%x for section %s",
	       scnhdr->sh_offset,
	       &strtab[scnhdr->sh_name]);
	return(FAILED);
    }
   
    from_data = read_image_ptr(fd_in, scnhdr, strtab);
    to_addr   = (uint8_t *)scnhdr->sh_addr;
    i         = 0;
    
    while(i<scnhdr->sh_size) {
#ifdef COMPILE_FOR_UNIX /* then native Sun4 compile */
#ifdef VERBOSE
	printf("\n0x%08x : %02x%02x%02x%02x", 
	       &to_addr[i], from_data[i], 
	       from_data[i+1], 
	       from_data[i+2], from_data[i+3]);
#endif
	i+=4;
#else
	to_addr[i] = from_data[i];
	i++;
#endif
    }
    return(PASSED);
}

uint8_t *read_image_ptr(FILE *fd_in, Elf32_External_Shdr *scnhdr, uint8_t *strtab)
{
    uint8_t *image_ptr;
    
#ifdef COMPILE_FOR_UNIX /* then native Sun4 compile */

    /* Under COMPILE_FOR_UNIX, we must dynamically allocate a buffer that we can 
     * hold the source data in.
     */
    image_ptr = (uint8_t *)malloc(scnhdr->sh_size);
    
    if (image_ptr == NULL) {
	printf("\nError: Malloc failed to allocate for %s section data.\n", 
	       &strtab[scnhdr->sh_name]);
	return((uint8_t *)FAILED);
    }
    
    /* Then copy from the COMPILE_FOR_UNIX file into the buffer */
    
    if (fread(image_ptr, 1, scnhdr->sh_size, fd_in) != scnhdr->sh_size) 
	{
	    printf("\nError: reading %s section data!\n",
		   &strtab[scnhdr->sh_name]);
	    
	    return((uint8_t *)FAILED);
	}

#else  
    /* PPC Embedded code here:
     * we do something slightly different than COMPILE_FOR_UNIX.
     */
    
    /* Instead of reading the file into a buffer, we can just provide a 
     * pointer to the file in FLASH. 
     *
     * Note: this call works like fread() in that it will update the
     * file position based on the size passed in.
     */
    
    if (fread_setptr(&image_ptr, 1, scnhdr->sh_size, fd_in) != scnhdr->sh_size) 
	{
	    printf("\nError: reading %s section data pointer!\n",
		   &strtab[scnhdr->sh_name]);
	    
	    return((uint8_t *)FAILED);
	}
#endif
    return(image_ptr);
}


bool_t elf_section_ok(Elf32_External_Shdr *scnhdr, 
			Elf32_External_Phdr *proghdr,
			uint8_t *strtab)
{
    
    /* cannot load sections that have a section size of ZERO */
    if (scnhdr->sh_size == 0) 
	return(FALSE);
    
    /* if section header type = string table header, skip continue */
    if (scnhdr->sh_type == SHT_STRTAB)
	return(FALSE);
    
    /* skip sections that are not program specific sections */    
    if (scnhdr->sh_type != SHT_PROGBITS)
	return(FALSE);
    
    /* Is the region for this section within the region for the current 
     * Program Section Spec */
    
#ifdef NEW_TOOLKIT
    if ((scnhdr->sh_addr >= proghdr->p_vaddr) && 
	(scnhdr->sh_addr <= proghdr->p_vaddr + proghdr->p_memsz)) 
#else
    if ((scnhdr->sh_addr >= proghdr->p_paddr) && 
	(scnhdr->sh_addr <= proghdr->p_paddr + proghdr->p_memsz)) 
#endif
      {
        /* ok, the section's start address is in range...*/
        
        /* Now is the size of the section compatible?  */
        
#ifdef NEW_TOOLKIT
        if ((scnhdr->sh_addr + scnhdr->sh_size) <=
            (proghdr->p_vaddr + proghdr->p_memsz))
#else  if ((scnhdr->sh_addr + scnhdr->sh_size) <=
            (proghdr->p_paddr + proghdr->p_memsz))
#endif
          {
            
            if (strcmp(&strtab[scnhdr->sh_name], ".comment") == 0)
              return(FALSE);
            
            /* If we made it here... then it must be a loadable section!*/
            return(TRUE);
          }
      }
    
    return(FALSE);
    
}
/* ************************************************
 *
 * scenerio 1. 
 *
 *      Target section starts within bss space.
 * 
 *           target_beg---------target_end
 *                |                |
 * --------+------+-----------+----+------------
 *         |                  |
 *      bss_beg-------------bss_end
 *
 * ************************************************
 *
 * scenerio 2.
 *
 *       Bss section is within the target section
 *
 *  target_beg---------------target_end
 *    |                        |
 * ---+----+-------------------+--+-------------
 *         |                      |
 *      bss_beg----------------bss_end
 *
 * ************************************************
 */

void check_bss_warning(Elf32_External_Shdr *scnhdr, uint8_t *strtab)
{
#ifndef COMPILE_FOR_UNIX
    uint32_t bss_beg = (uint32_t)&_begin_bss;
    uint32_t bss_end = (uint32_t)&_end_bss;
    uint32_t target_beg = (uint32_t)scnhdr->sh_addr;
    uint32_t target_end = (uint32_t)(scnhdr->sh_addr + scnhdr->sh_size);
    bool_t problem = FALSE;

    if ( (target_beg >= bss_beg) && (target_beg <= bss_end)) problem = TRUE;

    if ( (bss_beg >= target_beg) && (bss_beg <= target_end)) problem = TRUE;

    if (problem == TRUE) {
	printf("\n\nWARNING: Program Section(%s) currently being loaded @ 0x%x-%x, will corrupt the\n
elf loader's .bss memory @ 0x%x-%x\n", &strtab[scnhdr->sh_name], target_beg, target_end, bss_beg, bss_end);
    }
#endif

}


