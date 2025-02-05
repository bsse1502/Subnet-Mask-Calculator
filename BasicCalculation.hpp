#include <bits/stdc++.h>
using namespace std;

vector<string> split(string str, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
bool checkAddress(string str)
{
    vector<string> octets = split(str, '.');
    bool flag = true;
    int length = 0;
    for (string &octet : octets)
    {
        int num = stoi(octet);
        if (num > 255)
        {
            flag = false;
        }
        length++;
    }
    if (length > 4)
        flag = false;
    return flag;
}
int maskStrToCidr(string maskStr)
{
    vector<string> octets = split(maskStr, '.');
    int cidr = 0;
    for (string &octet : octets)
    {
        int num = stoi(octet);
        while (num > 0)
        {
            cidr += num & 1;
            num >>= 1;
        }
    }
    return cidr;
}
void strToHex(string str)
{
    vector<string> octets = split(str, '.');
    for (size_t i = 0; i < octets.size(); i++)
    {
        stringstream hexStream;
        hexStream << hex << uppercase << stoi(octets[i]);
        string hexValue = hexStream.str();
        if (hexValue.length() == 1)
        {
            hexValue = "0" + hexValue;
        }
        cout << hexValue;
        if (i != octets.size() - 1)
        {
            cout << ".";
        }
    }
    cout << endl;
}
void strToBinary(string str)
{
    vector<string> octets = split(str, '.');
    for (size_t i = 0; i < octets.size(); ++i)
    {
        int num = stoi(octets[i]);
        string binary = "";
        for (int j = 7; j >= 0; --j)
        {
            binary += (num & (1 << j)) ? '1' : '0';
        }
        cout << binary;
        if (i != octets.size() - 1)
        {
            cout << ".";
        }
    }
    cout << endl;
}
vector<int> calculateWildcardMask(const string &maskStr)
{
    vector<int> mask;
    stringstream ss(maskStr);
    string segment;
    
    while (getline(ss, segment, '.'))
    {
        mask.push_back(stoi(segment));
    }

    vector<int> wildcardMask(4, 0);
    for (int i = 0; i < 4; i++)
    {
        int maskPart = mask[i];
        int wildcardPart = 0;

        for (int bit = 7; bit >= 0; bit--)
        {
            int maskBit = (maskPart >= (1 << bit)) ? 1 : 0;
            int wildcardBit = (maskBit == 1) ? 0 : 1;
            wildcardPart += wildcardBit * (1 << bit);
            if (maskBit == 1)
            {
                maskPart -= (1 << bit);
            }
        }
        wildcardMask[i] = wildcardPart;
    }
    return wildcardMask;
}
void basicDisplay(string ipStr, string maskStr)
{
    if (checkAddress(ipStr))
        cout << "IP Address : " << ipStr << endl;
    else
    {
        cout << "Invalid IP Address" << endl;
        return;
    }
    if (checkAddress(maskStr))
        cout << "Subnet mask: " << maskStr << endl;
    else
    {
        cout << "Invalid Subnet mask" << endl;
        return;
    }

    cout << "IP Address with cidr: " << ipStr << "/" << maskStrToCidr(maskStr) << endl;
    cout << "IP Address of Hexadecimal: ";
    strToHex(ipStr);
    cout << "Subnet Mask of Hexadecimal: ";
    strToHex(maskStr);
    cout << "IP Address of Binary: ";
    strToBinary(ipStr);
    cout << "Subnet Mask of Binary: ";
    strToBinary(maskStr);
    vector<int> wildcardMask = calculateWildcardMask(maskStr);
    cout << "Wildcard Mask: ";
    for (size_t i = 0; i < wildcardMask.size(); i++)
    {
        cout << wildcardMask[i];
        if (i < wildcardMask.size() - 1)
        {
            cout << ".";
        }
    }
    cout << endl;

}
