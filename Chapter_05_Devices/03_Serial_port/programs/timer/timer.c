/*! Timer api testing */

#include <stdio.h>
#include <time.h>
#include <api/prog_info.h>

static timespec_t t0_realtime;
static timespec_t t0_monotonic;

/* static void alarm_nt ( sigval_t param )
{
	int num;
	timespec_t t;

	num = param.sival_int;
	clock_gettime ( CLOCK_REALTIME, &t );
	time_sub ( &t, &t0 );

	printf ( "[%d:%d] Alarm %d (every %d seconds)\n",
		t.tv_sec, t.tv_nsec/100000000, num, num );
} */

static void alarm_nt1 ( sigval_t param )
{
	timespec_t t_realtime;
	timespec_t t_montonic;

	clock_gettime ( CLOCK_REALTIME, &t_realtime );
	clock_gettime ( CLOCK_MONOTONIC, &t_montonic );
	time_sub ( &t_realtime, &t0_realtime );
	time_sub ( &t_montonic, &t0_monotonic );

	printf ( "CLOCK_MONOTONIC: %d:%d\n",
		t_montonic.tv_sec, t_montonic.tv_nsec/100000000);
		
	printf ( "CLOCK_REALTIME: %d:%d\n",
		t_realtime.tv_sec, t_realtime.tv_nsec/100000000);
}

static void alarm_nt2 ( sigval_t param )
{
	timespec_t t_realtime;
	timespec_t t_montonic;

	clock_gettime ( CLOCK_REALTIME, &t_realtime );
	clock_gettime ( CLOCK_MONOTONIC, &t_montonic );
	time_sub ( &t_realtime, &t0_realtime );
	time_sub ( &t_montonic, &t0_monotonic );

	timespec_t *t_realtime1;
	if(t_realtime.tv_sec > t_montonic.tv_sec) {
		t_realtime.tv_sec -= 1;
		t_realtime1 = &t_realtime;
		clock_settime(CLOCK_REALTIME, t_realtime1);
	}else if(t_realtime.tv_sec < t_montonic.tv_sec){
		t_realtime.tv_sec += 1;
		t_realtime1 = &t_realtime;
		clock_settime(CLOCK_REALTIME, t_realtime1);
	}
}

static void alarm_nt3 ( sigval_t param )
{
	timespec_t t_realtime;
	timespec_t t_montonic;

	clock_gettime ( CLOCK_REALTIME, &t_realtime );
	clock_gettime ( CLOCK_MONOTONIC, &t_montonic );
	time_sub ( &t_realtime, &t0_realtime );
	time_sub ( &t_montonic, &t0_monotonic );

	timespec_t *t_realtime1;
	if(t_realtime.tv_sec > t_montonic.tv_sec) {
		t_realtime.tv_sec -= 10;
		t_realtime1 = &t_realtime;
		clock_settime(CLOCK_REALTIME, t_realtime1);
	}else if(t_realtime.tv_sec < t_montonic.tv_sec){
		t_realtime.tv_sec += 10;
		t_realtime1 = &t_realtime;
		clock_settime(CLOCK_REALTIME, t_realtime1);
	}
}

int timer ()
{
	timespec_t t;
	itimerspec_t t1, t2, t3;
	timer_t timer1, timer2, timer3;
	sigevent_t evp1, evp2, evp3;

	printf ( "Example program: [%s:%s]\n%s\n\n", __FILE__, __FUNCTION__,
		 timer_PROG_HELP );

	clock_gettime ( CLOCK_REALTIME, &t );
	t0_realtime = t;
	printf ( "System real time: %d:%d\n", t.tv_sec, t.tv_nsec/100000000 );
	
	clock_gettime ( CLOCK_MONOTONIC, &t );
	t0_monotonic = t;
	printf ( "System monotonic time: %d:%d\n", t.tv_sec, t.tv_nsec/100000000 );

	evp1.sigev_notify = SIGEV_THREAD;
	evp1.sigev_notify_function = alarm_nt1;
	evp1.sigev_notify_attributes = NULL;
	
	evp2.sigev_notify = SIGEV_THREAD;
	evp2.sigev_notify_function = alarm_nt2;
	evp2.sigev_notify_attributes = NULL;

	evp3.sigev_notify = SIGEV_THREAD;
	evp3.sigev_notify_function = alarm_nt3;
	evp3.sigev_notify_attributes = NULL;

	/* timer1 */
	t1.it_interval.tv_sec = 1;
	t1.it_interval.tv_nsec = 0;
	t1.it_value.tv_sec = 1;
	t1.it_value.tv_nsec = 0;
	evp1.sigev_value.sival_int = t1.it_interval.tv_sec;
	timer_create ( CLOCK_REALTIME, &evp1, &timer1 );
	timer_settime ( &timer1, 0, &t1, NULL );

	// timer2 
	t2.it_interval.tv_sec = 2;
	t2.it_interval.tv_nsec = 0;
	t2.it_value.tv_sec = 2;
	t2.it_value.tv_nsec = 0;
	evp2.sigev_value.sival_int = t2.it_interval.tv_sec;
	timer_create ( CLOCK_REALTIME, &evp2, &timer2 );
	timer_settime ( &timer2, 0, &t2, NULL );
	
	// timer3
	t3.it_interval.tv_sec = 5;
	t3.it_interval.tv_nsec = 0;
	t3.it_value.tv_sec = 5;
	t3.it_value.tv_nsec = 0;
	evp3.sigev_value.sival_int = t3.it_interval.tv_sec;
	timer_create ( CLOCK_MONOTONIC, &evp3, &timer3 );
	timer_settime ( &timer3, 0, &t2, NULL );

	while (TIME_IS_SET(&t))
		if (clock_nanosleep(CLOCK_REALTIME, 0, &t, &t))
			printf("Interrupted sleep?\n");

	/* t.tv_sec = 11;
	t.tv_nsec = 0; */

	/* t.tv_sec = 3;
	t.tv_nsec = 0;
	clock_settime ( CLOCK_REALTIME, &t );
	clock_gettime ( CLOCK_REALTIME, &t ); */


	return 0;
}