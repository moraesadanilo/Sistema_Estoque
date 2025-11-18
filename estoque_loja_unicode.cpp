#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Produto {
private:
    string nome;
    double preco;
    int saldo_estoque;
    
public:
//CONSTRUTOR://
    Produto(string n, double p, int s){
        nome=n;
        preco=p;
        saldo_estoque=s;
    };
    Produto(string n, double p){
        nome=n;
        preco=p;
        saldo_estoque= 0;
    };
    Produto(string n){
        nome=n;
        preco=0;
        saldo_estoque= 0;
    };
//ENTRADAS E MODIFICAÇÕES//
    void entrada(Produto &item, int qtd){
        if(qtd>0){
            item.saldo_estoque+=qtd;
            cout<<"Entrada realizada com sucesso. Novo estoque: "<<item.getsaldo_estoque()<<endl;
        }else{
            cout<<"Valor invalido!"<<endl;
        }
    };
    void alterapreco(Produto &item, double valor){
        if(valor>=0 && valor!=item.preco){
            item.preco=valor;
            cout<<"Preço alterado com sucesso. Novo preço: "<<item.getpreco()<<endl;
        }else{
            cout<<"Valor invalido!"<<endl;
            //valor igual anterior
        }
            
    };
    // SETTERS - para modificar com validação 
    void setNome(string n){ 
        if (n.length() > 0) { 
            nome = n; 
        }else { 
        cout << "Erro: Nome não pode ser vazio!" << endl; 
            nome = "Sem nome"; 
        } 
    }
    
    //SAIDAS E CONSULTAS//
        void saida(Produto &item, int qtd){
            if(saldo_estoque>qtd){
              item.saldo_estoque-=qtd;
              cout<<"Entrada realizada com sucesso. Novo estoque: "<<item.getsaldo_estoque()<<endl;
            }else{
                cout<<"Valor invalido!"<<endl;
            }
        };
        void exibirproduto(){
            cout<<"Item: "<<nome<< " | Preco: "<<preco<< " | Estoque atual: "<<saldo_estoque<<endl;
        };
        
        string getnome(){
            return nome;
        }
        double getpreco(){
            return preco;
        }
        int getsaldo_estoque(){
            return saldo_estoque;
        }

};


int main() {
    Produto item1("Celular", 2000, 1);
    Produto item2("Camisa", 24.9);
    Produto item3("Vinho");
    item1.exibirproduto();
    item2.exibirproduto();
    item3.exibirproduto();

    return 0;
}
