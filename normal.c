#include <unistd.h>
int main() {
    write(1, "Hello OS!\n", 10);
    return 0;
}
