#include "uuid-test.h"
#include <iostream>
#include <string>

using namespace std;
using namespace ChinuxTeam;

int main(int argc, char *argv[])
{
    GUID guid_;
    guid_ = CreateGuid();
    std::string guid_str = GuidToString(guid_);
    std::cout << guid_str << std::endl;

    return 0;
}