#include "Produto.h"
#include <iostream>

// ############ IMPLEMENTAÇÕES ##########
//CONSTRUTOR://
//Produto::Produto(string n, double u, int s) : nome(n), valor_unit(u), saldo_estoque(s){}
Produto::Produto(string n, double u) : nome(n), valor_unit(u), saldo_estoque(0){}
Produto::Produto(string n) : nome(n), valor_unit(0), saldo_estoque(0){} 
// construtor padrão, inicializa com valores neutros
Produto::Produto() {
        setNome("");
        setValorUni(0.0);
        setSaldoEst(0);
}
//com validação
Produto::Produto(string n, double u, int s){ 
    setNome(n);      
    setValorUni(u);     
    setSaldoEst(s);    
} 

//ENTRADAS E MODIFICAÇÕES//
void Produto::entrada(Produto &item, int qtd){
        if(qtd>0){
            item.saldo_estoque+=qtd;
            cout<<"Entrada realizada com sucesso. Novo estoque: "<<item.getSaldo_estoque()<<endl;
        }else{
            cout<<"Valor invalido!"<<endl;
        }
};
void Produto::alteraPreco(Produto &item, double valor){
    if(valor>=0 && valor!=item.valor_unit){
        item.valor_unit=valor;
        cout<<"Preço alterado com sucesso. Novo preço: "<<item.getValor_unit()<<endl;
    }else{
        cout<<"Valor invalido!"<<endl;
        //valor igual anterior
    }
            
};
// SETTERS - para modificar com validação 
void Produto::setNome(string n){ 
    if (n.length() > 0) { 
        nome = n; 
    }else { 
    cout << "Erro: Nome não pode ser vazio!" << endl; 
        nome = "Sem nome"; 
    } 
};
void Produto::setValorUni(double u){
    if (u > 0 ) { 
            valor_unit = u;
        } 
    else { 
    cout << "Erro: Valor inválido! Mantendo valor anterior." <<endl;} 
};     
void Produto::setSaldoEst(int s){
    if (s > 0 ) { 
         saldo_estoque = s;
        } else { 
            cout << "Erro: Valor inválido! Mantendo valor anterior." <<endl;
        }
};

//SAIDAS E CONSULTAS//
    bool Produto::saida(Produto &item, int qtd){
            if(qtd<=0){
                cout<<"ERRO! Valor invalido."<<endl;
                return false;
            } else if(saldo_estoque>=qtd){
              item.saldo_estoque-=qtd;
              return true;
              //cout<<"Solicitacao atendida;
            }else{
                cout<<"Saldo insuficiente no estoque!"<<endl;
                return false;
            }
    };
    
    //Calcular valor total de cada item 
    double Produto::calcularValorTotalItem() const{
        return valor_unit * saldo_estoque;
    }
    
    // Exibe informações do produto
    void Produto::exibirproduto()const{
            cout<<"Item: "<<nome<< " | Valor unitario: "<<valor_unit<< " | Estoque atual: "<<saldo_estoque<<endl;
    };
    string Produto::getNome() const{
        return nome;
    };
    /*string Produto::getcategoria() const{
            return categoria;
    };*/
    double Produto::getValor_unit() const{
            return valor_unit;
    };
    int Produto::getSaldo_estoque() const{
            return saldo_estoque;
    };
