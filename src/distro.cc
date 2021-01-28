#include <string>
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

static Distro detectDistro() {
    if(fileExists("/usr/bin/dpkg")) return DEBIAN;
    if(fileExists("/usr/bin/pacman")) return ARCH;
    if(fileExists("/usr/bin/emerge")) return GENTOO;
    if(fileExists("/usr/bin/dnf")) return FEDORA;
    if(fileExists("/usr/bin/xbps-install")) return VOID;
}
