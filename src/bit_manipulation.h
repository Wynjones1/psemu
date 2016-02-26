#ifndef BIT_MANIPULATION
#define BIT_MANIPULATION

template<unsigned int MSB, unsigned int LSB>
constexpr uint32_t mask()
{
	static_assert(MSB >= LSB, "LSB cannot be greater than MSB");
	static_assert(MSB < 32, "MSB cannot be greater than 31");
	return (((uint64_t(1) << (MSB + 1)) - 1) >> LSB) << LSB;
}

template<unsigned int MSB, unsigned int LSB, typename T = uint32_t>
constexpr T extract(uint32_t value)
{
	return T((value & mask<MSB, LSB>()) >> LSB);
}

inline uint32_t sign_extend(uint16_t in)
{
	union
	{
		uint16_t u;
		int16_t  i;
	}temp16;
	union
	{
		uint32_t u;
		int32_t  i;
	}temp32;

	temp16.u = in;
	temp32.i = temp16.i;
	return temp32.u;
}
#endif