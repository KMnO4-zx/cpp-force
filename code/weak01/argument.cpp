// argument.cpp

#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {
    cout << "Number of arguments: " << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << i << ": " << argv[i] << endl;
    }
    return 0;
}