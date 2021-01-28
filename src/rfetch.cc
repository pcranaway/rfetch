#include <iostream>
#include "distro.cc"

using namespace std;

int main() {
    Distro distro = detectDistro();

    cout << "distro: " << getDistroName(distro) << "\n";
    cout << "packages: " << countPackages(distro) << "\n";
   
    string uptime = exec("uptime -p");
    replace(uptime, "up ", "");
    cout << "uptime: " << uptime << "\n";

    return 0;
}
