#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <unistd.h>

enum Distro {
    LINUX,
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
