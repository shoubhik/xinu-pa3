/* bsm.c - manage the backing store mapping*/

#include <conf.h>
#include <kernel.h>
#include <paging.h>
#include <proc.h>

#ifndef DEBUG
#define DEBUG
#endif

/*-------------------------------------------------------------------------
 * init_bsm- initialize bsm_tab
 *-------------------------------------------------------------------------
 */
SYSCALL init_bsm()
{
	int i;
	for(i=0;i<NUM_BACKING_STORE;i++){
#ifdef DEBUG
		kprintf("initializing bs with id: %d\n", i);
#endif
		bsm_tab[i].as_heap = 0;
		bsm_tab[i].status = BSM_UNMAPPED;
		bsm_tab[i].npages = 0;
		bsm_tab[i].frm = NULL;
		bsm_tab[i].owners = NULL;
	}
	return OK;
}

/*-------------------------------------------------------------------------
 * get_bsm - get a free entry from bsm_tab 
 *-------------------------------------------------------------------------
 */
SYSCALL get_bsm(int* avail)
{
	int  i;
	for(i=0;i<NUM_BACKING_STORE;i++){
		if(bsm_tab[i].status == BSM_UNMAPPED){
#ifdef DEBUG
	kprintf("granted backing store: %d\n", i);
#endif
			*avail = i;
			return OK;
		}
	}
	return SYSERR;
}

bs_t* alloc_bs(bsd_t id, int npages){
#ifdef DEBUG
	kprintf("allocating bs %d to proc %d with pages = %d\n", id, currpid, npages);
#endif
	bs_t *bs_t = &bsm_tab[id];
	if(bs_t->npages == 0) bs_t->npages = npages;
	bs_t->status = BSM_MAPPED;
	struct pentry *ptr = &proctab[currpid];
	bs_map_t *map = &(ptr->map[id]);
	map->next = NULL;

	if(bs_t->owners == NULL){
		bs_t->owners = map;
	}
	else{
		bs_map_t *temp = bs_t->owners;
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = map;
	}
	return bs_t;
}

int bs_add_mapping(bsd_t id, int pid, int vpno, int npages){
	bs_t *bs_t = &bsm_tab[id];
	bs_map_t *temp = bs_t->owners;
	while(temp != NULL){
		kprintf("inside while loop\n");
		if(temp->bs_pid == pid ){
#ifdef DEBUG
			kprintf("adding mapping for proc %d for bs %d , starting vpno %d and pages %d\n ",
					pid, id, vpno, npages);
#endif
			temp->bs_vpno = vpno;
			temp->bs_npages = npages;
			return OK;
		}
		temp = temp->next;
	}
	return SYSERR;
}


/*-------------------------------------------------------------------------
 * free_bsm - free an entry from bsm_tab 
 *-------------------------------------------------------------------------
 */
SYSCALL free_bsm(int i)
{
}

/*-------------------------------------------------------------------------
 * bsm_lookup - lookup bsm_tab and find the corresponding entry
 *-------------------------------------------------------------------------
 */
SYSCALL bsm_lookup(int pid, long vaddr, int* store, int* pageth)
{
}


/*-------------------------------------------------------------------------
 * bsm_map - add an mapping into bsm_tab 
 *-------------------------------------------------------------------------
 */
SYSCALL bsm_map(int pid, int vpno, int source, int npages)
{

}



/*-------------------------------------------------------------------------
 * bsm_unmap - delete an mapping from bsm_tab
 *-------------------------------------------------------------------------
 */
SYSCALL bsm_unmap(int pid, int vpno, int flag)
{
}


