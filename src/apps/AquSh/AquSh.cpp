/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include "tests.hpp"
#include <asm/power.hpp>
#include <constants.hpp>
#include <hardware/cpu.hpp>
#include <input.hpp>
#include <map.hpp>
#include <msg.hpp>
#include <panic.hpp>
#include <screen.hpp>
#include <string.hpp>
#include <time.hpp>
#include <types.hpp>

#include "commands.hpp"

String HostName;
map::MapStrStr *Vars;

void printprefix(String user) {
    io::Print(" [ ", 0x07);
    io::Print(user, 0x09);
    io::Print("@", 0x0F);
    io::Print(HostName, 0x02);
    io::Print(" ]", 0x07);
    io::Print(" $ ", 0x0F);
}

int TermStart(uint16_t theme) {
    clearscreen();

    io::Println("", 0x07);
    io::Println("                        @@@@@@@@@                           ", theme);
    io::Println("                       @@@@@@@@@@@@@@                       ", theme);
    io::Println("                       @@@@@@@@@@@@@@@@                     ", theme);
    io::Println("                       @@@@@@@@@@@@@@@@                     ", theme);
    io::Println("                    @@@@@@@@@@@@@@@@@@@     @@@@@           ", theme);
    io::Println("                    @@@@@@@@@@@@@@@@@@     @@@@@@@@         ", theme);
    io::Println("                    @@@@@@@@@@@@@@@@      @@@@@@@@@@        ", theme);
    io::Println("                    @@@@@@@@@@@@@@@@     @@@@@@@@@@@        ", theme);
    io::Println("                    @@@@@@@@@@@@@@@@    @@@@@   @@@@@       ", theme);
    io::Println("               @@@@@@@@@@@@@@@@@@@@    @@@@@@   @@@@@@      ", theme);
    io::Println("               @@@@@@@@@@@@@@@@@@     @@@@@@     @@@@@@     ", theme);
    io::Println("                @@@@@@@@@@@@@@@@     @@@@@@       @@@@@     ", theme);
    io::Println("                 @@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@@@@@@    ", theme);
    io::Println("                  @@@@@@@@@@@@     @@@@@@@@@@@@@@@@@@@@@@   ", theme);
    io::Println("                      @@@@@       @@@@@@@@@@@@@@@@@@@@@@@@  ", theme);
    io::Println("                                 @@@@@@             @@@@@@  ", theme);
    io::Println("                                 @@@@@@             @@@@@@  ", theme);
    io::Println("                                  @@@@               @@@@   ", theme);
    io::Println("", 0x07);

    io::ShowInfo(AQUILA_NAME);
    HostName = "AquilaPC";

    Vars = (map::MapStrStr *)malloc(sizeof(map::MapStrStr));
    map::Init(Vars, 1000);
    String user = "root";

    char buffer[256];
    char *args[10];
    while (true) {
        printprefix(user);
        input(buffer, sizeof(buffer), 0, 0x07);

        int argsCount = splitCmd(buffer, args, 10);

        for (int i = 1; i < argsCount; i++) {
            auto arg = String(args[i]);
            auto v = map::Get(Vars, args[i] + 1);
            if (arg.HasPrefix("$") && v) {
                args[i] = v;
            }
        }

        char *tmp[100];

        auto lenOf = SplitStr(buffer, '=', tmp, 5);
        auto correct = !(Contains(tmp[0], " ") || Contains(tmp[0], "/") || Contains(tmp[0], "\\") || Contains(tmp[0], "\"") || Contains(tmp[0], "'") || Contains(tmp[0], ".") || Contains(tmp[0], "$"));

        if (!correct) {
            io::ShowError("Invalid variable name!");
            continue;
        }

        if (argsCount == 1 && lenOf == 2) {
            map::Insert(Vars, tmp[0], tmp[1]);
            continue;
        }

        if (argsCount <= 0) {
            continue;
        }

        String farg = "";
        for (int i = 1; i < argsCount; i++) {
            farg += args[i];
            farg += " ";
        }

        if (strEq(args[0], "ver")) {
            io::Print(" ", 0x07);
            io::Print(AQUILA_NAME, 0x07);
            io::Print(" ", 0x07);
            io::Println(AQUILA_VERSION, 0x07);
        } else if (strEq(args[0], "vars")) {
            for (size_t i = 0; i < Vars->size; ++i) {
                const char *key = Vars->data[i].key;
                const char *value = Vars->data[i].value;
                io::Print(key);
                io::Print(": ");
                io::Println(value);
            }
        } else if (strEq(args[0], "get")) {
            io::Println(map::Get(Vars, farg.c_str()));
        } else if (strEq(args[0], "print")) {
            io::Println(farg, 0x07);
        } else if (strEq(args[0], "cowsay")) {
            cowsay(farg);
        } else if (strEq(args[0], "tests")) {
            bool (*tests[])() = {TestBasicAllocation, TestMultipleAllocations, TestReallocation, TestMemset, TestLargeAllocation, TestFreeNullPointer, TestString};

            auto testsLen = sizeof(tests) / sizeof(tests[0]);
            unsigned int failed = 0;
            for (size_t i = 0; i < testsLen; ++i) {
                if (!tests[i]()) failed++;
            }

            if (failed >= testsLen) {
                io::ShowError("All tests have failed!");
            } else if (failed > 0) {
                io::ShowWarn("Some tests have failed!");
            } else {
                io::ShowSuccess("All tests were successful!");
            }
        } else if (strEq(args[0], "map")) {
            mapf();
        } else if (strEq(args[0], "clear")) {
            clearscreen();
        } else if (strEq(args[0], "reboot")) {
            reboot();
        } else if (strEq(args[0], "shutdown")) {
            shutdown();
        } else if (strEq(args[0], "user")) {
            if (argsCount >= 2) {
                if (strEq(args[1], "set")) {
                    if (argsCount == 3)
                        user = args[2];
                    else
                        io::ShowError("Usage: user set <name>");
                } else if (strEq(args[1], "get")) {
                    io::Println(user, 0x07);
                } else {
                    io::ShowError("Usage: user get|set <name>");
                }
            } else {
                io::ShowError("Usage: user get|set <name>");
            }
        } else if (strEq(args[0], "cpu")) {
            io::Println(get_cpu_name(), 0x07);
        } else if (strEq(args[0], "aquilnote")) {
            AquilNoteMain(0x07, 0x9F);
        } else if (strEq(args[0], "hostname")) {
            if (argsCount >= 2) {
                if (strEq(args[1], "set")) {
                    if (argsCount == 3)
                        HostName = args[2];
                    else
                        io::ShowError("Usage: hostname set <name>");
                } else if (strEq(args[1], "get")) {
                    io::Println(HostName, 0x07);
                } else {
                    io::ShowError("Usage: hostname get|set <name>");
                }
            } else {
                io::ShowError("Usage: hostname get|set <name>");
            }
        } else if (strEq(args[0], "debug_panic")) {
            kernelpanic("DEBUG_KERNEL_PANIC");
        } else if (strEq(args[0], "help")) {
            help(theme);
        } else if (strEq(args[0], "wait")) {
            if (argsCount != 2) {
                io::ShowError("The wait command requires only 1 argument - duration");
                continue;
            }

            bool success;
            long duration = strToInt(args[1], &success);
            if (!success) {
                io::ShowError("The argument to the wait command must be an integer!");
                continue;
            }

            time::Sleep(duration);
        } else {
            char inf[70];
            joinStr("Command '", args[0], inf);
            char info[100];
            joinStr(inf, "' is not valid command or AEF binary!", info);
            io::ShowError(info);
        }
    }
}
