#include <string>
#include <stdio.h>
#include <iostream>

typedef struct _GUID
{
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
} GUID, UUID;

namespace ChinuxTeam
{

GUID CreateGuid();

std::string GuidToString(const GUID &guid);

} // namespace ChinuxTeam