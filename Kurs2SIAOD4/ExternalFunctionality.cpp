#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class ExtFunc
{
public:
    void convertFileToBinary() {
        FILE* input = fopen("C:\\Users\\sony\\Desktop\\OOPC++\\Kurs2SIAOD4\\Input.txt", "r"), * output = fopen("Output.bin", "w");
        if ((input != NULL) && (output != NULL))
        {
            while (!feof(input))
            {
                fread(check, 1, 1, input);
                fwrite(check, 1, 1, output);
            }
            fclose(output);
            fclose(input);
            cout << "Converted.\n";
        }
        else
            cout << "Can not find data file\n";
    }

    void findByKey(string key) {
        string line;
        ifstream input("Output.bin");
        if (!input.is_open())
            cout << "Can not find binary file\n";
        else
        {
            cout << "Results of search:\n";
            while (!input.eof())
            {
                getline(input, line);
                if (checkKey(key, line)) { cout << line << endl; }
            }
            cout << "End.\n";
            input.close();
        }
    }


    void updateByKey(string key, string adress, string fullName) {
        string line;
        ifstream input("Output.bin");
        ofstream output("Output2.bin");
        bool checker = false;
        if (!input.is_open())
            cout << "Can't find binary file\n";
        else
        {
            while (!input.eof())
            {
                getline(input, line);
                if (!checkKey(key, line)) { output << line << "\n"; }
                else {
                    output << key << " " << adress << " " << fullName << "\n";
                    checker = true;
                }
            }
            input.close();
            output.close();

            if (remove("Output.bin")) {
                cout << "can not remove\n";
            }
            else if (rename("Output2.bin", "Output.bin")) {
                cout << "Can not rename\n";
            }
            else {
                remove("Output2.bin");
                if (checker)
                    cout << "Data updated.\n";
                else
                    cout << "Can not find.\n";
            }
        }
    }

    void printFileResolt() {
        FILE* input;
        input = fopen("Output.bin", "r");
        if (input != NULL)
        {
            cout << "Binary file:\n";
            while (!feof(input))
            {
                fread(check, 1, 1, input);
                cout << check[0];
            }
            fclose(input);
            cout << "\nEnd.\n";
        }
        else
            cout << "Can not find binary file\n";
    }

    int startProgram(){
        Card record;
        while (true)
        {
            int codeCommand=6;
            cin >> codeCommand;
            switch (codeCommand)
            {
                case(1):
                    convertFileToBinary();
                    break;
                case(2):
                    printFileResolt();
                    break;
                case(3):
                    cout << "Enter key(number library card), address and FIO (street,num,num and data)\n";

                    cin.ignore();
                    getline(cin, record.key);

                    if (record.key.length() < 5) {
                        cout << "Not the correct key\n"; break;
                    }

                    getline(cin, record.address);
                    getline(cin, record.FIO);

                    updateByKey(record.key, record.address, record.FIO);
                    break;
                case(4):
                    cout << "Enter key(number library card)\n";
                    cin >> record.key;

                    if (record.key.length() < 5) {
                        cout << "Not the correct key\n";
                        break;
                    }

                    findByKey(record.key);
                    break;
                case(5):
                    if (remove("Output.bin")) {
                        cout << "Can not remove\n";
                    }
                    else {
                        cout << "Delete.\n";
                    }
                    break;
                case(6):
                    cout << "Completed\n";
                    return 0;
                default:
                    cout << "Not the correct command.\n";
                    break;
            }
        }
    }
private:
    struct Card {
        string key = "";
        string FIO = "";
        string address = "";
    };
    char check[0];

    bool checkKey(string key, string line) {
        int i = 0;
        for (i; i < 5; ++i)
        {
            if (key[i] != line[i]) {
                break;
            }
        }
        return i == 5;
    }
};


