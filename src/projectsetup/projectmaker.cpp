#include <iostream>
#include <string>
#include "projset.h"

int main() {
    std::string name, path, usever, pmver;

    std::cout << "[DBG] Enter project name: ";
    std::getline(std::cin, name);

    std::cout << "[DBG] Enter project path: ";
    std::getline(std::cin, path);

    std::cout << "[DBG] Enter user version: ";
    std::getline(std::cin, usever);

    std::cout << "[DBG] Enter package manager version: ";
    std::getline(std::cin, pmver);

    makeProject(name, path, usever, pmver);

    return 0;
}
