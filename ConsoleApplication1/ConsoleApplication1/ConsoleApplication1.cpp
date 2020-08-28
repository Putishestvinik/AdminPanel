#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <iomanip>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "func.h"
#pragma warning(disable : 4996)
using namespace std;

class Person {
    string name, address, number, check_pass; int id;
public:
    int getId() {
        return id;
    }
    string getName() {
        return name;
    }
    string getAddress() {
        return address;
    }
    string getNumber() {
        return number;
    }
    string getPass() {
        return check_pass;
    }
    void setId(int id) {
        this->id = id;
    }
    void setName(string name) {
        this->name = name;
    }
    void setAddress(string address) {
        this->address = address;
    }
    void setNumber(string number) {
        this->number = number;
    }
    void setPass(string password) {
        this->check_pass = password;
    }
};

class Tests {
public:
    string category; int count;
    multimap<int, string> questions;
    multimap<int, string> answers;
public:
    bool add() {
        bool is;
        if (!this->category.empty()) {
            cout << "Введите количество вопросов: "; cin >> count;
            if (count > 0) {
                for (int i = 0; i < count; i++) {
                    system("cls");
                    cout << "\n<-------- Question #" << i + 1 << "-------->\n";
                    string answer, question;  if (i == 0) { cin.ignore(); }
                    do {
                        cout << "Введите вопрос: "; getline(cin, question);
                        if (!question.empty()) {
                            do {
                                cout << "Введите ответ к вопросу: "; getline(cin, answer);
                                if (!answer.empty()) {
                                    questions.emplace(i, question);
                                    answers.emplace(i, answer);
                                    good("Вопрос успешно добавлен!");
                                }
                                else {
                                    error("Введите значение!");
                                }
                            } while (answer.empty());
                        }
                        else {
                            error("Введите значение!");
                        }
                    } while (question.empty());
                }
                return true;
            }
            else {
                error("Введите количество вопросов!");
            }

            return false;
        }
        else { return false; }
    }

    void show() {
        if (count != 0) {
            for (int i = 0; i < count; i++) {
                auto it = questions.find(i);
                auto iter = answers.find(i);
                cout << it->first << "\t" << it->second << " : " << iter->second << endl;
            }
        }
        else {
            error("Тесты ещё не были добавлены!");
        }
    }

    int quest() {
        int result = 0;
        for (int i = 0; i < count; i++) {
            auto it = questions.find(i);
            auto iter = answers.find(i); string answ;
            cout << it->first << "\t" << it->second << " : "; getline(cin, answ);
            if (answ == iter->second) { result++; }
            else { result--; }
        }
        return result;
    }

    void add(int id, string first, string second) {
        questions.emplace(id, first);
        answers.emplace(id, second);
    }

    void setS(int s) { count = s; }
    int getS() { return count; }
    void setCat(string category) {
        this->category = category;
    }
    string getCat() { return category; }
};

class Category {
private:
    vector<Tests> test; int size;
public:
    void sdacha_test(string User) {
        system("cls");

        ifstream file("test.txt");
        if (file.peek() != EOF) { this->load_without_messege(); }
        file.close();

        if (test.size() != 0) {
            cout << "Категории тестов: " << endl;
            for (auto it : test) {
                cout << "\t" << it.getCat() << endl;
            }

            string name; float result, s; bool check = false;
            cin.ignore(); cout << "\n\nВведите имя категории: "; getline(cin, name);
            if (!name.empty()) {
                system("cls");
                for (vector<Tests>::iterator it = test.begin(); it != test.end(); ++it) {
                    if (name == it->getCat()) { check = true; result = it->quest(); s = it->getS(); }
                }
                
                if (check == false) { error("Такой категории не существует!"); }
                else {
                    float fraction = (result / s) * 100;
                    if (fraction >= 0) { cout << "\nВаш результат: " << setprecision(3) << fraction << "%" << endl; }
                    else if (fraction < 0) { fraction = 0; good("Ваш результат: 0%"); }
                    this->save_results(User, name, fraction);
                }
            }

            
        }
        else {
            error("Тесты ещё не были добавлены!");
        }

    }

