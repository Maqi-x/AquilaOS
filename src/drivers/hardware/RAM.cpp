#include <hardware/RAM.hpp>
#include <strconv.hpp>
#include <string.hpp>
#include <types.hpp>

uint32 getRAM(MultibootInfo* mboot_ptr) {

    if (!(mboot_ptr->flags & (1 << 6))) return 0;

    return (mboot_ptr->memUpper + 1024) * 1024;
}

String formatBytes(uint64 bytes) {
    String units[] = {"B", "KB", "MB", "GB", "TB"};
    int unitIndex = 0;
    double size = bytes;

    while (size >= 1024 && unitIndex < 4) {
        size /= 1024;
        unitIndex++;
    }

    return strconv::LongToString(size) + units[unitIndex];
}
