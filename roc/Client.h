//
// Created by Jack on 2020/7/15.
//
#include<string>
#include <time.h>
#include "md5.h"

#ifndef ROC_SERVER_CPP_CLIENT_H
#define ROC_SERVER_CPP_CLIENT_H

using namespace std;

std::string base64EncodeString(const std::string &strString);

std::string rand_str(int len);


class Client {
public:
    string getToken(const string& channelName, const string& userId, int expireTime);

    Client(string authKey, string secretKey);

private:
    string _authKey;
    string _secretKey;

};


#endif //ROC_SERVER_CPP_CLIENT_H
