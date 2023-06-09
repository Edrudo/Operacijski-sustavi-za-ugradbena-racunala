/*! Simple program prepared for little debugging */

#include <stdio.h>
#include <api/prog_info.h>
#include <api/errno.h>
#include <kernel/errno.h>

static int inc(int n)
{
	n++;

	return n;
}

static int x=5;

int debug()
{
	int a, b, c;

	printf("Example program: [%s:%s]\n%s\n\n", __FILE__, __FUNCTION__,
		 debug_PROG_HELP);

	a = 1;

	b = a + 1;

	c = inc(a) + inc(b);

	a += b + c;
	b += a + c;
	c += a + b;

	printf("a=%d, b=%d, c=%d\n", a, b, c);

#if 1	/* compile with 'debug=yes' and without */
	//LOG(WARN, "This is log entry with WARN relevance");
	//LOG(INFO, "Address of 'a' is %x", &a);

	void k_startup();
	extern char system_info[];

	printf("\n");
	LOG(INFO, " k_startup (kernel code) is at %x", k_startup);
	LOG(INFO, " startup (kernel data) is at   %x", system_info);
	LOG(INFO, " debug (program code) is at    %x", debug);
	LOG(INFO, " x (program data) is at        %x", &x);
	LOG(INFO, " a (variable on stack) is at   %x", &a);

	ASSERT_ERRNO_AND_RETURN(TRUE, EINVAL);

	ASSERT(TRUE);
	//ASSERT(FALSE);
#endif
	return 0;
}
