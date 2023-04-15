#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <stdlib.h>

using namespace std;


struct katalog_tov {
    
    int kolvo_tovarov_odnogo_tipa;
    int cena_za_tovar;
    char name[20];
    int weight;
    int nomer;
    
};
int  kolvo_tovarov = 0;
int kol = 0;
katalog_tov kolvo[20], temp[20];


 void create_catalog()
{
    ofstream File1;
    File1.open("Katalog.txt", ios::app);
    if (!File1.is_open()) {
        cout << "Ошибка открытия файла!";
    }
    else
    {
        int x = 1;
        do {

            if (x != 1 && x != 2)
            {
                cout << "Введено неверное значение\nВведите заново:";
            }
            else {
                 int a;
                printf("Введите количество вводимых товаров: ");
                scanf_s("%d", &kolvo_tovarov);
                for (a = 0; a < kolvo_tovarov; a++) {
                    printf("Введите номер товара: ");
                    scanf_s("%d", &kolvo[a].nomer);
                    printf("Введите название товара: ");
                    scanf_s("%s", &kolvo[a].name, 20);
                    printf("Введите количество товаров одного типа: ");
                    scanf_s("%d", &kolvo[a].kolvo_tovarov_odnogo_tipa);
                    printf("Введите стоимость за товар: ");
                    scanf_s("%d", &kolvo[a].cena_za_tovar);
                    printf("Введите вес товара: ");
                    scanf_s("%d", &kolvo[a].weight);
                    printf("\n");
                    File1 << kolvo_tovarov << " " << kolvo[a].nomer << " " << kolvo[a].name << " " << kolvo[a].kolvo_tovarov_odnogo_tipa << " " << kolvo[a].cena_za_tovar << " " << kolvo[a].weight << " " << endl;
                    kol++;
                }
                cout << "\nПродолжить ввод?\n1 - да\n2 - нет\nВаш выбор:";
            }
            cin >> x;
        } while (x != 2);
    }
    File1.close();
}

void view() {
    setlocale(LC_ALL, "Rus");
     int a;
    printf("\n");
    printf("№          Назв. товара        Кол-во          Стоимость      Вес    \n");
    printf("---------------------------------------------------------------------\n");
    for (a = 0; a < kolvo_tovarov; a++) {
        printf("%-10d %-20s %-15d %-15d %-15d ", kolvo[a].nomer, kolvo[a].name, kolvo[a].kolvo_tovarov_odnogo_tipa, kolvo[a].cena_za_tovar, kolvo[a].weight);
        printf("\n");
        printf("-------------------------------------------------------------------\n");

    }   
    printf("\n");
}

void sort_nomer() {
    setlocale(LC_ALL, "Rus");
    register int a, b;
    for (a = 1; a < kolvo_tovarov; a++) for (b = kolvo_tovarov - 1; b >= a; b--) {
        if (kolvo[b - 1].nomer > kolvo[b].nomer) {
            temp[b] = kolvo[b - 1];
            kolvo[b - 1] = kolvo[b];
            kolvo[b] = temp[b];
        }
    }
    printf("Отсортированный по возрвстнаию номер товаров:");
    view();
}
int user()
{
    cout << "Выполнен вход в пользовательский аккаунт\n";
    int choice = 0;
    do {
        cout << "1 - Просмотреть каталог товаров\n2 - Отсортировать по возрвстнаию номер информации\n3 - Выйти из программы\n";
        cin >> choice;
        switch (choice)
        {
        case 1:view(); break;
        case 2:sort_nomer(); break;
        case 3: return 0; 
        default:cout << "Неверный выбор - Повторите попытку\n";
        }
    } while (choice != 4);
}

void admin()
{
    cout << "Выполнен вход в аккаунт администратора\n";
    int choice = 0;
    do {
        cout << "1 - Заполнить каталог товаров\n2 - Просмотреть каталог\n3 - Отсортировать по номеру\n4 - Перейти в аккаунт пользователя\n5 - Выйти из программы \n";
        cin >> choice;
        switch (choice)
        {
        case 1:create_catalog(); break;
        case 2:view(); break;   
        case 3:sort_nomer(); break;
        case 4:user(); break;
        case 5:return; 
        default:cout << "Неверный выбор - Повторите попытку\n";
        }
    } while (choice != 6);
    
}

int menu() {
    int choice;
    do {
        cout << "1-Регистрация"<<endl;
        cout << "2-Войти в существующий аккаунт" << endl;
        cout << "3-Выход из программы" << endl;
        cin >> choice;
    } while (choice > 3);
    return choice;
    }
bool IsValidLogin(const string& input) {
    const regex pattern("[a-zA-Z0-9_]+");
    return regex_match(input, pattern);
}

bool LoginExists(string login) {
    ifstream inputFile("Polzovateli.txt");
    bool loginExists = false;
    string existingLogin, password;
    while (inputFile >> existingLogin >> password) {
        if (existingLogin == login) {
            loginExists = true;
            break;
        }
    }
    inputFile.close();
    return loginExists;
}

void registration() {
    string login, password;
    ofstream file;
    file.open("users.txt", ofstream::app);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!";
    }
    else {
        cout << "Введите логин:";
        cin >> login;
        while (!IsValidLogin(login)) {
            cout << "Ошибка. Логин не должен содержать кириллицу и специальные символы.\nПовторите попытку: ";
            cin >> login;
        }
        while (LoginExists(login)) {
            cout << "Логин уже существует. Повторите ввод: ";
            cin >> login;
        }
        cout << "Введите пароль:";
        cin >> password;
        while (password.length() < 8) {
            cout << "Пароль должен содержать 8 и более символов. Повторите ввод: ";
            cin >> password;
        }
        cout << "Вы успешно зарегистрированны " << endl;
        user();
        
    }
    file << login << " " << password << endl;
    file.close();
}
void in() {
    string login, password, adm = "admin", admPassword = "QweF1", l, p;
    cout << "Введите логин:";
    cin >> login;
    cout << "Введите пароль:";
    cin >> password;
    ifstream File;
    int auth = 0;
    File.open("users.txt");
    while (!File.eof()) {

        File >> l >> p;
       
        if (l == login && p == password) {
            if (login == adm)
            {
                cout << "admin";
            }
            else {
                user();
            }
            auth = 1;
        }
        else if (login == adm && password == admPassword) {
            admin();
            return;
        }
    }
    if (auth == 0) {
        cout << "Данный пользователь не найден.\n";
    }
    File.close();
}

int main()
{
    setlocale(LC_ALL, "ru");
    switch (menu())  {
    case 1: {
        registration();
        break;
    }
    case 2: {
        in();
            break;
                  }
    case 3: {
            
        return 0;

    }
    
    

    }
    
    
}



