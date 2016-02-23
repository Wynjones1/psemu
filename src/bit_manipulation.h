#ifndef BIT_MANIPULATION
#define BIT_MANIPULATION

constexpr uint32_t mask(uint32_t msb, uint32_t lsb)
{
	return (((1 << msb) - 1) >> lsb) << lsb;
}

template<typename T = uint32_t>
constexpr T extract(uint32_t value, uint32_t msb, uint32_t lsb)
{
	return T((value & mask(msb, lsb)) >> lsb);
}

#endif