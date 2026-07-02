#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

void clear() {cout<< "\033[2J\033[1;1H";}

void rules(){
    clear();
    cout << "=========================================\n";
    cout << "            COMO JOGAR 2048\n";
    cout << "=========================================\n\n";

    cout << "Objetivo:\n";
    cout << "- Alcancar a peça de valor 2048.\n\n";

    cout << "Controles:\n";
    cout << "- W : mover para cima\n";
    cout << "- A : mover para a esquerda\n";
    cout << "- S : mover para baixo\n";
    cout << "- D : mover para a direita\n\n";

    cout << "Regras:\n";
    cout << "- A cada movimento surge uma nova peca (2 ou 4).\n";
    cout << "- Pecas com o mesmo valor se unem ao colidir.\n";
    cout << "- O valor da nova peca sera a soma das duas.\n";
    cout << "- O jogo termina quando nao houver mais movimentos possiveis.\n\n";
    cout << "Pressione ENTER para voltar ao menu...";
}

int randomNumber(){
    random_device rd;
    mt19937 generate(rd());
    uniform_int_distribution<int> distribution(0,3);
    return distribution(generate);
}
void printBoard (int board[4][4]){
     for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout<<board[i][j] << " ";
            if(j+1 == 4){
                cout<< "\n";
            }
        }
        
    }
}
void WASD(int board[4][4]){
    
    char tecla;
    cin>>tecla;
    while(tecla != 'w' && tecla != 'W' && tecla != 'a' && tecla != 'A' && tecla != 's' && tecla != 'S' && tecla != 'd' && tecla != 'D'){
        cout << "\nDigite uma tecla válida\n";
        cin>>tecla;
    }
    switch (tecla) {
                case 'w': case 'W':
                    for (int i = 0; i < 4; i++){
                        for (int j = 0; j < 4; j++){
                            while(board[i][j] == 0 && (board[i+1][j]!=0||board[i+2][j]!=0||board[i+3][j]!=0)){
                                for (int k = i+1; k < 4; k++){
                                    if(board[k][j] != 0){
                                        board[i][j] = board[k][j];
                                        board[k][j] = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        
                    }

                case 'a': case 'A':
                    for(int i = 0; i < 4; i++){
                        for (int j = 0; j < 4; j++){
                            while(board[i][j] == 0 && (board[i][j+1]!=0||board[i][j+2]!=0||board[i][j+3]!=0)){
                                for (int k = j+1; k < 4; k++){
                                    if(board[i][k] != 0){
                                        board[i][j] = board[i][k];
                                        board[i][k] = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        
                    }

                case 's': case 'S':
                    for(int i = 3; i >= 0; i--){
                        for (int j = 0; j < 4; j++){
                            while(board[i][j] == 0 && (board[i-1][j]!=0||board[i-2][j]!=0||board[i-3][j]!=0)){
                                for (int k = i-1; k >= 0; k--){
                                    if(board[k][j] != 0){
                                        board[i][j] = board[k][j];
                                        board[k][j] = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        
                    }

                case 'd': case 'D':
                    for(int i = 0; i < 4; i++){
                        for (int j = 3; j >= 0; j--){
                            while(board[i][j] == 0 && (board[i][j-1]!=0||board[i][j-2]!=0||board[i][j-3]!=0)){
                                for (int k = j-1; k >= 0; k--){
                                    if(board[i][k] != 0){
                                        board[i][j] = board[i][k];
                                        board[i][k] = 0;
                                        break;
                                    }
                                }
                            }
                        }
                        
                    }
            }
}
void start(){
    clear();
    char nick[4];
    cout<<" Digite seu nick (3 caracteres): \n";
    cin.getline(nick, 4);
    clear();
    int board[4][4] = {0};
    int points;
    board[randomNumber()][randomNumber()] = 2;
    board[randomNumber()][randomNumber()] = 4;
    printBoard(board);
    
    
    
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

            switch (opcao) {
                case 1:
                    start();
                    break;

                case 2:
                    break;

                case 3:
                    rules();
                    break;

                case 0:
                    cout << "\nObrigado por jogar\n";
                    break;

                default:
                    cout << "\nOpcao invalida\n";
            }
            if (opcao != 0) {
                cout << "Pressione ENTER para voltar ao menu...";
                cin.ignore();
                cin.get();
            }
        } while (opcao != 0);
    }

int main (){
    menu();
    

    return 0;
}