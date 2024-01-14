#include "transaction.hpp"

void transaction(const std::string& username, const std::string& password, double& balance, bool& isSendPressed, string& pass, string& user, string& sum, string& dataFolderPath) {

    string usernameFromFile, balanceFromFile;
    fstream Usernames, Balances;
    bool check1 = false, check2 = false;
    double tempBal;
    if (isSendPressed) {
        if (pass == password) {
            if (user == username) {
                cout << "You can't send money to yourself." << endl;
            }
            else {
                if (balance > stod(sum)) {
                    Usernames.open(dataFolderPath + "/usernames.txt", ios::in);
                    Balances.open(dataFolderPath + "/balances.txt", ios::app);
                    balance -= stod(sum);
                    while (getline(Usernames, usernameFromFile) && getline(Balances, balanceFromFile))
                    {
                        tempBal = stod(balanceFromFile);

                        if (usernameFromFile == username && !check1) {
                            cout << balance;
                            if (Balances.is_open())
                                Balances << balance;
                        }
                        else if (usernameFromFile == user && !check2) {
                            tempBal += stod(sum);
                            balanceFromFile = to_string(tempBal);
                            cout << balanceFromFile;
                            if(Balances.is_open())
                                Balances << balanceFromFile;
                        }
                        else if (usernameFromFile == "") {
                            cout << "Non existing username" << endl;
                            isSendPressed = false;
                        }
                        else if (check1 && check2) {
                            Usernames.close();
                            Balances.close();
                            isSendPressed = false;
                            break;
                        }
                    }
                    Usernames.close();
                    Balances.close();
                    isSendPressed = false;
                }
                else {
                    cout << "Not enough money to make this transaction!" << endl;
                    isSendPressed = false;
                }
            }
        }
        else {
            cout << "Wrong password!!" << endl;
            isSendPressed = false;
        }
    }
}