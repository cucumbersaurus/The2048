#include <iostream>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <string>
#include <locale>
#include <cstdlib>

using namespace std;

enum Colors{
    BLACK,
    BLUE,
    GREEN, 
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GRAY,
    DARK_GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    WHITE
};

string GAMEOVER[] = {
    "  ■■■■    ■■■    ■      ■ ■■■■■",
    "■          ■      ■  ■      ■  ■",
    "■          ■      ■  ■■  ■■  ■",
    "■    ■■  ■■■■■  ■  ■  ■  ■■■■■",
    "■      ■  ■      ■  ■      ■  ■",
    "■      ■  ■      ■  ■      ■  ■",
    "  ■■      ■      ■  ■      ■  ■■■■■",
    " ",
    "  ■■■    ■      ■  ■■■■■  ■■■■",
    "■      ■  ■      ■  ■          ■      ■",
    "■      ■  ■      ■  ■          ■      ■",
    "■      ■    ■  ■    ■■■■■  ■■■■",
    "■      ■    ■  ■    ■          ■      ■",
    "■      ■      ■      ■          ■      ■",
    "  ■■■        ■      ■■■■■  ■      ■",
};

int board[4][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

int last_board[4][4];
int gameoverCheckBoard[4][4];

int score = 0;
bool gameOver = false;

int maxn=0;

//string player;
void setConsole(){
    system("mode con: cols=80 lines=28");
    //system("mode con: cols=800 lines=280");

    CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(Colors foreground, Colors background) {
    int color = foreground + background * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void clear(){
    //cout<<"\x1B[2J\x1B[3J\x1B[H";
    for(int i=0;i<28;i++){
        gotoxy(0, i);
        cout<<"          "<<"          "<<"          "<<"          "<<"          "<<"          "<<"          "<<"          ";
    }
}

void setNumberColor(int num) {
    switch(num) {
    case 0:
        setColor(WHITE, BLACK);
        break;
    case 2:
        setColor(LIGHT_RED, BLACK);
        break;
    case 4:
        setColor(YELLOW, BLACK);
        break;
    case 8:
        setColor(LIGHT_GREEN, BLACK);
        break;
    case 16:
        setColor(LIGHT_CYAN, BLACK);
        break;
    case 32:
        setColor(LIGHT_BLUE, BLACK);
        break;
    case 64:
        setColor(LIGHT_MAGENTA, BLACK);
        break;
    case 128:
        setColor(RED, BLACK);
        break;
    case 256:
        setColor(BROWN, BLACK);
        break;
    case 512:
        setColor(GREEN, BLACK);
        break;
    case 1024:
        setColor(CYAN, BLACK);
        break;
    case 2048:
        setColor(WHITE, BLACK);
        break;
    }
}

string getOutputString(int x, int y) {
    int number = board[y][x];//이거 안하면 배열이 돌아서 출력됨

    string outputString;
    string numberString = to_string(number);

    int lrlen = (13 - numberString.size()) / 2 - 1;
    /*
    예시 : "│     0     │"
              ^      ^
              |      |
              이 두 부분이 left right length (lrlen)
    1. + │
    2. + " " * lrlen
    3. + (숫자)
    4. + " " * lreln
    5. 길이가 짧을경우(숫자의 자릿수가 짝수일때) " " 하나 추가
    6. + │
    */

    //1
    outputString.append("│");

    //2
    for (int i = 0; i < lrlen; i++) {
        outputString.append(" ");
    }

    //3
    outputString.append(numberString);

    //4
    for (int i = 0; i < lrlen; i++) {
        outputString.append(" ");
    }

    //5
    if (outputString.size() == 12) {
        outputString.append(" ");
    }

    //6
    outputString.append("│");

    return outputString;
}

void drawNum(int x, int y) {

    int nx = x * 14;
    int ny = y * 7;

    setNumberColor(board[y][x]);//마찬가지로 이렇게 해야 배열이 돌아서 출력되지 않음

    gotoxy(nx, ny);
    cout << "┌───────────┐";
    gotoxy(nx, ny + 1);
    cout << "│           │";
    gotoxy(nx, ny + 2);
    cout << "│           │";
    gotoxy(nx, ny + 3);
    cout << getOutputString(x, y);
    gotoxy(nx, ny + 4);
    cout << "│           │";
    gotoxy(nx, ny + 5);
    cout << "│           │";
    gotoxy(nx, ny + 6);
    cout << "└───────────┘";
}

void print() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            drawNum(i, j);
        }
    }

    gotoxy(57, 5);
    setColor(LIGHT_BLUE, BLACK);
    cout << "점수 : ";
    setColor(LIGHT_RED, BLACK);
    cout << score;

    gotoxy(57, 7);
    setColor(LIGHT_BLUE, BLACK);
    cout << "가장 큰 블럭 : ";
    setColor(LIGHT_RED, BLACK);
    cout << maxn;

    // gotoxy(57, 4);
    // setColor(BLUE, BLACK);
    // cout << "플레이어 : ";
    // setColor(CYAN, BLACK);
    // cout << player;
}