    void save_results(string username, string category, float result) {
        ofstream fout("results.txt", ios::app);
        if (fout.is_open()) {
            fout << CaesarIn(username) << " " << CaesarIn(category) << " " << result << endl;
        }
        good("Вы успешно сохранили свой результат!");
        fout.close();
    }

    void load_results(string username) {
        ifstream fin("results.txt"); string cat, user; float res; int i = 0; bool flag = false;
        cout << endl;
        if (fin.is_open()) {
            while (fin >> user >> cat >> res) {
                if (username == CaesarOut(user)) {
                    flag = true;
                    cout << "<--------- Тест #" << ++i << "--------->" << endl;
                    cout << "Категория: " << CaesarOut(cat) << endl;
                    cout << "Результат: " << res << "%" << endl;
                }
            }
        }

        if (flag == false) { error("Вы не сдавали ещё ни одного теста!"); }
        fin.close();
    }

    void add() {
        Tests temp;
        string name;
        cin.ignore(); cout << "Введите название категории: "; getline(cin, name);
        if (!name.empty()) {
            temp.setCat(name);
            if (temp.add()) {
                good("Категория была создана успешно!"); size++;
                test.push_back(temp);
            }
        }
        else { error("Заполните поле категории!"); }
    }

    void addTests() {
        string name; bool g;
        cin.ignore(); cout << "Введите название категории: "; getline(cin, name);
        if (!name.empty()) {
            for (vector<Tests>::iterator it = test.begin(); it != test.end(); ++it) {
                if (name == it->getCat()) {
                    this->show(name); g = true;
                    int numb; bool flag = false;
                    int temp;
                    cout << "Введите количество вопросов для добавления: "; cin >> temp;
                    if (temp > 0) {
                        for (int i = it->getS(); i < (it->getS() + temp); i++) {
                            system("cls");
                            cout << "\n<-------- Question #" << i + 1 << "-------->\n";
                            string answer, question; if (i == it->getS()) { cin.ignore(); }
                            do {
                                cout << "Введите вопрос: "; getline(cin, question);
                                if (!question.empty()) {
                                    do {
                                        cout << "Введите ответ к вопросу: "; getline(cin, answer);
                                        if (!answer.empty()) {
                                            it->questions.emplace(i, question);
                                            it->answers.emplace(i, answer);
                                            good("Вопрос успешно добавлен!");
                                        }
                                        else {
                                            error("Введите значение!");
                                        }
                                    } while (answer.empty());
                                }
                                else {
                                    error("Введите значение!");
                                }
                            } while (question.empty());
                        }
                        it->setS(it->getS() + temp);
                    }
                    else {
                        error("Введите количество вопросов!");
                    }
                }
            }
        }
        else {
            error("Вы не ввели имя категории");
        }

        if (g == false) { error("Такой категории не существует!"); }
    }

    void edit() {
        string name; bool g = false;
        cin.ignore(); cout << "Введите название категории: "; getline(cin, name);
        if (!name.empty()) {
            for (vector<Tests>::iterator it = test.begin(); it != test.end(); ++it) {
                if (name == it->getCat()) {
                    this->show(name); g = true;
                    int numb; bool flag = false;

                    cout << "Выберите номер теста который нужно изменить: "; cin >> numb;
                    if (numb >= 0) {
                        if (it->getS() != 0) {
                            for (int i = 0; i < it->getS(); i++) {
                                if (i == numb) {
                                    auto ite = it->questions.find(numb);
                                    auto iter = it->answers.find(numb);
                                    string question, answer; cin.ignore();
                                    do {
                                        cout << "Введите новый вопрос: "; getline(cin, question);
                                        if (!question.empty()) {
                                            do {
                                                cout << "Введите ответ к вопросу: "; getline(cin, answer);
                                                if (!answer.empty()) {

                                                    it->questions.erase(ite);
                                                    it->questions.emplace(numb, question);

                                                    it->answers.erase(iter);
                                                    it->answers.emplace(numb, answer);

                                                    good("Вопрос успешно изменен!");
                                                }
                                                else {
                                                    error("Вы не ввели новое значение!");
                                                }
                                            } while (answer.empty());
                                        }
                                        else {
                                            error("Вы не ввели новое значение!");
                                        }
                                    } while (question.empty());
                                }
                            }
                        }
                        else {
                            error("Тесты ещё не были добавлены!");
                        }
                    }

                }
            }
        }
        else {
            error("Вы не ввели имя категории");
        }

        if (g == false) { error("Такой категории не существует!"); return; }
    }

