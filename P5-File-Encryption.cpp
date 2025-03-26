#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void encryptFile(const string &filename, int key) {
    ifstream inputFile(filename, ios::binary);
    if (!inputFile) {
        cout << "Error: Unable to open file!\n";
        return;
    }

    string encryptedFilename = filename + ".enc";
    ofstream outputFile(encryptedFilename, ios::binary);
    if (!outputFile) {
        cout << "Error: Unable to create encrypted file!\n";
        return;
    }

    char ch;
    while (inputFile.get(ch)) {
        ch = ch ^ key;
        outputFile.put(ch);
    }

    inputFile.close();
    outputFile.close();
    cout << "File encrypted successfully! Saved as " << encryptedFilename << endl;
}

void decryptFile(const string &filename, int key) {
    ifstream inputFile(filename, ios::binary);
    if (!inputFile) {
        cout << "Error: Unable to open file!\n";
        return;
    }

    string decryptedFilename = "decrypted_" + filename;
    ofstream outputFile(decryptedFilename, ios::binary);
    if (!outputFile) {
        cout << "Error: Unable to create decrypted file!\n";
        return;
    }

    char ch;
    while (inputFile.get(ch)) {
        ch = ch ^ key;
        outputFile.put(ch);
    }

    inputFile.close();
    outputFile.close();
    cout << "File decrypted successfully! Saved as " << decryptedFilename << endl;
}

int main() {
    int choice;
    string filename;
    int key;

    while (true) {
        cout << "\n1. Encrypt File\n2. Decrypt File\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter file name to encrypt: ";
                cin >> filename;
                cout << "Enter encryption key (numeric): ";
                cin >> key;
                encryptFile(filename, key);
                break;
            case 2:
                cout << "Enter file name to decrypt: ";
                cin >> filename;
                cout << "Enter decryption key (same as encryption key): ";
                cin >> key;
                decryptFile(filename, key);
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
