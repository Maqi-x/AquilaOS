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

#include <time.hpp>

static char keymap[128] = {
    0,    27,  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',  '-', '=',  '\b', // 0x00 - 0x0E
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[',  ']', '\n', // 0x0F - 0x1C
    0,    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,    '\\', // 0x1D - 0x2B
    'z',  'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,   '*',  0,   ' ', // 0x2C - 0x39
    0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    '-', 0,    0,    0, // 0x3A - 0x47
    '+',  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,    0,    0 // 0x48 - 0x7F
};

static char shiftKeymap[128] = {
    0,    27,  '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',  '\b', // 0x00 - 0x0E
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', // 0x0F - 0x1C
    0,    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0,    '|', // 0x1D - 0x2B
    'Z',  'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,   '*', 0,   ' ', // 0x2C - 0x39
    0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   '-', 0,    0,    0, // 0x3A - 0x47
    '+',  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,    0 // 0x48 - 0x7F
};

static bool shiftLeftPressed = false;
static bool shiftRightPressed = false;
static bool capsLockOn = false;

static uint8 keyStates[128] = {0};

static uint8 readScancode() { return inb(0x60); }

uint16 cursorStartPos = 0;

#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

static uint16* video_memory = (uint16*)VIDEO_MEMORY;

void input(char* buffer, uint16 maxLength, bool secret, uint8 color, bool multiline, const char* end) {
    uint16 length = 0;
    cursorStartPos = cursorPos;
    uint16 endLen = end ? strlen(end) : 0;

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

        keyStates[key] = true;

        if (key == 0x1C) { // Enter
            buffer[length] = '\0';
            printchar('\n', 0x07);
            if (!multiline) break;
            continue;
        }

        if (key == 0x0E) { // Backspace
            if (cursorPos > cursorStartPos) {
                uint16 index = cursorPos - cursorStartPos;

                if (cursorPos % SCREEN_WIDTH == 0) {
                    cursorPos -= SCREEN_WIDTH;
                    updateCursor();

                    while ((video_memory[cursorPos] & 0xFF) == ' ' && (cursorPos % SCREEN_WIDTH) != 0) {
                        delchar();
                    }

                    continue;
                }

                for (uint16 i = index; i < length; i++) {
                    buffer[i - 1] = buffer[i];
                }

                buffer[length--] = '\0';

                delchar();
                continue;
            }
            continue;
        }

        if (multiline) {
            if (key == 0x48) { // Up arrow
                if (cursorPos >= SCREEN_WIDTH + cursorStartPos) {
                    cursorPos -= SCREEN_WIDTH;
                    updateCursor();
                    while ((video_memory[cursorPos] & 0xFF) == ' ' && (cursorPos % SCREEN_WIDTH) != 0) {
                        delchar();
                    }
                }
                continue;
            }

            if (key == 0x50) { // Down arrow
                if (cursorPos + SCREEN_WIDTH < cursorStartPos + length) {
                    cursorPos += SCREEN_WIDTH;
                    updateCursor();
                    while ((video_memory[cursorPos - 1] & 0xFF) == ' ' && (cursorPos % SCREEN_WIDTH) != 0) {
                        delchar();
                    }
                }
                continue;
            }
        }

        if (key == 0x4B && cursorPos > cursorStartPos) {
            cursorPos--;
            updateCursor();
            continue;
        }

        if (key == 0x4D && cursorPos < cursorStartPos + length) {
            cursorPos++;
            updateCursor();
            continue;
        }

        char c = '\0';
        switch (key) {
        case 0x2A: // Left Shift
        case 0x36: // Right Shift
            if (key == 0x2A) shiftLeftPressed = true;
            if (key == 0x36) shiftRightPressed = true;
            continue;
        case 0x3A: // CAPSLOCK
            capsLockOn = !capsLockOn;
            continue;
        default:
            bool shiftPressed = shiftLeftPressed || shiftRightPressed;
            char baseChar = keymap[key];
            if (baseChar >= 'a' && baseChar <= 'z') {
                c = (shiftPressed ^ capsLockOn) ? shiftKeymap[key] : keymap[key];
            } else {
                c = shiftPressed ? shiftKeymap[key] : keymap[key];
            }
            break;
        }

        if (!c) continue;

        if (length < maxLength - 1) {
            uint16 index = cursorPos - cursorStartPos;

            for (uint16 i = length; i > index; i--) {
                buffer[i] = buffer[i - 1];
            }

            buffer[index] = c;
            length++;
            buffer[length] = '\0';

            printchar(secret ? '*' : c, color, true);

            if (endLen > 0 && length >= endLen && strEq(buffer + length - endLen, end)) {
                break;
            }
        }
    }
}

uint8 readYN(char* text, uint8 color) {
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