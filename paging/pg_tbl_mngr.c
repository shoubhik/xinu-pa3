#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <paging.h>
#include <stdio.h>
#ifndef DEBUG
#define DEBUG
#endif


void init_glb_pages(){
  unsigned long   i, j, entry;
  for(i = 0 ;i < NUM_GLB_PAGES; i++){
	  get_frm(&(glb_pages[i].base_frm), FR_TBL);

	  glb_pages[i].base_frm->fr_pid = currpid;

#ifdef DEBUG
		  kprintf("assigned frame for table %d is %d\n", i, glb_pages[i].base_frm->frm_num);
#endif

	  for(j = 0; j < NUM_PAGE_TBL_ENTRIES;j++ ){
		  entry = 0;
		  entry = (((i*NUM_PAGE_TBL_ENTRIES) + j) << 12) | 3;
		  writeLong(glb_pages[i].base_frm->frm_num, j, entry);
	  }
  }
}

void initialize_pg_dir(page_dir *pg_dir){
	int  i;
	unsigned long entry = 0;
	get_frm(&(pg_dir->base_frm), FR_DIR);
	// add global pages
#ifdef DEBUG
	kprintf("assigning global pages\n");
#endif
	for( i=0; i< NUM_GLB_PAGES; i++){
		pg_dir->pd_entry[i].pd_pres = 1;
		pg_dir->pd_entry[i].pg_tbl = &glb_pages[i];
		entry = 0;
		entry = (glb_pages[i].base_frm->frm_num << 12) | 3;
		writeLong(pg_dir->base_frm->frm_num, i, entry);
	}
	printPage(pg_dir->base_frm->frm_num, NUM_GLB_PAGES);
	for(i = NUM_GLB_PAGES; i < NUM_PAGE_DIR_ENTRY; i++){
		pg_dir->pd_entry[i].pd_pres = 0;
	}
}

void printPageTable(int frm_num){
#ifdef DEBUG
	int i;
	unsigned long *data;
	kprintf("reading data for frame %d\n", frm_num);
	for(i = 0; i< NUM_PAGE_TBL_ENTRIES; i++){
		if(readLong(frm_num, i, &data) == SYSERR){
			kprintf("error reading form frame\n");
		}
	}
#endif

}

void printPage(int frm_num, int numOffest){
#ifdef DEBUG
	int i;
	unsigned long *data;
	kprintf("reading data for frame %d\n", frm_num);
	for(i = 0; i< numOffest; i++){
		if(readLong(frm_num, i, &data) == SYSERR){
			kprintf("error reading form frame\n");
		}
	}
#endif

}
