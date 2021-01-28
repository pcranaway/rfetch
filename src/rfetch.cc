#include <iostream>
#include "distro.cc"

using namespace std;

int main() {
    Distro distro = detectDistro();

    cout << "distro: " << getDistroName(distro) << "\n";
    cout << "packages: " << countPackages(distro) << "\n";
    cout << "uptime: " << exec("uptime -p") << "\n";

    return 0;
}
