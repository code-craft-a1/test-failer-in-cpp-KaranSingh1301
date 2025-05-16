#include <iostream>
#include <assert.h>
#include <vector>
#include <string>

std::vector<std::string> getColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    std::vector<std::string> map;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            char buffer[50];
            snprintf(buffer, sizeof(buffer), "%d | %s | %s", i * 5 + j, majorColor[i], minorColor[j]);
            map.push_back(buffer);
        }
    }
    return map;
}

void testPrintColorMap() {
    std::cout << "\nPrint color map test\n"; 
    auto colorMap = getColorMap();
    assert(colorMap.size() == 25);
    assert(colorMap[0] == "0 | White | Blue");
    assert(colorMap[24] == "24 | Violet | Slate");
    std::cout << "All is well (maybe!)\n";
}
