#include <iostream>
#include <string>
#include "roc/Client.h"

using namespace std;

int main() {


    string authKey = "WbykCN****8pwd3";
    string secretKey = "23423****dfsfs";
    Client client(authKey, secretKey);

    string channelName = "1234567****shao";
    string userId = "159****91766-10**26";
    int expireTime = 1594704891;

    string token = client.getToken(channelName, userId, expireTime);

    cout << "token:" << token << endl;
    return 0;
}
