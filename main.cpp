#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

void clear() {
    cout << "\033[2J\033[1;1H";
}

void rules() {
    clear();
    cout << "=========================================\n";
    cout << "            COMO JOGAR 2048\n";
    cout << "=========================================\n\n";

    cout << "Objetivo:\n";
    cout << "- Alcançar a peça de valor 2048.\n\n";

    cout << "Controles:\n";
    cout << "- W : mover para cima\n";
    cout << "- A : mover para esquerda\n";
    cout << "- S : mover para baixo\n";
    cout << "- D : mover para direita\n\n";

    cout << "Regras:\n";
    cout << "- A cada movimento surge uma nova peça.\n";
    cout << "- Peças iguais se unem.\n";
    cout << "- O jogo termina quando não houver movimentos possiveís.\n";
}

int randomNumber() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(0,3);
    return dist(gen);
}

void printBoard(int board[4][4]) {
    clear();

    for(int i=0;i<4;i++) {

        for(int j=0;j<4;j++) {

            cout << board[i][j] << " ";
        }

        cout << endl;
    }
}
void WASD(int board[4][4]){

    char tecla;
    cout << "\nMovimento (W A S D): ";
    cin >> tecla;

    while(tecla!='w' && tecla!='W' &&
          tecla!='a' && tecla!='A' &&
          tecla!='s' && tecla!='S' &&
          tecla!='d' && tecla!='D'){

        cout << "Digite uma tecla valida: ";
        cin >> tecla;
    }

    switch(tecla){

    case 'w':
    case 'W':

        for(int j=0;j<4;j++){
            for(int i=1;i<4;i++){

                if(board[i][j]!=0){

                    int k=i;

                    while(k>0 && board[k-1][j]==0){

                        board[k-1][j]=board[k][j];
                        board[k][j]=0;
                        k--;

                    }

                }

            }
        }

        break;

    case 's':
    case 'S':

        for(int j=0;j<4;j++){
            for(int i=2;i>=0;i--){

                if(board[i][j]!=0){

                    int k=i;

                    while(k<3 && board[k+1][j]==0){

                        board[k+1][j]=board[k][j];
                        board[k][j]=0;
                        k++;

                    }

                }

            }
        }

        break;

    case 'a':
    case 'A':

        for(int i=0;i<4;i++){
            for(int j=1;j<4;j++){

                if(board[i][j]!=0){

                    int k=j;

                    while(k>0 && board[i][k-1]==0){

                        board[i][k-1]=board[i][k];
                        board[i][k]=0;
                        k--;

                    }

                }

            }
        }

        break;

    case 'd':
    case 'D':

        for(int i=0;i<4;i++){
            for(int j=2;j>=0;j--){

                if(board[i][j]!=0){

                    int k=j;

                    while(k<3 && board[i][k+1]==0){

                        board[i][k+1]=board[i][k];
                        board[i][k]=0;
                        k++;

                    }

                }

            }
        }

        break;
    }

    printBoard(board);
}

void start(){

    clear();

    char nick[5];

    cout << "Digite seu nick (4 caracteres): ";

    cin.ignore();

    cin.getline(nick,5);

    int board[4][4]={0};

    int points=0;

    int l1,c1,l2,c2;

    do{

        l1=randomNumber();
        c1=randomNumber();
        l2=randomNumber();
        c2=randomNumber();

    }while(l1==l2 && c1==c2);

    board[l1][c1]=2;
    board[l2][c2]=4;

    while(true){

        printBoard(board);

        cout << "\nJogador: " << nick;
        cout << "\nPontos: " << points << endl;

        WASD(board);

    }

}
void menu() {

    int opcao;

    do {

        clear();

        cout << R"(

 ██████╗  ██████╗ ██╗  ██╗ █████╗
 ╚════██╗██╔═████╗██║  ██║██╔══██╗
  █████╔╝██║██╔██║███████║╚█████╔╝
 ██╔═══╝ ████╔╝██║╚════██║██╔══██╗
 ███████╗╚██████╔╝     ██║╚█████╔╝
 ╚══════╝ ╚═════╝      ╚═╝ ╚════╝

===================================
         MENU PRINCIPAL
===================================
[1] Iniciar Jogo
[2] Ver Ranking
[3] Como Jogar
[0] Sair
===================================

Escolha uma opcao: )";

        cin >> opcao;

        switch(opcao){

        case 1:
            start();
            break;

        case 2:

            clear();
            cout << "Ranking ainda nao implementado.\n";
            break;

        case 3:

            rules();
            break;

        case 0:

            cout << "\nObrigado por jogar!\n";
            break;

        default:

            cout << "\nOpção invalida!\n";
        }

        if(opcao != 0 && opcao != 1){

            cout << "\n\nPressione ENTER para voltar ao menu...";

            cin.ignore(1000,'\n');
            cin.get();

        }

    }while(opcao != 0);
}

int main(){

    menu();

    return 0;
}