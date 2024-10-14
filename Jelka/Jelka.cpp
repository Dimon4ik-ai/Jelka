#include <iostream>
#include <fstream>//для роботи з файлами
#include <cstdlib>//для функцій стандартної бібліотеки
#include <ctime>//для ініціалізації генератора випадкових чисел на основі поточного часу.
#include <vector>
#include <windows.h> // для зміни кольорів і Sleep() у Windows

using namespace std;

// Функція для зміни кольору тексту
void SetColor(int textColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor);
}

// Функція для випадкового додавання іграшок
char getRandomDecoration() {
    char decorations[] = { '@', '$', '%', '#' };
    int randomIndex = rand() % 5; // індекси від 0 до 4
    return (randomIndex == 4) ? '*' : decorations[randomIndex]; // якщо значення = 4 то виконується дія після знака 4,Якщо це неправда, то виконуються дії після знака : 20% шанс на те, що буде зірочка
}

// Функція для побудови одного рівня ялинки
void drawLevel(vector<vector<char>>& tree, int& rowIndex, int levelWidth, int height) {
    for (int i = 0; i < height; i++) {
        int stars = 2 * i + 1;
        int spaces = (levelWidth - stars) / 2;
        for (int j = 0; j < levelWidth; j++) {
            if (j >= spaces && j < spaces + stars) {
                if (rand() % 10 < 4) // 40% шанс, що замість зірочки буде іграшка
                    tree[rowIndex][j] = getRandomDecoration();
                else
                    tree[rowIndex][j] = '*';
            }
            else {
                tree[rowIndex][j] = ' ';
            }
        }
        rowIndex++;
    }
}

// Функція для малювання стовбура ялинки
void drawTrunk(vector<vector<char>>& tree, int& rowIndex, int trunkHeight, int trunkWidth, int levelWidth) {
    int spaces = (levelWidth - trunkWidth) / 2;
    for (int i = 0; i < trunkHeight; i++) {
        for (int j = 0; j < levelWidth; j++) {
            if (j >= spaces && j < spaces + trunkWidth)
                tree[rowIndex][j] = '|';
            else
                tree[rowIndex][j] = ' ';
        }
        rowIndex++;
    }
}

// Функція для виведення ялинки на екран
void displayTree(const vector<vector<char>>& tree, int levelWidth) {
    for (const auto& row : tree) {// auto означає  ключове слово для автоматичного визначення типу змінної  типу з посиланням на оригінальні дані, щоб уникнути копіювання рядків.
        for (char ch : row) {// row означає що ми проходимо по кожному символу всередині одного рядка.
            // Випадковий вибір кольору для іграшок
            if (ch == '@' || ch == '$' || ch == '%' || ch == '#') {
                int randomColor = rand() % 14 + 1; // Випадковий колір від 1 до 14
                SetColor(randomColor);
            }
            else if (ch == '|')
                SetColor(6); // коричневий для стовбура
            else
                SetColor(10);  // зелений для зірочок
            cout << ch;
        }
        cout << endl;
    }
    SetColor(7); // Повертаємо колір консолі до білого
}

// Функція для запису ялинки у файл
void saveTreeToFile(const vector<vector<char>>& tree, const string& filename) {
    ofstream file(filename);//Використовується клас для запису даних у файл.
    if (file.is_open()) {//Цей код перевіряє, чи файл успішно відкрився
        for (const auto& row : tree) {
            for (char ch : row) {
                file << ch;
            }
            file << endl;
        }
        file.close();
        cout << "Ялинка успішно збережена у файл " << filename << endl;
    }
    else {
        cout << "Не вдалося відкрити файл для запису." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ukr");
    system("chcp 65001");
    srand(time(0)); // ініціалізація рандому

    int n; // кількість рівнів ялинки
    cout << "Введіть кількість рівнів ялинки: ";
    cin >> n;

    // Налаштування розмірів ялинки
    int trunkHeight = 3;
    int trunkWidth = 3;
    int baseWidth = 2 * n + 1; // ширина основи останнього рівня

    // Підрахунок загальної висоти ялинки для двовимірного масиву
    int totalRows = 0;
    for (int i = 1; i <= n; i++) {
        totalRows += i;
    }
    totalRows += trunkHeight;

    // Двовимірний масив для збереження ялинки
    vector<vector<char>> tree(totalRows, vector<char>(baseWidth));
    // Малювання ялинки
    int rowIndex = 0;
    for (int i = 1; i <= n; i++) {
        drawLevel(tree, rowIndex, baseWidth, i);
    }
    drawTrunk(tree, rowIndex, trunkHeight, trunkWidth, baseWidth);

    // Запис ялинки у файл
    saveTreeToFile(tree, "christmas_tree.txt");
    //  return 0;

       // Анімація зміни кольорів іграшок
    while (true) {
        system("cls"); // Очищуємо екран перед виведенням оновленої ялинки
        displayTree(tree, baseWidth); // Виведення ялинки
        Sleep(1000); // Затримка на 1 секунду
    }

    return 0;
}