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
#include <types.hpp>
#include <screen.hpp>
#include <panic.hpp>

void kernelpanic(const char *errcode) {
    paintscreen(COLOR_3);
    println(" ", COLOR_1);
    println(" Kernel panic!", COLOR_2);
    println(" ", COLOR_1);
    print(" The system encountered a problem and could not continue! \n You can turn off the computer manually using the power button.", COLOR_1);
    println(" ", COLOR_1);
    print(" Error code: ", COLOR_1);
    print(errcode, COLOR_2);

    while (true) {
        asm("hlt");
    }
}
