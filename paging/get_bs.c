#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <paging.h>

int get_bs(bsd_t bs_id, unsigned int npages) {

  /* requests a new mapping of npages with ID map_id */
	int avail = 0;
	if((bs_id < 0 || bs_id > NUM_BACKING_STORE -1) || (npages < 1 || npages > 200))
		return SYSERR;
	bs_t *bs_t   = alloc_bs(bs_id, npages);
    return bs_t->npages;
}


