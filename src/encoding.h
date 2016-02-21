#ifndef ENCODING_H
#define ENCODING_H

constexpr uint32_t mask(uint32_t msb, uint32_t lsb)
{
    return (((1 << msb) - 1) >> lsb) << lsb;
}

constexpr uint32_t extract(uint32_t value, uint32_t msb, uint32_t lsb)
{
    return (value & mask(msb, lsb)) >> lsb;
}

class ImmediateInstruction
{
public:
    ImmediateInstruction(uint32_t value_)
    : value(value_)
    {}

    explicit operator uint32_t() { return value; }

    inline uint8_t op() { return extract(value, 31, 26);}
    inline uint8_t rs() { return extract(value, 25, 21);}
    inline uint8_t rt() { return extract(value, 20, 16);}
    inline uint8_t imm(){ return extract(value, 15,  0);}
    uint32_t value;
};

class JumpInstruction
{
public:
    JumpInstruction(uint32_t value_)
    : value(value_)
    {}

    explicit operator uint32_t() { return value; }

    inline uint8_t  op()    { return extract(value, 31, 26);}
    inline uint32_t target(){ return extract(value, 25,  0);}
    uint32_t value;
};

class RegisterInstruction
{
public:
    RegisterInstruction(uint32_t value_)
    : value(value_)
    {}

    explicit operator uint32_t() { return value; }

    inline uint8_t op()    { return extract(value, 31, 26);}
    inline uint8_t rs()    { return extract(value, 25, 21);}
    inline uint8_t rt()    { return extract(value, 20, 16);}
    inline uint8_t rd()    { return extract(value, 15, 11);}
    inline uint8_t shamt() { return extract(value, 10, 6);}
    inline uint8_t funct() { return extract(value,  5, 0);}
    uint32_t value;
};

#endif
