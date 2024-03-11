
#ifndef _HW_CPUID_H
#define _HW_CPUID_H

#define HZ 100
#define LATCH ( ( 1193180 + HZ / 2 ) / HZ )
#define CALIBRATE_LATCH ( 5 * LATCH )
#define CALIBRATE_TIME ( 5 * 1000020 / HZ )

unsigned long calibrate_tsc();

#endif
