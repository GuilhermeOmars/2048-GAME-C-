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
                    break;

                case 0:
                    cout << "\nObrigado por jogar!\n";
                    break;

                default:
                    cout << "\nOpcao invalida!\n";
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