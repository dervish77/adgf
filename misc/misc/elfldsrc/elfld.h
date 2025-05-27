#ifndef ELFLD_H
#define ELFLD_H

#include <types.h>
#include <elf.h>

bool_t elfld(FILE *fd_in, Elf32_External_Ehdr *elfhdr);


#endif /* ELFLD_H */

