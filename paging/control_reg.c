/* control_reg.c - read_cr0 read_cr2 read_cr3 read_cr4
		   write_cr0 write_cr3 write_cr4 enable_pagine */

#include <conf.h>
#include <kernel.h>
#include <paging.h>

#define CR0_PG 0x80000001

unsigned long tmp;
unsigned long temp1;
unsigned long *esp;
void write_cr3(unsigned long n) ;
unsigned long read_cr0(void);
unsigned long read_cr3(void) ;
void write_cr0(unsigned long n);

/*-------------------------------------------------------------------------
 * read_cr0 - read CR0
 *-------------------------------------------------------------------------
 */
unsigned long read_cr0(void) {

  STATWORD ps;
  unsigned long local_tmp;

  disable(ps);

  asm("pushl %eax");
  asm("movl %cr0, %eax");
  asm("movl %eax, tmp");
  asm("popl %eax");

  local_tmp = tmp;

  restore(ps);

  return local_tmp;
}

/*-------------------------------------------------------------------------
 * read_cr2 - read CR2
 *-------------------------------------------------------------------------
 */

unsigned long read_cr2(void) {

  STATWORD ps;
  unsigned long local_tmp;

  disable(ps);

  asm("pushl %eax");
  asm("movl %cr2, %eax");
  asm("movl %eax, tmp");
  asm("popl %eax");

  local_tmp = tmp;

  restore(ps);

  return local_tmp;
}


/*-------------------------------------------------------------------------
 * read_cr3 - read CR3
 *-------------------------------------------------------------------------
 */

unsigned long read_cr3(void) {

  STATWORD ps;
  unsigned long local_tmp;

  disable(ps);

  asm("pushl %eax");
  asm("movl %cr3, %eax");
  asm("movl %eax, tmp");
  asm("popl %eax");

  local_tmp = tmp;

  restore(ps);

  return local_tmp;
}


/*-------------------------------------------------------------------------
 * read_cr4 - read CR4
 *-------------------------------------------------------------------------
 */

unsigned long read_cr4(void) {

  STATWORD ps;
  unsigned long local_tmp;

  disable(ps);

  asm("pushl %eax");
  asm("movl %cr4, %eax");
  asm("movl %eax, tmp");
  asm("popl %eax");

  local_tmp = tmp;

  restore(ps);

  return local_tmp;
}


/*-------------------------------------------------------------------------
 * write_cr0 - write CR0
 *-------------------------------------------------------------------------
 */

void write_cr0(unsigned long n) {

  kprintf("entering function with val %08x\n", n);
  STATWORD ps;

  disable(ps);

  tmp = n;
  asm("pushl %eax");
  asm("movl $0x80000011, %eax");		/* mov (move) value at tmp into %eax register.
					   "l" signifies long (see docs on gas assembler)	*/
  asm("movl %eax, %cr0");
  asm("popl %eax");

  restore(ps);
  asm("movl %cr0, %eax");
  asm("movl %eax, temp1");
  kprintf("value inserted is %d\n", temp1);

}


/*-------------------------------------------------------------------------
 * write_cr3 - write CR3
 *-------------------------------------------------------------------------
 */

void write_cr3(unsigned long n) {


  STATWORD ps;

  disable(ps);

  tmp = n;
  asm("pushl %eax");
  asm("movl tmp, %eax");                /* mov (move) value at tmp into %eax register.
                                           "l" signifies long (see docs on gas assembler)       */
  asm("movl %eax, %cr3");
  asm("popl %eax");

  restore(ps);

}


/*-------------------------------------------------------------------------
 * write_cr4 - write CR4
 *-------------------------------------------------------------------------
 */

void write_cr4(unsigned long n) {


  STATWORD ps;

  disable(ps);

  tmp = n;
  asm("pushl %eax");
  asm("movl tmp, %eax");                /* mov (move) value at tmp into %eax register.
                                           "l" signifies long (see docs on gas assembler)       */
  asm("movl %eax, %cr4");
  asm("popl %eax");

  restore(ps);

}


/*-------------------------------------------------------------------------
 * enable_pagine - enable paging 
 *-------------------------------------------------------------------------
 */
/*void enable_paging(){
  
  unsigned long temp =  read_cr0();
  temp = temp | ( 0x1 << 31 ) | 0x1;
  write_cr0(temp); 
}*/
void enable_paging (unsigned long pd)
{
        unsigned long          cr0;
        kprintf("addr is %d\n", pd);
        kprintf (("load cr3\n"));
//        write_cr3 (pd);

        kprintf(("enable paging\n"));
        /*cr0  = read_cr0 ();
        cr0 |= CR0_PG;
        write_cr0 (cr0);*/
        cr0 =  read_cr0();
        kprintf("read cr0 = %d\n", cr0);
        cr0 = cr0 | ( 0x1 << 31 ) | 0x1;


          write_cr0(cr0);
        kprintf("=========== comes here \n");

//        cr0 = read_cr0 ();
//        kprintf (("cr0: %x, cr3 %x\n", read_cr0(), read_cr3()));
}


