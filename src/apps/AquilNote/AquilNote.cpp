#include <input.hpp>
#include <msg.hpp>
#include <screen.hpp>
#include <string.hpp>
#include <types.hpp>

void AquilNoteMain(uint8_t color, uint8_t barcolor) {
    clearscreen();
    paintline(0, barcolor);
    printct("AquilNote", barcolor);
    io::Println("", 0x0);
    char buffer[1762];
    while (1) {
        input(buffer, sizeof(buffer), 0, color);
        if (strEq(buffer, "!exit") || strEq(buffer, "!quit")) {
            clearscreen();
            break;
        }
        if (strEq(buffer, "!backline")) {
        }
    }
}