#include "transaction.hpp"

void transaction(const std::string& username, const std::string & password, double& balance, bool& isSendPressed, string& pass, string& user, string& sum, string& dataFolderPath) {
        
        string usernameFromFile, balanceFromFile;   
        fstream Usernames, Balances;
        double tempBal;
        if (isSendPressed) {
            if (pass == password) {
                if (user == username) {
                    cout << "You can't send money to yourself." << endl;
                }
                else {
                    if (balance > stod(sum)) {
                        Usernames.open(dataFolderPath + "/usernames.txt", ios::in);
                        Balances.open(dataFolderPath + "/balances.txt", ios::in | ios::out);
                        balance -= stod(sum);
                        while (getline(Usernames, usernameFromFile) && getline(Balances, balanceFromFile))
                        {
                            tempBal = stod(balanceFromFile);
                            //if (usernameFromFile == username) {
                            //    Balances << balance;
                            //}
                            if (usernameFromFile == user) {
                                cout << "Entered Username: " << username << endl;
                                cout << "Entered Balance: " << balance << endl;
                                tempBal += stod(sum);
                                balanceFromFile = to_string(tempBal);
                                Balances << balanceFromFile;
                                Usernames.close();
                                Balances.close();
                                isSendPressed = false;
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
