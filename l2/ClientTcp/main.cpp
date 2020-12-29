#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <sstream>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <math.h>
#include <vector>
#include <sstream>

using namespace std;

vector<int> merge(vector<int>, vector<int>);
vector<int> slice(vector<int>, int, int);
vector<int> mergeSort(vector<int>);

void printVector(vector<int> vec) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << "\n";
}

vector<int> fromStringToVector(string str) {
    vector<int> result(0);
    int start = 0;
    int end = 0;
    for (unsigned int i = 0; i < str.length(); i++) {
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
    for (unsigned int i = 0; i < vec.size(); i++) {
        if ( i != 0) str += " ";
        str += to_string(vec[i]);
    }

    return str;
}

int main(){

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in address;


		address.sin_family = AF_INET;
	    string ip;
	    cout << "enter ip address: ";
	    cin >> ip;
	    address.sin_addr.s_addr = inet_addr(ip.c_str());
	    int port;
	    cout << "enter port: ";
	    cin >> port;
	    cout << "\n";
	    address.sin_port = htons(port);

	    bind(sock, (struct sockaddr *) &address, sizeof(address));
	    listen(sock, 1);

	    int size = sizeof(address);

	    int connection = accept(sock, (sockaddr*)&address, (socklen_t*)&size);

	    int msg_size;
	    recv(connection, (char*)&msg_size, sizeof(int), 0);
	    char* msg = new char[msg_size + 1];
	    msg[msg_size] = '\0';
	    recv(connection, msg, msg_size, 0);

	    unsigned int startTime = clock();

	    vector<int> initial = fromStringToVector(string(msg));

	    cout << "initial vector: ";
	    //printVector(initial);
	    delete msg;

	    vector<int> sorted = mergeSort(initial);

	    unsigned int endTime = clock();

	    cout << "sorted vector: ";
	    printVector(sorted);

	    cout << "calculation time: " << endTime - startTime << "\n";

	    string result = fromVectorToString(sorted);
	    int res_size = result.length();
	    send(connection, (char*)&res_size, sizeof(int), 0);
	    send(connection, result.c_str(), res_size, 0);

	    cout << "resp has been sent" << "\n";

	    string a;
	    cin >> a;


	    return 0;
}

vector<int> merge(vector<int> left, vector<int> right) {
    vector<int> resultVector(0);
    int leftIndex = 0, rightIndex = 0;

    while (leftIndex < left.size() && rightIndex < right.size()) {
        if (left[leftIndex] < right[rightIndex]) {
            resultVector.push_back(left[leftIndex]);
            leftIndex++;
        }
        else {
            resultVector.push_back(right[rightIndex]);
            rightIndex++;
        }
    }
    while (leftIndex < left.size()) {
        resultVector.push_back(left[leftIndex]);
        leftIndex++;
    }
    while (rightIndex < right.size()) {
        resultVector.push_back(right[rightIndex]);
        rightIndex++;
    }

    return resultVector;
}

vector<int> slice(vector<int> vectorToSlice, int from, int to) {
    vector<int> newVector(0);
    for (int i = from; i < to; i++) {
        newVector.push_back(vectorToSlice[i]);
    }

    return newVector;
}

vector<int> mergeSort(vector<int> vec) {
    if (vec.size() <= 1) return vec;

    int middle = vec.size() / 2;
    vector<int> left = slice(vec, 0, middle);
    vector<int> right = slice(vec, middle, vec.size());

    return merge(mergeSort(left), mergeSort(right));
}
