#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <iostream>
#include <cstdlib>
#include <windows.h>

using namespace std;

int pos;
int dl = 0, sh = 0; // sh - ширина, dl - длина (высота)
int posy, posx; // Позиция игрока
bool normlabirint = false;
char** lab;


void Menu() {
    char menu[3][41] = {"1.Создать", "2.Играть", "3.Выход"};
    char marker[5] = "<---";
    
    for (int i = 0; i < 3; ++i) {
        printf("%s", menu[i]);
        if (i == pos) {
            printf("  %s", marker);
        }
        printf("\n");
    }
}

void Vvodrazm() {
    printf("\e[1;1H\e[2J");
    char strA[1000] = "";
    printf("Введите ширину (3-80): ");
    scanf("%s", strA);
    if (sscanf(strA, "%d", &sh) == 1) {
        if (sh >= 3 && sh <= 80) {
            char strB[1000] = "";
            printf("Введите длину (3-25): ");
            scanf("%s", strB);
            if (sscanf(strB, "%d", &dl) == 1) {
                if (dl >= 3 && dl <= 25) {
                    normlabirint = true;
                } else {
                    printf("Недопустимый ввод.\n");
                    normlabirint = false;
                    while (getch() != 13) {}
                }
            } else {
                printf("Недопустимый ввод.\n");
                normlabirint = false;
                while (getch() != 13) {}
            }
        } else {
            printf("Недопустимый ввод.\n");
            normlabirint = false;
            while (getch() != 13) {}
        }
    } else {
        printf("Недопустимый ввод.\n");
        normlabirint = false;
        while (getch() != 13) {}
    }
}

void Labirint() {
    lab = (char**)malloc(dl * sizeof(char*));
    for (int i = 0; i < dl; i++) {
        lab[i] = (char*)malloc(sh * sizeof(char));
    }

    for (int y = 0; y < dl; y++) {
        for (int x = 0; x < sh; x++) {
            if (x == 0 || x == sh - 1 || y == dl - 1) {
                lab[y][x] = '#';  // Стены по краям взял с лабиринта и лень менять поэтосу так точка ааххаха
            } else {
                lab[y][x] = '.';  // Пустые ячейки
            }
        }
    }

    // Инициализируем начальную позицию игрока (например, в левом верхнем углу внутри лабиринта)
    posx = 0;// razberesha
    posy = 0;
}

void risLabirint() {
     printf("\e[1;1H\e[2J");
    for (int y = 0; y < dl; y++) {
        for (int x = 0; x < sh; x++) {
            if (posy == y && posx == x) {
                cout << '@'; // Игрок
            } else {
                cout << lab[y][x];
            }
        }
        cout << endl;
    }
    printf("cтрелки - двигаться, b - строить,энтер -отправить снежинку, q - выход.\n");
}

void moved(int direction) {
    int newX = posx, newY = posy;
    int inp;
    if (direction == 224) {
    inp = getch();
    if (inp == 72 && posy > 0) newY--;
    if (inp == 80 && posy < dl - 1) newY++;
    if (inp == 75 && posx > 0) newX--;
    if (inp == 77 && posx < sh - 1) newX++;
    }
    
        posx = newX;
        posy = newY;
    
}

void moved2(int direction) {
    int newX = posx, newY = posy;
    int inp;
    if (direction == 224) {
    inp = getch();
    if (inp == 75 && posx > 0) newX--;
    if (inp == 77 && posx < sh - 1) newX++;
    }
    
        posx = newX;
        posy = newY;
    
}

void Fallofsnow() {
    for (int y = dl - 2; y >= 0; y--) {  // Снизу вверх, чтобы избежать перекрытия
        for (int x = 0; x < sh; x++) {
            if (lab[y][x] == '*') {
                if (lab[y + 1][x] == '.') {  
                    lab[y][x] = '.';
                    lab[y + 1][x] = '*';
                } else if (lab[y + 1][x] != '.' && lab[y + 1][x - 1] == '.') {  // Проверяем влево
                    if (lab[y + 2][x - 1] == '.'){
                    lab[y][x] = '.';
                    lab[y + 1][x - 1] = '*';}
                } else if (lab[y + 1][x] != '.' && lab[y + 1][x + 1] == '.') {  // Проверяем вправо
                    if (lab[y + 2][x + 1] == '.'){
                    lab[y][x] = '.';
                    lab[y + 1][x + 1] = '*';}
                }
            }
        }
    }
}


void lobakdota2fan1(int funct) {
    switch (funct) {
        case 0: {
            
            Vvodrazm();
            if(normlabirint){
                Labirint();
                int button;
                risLabirint();
                while(true){
                
                button = getch();
                if (button == 113) break;
                if (button == 224) {
                    moved(button);
                    risLabirint();
                }
                if (button == 98) {
                    if (lab[posy][posx] == '.' && posy != 1) { 
                        lab[posy][posx] = '#';
                        risLabirint();}}
            }}
        }break;

        case 1: {
        if (normlabirint) {
            posx = 0;
            posy = 0;
            int button2;

            while (true) {
                risLabirint();  

                
                if (_kbhit()) {
                    button2 = getch();
                    if (button2 == 113) break;  
                    if (button2 == 224) {     
                        moved2(button2);
                    }
                    if (button2 == 13) {      
                        if (lab[posy][posx] == '.') {
                            lab[posy+1][posx] = '*';
                        }
                    }
                }

                Fallofsnow();  
                Sleep(100);    
        }
    }
}
         break;

        default: break;
    }
}


int main() {
    int key;
    while (true) {
        Menu();
        int key = getch();
        if (key == 49) {
            pos = 0;
        } else if (key == 50) {
            pos = 1;
        } else if (key == 51) {
            pos = 2;
        } else if (key == 13) {
            if (pos == 2) {
                printf("\e[1;1H\e[2J");
                return 0;
            } else {
                lobakdota2fan1(pos);
            }
        } else if (key == 224) {
            key = getch();
            if (key == 72) {
                pos--;
                if (pos < 0) pos = 2;
            } else if (key == 80) {
                pos++;
                if (pos > 2) pos = 0;
            }
        }

        printf("\e[1;1H\e[2J");
    }

    return 0;
}