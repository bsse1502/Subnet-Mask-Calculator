#include <bits/stdc++.h>
using namespace std;

bool isValidIP(string &ip) {
    vector<int> ipParts(4, 0);
    stringstream ss(ip);
    string part;
    int i = 0;
    while (getline(ss, part, '.') && i < 4) {
        try {
            ipParts[i++] = stoi(part);
        } catch (...) {
            return false;
        }
    }
    if (i != 4) return false;
    for (int j = 0; j < 4; j++) {
        if (ipParts[j] < 0 || ipParts[j] > 255)
            return false;
    }
    return true;
}

int calculatePrefix(int neededIPs) {
    int totalIPs = neededIPs + 2;
    return 32 - ceil(log2(totalIPs));
}

string calculateBroadcastAddress(string networkAddress, int blockSize) {
    size_t pos = networkAddress.find_last_of('.');
    string ipPrefix = networkAddress.substr(0, pos + 1);
    int lastOctet = stoi(networkAddress.substr(pos + 1));
    int broadcast = lastOctet + blockSize - 1;

    if (broadcast > 255) {
        return "Unavailable";
    }
    return ipPrefix + to_string(broadcast);
}

pair<string, string> calculateHostRange(string networkAddress, int blockSize) {
    size_t pos = networkAddress.find_last_of('.');
    string ipPrefix = networkAddress.substr(0, pos + 1);
    int firstHost = stoi(networkAddress.substr(pos + 1)) + 1;
    int lastHost = firstHost + blockSize - 3;
    return {ipPrefix + to_string(firstHost), ipPrefix + to_string(lastHost)};
}

string calculateNetworkAddress(string baseIP, int offset) {
    vector<int> ipParts(4, 0);
    size_t pos = 0;
    int octetIndex = 0;

    while ((pos = baseIP.find('.')) != string::npos) {
        ipParts[octetIndex++] = stoi(baseIP.substr(0, pos));
        baseIP.erase(0, pos + 1);
    }
    ipParts[3] = stoi(baseIP);

    ipParts[3] += offset;

    for (int i = 3; i >= 0; i--) {
        if (ipParts[i] > 255) {
            if (i > 0) {
                ipParts[i - 1] += ipParts[i] / 256;
                ipParts[i] %= 256;
            } else {
                return "";
            }
        }
    }
    return to_string(ipParts[0]) + "." + to_string(ipParts[1]) + "." + to_string(ipParts[2]) + "." + to_string(ipParts[3]);
}

void SubnetMaskDivide(string baseIP) {
    int baseCIDR;
    size_t cidrPos = baseIP.find("/");
    string ipAddress = baseIP.substr(0, cidrPos);
    if (!isValidIP(ipAddress)) {
        cout << "Unavailable: The provided IP address is invalid." << endl;
        return;
    }
    baseCIDR = stoi(baseIP.substr(cidrPos + 1));

    int numCustomers;
    cout << "Enter the number of customers: ";
    cin >> numCustomers;

    int customerNeeds[numCustomers];
    cout << "Enter the number of IPs needed for each customer:\n";
    for (int i = 0; i < numCustomers; i++) {
        cout << "Customer " << i + 1 << ": ";
        cin >> customerNeeds[i];
    }

    int baseOffset = 0;
    cout << "\nSubnet Allocation:\n";
    cout << "-----------------------------------------------------" << endl;

    for (int i = 0; i < numCustomers; i++) {
        int neededIPs = customerNeeds[i];
        int prefix = calculatePrefix(neededIPs);
        int blockSize = 1 << (32 - prefix);

        string networkAddress = calculateNetworkAddress(ipAddress, baseOffset);

        if (networkAddress.empty()) {
            cout << "Error: IP address exceeds valid range." << endl;
            continue;
        }

        string broadcastAddress = calculateBroadcastAddress(networkAddress, blockSize);
        pair<string, string> hostRange = calculateHostRange(networkAddress, blockSize);

        if (broadcastAddress == "Unavailable") {
            cout << left << setw(10) << "Customer " + to_string(i + 1) << ": " << setw(20) << networkAddress + "/" + to_string(prefix)
                 << setw(35) << hostRange.first + " - " + hostRange.second
                 << "Unavailable (Broadcast exceeds range)" << "\n";
            continue;
        }
        cout << left << setw(10) << "Customer " + to_string(i + 1) << ": " << setw(20) << networkAddress + "/" + to_string(prefix)
             << setw(35) << hostRange.first + " - " + hostRange.second << broadcastAddress << "\n";

        baseOffset += blockSize;
    }
    cout << "-----------------------------------------------------------" << endl;
}
