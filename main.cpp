#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

struct jogador{
    char nick[5];
    int points = 0;
};

int indice = 0;

void menu();

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
    cout << "- D : mover para direita\n";
    cout << "- Q : sair do jogo\n\n";

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
    void spawnNumber(int board[4][4]){

    bool vazio = false;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(board[i][j] == 0){
                vazio = true;
            }
        }
    }

    if(!vazio)
        return;

    int linha, coluna;

    do{
        linha = randomNumber();
        coluna = randomNumber();
    }while(board[linha][coluna] != 0);

    if(randomNumber() == 0)
        board[linha][coluna] = 4;  
    else
        board[linha][coluna] = 2; 
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
void placar(jogador info[]){
    clear();
    cout << "=========================================\n";
    cout << "                RANKING\n";
    cout << "=========================================\n\n";
    int num = 1;
    jogador maior, menor;
    for(int i = 0; i<indice; i++){
        for(int f = i + 1; f<indice; f++){
            if(info[i].points<info[f].points){
                maior = info[f];
                menor = info[i];
                info[i] = maior;
                info[f] = menor;
                
            }
            else if(info[i].points>info[f].points){
                maior = info[i];
                menor = info[f];
                info[i] = maior;
                info[f] = menor;
            }
            else{
                maior = info[i];
                menor = info[f];
                info[i] = maior;
                info[f] = menor;
            }
        }
    }
    for(int k = 0; k<indice; k++)
    {
        cout<<num<<" - "<<info[k].nick<<" "<<info[k].points<<"\n";
        num++;
    }
}
bool WASD(int board[4][4]){

    char tecla;
    cout << "\nMovimento (W A S D): ";
    cout << "\nSair (Q): ";
    cin >> tecla;

    while(tecla!='w' && tecla!='W' &&
          tecla!='a' && tecla!='A' &&
          tecla!='s' && tecla!='S' &&
          tecla!='d' && tecla!='D' &&
          tecla!='q' && tecla!='Q'){

        cout << "Digite uma tecla valida: ";
        cin >> tecla;
    }

    switch(tecla){

case 'w':
case 'W':

    for(int j = 0; j < 4; j++){
        for(int i = 1; i < 4; i++){

            if(board[i][j] != 0){

                int k = i;

                while(k > 0 && board[k-1][j] == 0){
                    board[k-1][j] = board[k][j];
                    board[k][j] = 0;
                    k--;
                }

                while(k > 0 &&
                      board[k-1][j] == board[k][j]){

                    board[k-1][j] += board[k][j];
                    board[k][j] = 0;
                    break;
                }
            }
        }
    }
    break;

case 's':
case 'S':

    for(int j = 0; j < 4; j++){
        for(int i = 2; i >= 0; i--){

            if(board[i][j] != 0){

                int k = i;

                while(k < 3 && board[k+1][j] == 0){
                    board[k+1][j] = board[k][j];
                    board[k][j] = 0;
                    k++;
                }

                while(k < 3 &&
                      board[k+1][j] == board[k][j]){

                    board[k+1][j] += board[k][j];
                    board[k][j] = 0;
                    break;
                }
            }
        }
    }
    break;

case 'a':
case 'A':

    for(int i = 0; i < 4; i++){
        for(int j = 1; j < 4; j++){

            if(board[i][j] != 0){

                int k = j;

                while(k > 0 && board[i][k-1] == 0){
                    board[i][k-1] = board[i][k];
                    board[i][k] = 0;
                    k--;
                }

                while(k > 0 &&
                      board[i][k-1] == board[i][k]){

                    board[i][k-1] += board[i][k];
                    board[i][k] = 0;
                    break;
                }
            }
        }
    }
    break;

case 'd':
case 'D':

    for(int i = 0; i < 4; i++){
        for(int j = 2; j >= 0; j--){

            if(board[i][j] != 0){

                int k = j;

                while(k < 3 && board[i][k+1] == 0){
                    board[i][k+1] = board[i][k];
                    board[i][k] = 0;
                    k++;
                }

                while(k < 3 &&
                      board[i][k+1] == board[i][k]){

                    board[i][k+1] += board[i][k];
                    board[i][k] = 0;
                    break;
                }
            }
        }
    }
    break;
        
    case 'q':
    case 'Q':
        return false;
        break;
    }
    printBoard(board);
    return true;
}

void start(jogador info[]){
    
    clear();

    cout << "Digite seu nick (4 caracteres): ";

    cin.ignore();

    cin.getline(info[indice].nick,5);

    int board[4][4]={0};

    int l1,c1,l2,c2;

    do{

        l1=randomNumber();
        c1=randomNumber();
        l2=randomNumber();
        c2=randomNumber();

    }while(l1==l2 && c1==c2);
    /* test de números enquanto a função que vai gerar o números nn estiver pronta
     board[l2][c1] =2; 
    board[l1][c2] = 4; */
    board[l1][c1]=2;
    board[l2][c2]=4;

    while(true){

        printBoard(board);

        cout << "\nJogador: " << info[indice].nick;
        cout << "\nPontos: " << info[indice].points << endl;

        if(!WASD(board)){
            indice++;
            return;
        }
    }

}
void menu() {

    int opcao;
    jogador info[10];
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
            start(info);
            break;

        case 2:

            placar(info);
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