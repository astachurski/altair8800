#ifndef _MEMORY_H_
#define _MEMORY_H_

#ifdef ARDUINO
inline uint8_t read8(uint16_t address)
{
        uint8_t data;
        digitalWrite(5, LOW);
        SPI.transfer(3); // read byte
        SPI.transfer(0);
        SPI.transfer((address >> 8) & 0xff);
        SPI.transfer(address & 0xff); // 24 bit address
        data = SPI.transfer(0x00); // data
        digitalWrite(5, HIGH);
        return data;
}

inline void write8(uint16_t address, uint8_t val)
{
        digitalWrite(5, LOW);
        SPI.transfer(2); // write byte
        SPI.transfer(0);
        SPI.transfer((address >> 8) & 0xff);
        SPI.transfer(address & 0xff); // 24 bit address
        SPI.transfer(val); // data
        digitalWrite(5, HIGH);
}

inline uint16_t read16(uint16_t address)
{
        uint16_t result = 0;
        result = read8(address);
        result |= read8(address+1) << 8;

        return result;
}

inline void write16(uint16_t address, uint16_t val)
{
        write8(address, val & 0xff);
        write8(address+1, (val >> 8) & 0xff);
}
#else
extern uint8_t memory[64*1024];

inline uint8_t read8(uint16_t address)
{
        if(address < 64*1024)
                return memory[address];
        return 0;
}

inline void write8(uint16_t address, uint8_t val)
{
        if(address < 64*1024)
                memory[address] = val;
}

inline uint16_t read16(uint16_t address)
{
        if(address < 64*1024)
                return *(uint16_t*)&memory[address];
        return 0;
}

inline void write16(uint16_t address, uint16_t val)
{
        if(address < 64*1024)
                *(uint16_t*)&memory[address] = val;
}
#endif
#endif