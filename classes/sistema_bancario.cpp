#include <iostream>
#include <string>
#include <iomanip> //biblioteca pra determinar a quantidade de casas decimais
#include <locale.h> //biblioteca pra determinar o uso correto de acentua��o e pontua��o

using namespace std;

class Cliente {
    private:
        string nome, cpf;
    public:
        // M�todo para obter o nome do cliente
        string getnome(){
            return nome;
        }
        // M�todo para obter o cpf do cliente
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
        Cliente &titular; //Refer�ncia ao cliente que � o titular da conta
    public:
        //Construtor da classe ContaBancaria
        ContaBancaria(int n, Cliente &t, double s=0): numero(n), titular(t), saldo(s){ //inicializa os atributos da classe ContaBancaria

        }
        // M�todo para depositar o valor em uma conta
        void depositar(double valor){
            saldo += valor;
        }
        // M�todo para sacar o valor de uma conta
        void sacar(double valor){
            if(valor <= saldo){
                saldo-=valor;
            }
            else{
                cout << "Saldo insuficente para saldo." << endl;
            }
        }
        // M�todo para transferir um valor de uma conta para outra
        void transferir(double valor, ContaBancaria &destino){
            if(valor <= saldo){
                saldo -= valor;
                destino.depositar(valor);
                cout << "Transferido: R$ " << valor << " da conta " << numero << " para a conta " << destino.numero << endl;
            }
            else{
                cout << "N�o tem como transferir o valor pois o saldo est� insuficente!";
            }
        }
        // M�todo para transferir o valor igualmente para duas contas distintas
        void transferir(double valor, ContaBancaria &destino1, ContaBancaria &destino2){
            double valor_por_conta = valor / 2;
            if(valor <= saldo){
                saldo -= valor;
                destino1.depositar(valor_por_conta);
                destino2.depositar(valor_por_conta); 
                cout << "Transferido: R$ " << valor_por_conta << " para cada conta ( " << destino1.numero << " e " << destino2.numero << " ) da conta " << numero << endl;
            }
            else{
                cout << "N�o h� valor suficiente para fazer o dep�sito!" << endl;
            }
            }
        // M�todo para exibir o saldo atual da conta
        void exibirSaldo(){
            cout << "Saldo atual da conta " << numero << ": R$ " << fixed << setprecision(0) << saldo << endl;
        }
        // M�todo para exibir as informa��es da conta
        void exibirInformacoes(){
            cout << "Titular: " << titular.getnome() << ", ";
            cout << "CPF: " << titular.getcpf() << endl;
            cout << "N�mero da Conta: " << numero << ", Saldo: R$ " << saldo << endl;
        }


        };



int main() {
    // Define a localidade para uso correto da acentua��o
    setlocale(LC_ALL, "portuguese");
    // Cria��o dos clientes
    Cliente cliente1("Ana", "111.111.111-11");
    Cliente cliente2("Bruno", "222.222.222-22");
    Cliente cliente3("Carla", "333.333.333-33");

    // Cria��o das contas banc�rias com saldos iniciais
    ContaBancaria conta1(1001, cliente1, 1000.0);
    ContaBancaria conta2(1002, cliente2);
    ContaBancaria conta3(1003, cliente3);

    // Exibe o saldo inicial da conta de Ana
    conta1.exibirSaldo();

    // Ana transfere R$200 para Bruno
    conta1.transferir(200.0, conta2);

    // Ana transfere R$300 divididos entre Bruno e Carla
    conta1.transferir(300.0, conta2, conta3);

    // Exibi��o dos saldos finais
    cout << endl;
    conta1.exibirInformacoes();
    conta2.exibirInformacoes();
    conta3.exibirInformacoes();

    return 0;
}
