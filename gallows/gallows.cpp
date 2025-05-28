#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <clocale>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <locale>
using namespace std;

// Функция для чтения файла
void read_file_gallows(string name_file_gallows) {
    ifstream file(name_file_gallows); // Открываем файл для чтения
    if (!file.is_open()) { // Проверяем, открылся ли файл
        cout << "Файл не открывается";
    }
    else {
        string line;
        while (!file.eof()) { //пока не конец файла

            getline(file, line); // Читаем файл построчно
            cout << line<<endl;// Выводим строку
        }
    }
    file.close();
}
// Функция для выбора типа игры
int get_game_type() {
    int type;
    while (true) {
        cout << "Выберите вариант игры:\n1 - Игра с компьютером\n2 - Игра на двоих" << endl;
        cin >> type;// Ввод типа игры

        if (type == 1 || type == 2) {// Проверяем корректность ввода
            return type;
        }
        else {
            cout << "Ошибка! Введите только 1 или 2." << endl;
            cin.clear();          // сбрасываем флаг ошибки, если было введено не число
            cin.ignore(1000, '\n'); // очищаем буфер ввода (1000 символов или до '\n')
        }
    }
}
// Функция для выбора уровня игры
int get_game_level_type() {
    int type;
    while (true) {
        cout << "Выберите уровень игры:\n1 - Easy level(слова до 6 букв)\n2 - Hard level(слова от 7 и более букв)" << endl;
        cin >> type;// Ввод уровня игры

        if (type == 1 || type == 2) {// Проверка ввода
            return type;
        }
        else {
            cout << "Ошибка! Введите только 1 или 2." << endl;
            cin.clear();          // сбрасываем флаг ошибки, если было введено не число
            cin.ignore(1000, '\n'); // очищаем буфер ввода (1000 символов или до '\n')
        }
    }
}

// Функция для выбора слова из файла
string words_in_file() {
    srand(time(0));// Инициализируем генератор случайных чисел
    int number = rand() % 78; // Генерируем случайное число от 0 до 77 для выбора слова
    int i = 0;
    string word;
    int type = get_game_level_type();// Получаем уровень игры
    system("cls");
    // Условие для легкого уровня
    if (type == 1) {
        ifstream file("file_word1.txt");// Открываем файл для легкого уровня
        if (!file.is_open()) {
            cout << "Файл не открывается";
        }
        else {

            while (!file.eof()) { //пока не конец файла
                getline(file, word);// Читаем слово из файла
                if (number == i) {
                    break;
                }
                else {
                    i++;

                }
            }
        }
        file.close();
        return word;
    }
    // Условие для трудного уровня
    else {
        ifstream file("file_word2.txt"); //Открываем файл для трудного уровня
        if (!file.is_open()) {
            cout << "Файл не открывается";
        }

        else {
            while (!file.eof()) { //пока не конец файла
                getline(file, word);// Читаем слово из файла
                if (number == i) {
                    cout << word << endl; //удалить
                    break;
                }
                else {
                    i++;

                }
            }
        }
        file.close();
        return word;
    }
}
// Функция для преобразования русской буквы в верхний регистр
char russian_toupper(char ch) {
    if (ch >= 'а' && ch <= 'я') {
        return ch - ('а' - 'А');
    }
    if (ch == 'ё') return 'Ё';
    return ch;
}

// Функция для ввода слова от пользователя
string word_in_people() {
    string word;// Переменная для хранения слова
    int count; // Переменная для хранения длины слова
    int flag = 0;
    cout << "Введите слово:" << endl;
    while (flag == 0) {
        getline(cin, word);// Читаем слово
        count = word.size();// Сохраняем длину слова
        for (int i = 0; i < count; i++) {
            word[i] = russian_toupper(word[i]);// Преобразуем буквы в верхний регистр

            // Проверяем корректность введенного слова
            if ((word[i] >= 'А' && word[i] <= 'П') || (word[i] >= 'Р' && word[i] <= 'Я') || word[i] == 'Ё') {
                flag = 1;
            }
            else {
                cout << "Введите корректное слово." << endl;
                flag = 0;

                break;

            }
        }
        if (flag == 1) {// Если слово корректное
            string yes_no = "НЕТ";
            while (yes_no != "ДА") {
                cout << "Вы подтверждаете слово?\n Введите ДА или НЕТ" << endl;
                getline(cin, yes_no);// Подтверждение слова
                for (char& c : yes_no) {
                    c = toupper(c);
                }
                if (yes_no == "НЕТ") {
                    system("cls");
                    flag = 0;
                    cout << "Введите слово для игры:" << endl;
                    break;
                }
                else if (yes_no != "ДА") {
                    cout << "Некорректный ввод" << endl;

                }
            }

        }

    }
    system("cls");
    return word;
}

