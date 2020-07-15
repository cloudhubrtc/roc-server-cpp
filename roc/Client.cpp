//
// Created by Jack on 2020/7/15.
//

#include "Client.h"

#include <utility>

string Client::getToken(const string &channelName, const string &userId, int expireTime) {
    MD5 md5;
    string bodyStr =
            _authKey + "authkey" + _authKey + "channame" + channelName + "timestamp" + std::to_string(expireTime) +
            "userid" + userId;
    string encodeBody = md5.digestString((char *) (bodyStr).data());
    string encodeSecret = md5.digestString((char *) _secretKey.data());
    string secToken = md5.digestString((char *) (encodeBody + encodeSecret).data());

    string tokenJson = "{\"token\":\"" + secToken + "\",\"timestamp\":" + std::to_string(expireTime) + "}";

    return base64EncodeString(tokenJson);
}

Client::Client(string authKey, string secretKey) {
    _authKey = std::move(authKey);
    _secretKey = std::move(secretKey);
}

std::string base64EncodeString(const std::string &strString) {
    int nByteSrc = strString.length();
    std::string pszSource = strString;

    int i = 0;
    for (i = 0; i < nByteSrc; i++)
        if (pszSource[i] < 0 || pszSource[i] > 127)
            throw "can not encode Non-ASCII characters";

    const char *enkey = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string pszEncode(nByteSrc * 4 / 3 + 4, '\0');
    int nLoop = nByteSrc % 3 == 0 ? nByteSrc : nByteSrc - 3;
    int n = 0;
    for (i = 0; i < nLoop; i += 3) {
        pszEncode[n] = enkey[pszSource[i] >> 2];
        pszEncode[n + 1] = enkey[((pszSource[i] & 3) << 4) | ((pszSource[i + 1] & 0xF0) >> 4)];
        pszEncode[n + 2] = enkey[((pszSource[i + 1] & 0x0f) << 2) | ((pszSource[i + 2] & 0xc0) >> 6)];
        pszEncode[n + 3] = enkey[pszSource[i + 2] & 0x3F];
        n += 4;
    }

    switch (nByteSrc % 3) {
        case 0:
            pszEncode[n] = '\0';
            break;

        case 1:
            pszEncode[n] = enkey[pszSource[i] >> 2];
            pszEncode[n + 1] = enkey[((pszSource[i] & 3) << 4) | ((0 & 0xf0) >> 4)];
            pszEncode[n + 2] = '=';
            pszEncode[n + 3] = '=';
            pszEncode[n + 4] = '\0';
            break;

        case 2:
            pszEncode[n] = enkey[pszSource[i] >> 2];
            pszEncode[n + 1] = enkey[((pszSource[i] & 3) << 4) | ((pszSource[i + 1] & 0xf0) >> 4)];
            pszEncode[n + 2] = enkey[((pszSource[i + 1] & 0xf) << 2) | ((0 & 0xc0) >> 6)];
            pszEncode[n + 3] = '=';
            pszEncode[n + 4] = '\0';
            break;
    }

    return pszEncode;
}
