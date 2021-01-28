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
