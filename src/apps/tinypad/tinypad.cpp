#include <string.hpp>
#include <screen.hpp>
#include <msg.hpp>
#include <types.hpp>
#include <input.hpp>

int AquilNoteMain(uint8_t color, uint8_t barcolor) {
    clearscreen();
    paintline(0, barcolor);
    printct("AquilNote", barcolor);
    println(" ", 0x07);
    char buffer[1762];
    while (1) {
        input(buffer, sizeof(buffer), 0, color);
        if (strEq(buffer, ".exit")) {
            clearscreen();
            break;
        }
    }
    return 0;
}