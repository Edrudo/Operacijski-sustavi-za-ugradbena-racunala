/*! Startup function - initialize kernel subsystem */
#define _K_STARTUP_C_

#include "time.h"
#include "device.h"
#include "memory.h"
#include "fs.h"
#include <kernel/errno.h>
#include <kernel/features.h>
#include <arch/interrupt.h>
#include <arch/processor.h>
#include <api/stdio.h>
#include <api/prog_info.h>
#include <lib/string.h>

char system_info[] = 	OS_NAME ": " NAME_MAJOR ":" NAME_MINOR ", "
			"Version: " VERSION " (" ARCH ")";

/* state of kernel features */
uint kernel_features = FEATURE_SUPPORTED; /* initially set all to "on" state */

/*!
 * First kernel function (after boot loader loads it to memory)
 */
void k_startup()
{
	extern void *k_stdout; /* console for kernel messages */

	/* set initial stdout */
	kdevice_set_initial_stdout();

	/* initialize memory subsystem (needed for boot) */
	k_memory_init();

	/*! start with regular initialization */

	/* interrupts */
	arch_init_interrupts();

	/* detect memory faults (qemu do not detect segment violations!) */
	arch_register_interrupt_handler(INT_MEM_FAULT, k_memory_fault, NULL);
	arch_register_interrupt_handler(INT_UNDEF_FAULT, k_memory_fault, NULL);

	/* timer subsystem */
	k_time_init();

	/* devices */
	k_devices_init();

	/* switch to default 'stdout' for kernel */
	k_stdout = k_device_open(K_STDOUT, O_WRONLY);

	kprintf("%s\n", system_info);

	/* enable interrupts */
	enable_interrupts();

	stdio_init(); /* initialize standard input & output devices */

	k_fs_init("DISK", 512, 4096);

	int fd = open("file:test", O_CREAT | O_WRONLY, 0);
	kprintf("fd=%d\n", fd);
	int fd1 = open("file:test1", O_CREAT | O_WRONLY, 0);
	kprintf("fd1=%d\n", fd1);

	int retval = write(fd, "neki tekst", 11);
	kprintf("retval=%d\n", retval);
	retval = close(fd);
	kprintf("retval=%d\n", retval);
	
	int retval1 = write(fd1, "neki tekst1", 11);
	kprintf("retval1=%d\n", retval1);
	retval = close(fd1);
	kprintf("retval1=%d\n", retval1);

	fd = open("file:test", O_RDONLY, 0);
	kprintf("fd=%d\n", fd);
	char buff[11];
	retval = read(fd, buff, 11);
	kprintf("retval=%d\n", retval);
	kprintf("buff=%s\n", buff);

	fd1 = open("file:test1", O_RDONLY, 0);
	kprintf("fd1=%d\n", fd1);
	char buff1[11];
	retval1 = read(fd1, buff1, 11);
	kprintf("retval1=%d\n", retval1);
	kprintf("buff1=%s\n", buff1);


	/* start desired program(s) */
	//hello_world();
	//keyboard();
	//timer();
	/* segm_fault(); */

	kprintf("\nSystem halted!\n");
	halt();
}

/*! Turn kernel feature on/off */
uint sys__feature(uint features, int cmd, int enable)
{
	uint prev_state = kernel_features & features;

	ASSERT(!(features & ~FEATURE_SUPPORTED));

	if (cmd == FEATURE_GET)
		return prev_state;

	/* update state */
	if (enable)
		kernel_features |= features;
	else
		kernel_features &= ~features;

	/* action required? */

	if ((features & FEATURE_INTERRUPTS))
	{
		if (enable)
			enable_interrupts();
		else
			disable_interrupts();
	}

	return prev_state;
}
