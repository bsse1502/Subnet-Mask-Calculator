#include<bits/stdc++.h>
#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

string expandIPv6(const string& compressed) {
    stringstream ss;
    string segment;
    vector<string> segments;
    int emptyIndex = -1;
    
    for (int i = 0; i < compressed.size(); ++i) {
        if (compressed[i] == ':') {
            if (i > 0 && compressed[i-1] == ':') {
                emptyIndex = segments.size();
            } else {
                segments.push_back(segment);
                segment.clear();
            }
        } else {
            segment += compressed[i];
        }
    }
    segments.push_back(segment);
    while (segments.size() < 8) {
        if (emptyIndex == -1) segments.push_back("0000");
        else segments.insert(segments.begin() + emptyIndex, "0000");
    }

    for (auto &seg : segments) {
        while (seg.size() < 4) seg = "0" + seg;
        ss << seg << ":";
    }
    string expanded = ss.str();
    return expanded.substr(0, expanded.size() - 1); 
}

string ipv6ToBinary(const string& ipv6) {
    string expanded = expandIPv6(ipv6);
    stringstream binary;
    string segment;
    stringstream ss(expanded);
    while (getline(ss, segment, ':')) {
        unsigned int segVal = stoi(segment, nullptr, 16);
        binary << bitset<16>(segVal);
    }
    return binary.str();
}

string getNetworkAddress(const string& ipv6, int prefixLength) {
    string binaryIPv6 = ipv6ToBinary(ipv6);
    string networkBinary = binaryIPv6.substr(0, prefixLength);
    networkBinary += string(128 - prefixLength, '0');

    stringstream networkIPv6;
    for (int i = 0; i < 128; i += 16) {
        bitset<16> segment(networkBinary.substr(i, 16));
        networkIPv6 << hex << segment.to_ulong();
        if (i < 112) networkIPv6 << ":";
    }
    return networkIPv6.str();
}



