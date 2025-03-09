#include <ports.hpp>
#include <screen.hpp>
#include <string.hpp>

#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

static uint16* video_memory = (uint16*)VIDEO_MEMORY;
uint16 cursorPos = 0;

void updateCursor() {
    uint16 pos = cursorPos;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8)((pos >> 8) & 0xFF));
}

void scroll() {
    for (uint16 row = 0; row < SCREEN_HEIGHT - 1; row++) {
        for (uint16 col = 0; col < SCREEN_WIDTH; col++) {
            video_memory[row * SCREEN_WIDTH + col] = video_memory[(row + 1) * SCREEN_WIDTH + col];
        }
    }

    for (uint16 col = 0; col < SCREEN_WIDTH; col++) {
        video_memory[(SCREEN_HEIGHT - 1) * SCREEN_WIDTH + col] = ' ' | (0x07 << 8);
    }

    cursorPos = (SCREEN_HEIGHT - 1) * SCREEN_WIDTH;
}

void printchar(char c, uint8 color, bool shiftRight) {
    if (c == '\n') {
        cursorPos += SCREEN_WIDTH - (cursorPos % SCREEN_WIDTH);
    } else if (c == '\t') {
        for (int i = 0; i < 4; i++) {
            printchar(' ', color, shiftRight);
        }
    } else {
        if (shiftRight) {
            for (uint16 i = SCREEN_WIDTH * SCREEN_HEIGHT - 1; i > cursorPos; i--) {
                video_memory[i] = video_memory[i - 1];
            }
        }
        video_memory[cursorPos++] = (color << 8) | c;
    }

    if (cursorPos >= SCREEN_WIDTH * SCREEN_HEIGHT) scroll();

    updateCursor();
}

void printstr(const char* str, uint8 color) {
    while (*str) printchar(*str++, color);
}

void printint(uint16 value, uint8 color) {
    char buffer[6];
    int index = 5;

    buffer[index--] = '\0';

    do {
        buffer[index--] = '0' + (value % 10);
        value /= 10;
    } while (value > 0);

    for (int i = index + 1; buffer[i] != '\0'; i++) {
        printchar(' ', 0x07);
        printchar(buffer[i], color);
    }
}

void delchar() {
    if (cursorPos < 0 /*|| cursorPos % SCREEN_WIDTH == 0*/) return;
    cursorPos--;

    for (uint16 i = cursorPos; i < SCREEN_WIDTH * SCREEN_HEIGHT - 1; i++) {
        video_memory[i] = video_memory[i + 1];
    }

    video_memory[SCREEN_WIDTH * SCREEN_HEIGHT - 1] = ' ' | (0x07 << 8);

    updateCursor();
}

void clearscreen() {
    for (uint16 i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video_memory[i] = ' ' | (0x07 << 8);
    }
    cursorPos = 0;
    updateCursor();
}

void paintscreen(uint8 color) {
    for (uint16 i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video_memory[i] = ' ' | (color << 8);
    }
    cursorPos = 0;
    updateCursor();
}

void clearline(uint16 line) {
    if (line >= SCREEN_HEIGHT) {
        return;
    }

    for (uint16 col = 0; col < SCREEN_WIDTH; col++) {
        video_memory[line * SCREEN_WIDTH + col] = ' ' | (0x07 << 8);
    }

    if (cursorPos / SCREEN_WIDTH == line) {
        cursorPos = line * SCREEN_WIDTH;
        updateCursor();
    }
}

void paintline(uint16 line, uint8 color) {
    if (line >= SCREEN_HEIGHT) {
        return;
    }

    for (uint16 col = 0; col < SCREEN_WIDTH; col++) {
        video_memory[line * SCREEN_WIDTH + col] = ' ' | (color << 8);
    }

    if (cursorPos / SCREEN_WIDTH == line) {
        cursorPos = line * SCREEN_WIDTH;
        updateCursor();
    }
}

void printct(const char* str, uint8 color) {
    int length = strlen(str);
    if (length > SCREEN_WIDTH) {
        length = SCREEN_WIDTH;
    }

    int col = (SCREEN_WIDTH - length) / 2;

    uint16 row = cursorPos / SCREEN_WIDTH;
    cursorPos = row * SCREEN_WIDTH + col;

    char temp[SCREEN_WIDTH + 1];
    strcpy(temp, str);

    for (int i = 0; i < length; i++) {
        video_memory[cursorPos++] = (color << 8) | temp[i];
    }

    updateCursor();
}
