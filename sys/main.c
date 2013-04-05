/* user.c - main */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <paging.h>

void halt();

/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */
int main() {
//	for (i = 0; i < 16; i++) {
//		*addr = 'A' + i;
//		addr += NBPG;	//increment by one page each time
//	}
/////////////////////////////////////////////////////////////////
//	addr = (char*) 0x40000000; //1G
//	for (i = 0; i < 16; i++) {
//		kprintf("0x%08x: %c\n", addr, *addr);
//		addr += 4096;       //increment by one page each time
//	}
//
//	xmunmap(0x40000000 >> 12);

	return 0;
}
