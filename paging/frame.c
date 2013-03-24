/* frame.c - manage physical frames */
#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <paging.h>
#include <stdio.h>

/*-------------------------------------------------------------------------
 * init_frm - initialize frm_tab
 *-------------------------------------------------------------------------
 */
SYSCALL init_frm()
{
	int  i;
	for(i = 0 ;i < NFRAMES; i++){
		fr_map_t *frame = &frm_tab[i];
		frame->fr_status = FRM_UNMAPPED;
		frame->fr_pid = 0;
		frame->fr_vpno = 0;
		frame->fr_refcnt = 0;
		frame->fr_type = FR_PAGE;
		frame->fr_dirty = 0;
		frame->cookie = NULL;
		frame->fr_loadtime = 0;
		frame->base_addr = getBaseAddress(i);
		frame->frm_num = i;
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
  for( i = FRAME0; i < FRAME0 + NFRAMES; i++){
	  if(frm_tab[i].fr_status == FRM_UNMAPPED){
#ifdef DEBUG
		  kprintf("assigning frame %d for frame type %d", i, frameType);
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
	return getBaseAddress(frameNumber) + (unsigned long)(offset*sizeof(long)*BYTE);
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
	*data = (unsigned long *)getOffsetAddress(frame, offset);
	return OK;
}

