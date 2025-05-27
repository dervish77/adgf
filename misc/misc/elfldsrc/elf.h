#ifndef ELF_H
#define ELF_H

/* ELF support for BFD.
   Copyright (C) 1991, 1992 Free Software Foundation, Inc.

   Written by Fred Fish @ Cygnus Support, from information published
   in "UNIX System V Release 4, Programmers Guide: ANSI C and
   Programming Support Tools".

This file is part of BFD, the Binary File Descriptor library.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */


/* This file is part of ELF support for BFD, and contains the portions
   that describe how ELF is represented externally by the BFD library.
   I.E. it describes the in-file representation of ELF.  It requires
   the elf-common.h file which contains the portions that are common to
   both the internal and external representations. */
   
/* The 64-bit stuff is kind of random.  Perhaps someone will publish a
   spec someday.  */

/* ELF Header (32-bit implementations) */

typedef struct {
  unsigned char	 e_ident[16];		/* ELF "magic number" */
  unsigned short e_type;		/* Identifies object file type */
  unsigned short e_machine;		/* Specifies required architecture */
  unsigned long	 e_version;		/* Identifies object file version */
  unsigned long	 e_entry;		/* Entry point virtual address */
  unsigned long	 e_phoff;		/* Program header table file offset */
  unsigned long	 e_shoff;		/* Section header table file offset */
  unsigned long	 e_flags;		/* Processor-specific flags */
  unsigned short e_ehsize;		/* ELF header size in bytes */
  unsigned short e_phentsize;		/* Program header table entry size */
  unsigned short e_phnum;		/* Program header table entry count */
  unsigned short e_shentsize;		/* Section header table entry size */
  unsigned short e_shnum;		/* Section header table entry count */
  unsigned short e_shstrndx;		/* Section header string table index */
} Elf32_External_Ehdr;

/* Program header */

typedef struct {
  unsigned long	p_type;		        /* Identifies program segment type */
  unsigned long	p_offset;		/* Segment file offset */
  unsigned long	p_vaddr;		/* Segment virtual address */
  unsigned long	p_paddr;		/* Segment physical address */
  unsigned long	p_filesz;		/* Segment size in file */
  unsigned long	p_memsz;		/* Segment size in memory */
  unsigned long	p_flags;		/* Segment flags */
  unsigned long	p_align;		/* Segment alignment, file & memory */
} Elf32_External_Phdr;

/* Section header */

typedef struct {
  unsigned long	sh_name;		/* Section name, index in string tbl */
  unsigned long	sh_type;		/* Type of section */
  unsigned long	sh_flags;		/* Miscellaneous section attributes */
  unsigned long	sh_addr;		/* Section virtual addr at execution */
  unsigned long	sh_offset;		/* Section file offset */
  unsigned long	sh_size;		/* Size of section in bytes */
  unsigned long	sh_link;		/* Index of another section */
  unsigned long	sh_info;		/* Additional section information */
  unsigned long sh_addralign;           /* Section alignment */
  unsigned long	sh_entsize;		/* Entry size if section holds table */
} Elf32_External_Shdr;


/* Symbol table entry */
typedef struct {
  unsigned char	st_name[4];		/* Symbol name, index in string tbl */
  unsigned char	st_value[4];		/* Value of the symbol */
  unsigned char	st_size[4];		/* Associated symbol size */
  unsigned char	st_info[1];		/* Type and binding attributes */
  unsigned char	st_other[1];		/* No defined meaning, 0 */
  unsigned char	st_shndx[2];		/* Associated section index */
} Elf32_External_Sym;


/* Note segments */

typedef struct {
  unsigned char	namesz[4];		/* Size of entry's owner string */
  unsigned char	descsz[4];		/* Size of the note descriptor */
  unsigned char	type[4];		/* Interpretation of the descriptor */
  char		name[1];		/* Start of the name+desc data */
} Elf_External_Note;

/* Relocation Entries */
typedef struct {
  unsigned char r_offset[4];	/* Location at which to apply the action */
  unsigned char	r_info[4];	/* index and type of relocation */
} Elf32_External_Rel;

typedef struct {
  unsigned char r_offset[4];	/* Location at which to apply the action */
  unsigned char	r_info[4];	/* index and type of relocation */
  unsigned char	r_addend[4];	/* Constant addend used to compute value */
} Elf32_External_Rela;

/* dynamic section structure */

typedef struct {
  unsigned char	d_tag[4];		/* entry tag value */
  union {
    unsigned char	d_val[4];
    unsigned char	d_ptr[4];
  } d_un;
} Elf32_External_Dyn;


#endif /* ELF_H */
