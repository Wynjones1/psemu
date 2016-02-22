#include "cpu.h"
#include "memory.h"

int main(int argc, char **argv)
{
	Memory memory;
	CPU    cpu(memory);

	cpu.Start();
    return 0;
}
