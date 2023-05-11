/*! Timer api testing */
#include <stdio.h>
#include <time.h>
#include <api/prog_info.h>

static timespec_t t0;

static void print_clocks() {
    timespec_t monotonic_time, real_time;

	clock_gettime(CLOCK_MONOTONIC, &monotonic_time);
	time_sub(&monotonic_time, &t0);

	clock_gettime(CLOCK_REALTIME, &real_time);
	time_sub(&real_time, &t0);

    printf("CLOCK_MONOTONIC: %d:%d\n", monotonic_time.tv_sec, monotonic_time.tv_nsec / 100000000);
    printf("CLOCK_REALTIME:  %d:%d\n", real_time.tv_sec, real_time.tv_nsec / 100000000);
	printf("-----------------------\n");
}

void alarm_handler1() {
    print_clocks();
}

void alarm_handler2() {
    timespec_t monotonic_time, real_time;

	clock_gettime(CLOCK_MONOTONIC, &monotonic_time);
	time_sub(&monotonic_time, &t0);

	clock_gettime(CLOCK_REALTIME, &real_time);
	time_sub(&real_time, &t0);

    if (monotonic_time.tv_sec > real_time.tv_sec) {
		printf("+1s\n");
        real_time.tv_sec += 1;
    }
    else if (monotonic_time.tv_sec < real_time.tv_sec) {
		printf("-1s\n");
        real_time.tv_sec -= 1;
    }

    clock_settime(CLOCK_REALTIME, &real_time);
}

void alarm_handler3() {
	timespec_t monotonic_time, real_time;

	clock_gettime(CLOCK_MONOTONIC, &monotonic_time);
	time_sub(&monotonic_time, &t0);

	clock_gettime(CLOCK_REALTIME, &real_time);
	time_sub(&real_time, &t0);

    if (monotonic_time.tv_sec > real_time.tv_sec) {
		printf("+10s\n");
        real_time.tv_sec += 10;
    }
    else if (monotonic_time.tv_sec < real_time.tv_sec) {
		printf("-10s\n");
        real_time.tv_sec -= 10;
    }

    clock_settime(CLOCK_REALTIME, &real_time);
}

int timer() {
	timespec_t t;
	itimerspec_t t1, t2, t3;
	timer_t timer1, timer2, timer3;
	sigevent_t evp1, evp2, evp3;

	clock_gettime(CLOCK_REALTIME, &t);
	t0 = t;

	evp1.sigev_notify = SIGEV_THREAD;
	evp1.sigev_notify_function = alarm_handler1;
	evp1.sigev_notify_attributes = NULL;

	t1.it_interval.tv_sec = 1;
	t1.it_interval.tv_nsec = 0;
	t1.it_value.tv_sec = 1;
	t1.it_value.tv_nsec = 0;
	evp1.sigev_value.sival_int = t1.it_interval.tv_sec;
	timer_create(CLOCK_MONOTONIC, &evp1, &timer1);
	timer_settime(&timer1, 0, &t1, NULL);

	evp2.sigev_notify = SIGEV_THREAD;
	evp2.sigev_notify_function = alarm_handler2;
	evp2.sigev_notify_attributes = NULL;

	t2.it_interval.tv_sec = 2;
	t2.it_interval.tv_nsec = 0;
	t2.it_value.tv_sec = 2;
	t2.it_value.tv_nsec = 0;
	evp2.sigev_value.sival_int = t2.it_interval.tv_sec;
	timer_create(CLOCK_REALTIME, &evp2, &timer2);
	timer_settime(&timer2, 0, &t2, NULL);

	evp3.sigev_notify = SIGEV_THREAD;
	evp3.sigev_notify_function = alarm_handler3;
	evp3.sigev_notify_attributes = NULL;

	t3.it_interval.tv_sec = 5;
	t3.it_interval.tv_nsec = 0;
	t3.it_value.tv_sec = 5;
	t3.it_value.tv_nsec = 0;
	evp3.sigev_value.sival_int = t3.it_interval.tv_sec;
	timer_create(CLOCK_MONOTONIC, &evp3, &timer3);
	timer_settime(&timer3, 0, &t3, NULL);

	while(t.tv_sec < 5) {clock_gettime(CLOCK_MONOTONIC, &t);}
	t.tv_sec -= 2;
	
	clock_settime(CLOCK_REALTIME, &t);

	while(1) {}

	return 0;
}
