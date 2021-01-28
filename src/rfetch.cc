#include <iostream>
#include "distro.cc"

using namespace std;

void print(string key, string value) {
    cout << "\e[38;5;105m" << key << ": \e[0m" << value << "\n";
}

int main() {
    Distro distro = detectDistro();

    string name = getDistroName(distro);
    print("distro", name);

    int packages = countPackages(distro);
    print("packages", to_string(packages));

    string uptime = exec("uptime -p");
    replace(uptime, "up ", "");
    replace(uptime, "\n", "");
    print("uptime", uptime);

    return 0;
}
