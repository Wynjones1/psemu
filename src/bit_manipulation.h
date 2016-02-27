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

template<typename T0, typename T1 = uint32_t>
inline T1 sign_extend(T0 in)
{
	static_assert(std::is_unsigned<T0>::value, "Input must be an unsigned type.");
	static_assert(std::is_unsigned<T1>::value, "Input must be an unsigned type.");
	
	union
	{
		std::make_signed<T0>::type i;
		T0  u;
	}temp_in;
	union
	{
		std::make_signed<T1>::type i;
		T1 u;
	}temp_out;

	temp_in.u  = in;
	temp_out.i = temp_in.i;
	return temp_out.u;
}
#endif