// Функция для проверки корректности введенной буквы
char is_valid_letterr() {
    int flag = 0;
    char letter;// Переменная для хранения буквы
    while (flag == 0) {
        cout << "Введите букву" << endl;
        cin >> letter;

        letter = russian_toupper(letter);// Преобразуем букву в верхний регистр
        if ((letter >= 'А' && letter <= 'П') || (letter >= 'Р' && letter <= 'Я') || letter == 'Ё') {
            flag = 1;
        }
        else {
            cout << "Введите корректную букву." << endl;
        }
       
    }
    return letter;
}

// Функция для нахождения введенной буквы в слове
string find_letter(char letter, string word, string word_base, int count) {
    for (int i = 0; i < count; i++) {
        if (word[i] == letter) { // Если буква найдена в слове
            word_base[i] = letter;// Заменяем звездочку на букву
        }
    }
    return word_base;// Возвращаем обновленное слово
}

// Функция для отображения доступных и использованных букв
void show_alphabet(string used_letters) {
    cout << "Алфавит: ";
    string alphabet = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

    for (char letter : alphabet) {
        if (used_letters.find(letter) != string::npos) {
            cout << "_ ";  // скрываем использованные буквы
        }
        else {
            cout << letter << " ";  // показываем доступные
        }
    }
    cout << endl;
}

// Функция для проверки ввода "ДА" или "НЕТ"
string is_valid_yes_no() {
    string input;
    while (true) {
        cout << "Пpодолжим игру? Напишите ДА или НЕТ: ";
        cin >> input;

        for (char& c : input) {
            c = toupper(c); // Преобразуем в верхний регистр
        }

        if (input == "ДА" || input == "НЕТ") {
            return input;
        }
        else {
            cout << "Некорректный ввод. Пожалуйста, введите 'ДА' или 'НЕТ'." << endl;
        }
    }
}

int main() {
   
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);      // Ввод
    SetConsoleOutputCP(1251); // Вывод
    locale::global(locale(""));
    wcout.imbue(locale());
    wcin.imbue(locale());
     
    string name_file_gallows;
    string yes_no = "ДА";
    char start;// Переменная для ввода для запуска
    read_file_gallows("gallow.txt");
    cin >> start;
   

    system("cls");


    while (yes_no == "ДА") {
        string used_letters = "";// Очищаем использованные буквы
        int type = get_game_type();// Получаем тип игры
        string word;
        system("cls");
        // В зависимости от типа игры получаем слово
        if (type == 1) {
            word = words_in_file();
        }
        else {
            word = word_in_people();

        }


        int count = word.size();

        string word_base(count, '*');// Инициализируем слово из звездочек
        int er = 0;// Переменная для количества ошибок
        char letter;// Переменная для введенной буквы

        // Цикл для угадывания слова
        while (er < 7 and word_base != word) {
            name_file_gallows = "data" + to_string(er) + ".txt";
            read_file_gallows(name_file_gallows);
            cout << "Искомое слово: " << word_base << endl; // Выводим текущее состояние угадывания
            show_alphabet(used_letters);
            char letter = is_valid_letterr();
            used_letters += letter;
            // Ищем букву в загаданном слове
            string word_base_new = find_letter(letter, word, word_base, count);
            cout << word_base_new;
            if (word_base == word_base_new) {
                er++;
                // Если буква не угадана, увеличиваем счетчик ошибок
            }
            else{
                word_base = word_base_new;// Обновляем состояние слова
            }


            system("cls"); //очищение экрана

        }
        // Проверяем условия выигрыша и поражения
        if (er < 7) {
            cout << "Вы выиграли!" << " ;)" << endl;
            read_file_gallows("smile.txt");

        }
        else {
            cout << "Вы проиграли(" << endl;
            name_file_gallows = "data7.txt";
            read_file_gallows(name_file_gallows);
            cout << "Неугаданное слово:" << word << endl;
            read_file_gallows("smile1.txt");
        }
        yes_no = is_valid_yes_no();// Запрашиваем продолжение игры
        system("cls"); //очищение экрана

    }
    system("pause");
    return 0;
}