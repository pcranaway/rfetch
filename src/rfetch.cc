#include <iostream>
#include "distro.cc"

using namespace std;

int main() {
    Distro distro = detectDistro();

    /* distro */
    string name = getDistroName(distro);
    cout << "\e[38;5;105mdistro: \e[0m" << name << "\e[0m\n";

    /* packages */
    int packages = countPackages(distro);
    cout << "\e[38;5;105mpackages: \e[0m" << packages << "\e[0m\n";
  
    /* uptime */
    string uptime = exec("uptime -p");
    replace(uptime, "up ", "");
    replace(uptime, "\n", "");
    cout << "\e[38;5;105muptime: \e[0m" << uptime << "\e[0m\n";

    return 0;
}
