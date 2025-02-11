/*********************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

// #pragma clang++ optimize ("O3")

#include <memory.hpp>
#include <msg.hpp>
#include <screen.hpp>
#include <stdint.h>
#include <string.hpp>
#include <types.hpp>
// #include <map.hpp>
#include <constants.hpp>

#include "commands.hpp"

void cowsay(String message) {
    int MsgLen = message.Len();

    io::Print("  ", 0x07);
    for (int i = 0; i < MsgLen + 2; i++) {
        printchar('-', 0x07);
    }
    io::Println("", 0x07);

    io::Print(" < ", 0x07);
    io::Print(message, 0x07);
    io::Print(" > \n", 0x07);

    io::Print("  ", 0x07);
    for (int i = 0; i < MsgLen + 2; i++) {
        printchar('-', 0x07);
    }
    io::Println("", 0x07);

    io::Print("   \\   ^__^\n", 0x07);
    io::Print("    \\  (oo)\\_______\n", 0x07);
    io::Print("       (__)\\       )\\/\n", 0x07);
    io::Print("           ||---w||\n", 0x07);
    io::Print("           ||    ||\n", 0x07);
}

void mapf() {
    io::Print("\n", 0x07);
    io::Print(" 0x01", 0x01);
    io::Print(" 0x09", 0x09);
    io::Print(" 0x10", 0x10);
    io::Print(" 0x90", 0x90);
    io::Print("\n", 0x07);
    io::Print(" 0x02", 0x02);
    io::Print(" 0x0A", 0x0A);
    io::Print(" 0x20", 0x20);
    io::Print(" 0xA0", 0xA0);
    io::Print("\n", 0x07);
    io::Print(" 0x03", 0x03);
    io::Print(" 0x0B", 0x0B);
    io::Print(" 0x30", 0x30);
    io::Print(" 0xB0", 0xB0);
    io::Print("\n", 0x07);
    io::Print(" 0x04", 0x04);
    io::Print(" 0x0C", 0x0C);
    io::Print(" 0x40", 0x40);
    io::Print(" 0xC0", 0xC0);
    io::Print("\n", 0x07);
    io::Print(" 0x05", 0x05);
    io::Print(" 0x0D", 0x0D);
    io::Print(" 0x50", 0x50);
    io::Print(" 0xD0", 0xD0);
    io::Print("\n", 0x07);
    io::Print(" 0x06", 0x06);
    io::Print(" 0x0E", 0x0E);
    io::Print(" 0x60", 0x60);
    io::Print(" 0xE0", 0xE0);
    io::Print("\n", 0x07);
    io::Print(" 0x07", 0x07);
    io::Print(" 0x0F", 0x0F);
    io::Print(" 0x70", 0x70);
    io::Print(" 0xF0", 0xF0);
    io::Print("\n", 0x07);
    io::Print(" 0x08", 0x08);
    io::Print(" 0x00", 0x00);
    io::Print(" 0x80", 0x80);
    io::Print(" 0x00", 0x00);
    io::Println("\n", 0x07);
    io::Print(" ~!@#$%^&*()_+        `1234567890-= \n", 0x0F);
    io::Print(" qwertyuiop[]\\        QWERTYUIOP{}| \n", 0x0F);
    io::Print(" asdfghjkl;'          ASDFGHJKL:\" \n", 0x0F);
    io::Print(" zxcvbnm,./           ZXCVBNM<>? \n", 0x0F);
    io::Print("\n", 0x07);
}

void help(uint16_t theme) {
    //    mapAdd("ver", "displays OS version info");
    //    mapAdd("print <arg1>", "prints out <arg1>");
    //    mapAdd("map", "prints out every VGA color and every printable character
    //    in AquilaOS"); mapAdd("cowsay <arg1>", "displays ascii art of a cow
    //    saying <arg1>"); mapAdd("tinypad", "very simple note pad"); for
    //    (uint32_t i = 0; i < mapSize(); ++i) {
    //        auto command = mapKeyAt(i);
    //        auto description = mapGet(command);
    //        io::Print(command + ": ", theme);
    //        io::Println(description, 0x07);
    //    }
    io::Println("", 0x07);
    io::Print("> ", 0x07);
    io::Print("ver", theme);
    io::Println(": displays OS version info", 0x07);
    io::Print("> ", 0x07);
    io::Print("print <arg1>...", theme);
    io::Println(": prints out <arg1>", 0x07);
    io::Print("> ", 0x07);
    io::Print("map", theme);
    io::Println(": prints out every VGA color and every printable character in aurorOS", 0x07);
    io::Print("> ", 0x07);
    io::Print("cowsay <arg1>...", theme);
    io::Println(": displays ascii art of a cow saying <arg1>", 0x07);
    io::Print("> ", 0x07);
    io::Print("aquilnote", theme);
    io::Println(": very simple note pad", 0x07);
    io::Println("", 0x07);
}