#include <input.hpp>
#include <msg.hpp>
#include <screen.hpp>
#include <string.hpp>
#include <types.hpp>

void AquilNoteMain(uint8 color, uint8 barcolor) {
    clearscreen();
    paintline(0, barcolor);
    printct("AquilNote", barcolor);
    io::Println("", 0x0);
    char buffer[1000];
    // while (1) {
    input(buffer, sizeof(buffer), false, color, true, "!exit");
    // if (strEq(buffer, "!exit") || strEq(buffer, "!quit")) {
    //     clearscreen();
    //     break;
    // }
    // }
    clearscreen();
}