#include <iostream>
#include <stdlib.h>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <exception>
#include <stdexcept>
enum {
    ERROR_INVALID_ARGS = 1,
    ERROR_APPEND
};
using namespace std;

string url_encode(const string& value) {
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;
    for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
        string::value_type c = (*i);

        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }
        escaped << uppercase;
        escaped << '%' << setw(2) << int((unsigned char)c);
        escaped << nouppercase;
    }

    return escaped.str();
}

int main(int argc, char* argv[])
{
    int i = 1;
    string arg;
    if (argc == 1) {
        cout << "Not enough arguments provided";
        throw std::invalid_argument("Not enough arguments provided");
        return ERROR_INVALID_ARGS;
    }
    while (argv[i] != NULL) {
        if (argv[i + 1] == NULL) {
            try {
                arg.append(string(argv[i]));
            }
            catch (const std::exception& e) {
                cout << "Exception in append: " << e.what();
                return ERROR_APPEND;
            }
            
        }
        else {
            try {
                arg.append(string(argv[i])).append(" ");
            }
            catch (const std::exception& e) {
                cout << "Exception in append" << e.what();
                return ERROR_APPEND;
            }
            
        }
        i++;
    }
    arg = url_encode(arg);
    string cmd = string("start ").append("https://www.google.com/search?q=").append(arg);


    

    std::system(cmd.c_str());
}
