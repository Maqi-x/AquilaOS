/*********************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include <msg.hpp>
#include <screen.hpp>
#include <string.hpp>

namespace io {

// ---------------------- Print ------------------- //

void Print(const string str, uint8 color) { printstr(str, color); }
void Print(String str, uint8 color) { printstr(str.c_str(), color); }

void Println(const string str, uint8 color) {
    printstr(str, color);
    printchar('\n', color);
}

void Println(String str, uint8_t color) { io::Println(str.c_str(), color); }

// ---------------- Message Boxes (legacy) --------------- //

void ShowError(const string str) {
    printstr(" [ ERROR ]: ", 0x04);
    printstr(str, 0x07);
    printstr("\n", 0x07);
}

void ShowInfo(const string str) {
    printstr(" [ INFO ]: ", 0x01);
    printstr(str, 0x07);
    printstr("\n", 0x07);
}

void ShowWarn(const string str) {
    printstr(" [ WARNING ]: ", 0x0E);
    printstr(str, 0x07);
    printstr("\n", 0x07);
}

void ShowOk(const string str) {
    printstr(" [ OK ]: ", 0x0B);
    printstr(str, 0x07);
    printstr("\n", 0x07);
}

void ShowSuccess(const string str) {
    printstr(" [ SUCCESS ]: ", 0x0A);
    printstr(str, 0x07);
    printstr("\n", 0x07);
}

// ------------------ Message Boxes ------------------- //

void ShowError(String str) {
    printstr(" [ ERROR ]: ", 0x04);
    Println(str);
}

void ShowInfo(String str) {
    printstr(" [ INFO ]: ", 0x01);
    Println(str);
}

void ShowWarn(String str) {
    printstr(" [ WARNING ]: ", 0x0E);
    Println(str);
}

void ShowOk(String str) {
    printstr(" [ OK ]: ", 0x0B);
    Println(str);
}

void ShowSuccess(String str) {
    printstr(" [ SUCCESS ]: ", 0x0A);
    Println(str);
}

// void io::ShowCustomMsg(const string title, int color, const string str) {
//     printstr(" [ ");
//     printstr(" ");
// }

} // namespace io