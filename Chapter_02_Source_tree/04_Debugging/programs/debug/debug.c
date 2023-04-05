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

int x = 5;
int y[100];

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
	LOG ( WARN, "This is log entry with WARN relevance" );
	//LOG ( WARN, "This is log entry with WARN relevance" );

 	LOG ( INFO, "Address of 'a' is %x", &a );
	LOG ( INFO, "Address of 'x' is %x", &x );
	LOG ( INFO, "Address of 'y' is %x", y );
	LOG ( INFO, "Address of 'debug' is %x", debug );
	LOG ( INFO, "Address of 'inc' is %x", inc );

	ASSERT_ERRNO_AND_RETURN(TRUE, EINVAL);

	ASSERT(TRUE);
	//ASSERT(FALSE);
#endif
	return 0;
}
