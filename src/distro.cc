#include <string>
#include <unistd.h>

enum Distro {
    kDebian,
    kUbuntu,
    kArch,
    kGentoo,
    kFedora,
    kVoid
};

static bool fileExists(std::string path) {
    return access(path.c_str(), 0) == 0;
}
