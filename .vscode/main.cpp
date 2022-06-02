#include <bits/stdc++.h>
#include <conio.h>

using namespace std;

int board[4][4] = {
    {2, 2, 0, 0},
    {2, 2, 2, 2},
    {4, 2, 2, 4},
    {0, 2, 2, 4}
};

void print(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
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

void left(){
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

void getKey(){
    int key=_getch();
    cout<<key<<endl;
    if (key==224){
        key=_getch();
        cout<<key<<endl;
        switch(key){
            case 72://up
                break;
            case 77://right
                break;
            case 80://down
                break;
            case 75://left
                left();
                break;
        }
    }
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(0);
    srand(time(NULL));

    print();

    getKey();

    print();

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