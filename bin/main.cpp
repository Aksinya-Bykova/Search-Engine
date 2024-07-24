#include <iostream>
#include "../lib/response.h"

int main() {
    fs::path root_path = "/home/xunya/CLionProjects/labwork11/FILES";
    generate(root_path);
    set_metrics();
    response();
    return 0;
}
