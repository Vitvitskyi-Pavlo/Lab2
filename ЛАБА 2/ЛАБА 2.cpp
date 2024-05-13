#include <iostream>
#include <fstream>
#include <string>
using namespace std;



// Функція для розрахунку біта парності
bool parity(int n) {
    bool parity = false;
    while (n) {
        parity = !parity;
        n &= n - 1;
    }
    return parity;
}

void MenuTask()
{
    cout << "     Menu Task   \n";
    cout << "    1.  Calculation of expressions using bitwise operations  \n";
    cout << "    2.  Data encryption using bitwise operations \n";
    cout << "    3.  Exit \n";
}
void task1() {
    int a, b, c, d;
    int num1, num2;
    cout << "Введiть a, b, c, d: ";
    cin >> a >> b >> c >> d;
    b = b << 6;

    num1 = ((a << 4) - (a << 2)) + ((((d << 4) - d) + ((b << 4) - (b << 2))) >= 32) - ((c << 4) - (c << 2)) + ((d << 4) - d);
    num2 = (12 * a) + ((d * 15 + 12 * b) / 1024) - (12 * c) + (d * 15);

    cout << num1 << "\n";
    cout << num2 << "\n";

    system("pause");

}

void task2()
{
    // Вхідний текстовий файл
    ifstream infile("input.txt");
    if (!infile.is_open()) {
        cout << "Не вдалося відкрити вхідний файл!" << endl;

    }

    // Вихідний бінарний файл
    ofstream outfile("output.bin", ios::binary);
    if (!outfile.is_open()) {
        cout << "Не вдалося відкрити вихідний файл!" << endl;

    }

    // Змінні
    string line;
    int row = 1;
    while (getline(infile, line)) {
        // Доповнення пробілами
        line.resize(32, ' ');

        for (int i = 0; i < line.size(); i++) {
            // Перетворення в ASCII код
            unsigned char ch = line[i];
            int asciiCode = ch;

            // Розбиття на 2 байти
            unsigned char byte1 = (row << 5) | (i & 0x1F);
            unsigned char byte2 = (asciiCode & 0x7F) | ((parity(asciiCode) & 1) << 7);

            // Запис байтів у файл
            outfile.write((char*)&byte1, sizeof(byte1));
            outfile.write((char*)&byte2, sizeof(byte2));
        }

        row++;
    }

    infile.close();
    outfile.close();

    cout << "Шифрування завершено!" << endl;

    // Вхідний бінарний файл
    ifstream inf("output.bin", ios::binary);
    if (!inf.is_open()) {
        cout << "Не вдалося відкрити вхідний файл!" << endl;

    }

    // Вихідний текстовий файл
    ofstream outf("decrypted.txt");
    if (!outf.is_open()) {
        cout << "Не вдалося відкрити вихідний файл!" << endl;

    }

    // Змінні
    int rown = 1;
    while (true) {
        // Читання 2 байтів
        unsigned char byte1, byte2;
        inf.read((char*)&byte1, sizeof(byte1));
        inf.read((char*)&byte2, sizeof(byte2));

        // Перевірка кінця файлу
        if (inf.eof()) {
            break;
        }

        // Виділення інформації з байтів
        int position = (byte1 >> 5) & 0x1F;
        int asciiCode = (byte2 & 0x7F) | ((byte1 & 0x80) >> 7);

        // Перетворення ASCII коду в символ
        char ch = asciiCode;

        // Виведення розшифрованого тексту
        cout << ch;
        outfile << ch;

        // Перехід до наступного символу
        if (position == 31) {
            rown++;
            outfile << endl;
        }
    }

    inf.close();
    outf.close();

    cout << endl << "Розшифрування завершено!" << endl;



}

#include <iostream>
#include <fstream>
#include <string>
using namespace std;



int main()
{
    setlocale(LC_CTYPE, "Ukr");
    cout << "OOP. Template for laboratory work #2.\n";

    char ch = '5';
    do {
        system("cls");
        MenuTask();
        ch = cin.get();

        cin.get();

        switch (ch) {
        case '1': task1();   break;
        case '2': task2();   break;
        case '3': return 0;
        }
        cout << " Press any key and enter\n";
        ch = cin.get();
    } while (ch != '3');

    return 0;
}