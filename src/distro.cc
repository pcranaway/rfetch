#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <unistd.h>

enum Distro {
    DEBIAN,
    UBUNTU,
    ARCH,
    GENTOO,
    FEDORA,
    VOID
};

static bool fileExists(std::string path) {
    return access(path.c_str(), 0) == 0;
}

/* https://stackoverflow.com/a/478960/14674978 */
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


static Distro detectDistro() {
    if(fileExists("/usr/bin/dpkg")) return DEBIAN;
    if(fileExists("/usr/bin/pacman")) return ARCH;
    if(fileExists("/usr/bin/emerge")) return GENTOO;
    if(fileExists("/usr/bin/dnf")) return FEDORA;
    if(fileExists("/usr/bin/xbps-install")) return VOID;
}
