/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include "commands.hpp"
#include "tests.hpp"

#include <asm/power.hpp>
#include <hardware/RAM.hpp>
#include <hardware/cpu.hpp>

#include <math/eval.hpp>

#include <constants.hpp>
#include <map.hpp>
#include <strconv.hpp>
#include <string.hpp>
#include <types.hpp>

#include <input.hpp>
#include <msg.hpp>
#include <time.hpp>

#include <panic.hpp>
#include <screen.hpp>

#include <speaker.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Winfinite-recursion"
void crash() {
    int arr[1000000000];
    crash();
}
#pragma GCC diagnostic pop

String HostName;
map::MapStrStr* Vars;

bool isProtectedMode() {
    uint32 cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    return cr0 & 1;
}

void printprefix(String user) {
    io::Print(" [ ", 0x07);
    io::Print(user, 0x09);
    io::Print("@", 0x0F);
    io::Print(HostName, 0x02);
    io::Print(" ]", 0x07);
    io::Print(" $ ", 0x0F);
}

void TermStart() {
    uint16 theme = 0x0B;
    clearscreen();
    printLogo(theme);

    // io::Printf("Hello, %s! %d, %f", "world", 10, 12.3);
    io::Printf("Hello, %s! %d > %d? %t\n", "World", 10, 20, 10 > 20);

    io::ShowInfo(AQUILA_NAME);
    HostName = "AquilaPC";

    Vars = new map::MapStrStr();
    map::Init(Vars, 1000);
    String user = "root";

    char buffer[256];
    char* args[10];
    while (true) {
        printprefix(user);
        input(buffer, sizeof(buffer));

        int argsCount = splitCmd(buffer, args, 10);

        bool skip = false;
        for (int i = 1; i < argsCount; i++) {
            auto arg = String(args[i]);
            auto v = map::Get(Vars, args[i] + 1);
            if (arg.HasPrefix("$") && v) {
                args[i] = (char*)malloc(strlen(v) + 1);
                strcpy(args[i], v);
            }
        }

        for (int i = 1; i < argsCount; i++) {
            auto arg = String(args[i]);
            if (arg.HasPrefix("$(")) {
                if (!arg.HasSuffix(")")) {
                    io::ShowError(String("Expected ')' before '") + (i + 1 < argsCount ? args[i + 1] : "NEWLINE") + "' token");
                    skip = true;
                    break;
                }

                auto x = math::Eval(arg.TrimPrefix("$(").TrimSuffix(")").c_str());
                args[i] = (char*)malloc(strconv::LongToString(x).Len() + 1);
                strcpy(args[i], strconv::LongToString(x).c_str());
            }
        }

        if (skip) continue;

        char* tmp[100];

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
            // io::Println(farg);
            // io::Println(args[i]);
            // io::Println(farg + args[i]);
            farg += args[i];
            farg += " ";
        }

        if (strEq(args[0], "sysinfo")) {
            io::Printlnf("%s (%s) compiled on %s in %s", AQUILA_NAME, AQUILA_VERSION, COMPILER, __DATE__);
        } else if (strEq(args[0], "vars")) {
            for (size_t i = 0; i < Vars->size; i++) {
                auto key = Vars->data[i].key;
                auto value = Vars->data[i].value;
                io::Printlnf("%s: %s", key, value);
            }
        } else if (strEq(args[0], "get")) {
            io::Println(map::Get(Vars, farg.c_str()));
        } else if (strEq(args[0], "print")) {
            io::Println(farg, 0x07);
        } else if (strEq(args[0], "cowsay")) {
            cowsay(farg);
        } else if (strEq(args[0], "tests")) {
            bool (*tests[])() = {TestBasicAllocation, TestMultipleAllocations, TestReallocation, TestMemset, TestLargeAllocation, TestFreeNullPointer, TestString, TestSlice, TestArray};

            auto testsLen = sizeof(tests) / sizeof(tests[0]);
            unsigned int failed = 0;
            for (size_t i = 0; i < testsLen; ++i) {
                if (!tests[i]()) failed++;
            }

            if (failed >= testsLen)
                io::ShowError("All tests have failed!");
            else if (failed > 0)
                io::ShowWarn("Some tests have failed!");
            else
                io::ShowSuccess("All tests were successful!");

        } else if (strEq(args[0], "map")) {
            mapf();
        } else if (strEq(args[0], "clear")) {
            clearscreen();
        } else if (strEq(args[0], "reboot")) {
            reboot();
        } else if (strEq(args[0], "shutdown")) {
            shutdown();
            // } else if (strEq(args[0], "gui")) {

            //     // io::Print("framebuffer address: ");
            //     // io::Println((uint32)framebuffer);
            //     // while (true);
            //     if (!isProtectedMode()) {
            //         io::Println("aha");
            //         while (true) {}
            //     }
            //     setGUIMode();
            //     paintScreen(4);
            //     while (true);
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
            io::Println(getCPUName());
            // } else if (strEq(args[0], "ram")) {
            //     MultibootInfo* mbInfo = mboot_ptr;

            //     io::Println("Flags: ", mbInfo->flags);
            //     io::Println("Mem Lower: ", mbInfo->memLower);
            //     io::Println("Mem Upper: ", mbInfo->memUpper);
            //     io::Println("MMap Length: ", mbInfo->mmapLength);
            //     io::Println("MMap Addr: ", mbInfo->mmapAddr);
            //     io::Println(formatBytes(getRAM(mboot_ptr)));
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
            long duration = strconv::StrToInt(args[1], &success);
            if (!success) {
                io::ShowError("The argument to the wait command must be an integer!");
                continue;
            }

            time::Sleep(duration);
        } else if (strEq(args[0], "eval")) {
            io::Println(math::Eval(farg.c_str()));
        } else if (strEq(args[0], "timeget")) {
            char* tmp = nullptr;
            time::Now().Format(tmp);
            io::Println(tmp);
            delete tmp;
        } else if (strEq(args[0], "startup-song")) {
            playStartupSong();
        } else if (strEq(args[0], "crash")) {
            crash();
        } else {
            io::ShowErrorf("Command '%s' is not valid command or AEF binary!", args[0]);
        }
        for (int i = argsCount; i > 0; i--) {
            free(args[i]);
        }
    }
    delete Vars;
}
