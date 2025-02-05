#include <bits/stdc++.h>
using namespace std;

bool isValidIP(const vector<int>& ip) {
    for (int i = 0; i < 4; ++i) {
        if (ip[i] < 0 || ip[i] > 255) {
            return false;
        }
    }
    return true;
}

void displayIPAddress(const vector<int>& ip) {
    cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3];
}

vector<int> calculateNetworkAddress(const vector<int>& ip, int cidr) {
    vector<int> networkAddress = ip;
    int fullOctets = cidr / 8;
    int remainingBits = cidr % 8;

    for (int i = fullOctets; i < 4; ++i) {
        if (i == fullOctets) {
            networkAddress[i] = (networkAddress[i] >> (8 - remainingBits)) << (8 - remainingBits);
        } else {
            networkAddress[i] = 0;
        }
    }

    return networkAddress;
}

vector<int> calculateBroadcastAddress(const vector<int>& networkAddress, int cidr) {
    vector<int> broadcastAddress = networkAddress;
    int fullOctets = cidr / 8;
    int remainingBits = cidr % 8;

    for (int i = fullOctets; i < 4; ++i) {
        if (i == fullOctets) {
            broadcastAddress[i] |= (1 << (8 - remainingBits)) - 1;
        } else {
            broadcastAddress[i] = 255;
        }
    }

    return broadcastAddress;
}

void calculateSubnets(const vector<int>& baseIP, int cidr) {
    int totalIPs = pow(2, 32 - cidr); 
    int increment = totalIPs; 
    int subnets = 256 / totalIPs;

    vector<int> currentIP = baseIP;
    cout << "All " << subnets << " of the Possible /" << cidr << " Networks for " << baseIP[0] << "." << baseIP[1] << "." << baseIP[2] << ".*" << endl;
    cout << "Network Address\t\t\tUsable Host Range\t\t\tBroadcast Address" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < subnets; i++) {
        vector<int> networkAddress = calculateNetworkAddress(currentIP, cidr);
        vector<int> firstUsable = networkAddress;
        firstUsable[3] += 1;

        vector<int> lastUsable = calculateBroadcastAddress(networkAddress, cidr);
        lastUsable[3] -= 1;

        vector<int> broadcastAddress = calculateBroadcastAddress(networkAddress, cidr);

        displayIPAddress(networkAddress);
        cout << "\t\t\t";
        displayIPAddress(firstUsable);
        cout << " - ";
        displayIPAddress(lastUsable);
        cout << "\t\t";
        displayIPAddress(broadcastAddress);
        cout << endl;

        currentIP[3] += increment;

        for (int j = 3; j >= 0; j--) {
            if (currentIP[j] > 255) {
                currentIP[j] = 0;
                if (j > 0) {
                    currentIP[j - 1]++;
                }
            }
        }
    }
}

void divideIP_follow_cidr(string input) {
    size_t slashPos = input.find('/');
    if (slashPos == string::npos) {
        cout << "Error: CIDR notation must include '/' followed by the CIDR value (e.g 118.179.60.0/28)" << endl;
        return;
    }

    string ipPart = input.substr(0, slashPos);
    string cidrPart = input.substr(slashPos + 1);

    if (cidrPart.empty() || !all_of(cidrPart.begin(), cidrPart.end(), ::isdigit)) {
        cout << "Error: CIDR part must be a number." << endl;
        return;
    }

    int cidr = stoi(cidrPart);

    if (cidr < 0 || cidr > 32) {
        cout << "Error: Invalid CIDR value. It should be between 0 and 32." << endl;
        return;
    }

    vector<int> baseIP(4);
    stringstream ss(ipPart);
    char dot;
    ss >> baseIP[0] >> dot >> baseIP[1] >> dot >> baseIP[2] >> dot >> baseIP[3];

    if (!isValidIP(baseIP)) {
        cout << "Error: Each part of the IP address must be between 0 and 255." << endl;
        return;
    }

    calculateSubnets(baseIP, cidr);
}

