#include <iostream>
#include <string>
#include <iomanip> //biblioteca pra determinar a quantidade de casas decimais
#include <locale.h> //biblioteca pra determinar o uso correto de acentuação e pontuação

using namespace std;

class Cliente {
    private:
        string nome, cpf;
    public:
        // Método para obter o nome do cliente
        string getnome(){
            return nome;
        }
        // Método para obter o cpf do cliente
        string getcpf(){
            return cpf;
        }
        //construtor da classe Cliente
        Cliente(string n, string c){
            nome = n;
            cpf = c;
        }
};

class ContaBancaria {
    private:
        int numero;
        double saldo;
        Cliente &titular; //Referência ao cliente que é o titular da conta
    public:
        //Construtor da classe ContaBancaria
        ContaBancaria(int n, Cliente &t, double s=0): numero(n), titular(t), saldo(s){ //inicializa os atributos da classe ContaBancaria

        }
        // Método para depositar o valor em uma conta
        void depositar(double valor){
            saldo += valor;
        }
        // Método para sacar o valor de uma conta
        void sacar(double valor){
            if(valor <= saldo){
                saldo-=valor;
            }
            else{
                cout << "Saldo insuficente para saldo." << endl;
            }
        }
        // Método para transferir um valor de uma conta para outra
        void transferir(double valor, ContaBancaria &destino){
            if(valor <= saldo){
                saldo -= valor;
                destino.depositar(valor);
                cout << "Transferido: R$ " << valor << " da conta " << numero << " para a conta " << destino.numero << endl;
            }
            else{
                cout << "Não tem como transferir o valor pois o saldo está insuficente!";
            }
        }
        // Método para transferir o valor igualmente para duas contas distintas
        void transferir(double valor, ContaBancaria &destino1, ContaBancaria &destino2){
            double valor_por_conta = valor / 2;
            if(valor <= saldo){
                saldo -= valor;
                destino1.depositar(valor_por_conta);
                destino2.depositar(valor_por_conta); 
                cout << "Transferido: R$ " << valor_por_conta << " para cada conta ( " << destino1.numero << " e " << destino2.numero << " ) da conta " << numero << endl;
            }
            else{
                cout << "Não há valor suficiente para fazer o depósito!" << endl;
            }
            }
        // Método para exibir o saldo atual da conta
        void exibirSaldo(){
            cout << "Saldo atual da conta " << numero << ": R$ " << fixed << setprecision(0) << saldo << endl;
        }
        // Método para exibir as informações da conta
        void exibirInformacoes(){
            cout << "Titular: " << titular.getnome() << ", ";
            cout << "CPF: " << titular.getcpf() << endl;
            cout << "Número da Conta: " << numero << ", Saldo: R$ " << saldo << endl;
        }


        };



int main() {
    // Define a localidade para uso correto da acentuação
    setlocale(LC_ALL, "portuguese");
    // Criação dos clientes
    Cliente cliente1("Ana", "111.111.111-11");
    Cliente cliente2("Bruno", "222.222.222-22");
    Cliente cliente3("Carla", "333.333.333-33");

    // Criação das contas bancárias com saldos iniciais
    ContaBancaria conta1(1001, cliente1, 1000.0);
    ContaBancaria conta2(1002, cliente2);
    ContaBancaria conta3(1003, cliente3);

    // Exibe o saldo inicial da conta de Ana
    conta1.exibirSaldo();

    // Ana transfere R$200 para Bruno
    conta1.transferir(200.0, conta2);

    // Ana transfere R$300 divididos entre Bruno e Carla
    conta1.transferir(300.0, conta2, conta3);

    // Exibição dos saldos finais
    cout << endl;
    conta1.exibirInformacoes();
    conta2.exibirInformacoes();
    conta3.exibirInformacoes();

    return 0;
}
