#include <iostream>
#include <cstring>
#include "file_encoder.h"
#include "file_decoder.h"
#include "file_exceptions.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 4 || (strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-e") != 0)) {
        cout
                << "Arguments have wrong format. \nWrite \"-e input_file output_file\" for encoding \nWrite \"-d input_file output_file\" for decoding";
    } else {
        try {
            if (strcmp(argv[1], "-d") == 0) {
                file_decoder dec(argv[2], argv[3]);
                dec.decode_all();
            } else {
                file_encoder enc(argv[2], argv[3]);
                enc.encode_all();
            }
        } catch (exception e) {
            cout << e.what();
        }
    }
}