    void save() {
        ofstream fout("test.txt");
        if (fout.is_open()) {
            fout << size << endl;
            for (auto cat : test) {
                if (cat.getS() != 0) {
                    fout << cat.getS() << " " << CaesarIn(cat.getCat()) << endl;
                    for (int i = 0; i < cat.getS(); i++) {
                        auto it = cat.questions.find(i);
                        auto iter = cat.answers.find(i);
                        fout << it->first << " " << CaesarIn(it->second) << " " << CaesarIn(iter->second) << endl;
                    }
                }
                else { cout << "\nTests empty!\n" << endl; return; }
            }
        }
        good("Вы успешно сохранили тесты!");
        fout.close();
    }

    void loAd() {
        ifstream fin("test.txt"); int sz, counter, id; string category, f, s;
        test.clear();

        if (fin.is_open()) {
            fin >> counter; size = counter;
            while (counter > 0) {
                Tests temp;
                fin >> sz >> category;
                temp.setS(sz);
                temp.setCat(CaesarOut(category));

                while (sz >= 1) {
                    fin >> id >> f >> s;
                    temp.add(id, CaesarOut(f), CaesarOut(s)); sz--;
                };

                //temp.show();
                test.push_back(temp);
                counter--;
            };
        }

        good("Вы успешно загрузили тесты!");
        fin.close();
    }

    void load_without_messege() {
        ifstream fin("test.txt"); int sz, counter, id; string category, f, s;
        test.clear();

        if (fin.is_open()) {
            fin >> counter; size = counter;
            while (counter > 0) {
                Tests temp;
                fin >> sz >> category;
                temp.setS(sz);
                temp.setCat(CaesarOut(category));

                while (sz >= 1) {
                    fin >> id >> f >> s;
                    temp.add(id, CaesarOut(f), CaesarOut(s)); sz--;
                };

                test.push_back(temp);
                counter--;
            };
        }

        fin.close();
    }

    void save_without_messege() {
        ofstream fout("test.txt");
        if (fout.is_open()) {
            fout << size << endl;
            for (auto cat : test) {
                if (cat.getS() != 0) {
                    fout << cat.getS() << " " << CaesarIn(cat.getCat()) << endl;
                    for (int i = 0; i < cat.getS(); i++) {
                        auto it = cat.questions.find(i);
                        auto iter = cat.answers.find(i);
                        fout << it->first << " " << CaesarIn(it->second) << " " << CaesarIn(iter->second) << endl;
                    }
                }
            }
        }
        fout.close();
    }

    void show(string cat) {
        if (test.size() != 0) {
            for (auto it : test) {
                if (cat == it.getCat()) {
                    it.show();
                }
            }
        }
        else {
            error("Тесты ещё не были добавлены!");
        }
    }

    void show() {
        if (test.size() != 0) {
            for (auto it : test) {
                cout << "Категория: " << it.getCat() << endl;
                it.show();
            }
        }
        else {
            error("Тесты ещё не были добавлены!");
        }
    }
};

class Users {
    vector<Person> users;
    int count = 0;
public:
    Users() {}
    int add() {
        Person pupil; bool check_user = false;
        string n, a, num, check; 

        cout << "ФИО(Имя пользователя): "; getline(cin, n);
        check_user = findName(n);
        if (check_user) { error("Имя пользователя уже занято!"); return -1; }
        else {
            pupil.setName(n); pupil.setId(count);
            check = getPassword(); pupil.setPass(check); cout << endl;
            cout << "Адрес: "; getline(cin, a); pupil.setAddress(a);
            cout << "Телефон: "; getline(cin, num); pupil.setNumber(num);
            users.push_back(pupil);
            count++;
            good("Вы успешно зарегистрировались!");
            return pupil.getId();
        }
        return -1;
    }

