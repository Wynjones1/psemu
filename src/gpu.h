#ifndef GPU_H
#define GPU_H
#include <array>
#include <stdint.h>

constexpr uint32_t FB_WIDTH  = 1024;
constexpr uint32_t FB_HEIGHT = 512;

enum class PacketType
{
	GPU_COMMAND = 0,
	POLYGON_PRIMITIVE,
	LINE_PRIMITIVE,
	SPRITE_PRIMITIVE,
	TRANSFER_COMMAND,
	ENVIRONMENT_COMMAND = 7,
};

class GPU
{
public:
	/*
		(0, 0)      = top left.
		(1023, 511) = bottom right.
	*/
	std::array<std::array<uint16_t, FB_WIDTH>, FB_HEIGHT> framebuffer;
};

#endif
