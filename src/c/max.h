#if ! defined (__MAX_H__)
#define __MAX_H__

#define forever for( ; ; )
#define infinite_loop while(1)
#define SQSUM(x) (((x) * (x)) + ((x + 1) * (x + 1)))
#define SUMSQ(x) (((x) + (x + 1)) * ((x) + (x + 1))) 
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define swap(type, x, y) { type tmp = x; x = y; y = tmp; }
/* #define double(x) ((x) * 2) */
#define debug_variable(msg, x, printf_type) printf(msg #x " = " printf_type, x)
#define cat(type, x, y) type x##y 

#ifdef double
#error "Please do not use C keywords as macro name even if it is possible"
#endif

int max(int x, int y);

#endif