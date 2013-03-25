/* frame.c - manage physical frames */
#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <paging.h>
#include <stdio.h>
#ifndef DEBUG
#define DEBUG
#endif
/*-------------------------------------------------------------------------
 * init_frm - initialize frm_tab
 *-------------------------------------------------------------------------
 */
SYSCALL init_frm()
{
	int  i;
	for(i = 0 ;i < NFRAMES; i++){
		frm_tab[i].fr_status = FRM_UNMAPPED;
		frm_tab[i].fr_pid = 0;
		frm_tab[i].fr_vpno = 0;
		frm_tab[i].fr_refcnt = 0;
		frm_tab[i].fr_type = FR_PAGE;
		frm_tab[i].fr_dirty = 0;
		frm_tab[i].cookie = NULL;
		frm_tab[i].fr_loadtime = 0;
		frm_tab[i].base_addr = getBaseAddress(i+FRAME0);
		frm_tab[i].frm_num = i+FRAME0;
	}
  return OK;
}

/*-------------------------------------------------------------------------
 * get_frm - get a free frame according page replacement policy
 *-------------------------------------------------------------------------
 */
SYSCALL get_frm(fr_map_t **frame, int frameType)
{
	// for now just return the first frame.
  int  i;
  for( i = 0; i < NFRAMES; i++){
	  if(frm_tab[i].fr_status == FRM_UNMAPPED){
#ifdef DEBUG
		  kprintf("assigning frame %d for frame type %d and base address = %d\n", frm_tab[i].frm_num, frameType, frm_tab[i].base_addr);
#endif
		  frm_tab[i].fr_status = FRM_MAPPED;
		  frm_tab[i].fr_type = frameType;
		  *frame = &frm_tab[i];
		  break;
	  }
  }
  return OK;
}

/*-------------------------------------------------------------------------
 * free_frm - free a frame 
 *-------------------------------------------------------------------------
 */
SYSCALL free_frm(int i)
{

  kprintf("To be implemented!\n");
  return OK;
}

unsigned long getBaseAddress(int frameNumber){
	return (unsigned long)(frameNumber * NBPG);
}

unsigned long getOffsetAddress(int frameNumber, int offset){
	unsigned long result = getBaseAddress(frameNumber) + (unsigned long)(offset*sizeof(long));
	if(offset  == 128 ){
		kprintf("address for frame %d and offset 128 is %d\n", frameNumber, result);
	}
	return result;

}

SYSCALL writeLong(int frame, int offset, unsigned long value){
	if((frame < 1024 || frame > 4095) || (offset < 0  || offset > 1024))
		return SYSERR;
	unsigned long *data = (unsigned long *)getOffsetAddress(frame, offset);
	// write data
	*data = value;
	return OK;

}

SYSCALL readLong(int frame , int offset, unsigned long **data){
	if((frame < 1024 || frame > 4095) || (offset < 0  || offset > 1024))
			return SYSERR;
#ifdef DEBUG
	kprintf("for frame %d and offset %d data = %d\n", frame, offset, *((unsigned long *)getOffsetAddress(frame, offset)));
#endif
	*data = (unsigned long *)getOffsetAddress(frame, offset);
	return OK;
}

