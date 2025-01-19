/**
 * -------------------------------------------------------------------------
 *                                   AquilaOS
 * (c) 2022-2024 Interpuce
 * 
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Interpuce/AquilaOS/blob/main/LICENSE.md
 * -------------------------------------------------------------------------
 */

#include <msg.hpp>
#include <constants.hpp>
#include <string.hpp>
#include <input.hpp>
#include <asm/power.hpp>
#include <types.hpp>
#include <panic.hpp>
#include <screen.hpp>
#include <hardware/cpu.hpp>

#include "commands.hpp"

void printprefix(const char* user, const char* pcname) {
    print(" [ ", 0x07);
    print(user, 0x09);
    print("@", 0x0F);
    print(pcname, 0x02);
    print(" ]", 0x07);
    print(" $ ", 0x0F);
}

int TermStart(uint16_t theme) {
    clearscreen();

    println("", 0x07);
    println("                        @@@@@@@@@                           ", theme);
    println("                       @@@@@@@@@@@@@@                       ", theme);
    println("                       @@@@@@@@@@@@@@@@                     ", theme);
    println("                       @@@@@@@@@@@@@@@@                     ", theme);
    println("                    @@@@@@@@@@@@@@@@@@@     @@@@@           ", theme);
    println("                    @@@@@@@@@@@@@@@@@@     @@@@@@@@         ", theme);
    println("                    @@@@@@@@@@@@@@@@      @@@@@@@@@@        ", theme);
    println("                    @@@@@@@@@@@@@@@@     @@@@@@@@@@@        ", theme);
    println("                    @@@@@@@@@@@@@@@@    @@@@@   @@@@@       ", theme);
    println("               @@@@@@@@@@@@@@@@@@@@    @@@@@@   @@@@@@      ", theme);
    println("               @@@@@@@@@@@@@@@@@@     @@@@@@     @@@@@@     ", theme);
    println("                @@@@@@@@@@@@@@@@     @@@@@@       @@@@@     ", theme);
    println("                 @@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@@@@@@    ", theme);
    println("                  @@@@@@@@@@@@     @@@@@@@@@@@@@@@@@@@@@@   ", theme);
    println("                      @@@@@       @@@@@@@@@@@@@@@@@@@@@@@@  ", theme);
    println("                                 @@@@@@             @@@@@@  ", theme);
    println("                                 @@@@@@             @@@@@@  ", theme);
    println("                                  @@@@               @@@@   ", theme);
    println("", 0x07);

    print_info(AQUILA_NAME);

    char user[4];
    strcpy(user, "root");

    char buffer[128];
    char *args[10];
    while (1) {
        printprefix(user, PC_NAME);
        input(buffer, sizeof(buffer), 0, 0x07);

        int argsCount = SplitStr(buffer, ' ', args, 10);

        if (argsCount > 0) {
            char farg[1024] = "";
            for (int i = 1; i < argsCount; i++) {
                strcat(farg, args[i]);
                strcat(farg, " ");
            }

            if (strEq(args[0], "ver")) {
                print(" ", 0x07);
                print(AQUILA_NAME, 0x07);
                print(" ", 0x07);
                println(AQUILA_VERSION, 0x07);
            } else if (strEq(args[0], "print")) {
                println(farg ,0x07);
            } else if (strEq(args[0], "cowsay")) {
                cowsay(farg);
            } else if (strEq(args[0], "map")) {
                map();
            } else if (strEq(args[0], "clear")) {
                clearscreen();
            } else if (strEq(args[0], "reboot")) {
                reboot();
            } else if (strEq(args[0], "shutdown")) {
                shutdown();
            } else if (strEq(args[0], "chuser")) {
                if (strlen(farg) < 1 || strlen(farg) > 8) {
                    print_error("User name must be between 1 and 8 characters long!");
                } else {
                    strcpy(user, farg);
                }
            } else if (strEq(args[0], "cpu")) {
                println(get_cpu_name(), 0x07);
            } else if (strEq(args[0], "AquilNote")) {
                AquilNoteMain(0x07, 0x9F);
            } else if (strEq(args[0], "debug_panic")) {
                kernelpanic("DEBUG_KERNEL_PANIC");
            } else if (strEq(args[0], "help")) {
                help(theme);
            } else {
                printstr(" ERROR ", 0x04);
                printstr(": ", 0x07);
                printstr(args[0], 0x07);
                printstr(" is neither a known command nor valid AEF binary! \n", 0x07);
            }
        }
    }
}

