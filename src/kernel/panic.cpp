/*********************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include <msg.hpp>
#include <panic.hpp>
#include <screen.hpp>
#include <types.hpp>

void kernelpanic(const char* errcode) {
    paintscreen(COLOR_3);
    io::Println(" ", COLOR_1);
    io::Println(" Kernel panic!", COLOR_2);
    io::Println(" ", COLOR_1);
    io::Print(" The system encountered a problem and could not continue! \n You can "
              "turn off the computer manually using the power button.",
              COLOR_1);
    io::Println(" ", COLOR_1);
    io::Print(" Error code: ", COLOR_1);
    io::Print(errcode, COLOR_2);

    while (true) {
        asm("hlt");
    }
}
