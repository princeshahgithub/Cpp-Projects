#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void processFile(const string &inputName, const string &outputName, int key) {
    ifstream inputFile(inputName, ios::binary);
    ofstream outputFile(outputName, ios::binary);

    if (!inputFile || !outputFile) {
        cerr << "Error: File access failure." << endl;
        return;
    }

    const size_t BUFFER_SIZE = 64 * 1024;
    vector<char> buffer(BUFFER_SIZE);

    while (inputFile.read(buffer.data(), BUFFER_SIZE) || inputFile.gcount() > 0) {
        streamsize bytesRead = inputFile.gcount();
  
        for (streamsize i = 0; i < bytesRead; ++i) {
            buffer[i] ^= key;
        }
        
        outputFile.write(buffer.data(), bytesRead);
    }

    inputFile.close();
    outputFile.close();
    cout << "Transformation complete: " << outputName << endl;
}

int main() {
    int choice;
    string filename;
    int key;

    while (true) {
        cout << "\n1. Encrypt File\n2. Decrypt File\n3. Exit\nEnter choice: ";
        if (!(cin >> choice)) break;

        if (choice == 3) return 0;

        cout << "Enter file name: ";
        cin >> filename;
        cout << "Enter numeric key: ";
        cin >> key;

        if (choice == 1) {
            processFile(filename, filename + ".enc", key);
        } else if (choice == 2) {
            processFile(filename, "decrypted_" + filename, key);
        } else {
            cout << "Invalid choice." << endl;
        }
    }
    return 0;
}
