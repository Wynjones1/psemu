#ifndef BIT_MANIPULATION
#define BIT_MANIPULATION
#include <type_traits>

inline constexpr uint64_t mask(unsigned int MSB, unsigned int LSB)
{
	return (((uint64_t(-1) >> (63 - MSB))) >> LSB) << LSB;
}

template<typename T = uint32_t>
inline constexpr T extract(T value, unsigned int MSB, unsigned int LSB)
{
	return T((value & mask(MSB, LSB)) >> LSB);
}

inline void encode(uint32_t &out, uint32_t in, unsigned int msb, unsigned int lsb)
{
	auto value_mask = mask(msb, lsb);
	// Mask out the bits we are setting.
	out &= ~value_mask;
	// Insert the bits.
	out |= (in << lsb) & value_mask;
}

template<typename T = uint32_t>
inline constexpr T sign_bit(T in)
{
    return extract(in, 8 * sizeof(T) - 1, 8 * sizeof(T) - 1);
}

template<typename T0, typename T1 = uint32_t>
inline T1 sign_extend(T0 in)
{
	static_assert(std::is_unsigned<T0>::value, "Input must be an unsigned type.");
	static_assert(std::is_unsigned<T1>::value, "Input must be an unsigned type.");
	
	union
	{
		typename std::make_signed<T0>::type i;
		T0  u;
	}temp_in;
	union
	{
		typename std::make_signed<T1>::type i;
		T1 u;
	}temp_out;

	temp_in.u  = in;
	temp_out.i = temp_in.i;
	return temp_out.u;
}

template<typename T= int32_t>
inline auto to_unsigned(const T in) -> typename std::make_unsigned<T>::type
{
	union
	{
		T signed_;
		typename std::make_unsigned<T>::type unsigned_;
	}temp;
	temp.signed_ = in;
	return temp.unsigned_;
}

template<typename T = uint32_t>
inline auto to_signed(const T in) -> typename std::make_signed<T>::type
{
	union
	{
		T unsigned_;
		typename std::make_signed<T>::type signed_;
	}temp;
	temp.unsigned_ = in;
	return temp.signed_;
}

#endif
