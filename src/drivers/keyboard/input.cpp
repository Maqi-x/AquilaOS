/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include <input.hpp>
#include <msg.hpp>
#include <ports.hpp>
#include <screen.hpp>
#include <string.hpp>

static char keymap[128] = {0, 27,  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',  '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
                           0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,   '\\', 'z',  'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,   '*', 0,   ' ',
                           0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    '-', 0,   0,    0,    '+', 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};

static char shiftKeymap[128] = {0, 27,  '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
                                0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0,   '|',  'Z',  'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,   '*', 0,   ' ',
                                0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   '-', 0,   0,    0,    '+', 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};

static uint8_t shiftLeftPressed = 0;
static uint8_t shiftRightPressed = 0;

static uint8_t keyStates[128] = {0};

static uint8_t readScancode() { return inb(0x60); }

void input(char *buffer, uint16 maxLength, uint8 secret, uint8 color) {
    uint16 length = 0;

    while (1) {
        uint8 scanCode = readScancode();
        uint8 shiftReleased = scanCode & 0x80;
        uint8 key = scanCode & ~0x80;

        if (shiftReleased) {
            keyStates[key] = 0;

            switch (key) {
            case 0x2A:
                shiftLeftPressed = 0;
                break;
            case 0x36:
                shiftRightPressed = 0;
                break;
            }
            continue;
        }

        if (keyStates[key]) {
            continue;
        }

        keyStates[key] = 1;

        if (key == 0x1C) {
            buffer[length] = '\0';
            io::Println("", 0x07);
            break;
        }

        if (key == 0x0E && length > 0) {
            length--;
            buffer[length] = '\0';
            delchar();
            continue;
        }

        char c = '\0';
        switch (key) {
        case 0x2A:
        case 0x36:
            if (shiftReleased) break;
            if (key == 0x2A) shiftLeftPressed = 1;
            if (key == 0x36) shiftRightPressed = 1;
            continue;
        default:
            c = (shiftLeftPressed || shiftRightPressed) ? shiftKeymap[key] : keymap[key];
            break;
        }

        if (!c) {
            continue;
        }

        if (length < maxLength - 1) {
            buffer[length++] = c;
            buffer[length] = '\0';

            if (secret) {
                printchar('*', color);
            } else {
                printchar(c, color);
            }
        }
    }
}

uint8 readYN(char *text, uint8 color) {
    while (true) {
        io::Print(" ", color);
        io::Print(text, color);
        char buffer[2];
        input(buffer, sizeof(buffer), 0, color);
        if (strEq(buffer, "Y") || strEq(buffer, "y")) {
            return 1;
        } else if (strEq(buffer, "N") || strEq(buffer, "n")) {
            return 0;
        } else {
            io::ShowError("Incorrect option!");
        }
        io::Print("\n", 0x07);
    }
}