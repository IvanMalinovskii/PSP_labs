// sending_client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <winsock2.h>
#include <vector>
#include <string>

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996)

using namespace std;

void printVector(vector<int> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << "\n";
}

vector<int> fromStringToVector(string str) {
    vector<int> result(0);
    int start = 0;
    int end = 0;
    for (int i = 0; i < str.length(); i++) {
        if (!isspace(str[i])) end = i;
        else {
            string numberString = str.substr(start, end - start + 1);
            result.push_back(atoi(numberString.c_str()));
            start = i + 1;
        }
    }
    string numberString = str.substr(start);
    result.push_back(atoi(numberString.c_str()));

    return result;
}
string fromVectorToString(vector<int> vec) {
    string str;
    for (int i = 0; i < vec.size(); i++) {
        if (i != 0) str += " ";
        str += to_string(vec[i]);
    }

    return str;
}
sockaddr_in createAddress(string ip, int port) {
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr(ip.c_str());

    return address;
}

vector<sockaddr_in> createAddresses() {
    vector<sockaddr_in> addresses(0);

    addresses.push_back(createAddress("127.0.0.1", 3000));

    return addresses;
}

int main()
{
    WSADATA wsadata;

    vector<SOCKET> sockets(0);

    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
        std::cout << "startap error: " << WSAGetLastError << "\n";
        return 1;
    }
    vector<sockaddr_in> addresses = createAddresses();
    cout << addresses.size();
    for (int i = 0; i < addresses.size(); i++) {
        SOCKET sock;

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
            std::cout << "socket error: " << WSAGetLastError << "\n";
            return 1;
        }
        sockaddr_in address = addresses[i];
        connect(sock, (SOCKADDR*)&address, sizeof(address));

        vector<int> vec = { 5, 3, 6, 8, 2, 1, 5 };
        string str = fromVectorToString(vec);

        int res_size = str.length();
        send(sockets[i], (char*)&res_size, sizeof(int), 0);
        send(sockets[i], str.c_str(), res_size, 0);

        cout << "message[" << i << "] has been sent";

        sockets.push_back(sock);
    }

    int msg_size;
    recv(sockets[0], (char*)&msg_size, sizeof(int), 0);
    char* msg = new char[msg_size + 1];
    msg[msg_size] = '\0';
    recv(sockets[0], msg, msg_size, 0);

    vector<int> result = fromStringToVector(string(msg));

    cout << "result vector: ";
    printVector(result);

    string a;
    cin >> a;
}
