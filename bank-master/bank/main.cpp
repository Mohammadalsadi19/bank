#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

class User {
private:
    string UID;
    string name;
    string gender;
    string balance;
    string password;

public:
    User()
        : UID(""), name(""), gender(""), password(""), balance("") {}
    User(const string& UID, const string& name, const string& gender,
        const string& password, const string& balance)
        : UID(UID), name(name), gender(gender), password(password), balance(balance) {}

    void fetchData() {
        ifstream get("data.txt");
        string data;
        while (get >> UID >> name >> gender >> password >> balance) {
            //instanceOfUser.emplace_back();
            cout << "UID: " << UID << ", Name: " << name << ", Gender: " << gender << ", Balance: " << balance << endl;
            //cout << instanceOfUser.back().UID << instanceOfUser.back().name << instanceOfUser.back().password << endl;
        }
    }
    void setData(string addedData) {
        ofstream set("data.txt", ios::app);
        set << addedData << endl;
    }

    bool checkCredentials(const string& EUID, const string& Epassword) const {
        return (EUID == UID && Epassword == password);
    }

    bool create() {
        UID = to_string(rand() % 90000 + 9999);
        cout << "Enter your name: ";
        cin >> name;
        cout << "If you are male, enter 1. If you are female, enter 0: ";
        cin >> gender;
        cout << "Set Your Password: ";
        cin >> password;
        cout << "Enter your initial balance : ";
        cin >> balance;
        string data = UID + " " + name + " " + gender + " " + password + " " + balance;
        setData(data);
        return true;
    }
    bool withdraw(float amount) {
        float sbalance = stof(balance);
        if (amount <= stof(balance)) {
            if ((int)amount % 5 == 0) {
                cout << "Pull your card please" << endl;
                sbalance -= amount;
                balance = to_string(sbalance);
                return true;
            }
        }
        return false;
    }

    void deposit(float amount) {
        float sbalance = stof(balance);
        cout << "Pull your card please" << endl;
        sbalance += amount;
        balance = to_string(sbalance);
    }

    string checkBalance() {
        return balance;
    }
};

int main() {
    srand(time(0));
    vector<User> users;

    ifstream get("data.txt");
    string UID, name, gender, password, balance;
    while (get >> UID >> name >> gender >> password >> balance) {
        users.emplace_back(UID, name, gender, password, balance);
        cout << "UID: " << UID << ", Name: " << name << ", Gender: " << gender << ", Balance: " << balance << endl;
    }
    get.close();

    bool acc;
    User currentUser;  // Store the current user once logged in

    while (true) {
        cout << "Do You Have an account: (0/1)";
        cin >> acc;

        if (acc) {
            string EUID, Epassword;
            cout << "Enter Your ID: ";
            cin >> EUID;
            cout << "Enter Your Password: ";
            cin >> Epassword;

            bool loginSuccessful = false;
            for (auto& user : users) {
                if (user.checkCredentials(EUID, Epassword)) {
                    loginSuccessful = true;
                    cout << "Login successful!" << endl;
                    currentUser = user;  // Store the current user for further actions
                    break;
                }
            }

            if (!loginSuccessful) {
                cout << "Login failed. Invalid UID or password." << endl;
            }
            else {
                // Once logged in, provide a menu for actions
                int choice;
                while (true) {
                    cout << "1. Check Balance\n2. Deposit\n3. Logout\n4. Withdraw\nEnter your choice: ";
                    cin >> choice;

                    switch (choice) {
                    case 1:
                        cout << "Balance: " << currentUser.checkBalance() << endl;
                        break;
                    case 2:
                        float amount;
                        cout << "Enter the amount to deposit: ";
                        cin >> amount;
                        currentUser.deposit(amount);
                        cout << "Deposit successful. New balance: " << currentUser.checkBalance() << endl;
                        break;
                    case 4:
                        float amountw;                        
                        cout << "Enter the amount to withdraw: ";
                        cin >> amountw;
                        currentUser.withdraw(amountw);
                        break;
                    case 3:
                        // Logout and exit the inner loop
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }

                    if (choice == 3) {
                        break;  // Exit the inner loop when user chooses to logout
                    }
                }
            }
        }
    }

    return 0;
}
