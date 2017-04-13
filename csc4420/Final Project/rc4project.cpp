#include <iostream>
#include <string>
#include <fstream>
#include "rc4_enc.c"
#include "rc4_skey.c"
using namespace std;

#define KEY "testkeylol"
#define KEY_LENGTH (sizeof(KEY)-1)

void decodeAndEncode(char *argv[]);

int main(int argc, char *argv[]){
	if(argc < 2){
		cerr << "Error: File name not specified.";
		return 0;}
	if(argc > 2){
		cerr << "Error: Too many arguments.";
		return 0;}
	decodeAndEncode(argv);
	return 0;}

void decodeAndEncode(char* argv[]){
	ifstream ifs(argv[1]);
        string data((istreambuf_iterator<char>(ifs)),
                (istreambuf_iterator<char>()));
        ofstream ouf;
	ouf.open(argv[1], ios::binary);
        RC4_KEY key;
        int datalen = data.size();
        unsigned char *buffer = (unsigned char*)malloc(datalen + 1);
        memset(buffer, 0, datalen + 1);
        RC4_set_key(&key, KEY_LENGTH, (const unsigned char*)KEY);
        RC4(&key, datalen, (const unsigned char*)data.c_str(), buffer);
        string ret((char*)buffer, datalen);
        free(buffer);
        ouf.clear();
        ouf << ret;
        ouf.close();}
