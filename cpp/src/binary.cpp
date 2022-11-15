#include "key/key.h"
int main() {
    Key key{};
    printf("key[%d]: 0x%x\n", 101, key[101]);
}