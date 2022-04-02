#include <fstream>
#include <iostream>

#include "Loader.hpp"

#include <cstdlib>
#include <cstring>

template <typename T>
constexpr T SwapBytes(T Item)
{
	int8_t WasNegative = (Item < 0) ? -1 : 1;
	Item = (Item < 0) ? -Item : Item;

	if constexpr (sizeof(T) == 1)
	{
		return WasNegative * Item;
	}
	else if constexpr (sizeof(T) == 2)
	{
		return WasNegative * __builtin_bswap16(Item);
	}
	else if constexpr (sizeof(T) == 4)
	{
		return WasNegative * __builtin_bswap32(Item);
	}
	else if constexpr (sizeof(T) == 8)
	{
		return WasNegative * __builtin_bswap64(Item);
	}
}

const int EndiannessChecker = 1;
constexpr bool IsBigEndian()
{
	return *(reinterpret_cast<const char*>(&EndiannessChecker)) != EndiannessChecker;
}


picovm::Loader::ContentFile picovm::Loader::Load(const char *Location)
{
	std::ifstream Content;
	Content.open(Location, std::ios::in | std::ios::binary | std::ios::ate);
	if (Content.is_open() == false)
	{
		return {nullptr, 0};
	}

	/* We open at the end of the file to get the size. */
	std::streampos FileSize = Content.tellg();

	/* Return to the start. */
	Content.seekg(0, std::ios::beg);

	uint8_t *RawContent = new uint8_t[FileSize];
	Content.read((char*)RawContent, FileSize);
	Content.close();

	return {RawContent, FileSize};
}

uint8_t picovm::Loader::LoadU8(uint8_t *VirtMem, uint64_t Offset)
{
	uint8_t Content;
	std::memcpy(&Content, &VirtMem[Offset], sizeof(uint8_t));
	if (IsBigEndian())
	{
		Content = SwapBytes<uint8_t>(Content);
	}
	return Content;

}

uint16_t picovm::Loader::LoadU16(uint8_t *VirtMem, uint64_t Offset)
{
	uint16_t Content;
	std::memcpy(&Content, &VirtMem[Offset], sizeof(uint16_t));
	if (IsBigEndian())
	{
		Content = SwapBytes<uint16_t>(Content);
	}
	return Content;
}

uint32_t picovm::Loader::LoadU32(uint8_t *VirtMem, uint64_t Offset)
{
	uint32_t Content;
	std::memcpy(&Content, &VirtMem[Offset], sizeof(uint32_t));
	if (IsBigEndian())
	{
		Content = SwapBytes<uint32_t>(Content);
	}
	return Content;
}

uint64_t picovm::Loader::LoadU64(uint8_t *VirtMem, uint64_t Offset)
{
	uint64_t Content;
	std::memcpy(&Content, &VirtMem[Offset], sizeof(uint64_t));
	if (IsBigEndian())
	{
		Content = SwapBytes<uint64_t>(Content);
	}
	return Content;
}

int8_t picovm::Loader::LoadS8(uint8_t *VirtMem, uint64_t Offset)
{
	int8_t Content;
	std::memcpy(&Content, &VirtMem[Offset], sizeof(int8_t));
	if (IsBigEndian())
	{
		Content = SwapBytes<int8_t>(Content);
	}
	return Content;
}

int16_t picovm::Loader::LoadS16(uint8_t *VirtMem, uint64_t Offset)
{
	int16_t Content;
	std::memcpy(&Content, &VirtMem[Offset], sizeof(int16_t));
	if (IsBigEndian())
	{
		Content = SwapBytes<int16_t>(Content);
	}
	return Content;
}

int32_t picovm::Loader::LoadS32(uint8_t *VirtMem, uint64_t Offset)
{
	int32_t Content;
	std::memcpy(&Content, &VirtMem[Offset], sizeof(int32_t));
	if (IsBigEndian())
	{
		Content = SwapBytes<int32_t>(Content);
	}
	return Content;
}

int64_t picovm::Loader::LoadS64(uint8_t *VirtMem, uint64_t Offset)
{
	int64_t Content;
	std::memcpy(&Content, &VirtMem[Offset], sizeof(int64_t));
	if (IsBigEndian())
	{
		Content = SwapBytes<int64_t>(Content);
	}
	return Content;
}

void picovm::Loader::Unload(picovm::Loader::ContentFile Content)
{
	if (Content.FileSize)
	{
		delete[] Content.MemoryRaw;		
	}
}

