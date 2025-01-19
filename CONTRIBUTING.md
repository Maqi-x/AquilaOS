# Contributing to AquilaOS & compiling OS

Thanks for your interest in contributing to AquilaOS. This is a quick guide how to contribute to AquilaOS.

## Code writing standards

There are standards in writing code for AquilaOS and to not make ten next useless commits reverting the change, please read `AquilaOS Code-writing standards` below.

1. Use [camelCase](https://en.wikipedia.org/wiki/camelCase) or PascalCase style.
2. Never make directory in repo root folder if this is not absolutelly necessary (read [your creation warning](#contributing-to-the-apps)).
3. Do not use `#include "../include/something_there.hpp"`. Instead, use `#include <something_there.hpp>`.
4. Do not make any C/C++ or other non-header files in `include` directory.

Your pull request will be **rejected** if any of standards above is not used in your code.

## Contributing to AquilaOS Kernel

If you want to contribute to AquilaOS kernel you need to have previous experience with OS-dev. You can break the code very easily, so always [compile the OS](#compiling-and-running-AquilaOS) and check the changes. Every change must be described with English and can't rebuild the entire kernel (if you want, make issue as feature request).

## Contributing to the apps

The apps are not that easy to break, so you can do more changes.

> [!TIP]
> Avoid creating new apps, because they are absolutely **your** creation and you have copyright to them.

## Compiling and running AquilaOS

### Compilation

> [!CAUTION]
> You will do this only at your own risk. We don't officially support any OS builds compiled by the user.

First - make sure you have Linux distribution installed and you are going to execute these commands on Linux distribution.

To clone, compile and run virtually AquilaOS you will need `git`, `make`, `lld`, `clang`, `nasm`, `binutils` and `qemu-system-x86_64` installed.

Clone the repository to the current folder skipping unnecessary commit history:

`git clone https://github.com/Maqi-x/AquilaOS . --depth 1`

Run this command in AquilaOS repo to build the OS:

`make`

### Running OS in virtual machine

Run this command to run the OS:

`make run`

Or you can run AquilaOS using this command:

`qemu-system-x86_64 -kernel kernel.elf`
