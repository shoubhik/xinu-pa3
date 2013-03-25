/* paging.h */
#ifndef _PAGING_H_
#define _PAGING_H_

typedef unsigned int	 bsd_t;



/* Structure for a page table entry */

typedef struct {

  unsigned int pt_pres	: 1;		/* page is present?		*/
  unsigned int pt_write : 1;		/* page is writable?		*/
  unsigned int pt_user	: 1;		/* is use level protection?	*/
  unsigned int pt_pwt	: 1;		/* write through for this page? */
  unsigned int pt_pcd	: 1;		/* cache disable for this page? */
  unsigned int pt_acc	: 1;		/* page was accessed?		*/
  unsigned int pt_dirty : 1;		/* page was written?		*/
  unsigned int pt_mbz	: 1;		/* must be zero			*/
  unsigned int pt_global: 1;		/* should be zero in 586	*/
  unsigned int pt_avail : 3;		/* for programmer's use		*/
  unsigned int pt_base	: 20;		/* location of page?		*/
  unsigned long *page_adder;

} pt_t;


typedef struct{
  unsigned int pg_offset : 12;		/* page offset			*/
  unsigned int pt_offset : 10;		/* page table offset		*/
  unsigned int pd_offset : 10;		/* page directory offset	*/
} virt_addr_t;

typedef struct{
  int bs_status;			/* MAPPED or UNMAPPED		*/
  int bs_pid;				/* process id using this slot   */
  int bs_vpno;				/* starting virtual page number */
  int bs_npages;			/* number of pages in the store */
  int bs_sem;				/* semaphore mechanism ?	*/
} bs_map_t;

typedef struct{
  int fr_status;			/* MAPPED or UNMAPPED		*/
  int fr_pid;				/* process id using this frame  */
  int fr_vpno;				/* corresponding virtual page no*/
  int fr_refcnt;			/* reference count		*/
  int fr_type;				/* FR_DIR, FR_TBL, FR_PAGE	*/
  int fr_dirty;
  void *cookie;				/* private data structure	*/
  unsigned long int fr_loadtime;	/* when the page is loaded 	*/
  unsigned long base_addr;
  unsigned int frm_num;
}fr_map_t;

#define NUM_PAGE_TBL_ENTRIES 1024

typedef struct{
	fr_map_t *base_frm;
	pt_t entry[NUM_PAGE_TBL_ENTRIES];
} page_table;

/* Structure for a page directory entry */

typedef struct {
  unsigned int pd_pres	: 1;		/* page table present?		*/
  unsigned int pd_write : 1;		/* page is writable?		*/
  unsigned int pd_user	: 1;		/* is use level protection?	*/
  unsigned int pd_pwt	: 1;		/* write through cachine for pt?*/
  unsigned int pd_pcd	: 1;		/* cache disable for this pt?	*/
  unsigned int pd_acc	: 1;		/* page table was accessed?	*/
  unsigned int pd_mbz	: 1;		/* must be zero			*/
  unsigned int pd_fmb	: 1;		/* four MB pages?		*/
  unsigned int pd_global: 1;		/* global (ignored)		*/
  unsigned int pd_avail : 3;		/* for programmer's use		*/
  unsigned int pd_base	: 20;		/* location of page table?	*/
  page_table *pg_tbl;
} pd_t;

#define NUM_PAGE_DIR_ENTRY 1024

typedef struct {
	fr_map_t *base_frm;
	pd_t pd_entry[NUM_PAGE_DIR_ENTRY];
}page_dir;

#define NFRAMES 	1024	/* number of frames		*/

extern bs_map_t bsm_tab[];
extern fr_map_t frm_tab[];
extern page_table glb_pages[];
extern page_dir proc_zero_page_dir;
/* Prototypes for required API calls */
SYSCALL xmmap(int, bsd_t, int);
SYSCALL xunmap(int);

/* given calls for dealing with backing store */

int get_bs(bsd_t, unsigned int);
SYSCALL release_bs(bsd_t);
SYSCALL read_bs(char *, bsd_t, int);
SYSCALL write_bs(char *, bsd_t, int);

#define NBPG		4096	/* number of bytes per page	*/
#define FRAME0		1024	/* zero-th frame		*/



#define BSM_UNMAPPED	0
#define BSM_MAPPED	1

#define FRM_UNMAPPED	0
#define FRM_MAPPED	1

#define FR_PAGE		0
#define FR_TBL		1
#define FR_DIR		2

#define FIFO		3
#define AGING		4

#define MAX_ID          7              /* You get 8 mappings, 0 - 8 */

#define BACKING_STORE_BASE	0x00800000
#define BACKING_STORE_UNIT_SIZE 0x00100000

#define NUM_GLB_PAGES 4
#define NUM_BACKING_STORE 8
#define NUM_BS_PAGES 256



// custom functions
#define BYTE 8
unsigned long getBaseAddress(int frameNumber);
SYSCALL writeLong(int frame, int offset, unsigned long value);
SYSCALL readLong(int frame , int offset, unsigned long **data);
unsigned long getOffsetAddress(int frameNumber, int offset);
void init_glb_pages();
void printPageTable(int frm_num);
void initialize_pg_dir(page_dir *pg_dir);

#endif
