#include<bits/stdc++.h>
#include "BasicCalculation.hpp"
#include "BasicSubnetting.hpp"
#include "DivideIP.hpp"
using namespace std;


int main()
{
    string ipStr;
    string maskStr;
    cout<<"Enter IP Address (e.g., 192.168.0.106): ";
    cin>>ipStr;
    cout<<"Enter Subnet mask (e.g., 255.255.255.128): ";
    cin>>maskStr;
    basicDisplay(ipStr,maskStr);

    cout<<"--------------------------------------------------"<<endl<<endl;
    string ip;
    cout<<"Enter IP address with CIDR notation for Subnetting.as(192.168.0.157/22):";
    cin>>ip;
    SubnetMaskDivide(ip);
    cout<<"-----------------------------------------"<<endl<<endl;
    cout << "DEnter IP address with CIDR notation: (e.g 192.168.0.4/28): ";
    string ipD;
    cin >> ipD;
    divideIP_follow_cidr(ipD);
    return 0;
}