    void edit() {
        int _id;  bool flag = false;
        if (count != 0) {
            this->show();
            cin.ignore(); cout << "\nВведите номер пользователя для редактирования:"; cin >> _id;
            for (auto it : users) {
                if (flag == false) {
                    if (it.getId() == _id) {
                        flag = true;
                        int ch, edit = 0;
                        do {
                            system("cls");
                            cout << "\nЧто хотите отредактировать?\n0 - \t<-\n1 - ФИО\n2 - Адрес\n3 - Телефон\n"; cin >> ch;
                            if (ch == 0) { break; }
                            else if (ch == 1) {
                                string n; cin.ignore(); bool use;
                                cout << "ФИО(Имя пользователя): "; getline(cin, n);
                                use = findName(n);
                                if (use) { edit--; error("Имя пользователя уже занято!"); }
                                else { users[_id].setName(n); edit++; good("Имя пользователя успешно изменено!"); }
                            }
                            else if (ch == 2) {
                                string a; cin.ignore(); 
                                cout << "Адрес: "; getline(cin, a); 
                                if (!a.empty()) { users[_id].setAddress(a); edit++; }
                                else { error("Вы не заполнили поле Адрес"); edit--; }
                            }
                            else if (ch == 3) {
                                string num; cin.ignore();
                                cout << "Телефон: "; getline(cin, num);
                                if (!num.empty()) { users[_id].setNumber(num); edit++; }
                                else { error("Вы не заполнили поле Адрес"); edit--; }
                            }
                            else {
                                error("Wrong input!"); 
                            }
                        } while (ch != 0);
                        if (edit >= 0) {
                            good("К пользователю " + users[_id].getName() + " применены все изменения!");
                        }
                        else {
                            error("Возможно во время выполнения возникали ошибки, но изменения применены!");
                        }
                        break;
                    }
                }
            }
        }
        if (flag == false) { error("Пользователь не найден!"); }
        cout << endl;
    }
    void del() {
        int _id;  bool flag = false;
        if (count != 0) {
            this->show();
            cin.ignore(); cout << "\nВведите номер пользователя для удаления:"; cin >> _id;
            for (auto it:users) {
                if (flag == false) {
                    if (it.getId() == _id) {
                        flag = true; good("Пользователь " + it.getName() + " Успешно удален!");
                        users.erase(users.begin() + _id);
                        count--;
                        break;
                    }
                }
            }
        }
        if (flag == false) { error("Пользователь не найден!"); }
        cout << endl;

    }
    void show() {
        if (count != 0) {
            for (auto it : users) {
                cout << it.getId() << " / " << it.getName() << " / " << it.getAddress() << " / " << it.getNumber() << endl;
            }
        }
        else { cout << "\nvector is empty!\n" << endl; return; }
    }
    void save() {
        if (count != 0) {
            ofstream fout("users.txt");
            if (fout.is_open()) {
                fout << count << endl;
                for (auto it : users) {
                    fout << it.getId() << " " << CaesarIn(it.getName()) << " " << CaesarIn(it.getPass()) << " " << CaesarIn(it.getAddress()) << " " << CaesarIn(it.getNumber()) << endl;
                }

                good("Вы успешно сохранили пользователей!");
            }
            fout.close();
        }
        else { cout << "\nUsers empty!\n" << endl; return; }
    }
    void load() {
        ifstream fin("users.txt");
        if (fin.peek() == EOF) { error("File empty!"); return; }
        if (fin.is_open()) {
            fin >> count;
            users.clear();
            if (count != 0) {
                Person pupil; string n, a, num, p; int i;
                while (fin >> i >> n >> p >> a >> num) {
                    pupil.setId(i);
                    pupil.setName(CaesarOut(n)); pupil.setAddress(CaesarOut(a));
                    pupil.setNumber(CaesarOut(num)); pupil.setPass(CaesarOut(p));
                    users.push_back(pupil);
                }
            }
            good("Вы успешно загрузили пользователей!");
            fin.close();
        }
    }
    void Load() {
        ifstream fin("users.txt");
        if (fin.is_open()) {
            fin >> count;
            users.clear();
            if (count != 0) {
                Person pupil; string n, a, num, p; int i;
                while (fin >> i >> n >> p >> a >> num) {
                    pupil.setId(i);
                    pupil.setName(CaesarOut(n)); pupil.setAddress(CaesarOut(a));
                    pupil.setNumber(CaesarOut(num)); pupil.setPass(CaesarOut(p));
                    users.push_back(pupil);
                }
            }
            fin.close();
        }
    }
    void Save() {
        if (count != 0) {
            ofstream fout("users.txt");
            if (fout.is_open()) {
                fout << count << endl;
                for (auto it : users) {
                    fout << it.getId() << " " << CaesarIn(it.getName()) << " " << CaesarIn(it.getPass()) << " " << CaesarIn(it.getAddress()) << " " << CaesarIn(it.getNumber()) << endl;
                }
            }
            fout.close();
        }
        else { return; }
    }

