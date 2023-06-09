/*! Modules, memory segments */
#pragma once
#include <api/prog_info.h>

/* memory segments/module types */
enum {
	MS_KERNEL = 3,
	MS_KHEAP,
	MS_PROGRAM,
	MS_PROCESS,
	MS_OTHER,
	MS_END
};

/*! memory segment descriptors used in run-time */
typedef struct _mseg_t_
{
	uint	 type;
	void	*start; /* start address - physical address! */
	size_t	 size;
}
mseg_t;

mseg_t *arch_memory_init();


/*! modules in system images */
/* magic numbers for headers */
#define PMAGIC1		0x11235813
#define PMAGIC2		0x16180334

/* Modules loaded with kernel */
typedef struct _module_t_
{
	uint32  magic[4];
		/* magic numbers to identify start of module */

	uint32  type;
		/* MS_PROGRAM, MS_OTHER */

	/* for calculating size */
	void   *start;
	void   *end;

	char    name[16];
		/* (short) module/program name or description */

	/* after this header, comes rest of module! */
}
module_t;

/* created at compile time; set as program beginning */
typedef struct program_loaded_as_module
{
	union {
		module_t   mod;
			   /* module header */
		program_t  prog;
			   /* program header set in compile time */
		process_t  proc;
			   /* set and used in runtime */
	};
}
module_program_t;

/*
 * Memory map of module: (addresses grows downward!)
 * +--------------------------------------------------------------------------+
 * |                               module_t header                            |
 * +--------------------------------------------------------------------------+
 * |                               module content                             |
 * +--------------------------------------------------------------------------+
 *
 * When module contains a program:
 * +--------------------------------------------------------------------------+
 * |                              process_t header                            |
 * |            (includes module_t and program_t header parts)               |
 * +--------------------------------------------------------------------------+
 * |                .text, .*data*, .bss, ... (compiled sections)             |
 * +--------------------------------------------------------------------------+
 */
