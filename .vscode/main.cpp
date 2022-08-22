#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

int board[4][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

int last_board[4][4];

void print(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout<<board[i][j]<<"\t";
        }
        cout<<endl<<endl<<endl;
    }
}

void newNum(){
    int random = 0; 
    while(true){
	    random = rand()%16; 
	    cout<<random<<endl;
        if(board[random/4][random%4]==0){
            random = rand()%10;
            if(random==0){
                board[random/4][random%4]=4;
            }
            else{
                board[random/4][random%4]=2;
            }
            break;
        }
    }
}

void rotate(){
    int tmp = board[0][0];
    board[0][0] = board[3][0];
    board[3][0] = board[3][3];
    board[3][3] = board[0][3];
    board[0][3] = tmp;

    tmp = board[0][1];
    board[0][1] = board[2][0];
    board[2][0] = board[3][2];
    board[3][2] = board[1][3];
    board[1][3] = tmp;

    tmp = board[0][2];
    board[0][2] = board[1][0];
    board[1][0] = board[3][1];
    board[3][1] = board[2][3];
    board[2][3] = tmp;

    tmp = board[1][1];
    board[1][1] = board[2][1];
    board[2][1] = board[2][2];
    board[2][2] = board[1][2];
    board[1][2] = tmp;
}

void merge(){
    for(int i=0;i<4;i++){
        for(int j=1;j<4;j++){
            if(board[i][j]!=0){
                int idx=j;
                for(int k=j-1;k>=0;k--){
                    if(board[i][k]!=0){
                        break;
                    }
                    idx=k;
                }
                int tmp = board[i][j];
                board[i][j]=board[i][idx];
                board[i][idx]=tmp;

            } 
        }
    }


    for(int i=0;i<4;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==board[i][j+1]){
                board[i][j]*=2;
                board[i][j+1]=0;
            }
        }
    }

    for(int i=0;i<4;i++){
        for(int j=1;j<4;j++){
            if(board[i][j]!=0){
                int idx=j;
                for(int k=j-1;k>=0;k--){
                    if(board[i][k]!=0){
                        break;
                    }
                    idx=k;
                }
                int tmp = board[i][j];
                board[i][j]=board[i][idx];
                board[i][idx]=tmp;   

            } 
        }
    }
}

void copy(){
    for(int i=0;i<4;i++){
        for(int j =0;j<4;j++){
            last_board[i][j] = board[i][j];
        }
    }
}

bool isSame(){
    for(int i=0;i<4;i++){
        for(int j =0;j<4;j++){
            if(last_board[i][j] != board[i][j]){
                return false;
            }
        }
    }
    return true;
}

void left(){
    merge();
}

void right(){
    rotate();
    rotate();
    merge();
    rotate();
    rotate();
}

void up(){
    rotate();
    rotate();
    rotate();
    merge();
    rotate();
}

void down(){
    rotate();
    merge();
    rotate();
    rotate();
    rotate();
}


void getKey(){
    int key=_getch();
    cout<<key<<endl;

    copy();

    if (key==224){
        key=_getch();
        cout<<key<<endl;
        switch(key){
            case 72://up
                up();
                break;
            case 77://right
                right();
                break;
            case 80://down
                down();
                break;
            case 75://left
                left();
                break;
        }
    }
    if(!isSame()){
        newNum();
    }
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(0);
    srand(time(NULL));

    newNum();
    print();

    while(true){
        getKey();
        print();
    }

    /*
    for(int i=0;i<30;i++){
        newNum();
        print();
        cout<<endl;
        left();
        print();
    }*/
    
    system("pause");
    return 0;
}