#include <stdint.h>

#ifndef CODE_HEADER_HPP_
#define CODE_HEADER_HPP_

namespace picovm::Loader
{

struct ContentFile
{
	uint8_t *MemoryRaw;
	uint64_t FileSize;
};

ContentFile Load(const char *Location);

uint8_t LoadU8(uint8_t *Content, uint64_t Offset);
uint16_t LoadU16(uint8_t *Content, uint64_t Offset);
uint32_t LoadU32(uint8_t *Content, uint64_t Offset);
uint64_t LoadU64(uint8_t *Content, uint64_t Offset);

int8_t LoadS8(uint8_t *Content, uint64_t Offset);
int16_t LoadS16(uint8_t *Content, uint64_t Offset);
int32_t LoadS32(uint8_t *Content, uint64_t Offset);
int64_t LoadS64(uint8_t *Content, uint64_t Offset);

void Unload(ContentFile Content);

}


#endif