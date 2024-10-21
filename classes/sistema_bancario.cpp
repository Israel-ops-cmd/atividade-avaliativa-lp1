#include <iostream>
#include <string>
#include <iomanip>
#include <locale.h>

using namespace std;

class Cliente {
    private:
        string nome, cpf;
    public:
        string getnome(){
            return nome;
        }
        string getcpf(){
            return cpf;
        }
        Cliente(string n, string c){
            nome = n;
            cpf = c;
        }
};

class ContaBancaria {
    private:
        int numero;
        double saldo;
        Cliente &titular;
    public:
        ContaBancaria(int n, Cliente &t, double s=0): numero(n), titular(t), saldo(s){

        }
        void depositar(double valor){
            saldo += valor;
        }
        void sacar(double valor){
            if(valor <= saldo){
                saldo-=valor;
            }
            else{
                cout << "Saldo insuficente para saldo." << endl;
            }
        }
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
        void exibirSaldo(){
            cout << "Saldo atual da conta " << numero << ": R$ " << fixed << setprecision(2) << saldo << endl;
        }
        void exibirInformacoes(){
            cout << "Titular: " << titular.getnome() << ", ";
            cout << "CPF: " << titular.getcpf() << endl;
            cout << "Número da Conta: " << numero << ", Saldo: R$ " << saldo << endl;
        }


        };



int main() {
    // Criação dos clientes
    setlocale(LC_ALL, "portuguese");
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
