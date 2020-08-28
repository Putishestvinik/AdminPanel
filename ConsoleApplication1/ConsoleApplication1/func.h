#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <array>
#include <vector>
#include <locale>
#include <fstream>
#include <streambuf>

using namespace std;

string CaesarIn(string buff) {
    for (int i = 0; i < buff.length(); i++)
        buff[i] += 3;
    return buff;
}

string CaesarOut(string buff) {
    for (int i = 0; i < buff.length(); i++)
        buff[i] -= 3;
    return buff;
}

void error(string er) {
    system("color 0C");
    cout << "\n" << er << "\n\n"; system("pause");
    system("color 07");
}

void good(string er) {
    system("color 0A");
    cout << "\n" << er << "\n\n"; system("pause");
    system("color 07");
}

string getPassword() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

    string word;
    cout << "Пароль(символы скрыты, после введения нажмите Enter): "; getline(cin, word);

    SetConsoleMode(hStdin, mode | ENABLE_ECHO_INPUT);
    return word;
}

bool findName(string n) {
    int count; bool check_user_ = false;
    ifstream fin("users.txt");
    if (!n.empty()) {
        if (fin.peek() == EOF) { return check_user_; }
        if (fin.is_open()) {
            fin >> count;
            if (count != 0) {
                string name, pass, adrs, number; int id;
                while (fin >> id >> name >> pass >> adrs >> number) {
                    if (n == CaesarOut(name)) { check_user_ = true; }
                }
            }
        }
    }
    fin.close();
    return check_user_;
}

void changePassR() {
    ifstream fin("admin.txt");
    if (fin.peek() == EOF) { error("You don't have permission to this function!"); }
    if (fin.is_open()) {
        string name, password, check_pass;
        fin >> name >> password; password = CaesarOut(password); cin.ignore();
        cout << "Cтарый "; check_pass = getPassword();
        if (password == check_pass) {
            cout << "\nВведите ваш новый "; check_pass = getPassword();
            if (check_pass != password) {
                fin.close();

                ofstream fout("admin.txt");
                fout << name << " " << CaesarIn(check_pass);
                fout.close(); good("Пароль изменен!");

                return;
            }
            else {
                error("Старый и новый пароли не могут совпадать!");
            }
        }
        else {
            error("Пароль который вы ввели не совпадает со старым паролем!");
        }
    }
    fin.close();
}