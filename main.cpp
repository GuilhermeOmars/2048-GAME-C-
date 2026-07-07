#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;

struct jogador {
    char nick[6]; 
    int points = 0;
    long tempo = 0;
};

const string ARQUIVO_RANKING = "ranking.txt";

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
    cout << "- O jogo termina quando não houver movimentos possíveis.\n";
}

int randomNumber() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 3);
    return dist(gen);
}

void spawnNumber(int board[4][4]) {
    bool vazio = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                vazio = true;
            }
        }
    }
    if (!vazio) return;

    int linha, coluna;
    do {
        linha = randomNumber();
        coluna = randomNumber();
    } while (board[linha][coluna] != 0);

    if (randomNumber() == 0)
        board[linha][coluna] = 4;  
    else
        board[linha][coluna] = 2; 
}

string getColor(int value) {
    switch (value) {
        case 2:    return "\033[38;5;251m"; 
        case 4:    return "\033[38;5;222m"; 
        case 8:    return "\033[38;5;208m"; 
        case 16:   return "\033[38;5;202m"; 
        case 32:   return "\033[38;5;196m"; 
        case 64:   return "\033[38;5;160m"; 
        case 128:  return "\033[38;5;228m"; 
        case 256:  return "\033[38;5;220m"; 
        case 512:  return "\033[38;5;114m"; 
        case 1024: return "\033[38;5;42m";  
        case 2048: return "\033[38;5;45m";  
        default:   return "\033[38;5;93m";  
    }
}

void printBoard(int board[4][4]) {
    clear();
    cout << "============= 2048 =============\n\n";
    for (int i = 0; i < 4; i++) {
        cout << "  ";
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                cout << "\033[0m" << setw(5) << ".";
            } else {
                cout << getColor(board[i][j]) << setw(5) << board[i][j] << "\033[0m";
            }
        }
        cout << "\n\n";
    }
    cout << "================================\n";
}

int loadRanking(jogador lista[]) {
    ifstream arq(ARQUIVO_RANKING, ios::in);
    if (!arq) return 0; 

    int qtd = 0;
    while (qtd < 5 && arq >> lista[qtd].nick >> lista[qtd].points >> lista[qtd].tempo) {
        qtd++;
    }
    arq.close();
    return qtd;
}

void saveRanking(jogador lista[], int qtd) {
    ofstream arq(ARQUIVO_RANKING, ios::out);
    if (!arq) return;

    for (int i = 0; i < qtd && i < 5; i++) {
        arq << lista[i].nick << " " << lista[i].points << " " << lista[i].tempo << "\n";
    }
    arq.close();
}

void updateRanking(jogador novo) {
    jogador lista[6];
    int qtd = loadRanking(lista);

    lista[qtd] = novo;
    qtd++;

    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (lista[i].points < lista[j].points || 
               (lista[i].points == lista[j].points && lista[i].tempo > lista[j].tempo)) {
                jogador temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }

    if (qtd > 5) qtd = 5; 
    saveRanking(lista, qtd);
}

void placar() {
    clear();
    cout << "=========================================\n";
    cout << "                RANKING\n";
    cout << "=========================================\n\n";
    
    jogador lista[5];
    int qtd = loadRanking(lista);

    if (qtd == 0) {
        cout << "Nenhum registro encontrado ainda!\n";
    } else {
        for (int i = 0; i < qtd; i++) {
            cout << i + 1 << " - " << setw(5) << left << lista[i].nick 
                 << " " << lista[i].points << " Tempo: " << lista[i].tempo << "s\n";
        }
    }
}

bool checkWin(int board[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 2048) return true;
        }
    }
    return false;
}

bool checkGameOver(int board[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) return false; 
            if (i < 3 && board[i][j] == board[i+1][j]) return false; 
            if (j < 3 && board[i][j] == board[i][j+1]) return false; 
        }
    }
    return true; 
}

