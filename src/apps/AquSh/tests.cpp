/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include "tests.hpp"
#include <string.hpp>

#include <Types/Array.hpp>
#include <Types/Slice.hpp>

bool TestBasicAllocation() {
    io::ShowInfo("[ TestBasicAllocation ] - Starting");

    int* ptr = (int*)malloc(sizeof(int));
    if (ptr == nullptr) {
        io::ShowError("[ TestBasicAllocation ] - Allocation error");
        return false;
    }

    *ptr = 42;
    if (*ptr != 42) {
        io::ShowError("[ TestBasicAllocation ] - Memory write error");
        free(ptr);
        return false;
    }

    free(ptr);
    io::ShowOk("[ TestBasicAllocation ] - Test completed successfully");
    return true;
}

bool TestMultipleAllocations() {
    io::ShowInfo("[ TestMultipleAllocations] - Starting");

    int* ptr1 = (int*)malloc(sizeof(int));
    int* ptr2 = (int*)malloc(sizeof(int));
    int* ptr3 = (int*)malloc(sizeof(int));

    if (ptr1 == nullptr || ptr2 == nullptr || ptr3 == nullptr) {
        io::ShowError("[ TestMultipleAllocations ] - Allocation error");
        free(ptr1);
        free(ptr2);
        free(ptr3);
        return false;
    }

    *ptr1 = 1;
    *ptr2 = 2;
    *ptr3 = 3;

    if (*ptr1 != 1 || *ptr2 != 2 || *ptr3 != 3) {
        io::ShowError("[ TestMultipleAllocations ] - Memory write error");
        free(ptr1);
        free(ptr2);
        free(ptr3);
        return false;
    }

    free(ptr1);
    free(ptr2);
    free(ptr3);

    io::ShowOk("[ TestMultipleAllocations ] - Test successful");
    return true;
}

bool TestReallocation() {
    io::ShowInfo("[ TestReallocation ] - Starting");

    int* ptr = (int*)malloc(sizeof(int));
    if (ptr == nullptr) {
        io::ShowError("[ TestReallocation ] - Initial allocation failed");
        return false;
    }

    *ptr = 99;
    free(ptr);

    ptr = (int*)malloc(sizeof(int));
    if (ptr == nullptr) {
        io::ShowError("[ TestReallocation ] - Reallocation failed");
        return false;
    }

    *ptr = 77;
    if (*ptr != 77) {
        io::ShowError("[ TestReallocation ] - Memory corruption detected");
        free(ptr);
        return false;
    }

    free(ptr);
    io::ShowOk("[ TestReallocation ] - Test successful");
    return true;
}

bool TestMemset() {
    io::ShowInfo("[ TestMemset ] - Starting");

    char* buffer = (char*)malloc(10);
    if (buffer == nullptr) {
        io::ShowError("[ TestMemset ] - Allocation failed");
        return false;
    }

    memset(buffer, 0xAB, 10);
    for (int i = 0; i < 10; i++) {
        if (buffer[i] != (char)0xAB) {
            io::ShowError("[ TestMemset ] - Memset failed");
            free(buffer);
            return false;
        }
    }

    free(buffer);
    io::ShowOk("[ TestMemset ] - Test successful");
    return true;
}

bool TestFreeNullPointer() {
    io::ShowInfo("[ TestFreeNullPointer ] - Starting");

    free(nullptr);
    io::ShowOk("[ TestFreeNullPointer ] - Test successful");
    return true;
}

bool TestLargeAllocation() {
    io::ShowInfo("[ TestLargeAllocation ] - Starting");

    size_t largeSize = 1024 * 1024;
    void* ptr = malloc(largeSize);
    if (ptr == nullptr) {
        io::ShowError("[ TestLargeAllocation ] - Large allocation failed");
        return false;
    }

    memset(ptr, 0xCC, largeSize);
    free(ptr);

    io::ShowOk("[ TestLargeAllocation ] - Test successful");
    return true;
}

bool TestString() {
    io::ShowInfo("[ TestString ] - Starting");
    String str("Hello world!");
    io::Println(str);
    String str2 = String("Hello") + " world!";
    io::Println(str2);
    bool eqTest = str == str2;
    io::Println((eqTest ? "str == Hello world!" : "str != Hello world!"));
    if (eqTest)
        io::ShowOk("[ TestString ] - Test successful");
    else
        io::ShowError("[ TestString ] - failed");
    return eqTest;
}

bool TestSlice() {
    io::ShowInfo("[ TestSlice ] - Starting");
    Slice<int> arr;
    for (int i = 10; i > 0; i--) {
        arr.Append(i);
    }

    Slice<int> arr2;
    arr2.Append(123);
    arr.Extend(arr2);

    for (auto i = arr.Len(); i > 0; i--) {
        io::Println(arr[i]);
    }

    if (arr != arr2) {
        io::ShowOk("[ TestSlice ] - Test successful");
        return true;
    } else {
        io::ShowError("[ TestSlice ] - failed");
        return false;
    }
}

bool TestArray() {
    io::ShowInfo("[ TestArray ] - Starting");
    Array<int, 6> arr = {1, 4, 5, 6, 2, 8};
    if (arr[1] == 4 && arr[5] == 8) {
        io::ShowOk("[ TestArray ] - Test successful");
        return true;
    } else {
        io::ShowError("[ TestArray ] - failed");
        return false;
    }
}