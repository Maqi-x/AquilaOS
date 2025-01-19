/**
 * -------------------------------------------------------------------------
 *                                   AquilaOS
 * (c) 2022-2024 Interpuce
 * 
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Interpuce/AquilaOS/blob/main/LICENSE.md
 * -------------------------------------------------------------------------
 */

//#pragma clang++ optimize ("O3")

#include <types.hpp>
#include <msg.hpp>
#include <string.hpp>
#include <screen.hpp>
#include <stdint.h>
//#include <map.hpp>
#include <constants.hpp>


#include "commands.hpp"

void cowsay(char message[1024]) {
    int message_length = strlen(message);

    print("  ", 0x07);
    for (int i = 0; i < message_length + 2; i++) {
        printchar('-', 0x07);
    }
    println("", 0x07);

    print(" < ", 0x07);
    print(message, 0x07);
    print(" > \n", 0x07);

    print("  ", 0x07);
    for (int i = 0; i < message_length + 2; i++) {
        printchar('-', 0x07);
    }
    println("", 0x07);

    print("   \\   ^__^\n", 0x07);
    print("    \\  (oo)\\_______\n", 0x07);
    print("       (__)\\       )\\/\n", 0x07);
    print("           ||---w||\n", 0x07);
    print("           ||    ||\n", 0x07);
}

void map() {
    print("\n", 0x07); 
    print(" 0x01", 0x01); print(" 0x09", 0x09);
    print(" 0x10", 0x10); print(" 0x90", 0x90);
    print("\n", 0x07); 
    print(" 0x02", 0x02); print(" 0x0A", 0x0A);
    print(" 0x20", 0x20); print(" 0xA0", 0xA0);
    print("\n", 0x07); 
    print(" 0x03", 0x03); print(" 0x0B", 0x0B);
    print(" 0x30", 0x30); print(" 0xB0", 0xB0);
    print("\n", 0x07); 
    print(" 0x04", 0x04); print(" 0x0C", 0x0C);
    print(" 0x40", 0x40); print(" 0xC0", 0xC0);
    print("\n", 0x07); 
    print(" 0x05", 0x05); print(" 0x0D", 0x0D);
    print(" 0x50", 0x50); print(" 0xD0", 0xD0);
    print("\n", 0x07); 
    print(" 0x06", 0x06); print(" 0x0E", 0x0E);
    print(" 0x60", 0x60); print(" 0xE0", 0xE0);
    print("\n", 0x07); 
    print(" 0x07", 0x07); print(" 0x0F", 0x0F);
    print(" 0x70", 0x70); print(" 0xF0", 0xF0);
    print("\n", 0x07); 
    print(" 0x08", 0x08); print(" 0x00", 0x00);
    print(" 0x80", 0x80); print(" 0x00", 0x00);
    println("\n", 0x07); 
    print(" ~!@#$%^&*()_+        `1234567890-= \n", 0x0F);
    print(" qwertyuiop[]\\        QWERTYUIOP{}| \n", 0x0F);
    print(" asdfghjkl;'          ASDFGHJKL:\" \n", 0x0F);
    print(" zxcvbnm,./           ZXCVBNM<>? \n", 0x0F);
    print("\n", 0x07); 
}

void help(uint16_t theme) {
//    mapAdd("ver", "displays OS version info");
//    mapAdd("print <arg1>", "prints out <arg1>");
//    mapAdd("map", "prints out every VGA color and every printable character in AquilaOS");
//    mapAdd("cowsay <arg1>", "displays ascii art of a cow saying <arg1>");
//    mapAdd("tinypad", "very simple note pad");
//    for (uint32_t i = 0; i < mapSize(); ++i) {
//        auto command = mapKeyAt(i);
//        auto description = mapGet(command);
//        print(command + ": ", theme);
//        println(description, 0x07);
//    }
    println("", 0x07);
    print("> ", 0x07); print("ver", theme); println(": displays OS version info", 0x07);
    print("> ", 0x07); print("print <arg1>...", theme); println(": prints out <arg1>", 0x07);
    print("> ", 0x07); print("map", theme); println(": prints out every VGA color and every printable character in aurorOS", 0x07);
    print("> ", 0x07); print("cowsay <arg1>...", theme); println(": displays ascii art of a cow saying <arg1>", 0x07);
    print("> ", 0x07); print("tinypad", theme); println(": very simple note pad", 0x07);
    println("", 0x07);
}