    void menu(int id, Category& tests) {
        int choice;
        string user = username(id);
        do {
            system("cls");
            cout << "\n0 - Logout\n1 - Сдать тест\n2 - Просмотр результатов\n"; cin >> choice;
            switch (choice) {
            case 1:
                tests.sdacha_test(user);
                break;
            case 2:
                tests.load_results(user);
                system("pause");
                break;
            }
        } while (choice != 0);
    }

    string username(int id) { return users[id].getName(); }

    ~Users() { }
};


class Admin {
public:
    void menu(Users &stud, Category&cat) {
        int choice, ch;

        ifstream file("users.txt"); bool bo = false;
        if (file.peek() != EOF) { stud.Load(); bo = true; }
        file.close();
        if (bo) { good("Список студентов успешно загружен!"); }

        do {
            system("cls");
            cout << "Что мы делаем?\n0 - Logout\n1 - Управление пользователями\n2 - Просмотр статистики\n3 - Управление тестированием\n4 - Изменить пароль\n"; cin >> choice;
            switch (choice) {
            case 1:
                do {
                    system("cls");
                    cout << "0 - \t<- \n1 - Добавить пользователя\n2 - Редактировать пользователя\n3 - Удалить пользователя\n4 - Сохранить юзеров\n5 - Загрузить пользователей\n6 - Show\n"; cin >> ch;
                    if (ch == 1) {
                        system("cls"); cin.ignore();
                        stud.add();
                    }
                    else if (ch == 2) {
                        system("cls");
                        stud.edit();
                    }
                    else if (ch == 3) {
                        system("cls");
                        stud.del();
                        stud.Save();
                    }
                    else if (ch == 4) {
                        system("cls");
                        stud.save();
                    }
                    else if (ch == 5) {
                        system("cls");
                        stud.load();
                    }
                    else if (ch == 6) {
                        system("cls");
                        stud.show();
                        system("pause");
                    }
                } while (ch != 0);
                break;
            case 2:
                do {
                    system("cls");
                    cout << "0 - \t<- \n1 - Просмотр общих результатов\n2 - Просмотр результатов по категории\n3 - Просмотр результатов студента\n4 - Сохранить статистику\n"; cin >> ch;
                    if (ch == 1) {
                        ifstream fin("results.txt");
                        if (fin.is_open()) {
                            string username, category; int res, i = 0;
                            while (fin >> username >> category >> res) {
                                cout << "\n<------- Test #" << ++i << "--------->";
                                cout << "\nИмя пользователя: " << CaesarOut(username) << endl;
                                cout << "Категория: " << CaesarOut(category) << endl;
                                cout << "Результат: " << res << "%" << endl;
                            }
                        }
                        system("pause");
                        fin.close();
                    }
                    else if (ch == 2) {
                        string temp; bool flag = false;
                        cin.ignore(); cout << "Введите категорию: ";  getline(cin, temp);
                        ifstream fin("results.txt");
                        if (fin.is_open()) {
                            string username, category; int res, i = 0;
                            while (fin >> username >> category >> res) {
                                if (temp == CaesarOut(category)) {
                                    flag = true;
                                    cout << "\n<------- Test #" << ++i << "--------->";
                                    cout << "\nИмя пользователя: " << CaesarOut(username) << endl;
                                    cout << "Категория: " << CaesarOut(category) << endl;
                                    cout << "Результат: " << res << "%" << endl;
                                }
                            }
                        }

                        if (flag == false) { error("Сдач по этой категории нет!"); }
                        else { system("pause"); }
                        fin.close();
                    }
                    else if (ch == 3) {
                        stud.show(); string username;
                        cin.ignore(); cout << "\nВведите имя пользователя: ";  getline(cin, username);
                        cat.load_results(username);
                        system("pause");
                    }
                    else if (ch == 4) {
                        string path;
                        cin.ignore(); cout << "Введите полный путь к файлу: "; getline(cin, path);
                        ofstream fout(path);
                        if (fout.is_open()) {
                            int choic;
                            do {
                                system("cls");
                                cout << "0 - \t<- \nКакую статистику вы хотите сохранить?\n1 - Full\n2 - By category\n3 - By user\n"; cin >> choic;
                                if (choic == 1) {
                                    ifstream fin("results.txt");
                                    if (fin.is_open()) {
                                        string username, category; int res, i = 0;
                                        while (fin >> username >> category >> res) {
                                            fout << "\n<------- Test #" << ++i << "--------->";
                                            fout << "\nИмя пользователя: " << CaesarOut(username) << endl;
                                            fout << "Категория: " << CaesarOut(category) << endl;
                                            fout << "Результат: " << res << "%" << endl;
                                        }
                                    }
                                    fin.close();
                                }
                                else if (choic == 2) {
                                    string temp; bool flag = false;
                                    cin.ignore(); cout << "Введите категорию: ";  getline(cin, temp);
                                    ifstream fin("results.txt");
                                    if (fin.is_open()) {
                                        string username, category; int res, i = 0;
                                        while (fin >> username >> category >> res) {
                                            if (temp == CaesarOut(category)) {
                                                flag = true;
                                                fout << "\n<------- Test #" << ++i << "--------->";
                                                fout << "\nИмя пользователя: " << CaesarOut(username) << endl;
                                                fout << "Категория: " << CaesarOut(category) << endl;
                                                fout << "Результат: " << res << "%" << endl;
                                            }
                                        }
                                    }

                                    if (flag == false) { error("Сдач по этой категории нет!"); }
                                    else { system("pause"); }
                                    fin.close();
                                }
                                else if (choic == 3) {
                                    stud.show(); string username;
                                    cin.ignore(); cout << "\nВведите имя пользователя: ";  getline(cin, username);

                                    ifstream fin("results.txt"); string cat, user; float res; int i = 0; bool flag = false;
                                    cout << endl;
                                    if (fin.is_open()) {
                                        while (fin >> user >> cat >> res) {
                                            if (username == CaesarOut(user)) {
                                                flag = true;
                                                fout << "<--------- Тест #" << ++i << "--------->" << endl;
                                                fout << "Категория: " << CaesarOut(cat) << endl;
                                                fout << "Результат: " << res << "%" << endl;
                                            }
                                        }
                                    }

                                    if (flag == false) { error("Вы не сдавали ещё ни одного теста!"); }
                                    fin.close();

                                    system("pause");
                                }
                            } while (choic != 0);

                            good("Users are saved");
                            fout.close();
                        }
                    }
                } while (ch != 0);
                break;
            case 3:
                do {
                    system("cls");
                    cout << "0 - \t<- \n1 - Добавить категорию\n2 - Добавить тесты в категорию\n3 - Изменить тест\n4 - Импортировать тесты\n5 - Експортировать тесты\n6 - Show\n"; cin >> ch;
                    if (ch == 1) {
                        system("cls");
                        cat.add();
                    }
                    else if (ch == 2) {
                        system("cls");
                        cat.addTests();
                    }
                    else if (ch == 3) {
                        system("cls");
                        cat.edit();
                        cat.save_without_messege();
                    }
                    else if (ch == 4) {
                        system("cls");
                        cat.save();
                    }
                    else if (ch == 5) {
                        system("cls");
                        cat.loAd();
                    }
                    else if (ch == 6) {
                        system("cls");
                        cat.show();
                        system("pause");
                    }
                } while (ch != 0);
                break;
            case 4:
                int change;
                do {
                    system("cls");
                    cout << "0 - \t<- \n1 - Помню старый пароль\n"; cin >> change;
                    if (change == 1) {
                        changePassR();
                    }
                } while (change != 0);
            }
        } while (choice != 0);
        
    }
};


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "");
    int ch;
    Users students;
    Category tests;

    cout << "0 - Stop script\n\n\n";
    cout << "Кто вы?\n1 - Admin\n2 - User\n"; cin >> ch;
    if (ch == 1) {
        ifstream file("admin.txt");
        if (file.peek() == EOF) {
            system("cls");
            file.close();
            string username, password; bool flag = false;
            cin.ignore(); cout << "Придумайте имя пользователя: "; getline(cin, username);
            if (!username.empty()) {
                password = getPassword();
                flag = true;
            }
            else { cout << "\nUsername is invalid!\n\n"; }

            if (flag) {

                ofstream fout("admin.txt");
                fout << CaesarIn(username) << " " << CaesarIn(password);
                fout.close();
                // adminka
                Admin session;
                session.menu(students, tests);

            }
            else {
                cout << "\nPassword is invalid!\n\n";
            }
        }
        else {
            string username, password;
            file >> username >> password;
            username = CaesarOut(username); password = CaesarOut(password);
            file.close();

            string check_user, check_pass; bool flag_ = false;
            do {
                system("cls");
                cin.ignore(); cout << "Имя пользователя: "; getline(cin, check_user);
                if (username == check_user) {
                    check_pass = getPassword();
                    if (password == check_pass) {
                        flag_ = true;
                        system("cls");
                        good("Приветствую " + username + "! Вы успешно вошли в систему!");
                        // adminka
                        Admin session;
                        session.menu(students, tests);
                    }
                    else {
                        error("Неверный пароль!");
                        cout << "\n0 - Stop try!\n1 - Try again!\n"; int ch; cin >> ch;
                        if (ch == 0) { flag_ = true; }
                    }
                }
                else {
                    error("Такого администротора не существует!");
                    cout << "0 - Stop try!\n1 - Try again!\n"; int ch; cin >> ch;
                    if (ch == 0) { flag_ = true; }
                }

            } while (flag_ == false);
        }

    }
    else if (ch == 2) {
        system("cls");
        int ch; cout << "0 - Exit\n\n\n1 - Login\n2 - Registration\n"; cin >> ch;

        if (ch == 1) {
            system("cls"); string check_name, check_pass; bool flag = false;

            do {
                ifstream file("users.txt");
                system("cls");
                cin.ignore(); cout << "Имя пользователя: "; getline(cin, check_name);
                if (file.is_open()) {
                    string username, password, addr, number; int id, temp;
                    file >> temp;
                    while (file >> id >> username >> password >> addr >> number) {
                        username = CaesarOut(username); password = CaesarOut(password);
                        if (username == check_name) {
                            check_pass = getPassword();
                            if (password == check_pass) {
                                students.Load();
                                flag = true;
                                system("cls");
                                good("Приветствую " + username + "! Вы успешно вошли в систему!");
                                //user session
                                students.menu(id, tests);
                            }
                        }
                    }
                    if(flag == false) {
                        error("Вход не удался!");
                        cout << "0 - Stop try!\n1 - Try again!\n"; int ch; cin >> ch;
                        if (ch == 0) { flag = true; }
                    }
                    file.close();
                }
            } while (flag == false);
        }
        else if (ch == 2) {
            system("cls");
            ifstream file("users.txt");
            if (file.peek() != EOF) { students.Load(); }
            file.close();
            int ID = -1;

            cin.ignore();
            do {
                system("cls");
                ID = students.add();
            } while (ID == -1);

            students.Save();
            //user session
            students.menu(ID, tests);

        }
    }
    else {
        cout << "\n\nBye!\n\n"; return 0;
    }


}