//미완성
void printGameOverMessage() {

    for(int i=0;i<15;i++){
        if(i<7) setColor(LIGHT_BLUE, BLACK);
        else setColor(LIGHT_RED, BLACK);
        
        for(int j=0;j<GAMEOVER[i].size();j++){
            if(GAMEOVER[i][j] == ' '){
                continue;
            }
            else{
                gotoxy(j+10, i+3);
                cout<<GAMEOVER[i][j];
            }
        }
        cout<<endl;
    }

}

int newNum() {
    int randpos = 0;
    while (true) {
        randpos = rand() % 16;
        if (board[randpos / 4][randpos % 4] == 0) {//빈칸 찾기
            int randnum = rand() % 10;

            if (randnum == 0){
                board[randpos / 4][randpos % 4] = 4;//10% 확률로 4
                return 4;
            }
            else {
                board[randpos / 4][randpos % 4] = 2;//나머지 2
                return 2;
            }
        }
    }
}

void rotate() {
    int tmp[4][4];

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            tmp[j][4-i-1] = board[i][j];
        }
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            board[i][j] = tmp[i][j];
        }
    }

}

void push() {
    int tmp[4][4] = {0};
    for(int i=0;i<4;i++){
        for(int j=0,idx=0;j<4;j++){
            if(board[i][j]!=0){
                tmp[i][idx]=board[i][j];
                idx++;
            }
        }
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            board[i][j]=tmp[i][j];
        }
    }
}

void merge(bool checkMode) {
    
    push();

    for(int i=0;i<4;i++){
        for(int j=1;j<4;j++){
            if(board[i][j]!=0&&board[i][j]==board[i][j-1]){
                if(!checkMode){
                    score+=board[i][j]*2;
                    maxn = max(maxn, board[i][j]*2);
                }
                board[i][j]+=board[i][j-1];
                board[i][j-1]=0;
                j++;
            }
        }
    }

    push();
}

void copy() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            last_board[i][j] = board[i][j];
        }
    }
}

void 

copyBoardToOver() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gameoverCheckBoard[i][j] = board[i][j];
        }
    }
}

void copyOverToBoard() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = gameoverCheckBoard[i][j];
        }
    }
}

void left(bool checkMode) {
    merge(checkMode);
}

void right(bool checkMode) {
    rotate();
    rotate();
    merge(checkMode);
    rotate();
    rotate();
}

void up(bool checkMode) {
    rotate();
    rotate();
    rotate();
    merge(checkMode);
    rotate();
}

void down(bool checkMode) {
    rotate();
    merge(checkMode);
    rotate();
    rotate();
    rotate();
}

bool isSame() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (last_board[i][j] != board[i][j]) return false;
        }
    }
    return true;
}

bool isFull() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) return false;
        }
    }
    return true;
}

bool isGameOver() {
    copy();

    bool l;
    bool r;
    bool u;
    bool d;

    copyBoardToOver();

    left(true);
    l = isSame();

    copyOverToBoard();
    right(true);
    r = isSame();

    copyOverToBoard();
    up(true);
    u = isSame();

    copyOverToBoard();
    down(true);
    d = isSame();

    copyOverToBoard();

    if (l && r && u && d) {
        return true;
    }
    return false;
}


void checkGameOver(){
    if (isFull()) {
        if (isGameOver()) {
            printGameOverMessage();
            gameOver = true;
        }
    }
}


void getKey() {
    int key = _getch();//2바이트라서 1바이트 먼저 제거

    copy();//키 입력후 변화가 있는지 확인

    if (key == 224) {
        key = _getch();
        switch (key) {
        case 72://위쪽
            up(false);
            break;
        case 77://오른쪽
            right(false);
            break;
        case 80://아래쪽
            down(false);
            break;
        case 75://왼쪽
            left(false);
            break;
        }
    }

    if (!isSame()) {//변화가 있을때만 새 숫자 생성
        newNum();
    }

    checkGameOver();
}

void onGame(){

    clear();

    gameOver = false;
    score = 0;
    maxn=0;

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            board[i][j]=0;
            last_board[i][j]=0;
            gameoverCheckBoard[i][j]=0;
        }
    }

    for(int i=0;i<2;i++){
        int tmp = newNum();
        maxn = max(maxn, tmp);
    }

    while (!gameOver) {
        print();
        getKey();
    }
}

bool isKeepPlaying(){
    cout<<"게임이 종료되었습니다. 다시 하겠습니까?"<<endl<<"계속 | y"<<endl<<"그만 | n";
    while (true)
    {   
        char ch = _getch();
        if(ch=='y'||ch=='Y'){
            return true;
        }
        else if(ch=='n'||ch=='N'){
            cout<<endl;
            return false;
        }
    }
}

int main() {

    setConsole();
    ios::sync_with_stdio(false);
    cin.tie(0);
    srand(time(NULL));
    
    bool keepPlay = true;

    //printGameOverMessage();

    // for(int i=0;i<7;i++){
    //     cout<<GAMEOVER[i]<<endl;
    // }

    
    while (keepPlay){
    //getPlayerName();
    onGame();
    keepPlay = isKeepPlaying(); 
    }
    
    return 0;
}