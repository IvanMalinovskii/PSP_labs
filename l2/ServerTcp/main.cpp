#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <vector>
#include <thread>
#include <cstring>
#include <chrono>

using namespace std;


vector<int> merge(vector<int>, vector<int>);

void printVector(vector<int> vec) {

	for (int i = 0; i < vec.size(); i++) {

	cout << vec[i] << " ";

	}

	cout << "\n";

}

vector<int> slice(vector<int> vectorToSlice, int from, int to) {

	vector<int> newVector(0);

	for (int i = from; i < to; i++) {

	newVector.push_back(vectorToSlice[i]);

	}

	return newVector;

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

	addresses.push_back(createAddress("127.0.0.1", 3001));

	return addresses;

}

vector<int> createParts(int vectorSize, int count) {

	vector<int> parts(count);

	int inOnePart = vectorSize / count;

	int mod = vectorSize % count;

	for (int i = 0; i < count; i++) {

	parts[i] = inOnePart;

	if (mod != 0) {

	parts[i]++;

	mod--;

	}

	}

	return parts;

}


int main(){

		std::vector<int> sockets;

		vector<sockaddr_in> addresses = createAddresses();

		string initial;

		/*cout << "enter unsorted vector: ";

		getline(cin, initial);*/

		ifstream file("vector.txt");

		string str;

		if (file.is_open()) {

		while (getline(file, str)) {

		initial += " " + str;

		}

		file.close();

		}

		else {

		cout << "ERR";

		return -1;

		}

		cout << "string: " << initial << "\n\n\n";

		unsigned int startTime = clock();

		vector<int> unsorted = fromStringToVector(initial);

		printVector(unsorted);

		vector<int> parts = createParts(unsorted.size(), addresses.size());

		for (int i = 0; i < addresses.size(); i++) {

		int sock = socket(AF_INET, SOCK_STREAM, 0);

		vector<int> vec;

		while (parts[i] != 0) {

		vec.push_back(unsorted[unsorted.size() - 1]);

		unsorted.pop_back();

		parts[i]--;

		}

		printVector(vec);

		if (sock == -1){
			        		std::cout << "Can not create a socket, try again" << std::endl;
			        		return -1;
			        }

		sockaddr_in address = addresses[i];

		connect(sock, (sockaddr*)&address, sizeof(address));

		string str = fromVectorToString(vec);

		int res_size = str.length();

		send(sock, (char*)&res_size, sizeof(int), 0);

		send(sock, str.c_str(), res_size, 0);

		cout << "message[" << i << "] has been sent"<< "\n";

		sockets.push_back(sock);

		}

		vector<int> merged(0);

		for (int i = 0; i < sockets.size(); i++) {

		int msg_size;

		recv(sockets[i], (char*)&msg_size, sizeof(int), 0);

		char* msg = new char[msg_size + 1];

		msg[msg_size] = '\0';

		recv(sockets[i], msg, msg_size, 0);

		vector<int> result = fromStringToVector(string(msg));

		cout << "result vector: ";

		printVector(result);

		merged = merge(merged, result);

		}

		unsigned int endTime = clock();

		cout << "\n" << "result merged vector: ";

		printVector(merged);

		cout << "caclulation time: " << endTime - startTime << "\n";

		string a;

		cin >> a;

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

