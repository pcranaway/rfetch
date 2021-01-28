#include <iostream>
#include "distro.cc"

using namespace std;

int main() {
    Distro distro = detectDistro();

    cout << "\e[38;5;105mdistro: \e[0m" << getDistroName(distro) << "\e[0m\n";
    cout << "\e[38;5;105mpackages: \e[0m" << countPackages(distro) << "\e[0m\n";
   
    string uptime = exec("uptime -p");
    replace(uptime, "up ", "");
    replace(uptime, "\n", "");
    cout << "\e[38;5;105muptime: \e[0m" << uptime << "\e[0m\n";

    return 0;
}
