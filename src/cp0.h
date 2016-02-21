#ifndef CP0_H
#define CP0_H
#include <stdint.h>

enum class ExeCode
{
	INT = 0,
	MOD,
	TLBL,
	TLBS,
	ADEL,
	ADES,
	IBE,
	DBE,
	SYS,
	BP,
	RI,
	CPU,
	OVF,
};

class CP0
{
public:
};

#endif