bool WASD(int board[4][4], jogador &info_atual) {
    char tecla;
    cout << "\nMovimento (W A S D) ou Sair (Q): ";
    
    auto inicio = chrono::steady_clock::now();
    cin >> tecla;
    auto fim = chrono::steady_clock::now();
    info_atual.tempo += chrono::duration_cast<chrono::seconds>(fim - inicio).count();

    tecla = tolower(tecla);
    while (tecla != 'w' && tecla != 'a' && tecla != 's' && tecla != 'd' && tecla != 'q') {
        cout << "Digite uma tecla valida: ";
        inicio = chrono::steady_clock::now();
        cin >> tecla;
        fim = chrono::steady_clock::now();
        info_atual.tempo += chrono::duration_cast<chrono::seconds>(fim - inicio).count();
        tecla = tolower(tecla);
    }

    if (tecla == 'q') return false; 

    int copia[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) copia[i][j] = board[i][j];
    }

    bool combinado[4][4] = {false}; 

    if (tecla == 'w') {
        for (int j = 0; j < 4; j++) {
            for (int i = 1; i < 4; i++) {
                if (board[i][j] != 0) {
                    int k = i;
                    while (k > 0 && board[k - 1][j] == 0) {
                        board[k - 1][j] = board[k][j];
                        board[k][j] = 0;
                        k--;
                    }
                    if (k > 0 && board[k - 1][j] == board[k][j] && !combinado[k - 1][j]) {
                        board[k - 1][j] *= 2;
                        info_atual.points += board[k - 1][j]; 
                        board[k][j] = 0;
                        combinado[k - 1][j] = true; 
                    }
                }
            }
        }
    }
    else if (tecla == 's') {
        for (int j = 0; j < 4; j++) {
            for (int i = 2; i >= 0; i--) {
                if (board[i][j] != 0) {
                    int k = i;
                    while (k < 3 && board[k + 1][j] == 0) {
                        board[k + 1][j] = board[k][j];
                        board[k][j] = 0;
                        k++;
                    }
                    if (k < 3 && board[k + 1][j] == board[k][j] && !combinado[k + 1][j]) {
                        board[k + 1][j] *= 2;
                        info_atual.points += board[k + 1][j]; 
                        board[k][j] = 0;
                        combinado[k + 1][j] = true; 
                    }
                }
            }
        }
    }
    else if (tecla == 'a') {
        for (int i = 0; i < 4; i++) {
            for (int j = 1; j < 4; j++) {
                if (board[i][j] != 0) {
                    int k = j;
                    while (k > 0 && board[i][k - 1] == 0) {
                        board[i][k - 1] = board[i][k];
                        board[i][k] = 0;
                        k--;
                    }
                    if (k > 0 && board[i][k - 1] == board[i][k] && !combinado[i][k - 1]) {
                        board[i][k - 1] *= 2;
                        info_atual.points += board[i][k - 1]; 
                        board[i][k] = 0;
                        combinado[i][k - 1] = true; 
                    }
                }
            }
        }
    }
    else if (tecla == 'd') {
        for (int i = 0; i < 4; i++) {
            for (int j = 2; j >= 0; j--) {
                if (board[i][j] != 0) {
                    int k = j;
                    while (k < 3 && board[i][k + 1] == 0) {
                        board[i][k + 1] = board[i][k];
                        board[i][k] = 0;
                        k++;
                    }
                    if (k < 3 && board[i][k + 1] == board[i][k] && !combinado[i][k + 1]) {
                        board[i][k + 1] *= 2;
                        info_atual.points += board[i][k + 1]; 
                        board[i][k] = 0; // Corrigido aqui de board[k][j] para board[i][k]
                        combinado[i][k + 1] = true; 
                    }
                }
            }
        }
    }

    bool mudou = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != copia[i][j]) mudou = true;
        }
    }

    if (mudou) { 
        spawnNumber(board); 
    }

    return true;
}

void start(jogador info[]) {
    clear();
    cout << "Digite seu nick (4 caracteres): ";
    
    jogador p; 
    cin >> p.nick;

    int board[4][4] = {0}; 

    spawnNumber(board);
    spawnNumber(board);

    while (true) {
        printBoard(board);

        cout << "\nJogador: " << p.nick;
        cout << "\nPontos: " << p.points << "\n";

        if (checkWin(board)) { 
            printBoard(board);
            cout << "\nPARABENS! Voce alcancou a peca 2048 e venceu!\n";
            updateRanking(p); 
            break;
        }

        if (checkGameOver(board)) { 
            printBoard(board);
            cout << "\nFIM DE JOGO! Nao ha mais movimentos possiveis.\n";
            updateRanking(p); 
            break;
        }

        if (!WASD(board, p)) {
            cout << "\nPartida encerrada. Gravando dados no ranking...\n";
            updateRanking(p); 
            break;
        }
    }
    
    cout << "\nPressione ENTER para continuar...";
    cin.get();
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

        if (!(cin >> opcao)) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcao = -1;
        }

        switch (opcao) {
            case 1:
                start(info);
                break;
            case 2:
                placar();
                break;
            case 3:
                rules();
                break;
            case 0:
                cout << "\nObrigado por jogar!\n";
                break;
            default:
                cout << "\nOpcao invalida!\n";
        }

        if (opcao != 0 && opcao != 1) {
            cout << "\n\nPressione ENTER para voltar ao menu...";
            cin.ignore(1, '\n');
            cin.get();
        }

    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}