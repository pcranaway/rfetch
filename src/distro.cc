#include <string>
#include "util.cc"

enum Distro {
    LINUX,
    DEBIAN,
    UBUNTU,
    ARCH,
    GENTOO,
    FEDORA,
    VOID
};

static std::string getDistroName(Distro distro) {
    if(distro == LINUX) return "Linux";
    if(distro == DEBIAN) return "Debian";
    if(distro == UBUNTU) return "Ubuntu";
    if(distro == ARCH) return "Arch Linux";
    if(distro == GENTOO) return "Gentoo";
    if(distro == FEDORA) return "Fedora";
    if(distro == VOID) return "Void Linux";

    return "Unknown";
}

static Distro detectDistro() {
    if(fileExists("/usr/bin/dpkg")) return DEBIAN;
    if(fileExists("/usr/bin/pacman")) return ARCH;
    if(fileExists("/usr/bin/emerge")) return GENTOO;
    if(fileExists("/usr/bin/dnf")) return FEDORA;
    if(fileExists("/usr/bin/xbps-install")) return VOID;

    return LINUX;
}

static int countPackages(Distro distro) {
    std::string command;

    if(distro == DEBIAN || distro == UBUNTU) {
        command = "dpkg-query -f '.\n' -W";
    }

    if(distro == ARCH) {
        command = "pacman -Qq";
    }

    if(distro == GENTOO) {
        command = "equery list \"*\"";
    }

    if(distro == FEDORA) {
        command = "rpm -qa";
    }

    if(distro == VOID) {
        command = "xbps-query -l";
    }

    if(distro == LINUX) {
        command = "ls /usr/bin";
    }

    command += " | wc -l";

    std::string output = exec(command.c_str());
    return atoi(output.c_str());
}
