/********方法二**********/
/*libuuid是一个用于生成UUID的C库，具体用法参考http://linux.die.net/man/3/libuuid，示例如下：*/

#include <stdio.h>
#include <uuid/uuid.h>

int main(int argc, char **argv)
{
    uuid_t uuid;
    char str[36];

    uuid_generate(uuid);
    uuid_unparse(uuid, str);

    printf("%s\n", str);

    return 0;
}
