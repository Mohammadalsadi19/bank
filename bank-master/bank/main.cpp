    #include <iostream>
    #include <string>
    #include <fstream>
    #include <algorithm>

    using namespace std;

    class User {
    private:
        string UID;
        string name;
        enum card { silver, gold, diamond };
        bool gender;
        float balance;
        float normalBalance;
        string password;

    public:
        string fetchData() {
            ifstream get("data.txt");
            User user[10];
            string data;
            while (getline(get, data)) {
                cout << data << endl;
            }
            return data;
        }
        void setData(string addedData) {
            ofstream set("data.txt");
            set << addedData << endl;
        }
        User() {
            fetchData();
            bool acc;
            cout << "Do You Have an account: (0/1)";
            cin >> acc;
            if (acc) {
                login();
            }
            else {
                create();
            }

        }
        bool checkCredentials(string EUID, string Epassword) {
            cout << "Debug: EUID=" << EUID << " Epassword=" << Epassword
                << " UID=" << UID << " password=" << password << endl;
            return (EUID == UID && Epassword == password);
        }


        bool create() {
            string data;
            UID = to_string(rand() % 90000 + 9999);
            cout << "Enter your name: ";
            cin >> name;
            cout << "if u r male enter 1, if u r female enter 0: ";
            cin >> gender;
            cout << "Set Your Password: ";
            cin >> password;
            cout << "enter your initial balance : ";
            cin >> balance;
            data = UID + " " + name + " " + to_string(gender) + " " + password + " " + to_string(balance);
            setData(data);
            return 1;
        }


        bool login() {
            string EUID;
            string Epassword;
            cout << "Enter Your ID";
            cin >> EUID;
            cout << "Enter Your Password";
            cin >> Epassword;
            if (checkCredentials(EUID, Epassword)) {
                cout << "Your Are Logged In";
                return 1;
            }
            else {
                cout << "Try Again!" << endl;
                login();
            }
        }

        bool withdraw(float amount) {
            if (amount <= balance) {
                if ((int)amount % 5 == 0) {
                    cout << "pull your card please";
                    balance -= amount;
                    return 1;
                }
            }
            else return 0;
        }
        void deposit(float amount) {
            cout << "pull your card please";
            balance += amount;
        }
        float checkBalance() {
            return balance;
        }
    };


    int main()
    {
        srand(time(0));
        User user[50];
        return 0;
    }