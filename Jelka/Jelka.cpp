#include <iostream>
#include <fstream>//��� ������ � �������
#include <cstdlib>//��� ������� ���������� ��������
#include <ctime>//��� ����������� ���������� ���������� ����� �� ����� ��������� ����.
#include <vector>
#include <windows.h> // ��� ���� ������� � Sleep() � Windows

using namespace std;

// ������� ��� ���� ������� ������
void SetColor(int textColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor);
}

// ������� ��� ����������� ��������� �������
char getRandomDecoration() {
    char decorations[] = { '@', '$', '%', '#' };
    int randomIndex = rand() % 5; // ������� �� 0 �� 4
    return (randomIndex == 4) ? '*' : decorations[randomIndex]; // ���� �������� = 4 �� ���������� �� ���� ����� 4,���� �� ��������, �� ����������� 䳿 ���� ����� : 20% ���� �� ��, �� ���� ������
}

// ������� ��� �������� ������ ���� ������
void drawLevel(vector<vector<char>>& tree, int& rowIndex, int levelWidth, int height) {
    for (int i = 0; i < height; i++) {
        int stars = 2 * i + 1;
        int spaces = (levelWidth - stars) / 2;
        for (int j = 0; j < levelWidth; j++) {
            if (j >= spaces && j < spaces + stars) {
                if (rand() % 10 < 4) // 40% ����, �� ������ ������ ���� �������
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

// ������� ��� ��������� �������� ������
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

// ������� ��� ��������� ������ �� �����
void displayTree(const vector<vector<char>>& tree, int levelWidth) {
    for (const auto& row : tree) {// auto ������  ������� ����� ��� ������������� ���������� ���� �����  ���� � ���������� �� ��������� ���, ��� �������� ��������� �����.
        for (char ch : row) {// row ������ �� �� ��������� �� ������� ������� �������� ������ �����.
            // ���������� ���� ������� ��� �������
            if (ch == '@' || ch == '$' || ch == '%' || ch == '#') {
                int randomColor = rand() % 14 + 1; // ���������� ���� �� 1 �� 14
                SetColor(randomColor);
            }
            else if (ch == '|')
                SetColor(6); // ���������� ��� ��������
            else
                SetColor(10);  // ������� ��� ������
            cout << ch;
        }
        cout << endl;
    }
    SetColor(7); // ��������� ���� ������ �� �����
}

// ������� ��� ������ ������ � ����
void saveTreeToFile(const vector<vector<char>>& tree, const string& filename) {
    ofstream file(filename);//��������������� ���� ��� ������ ����� � ����.
    if (file.is_open()) {//��� ��� ��������, �� ���� ������ ��������
        for (const auto& row : tree) {
            for (char ch : row) {
                file << ch;
            }
            file << endl;
        }
        file.close();
        cout << "������ ������ ��������� � ���� " << filename << endl;
    }
    else {
        cout << "�� ������� ������� ���� ��� ������." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ukr");
    system("chcp 65001");
    srand(time(0)); // ����������� �������

    int n; // ������� ���� ������
    cout << "������ ������� ���� ������: ";
    cin >> n;

    // ������������ ������ ������
    int trunkHeight = 3;
    int trunkWidth = 3;
    int baseWidth = 2 * n + 1; // ������ ������ ���������� ����

    // ϳ�������� �������� ������ ������ ��� ����������� ������
    int totalRows = 0;
    for (int i = 1; i <= n; i++) {
        totalRows += i;
    }
    totalRows += trunkHeight;

    // ���������� ����� ��� ���������� ������
    vector<vector<char>> tree(totalRows, vector<char>(baseWidth));
    // ��������� ������
    int rowIndex = 0;
    for (int i = 1; i <= n; i++) {
        drawLevel(tree, rowIndex, baseWidth, i);
    }
    drawTrunk(tree, rowIndex, trunkHeight, trunkWidth, baseWidth);

    // ����� ������ � ����
    saveTreeToFile(tree, "christmas_tree.txt");
    //  return 0;

       // ������� ���� ������� �������
    while (true) {
        system("cls"); // ������� ����� ����� ���������� �������� ������
        displayTree(tree, baseWidth); // ��������� ������
        Sleep(1000); // �������� �� 1 �������
    }

    return 0;
}