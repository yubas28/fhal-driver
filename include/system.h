#ifndef SYSTEM_H_
#define SYSTEM_H_
#define WEAK __attribute__ ((weak))
#define ALIAS(x) __attribute__ ((alias(#x)))
#define INTERRUPT(x) __attribute__ ((interrut(x)))
#define SECTION(x) __attribute__ ((section(x)))
#define NAKED __attribute__ ((naked))
#define USED __attribute__ ((used))
#define NSEC_PER_SEC 1000000000ULL
#define BIT(x) (1 << x)
#endif
