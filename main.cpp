#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;

const int SIZE = 4;
int board[SIZE][SIZE];
int points = 0;

 void clear() {cout<< "\033[2J\033[1;1H";}
 void start(){
    clear();
}
void rules(){
    clear();
     cout << "=========================================\n";
    cout << "            COMO JOGAR 2048\n";
    cout << "=========================================\n\n";

    cout << "Objetivo:\n";
    cout << "- Alcancar a peca de valor 2048.\n\n";

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
    cin.ignore();
    cin.get();
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