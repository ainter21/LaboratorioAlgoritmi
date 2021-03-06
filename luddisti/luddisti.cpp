#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <vector>


using namespace std;



int N;
int M;
int numeroKing = 0;


int *id;


struct nodo
{
    int nome;
    vector <int> vic;
    bool visitato=false;
    bool hasKing = false;
};

vector <nodo> grafo;





void ccdfs(int conta,int indiceNodo, int id[],vector <nodo>& grafoBucato);
void cc(vector <nodo>& grafoBucato,stack<nodo> S);

vector <nodo> creaGrafoBucato(int nodoDaRimuovere);

stack <nodo> creaStack(vector<nodo>& grafoBucato);

void controllaFoglie();

int main()
{

    ifstream in("input.txt");
    ofstream out("output.txt");
    in>>N>>M;

    grafo.resize(N);

    for(int i = 0; i < M; i++)
    {


        int from,to;
        in>>from>>to;

        grafo[from].vic.push_back(to);

        grafo[to].vic.push_back(from);
    }
    for (int i = 0; i < N; i++)
    {
        grafo[i].nome = i;
    }

    controllaFoglie();

    for(int i=0; i<N; i++){
    	
    	vector <nodo> grafoBucato = creaGrafoBucato(i);
    	stack <nodo> S = creaStack(grafoBucato);
    	cc(grafoBucato,S);

    }
	out << numeroKing<<endl;
    for (int i=0; i <N; i++){
    	if(grafo[i].hasKing){
    		out <<grafo[i].nome<<" ";
    	}
    }

    
    for(int i=0; i <N; i++){

    	//cout<<grafo[i].hasKing<<" ";
    }//cout << endl;


    



    return 0;
}






void  cc(vector <nodo>& grafoBucato, stack <nodo> S){
	id = new int[N];
    for(int i=0; i < N; i++){
        id[i]=0;

    }
    ////cout << "id settati a 0"<<endl;
    int conta = 0;
    while(!S.empty()){

        nodo u = S.top();
        //cout <<"Nodo in top = " <<u.nome<<endl;
        S.pop();

        if(id[u.nome]==0 && u.nome!=-1){

            //cout<<"id di " <<u.nome<<" = 0"<<endl;
            conta +=1;
            ccdfs(conta,u.nome,id,grafoBucato);
        }
    }


    //cout <<"id{ ";
    for(int i=0;i<N;i++){
    	//cout << id[i]<<" ";
    }//cout<<"}"<<endl;

    //cout <<"Conta = "<<conta<<endl;    
    for(int i=1; i <= conta;i++){
    	bool componenteHasKing = false;

    	for(int j=0; j<N && componenteHasKing==false; j++){

    		//cout<<"Il nodo "<<grafoBucato[j].nome<<" appartiene alla componenete connessa "<<id[j]<<", verifico la "<<i<<" componente"<<endl;

    		if(id[j]==i && grafoBucato[j].nome!=-1){
    			//cout <<"j=i"<<endl;
    			if(grafoBucato[j].hasKing){
    				//cout <<"La componente connessa "<<i<<" ha un king"<<endl;
    				componenteHasKing=true;
    			}
    		}
    	}
    	if(!componenteHasKing){
    		//cout <<"entro ciclo"<<endl;
    		for(int k=0; k < N && componenteHasKing == false; k++)
    		{
    			if(id[k]==i && grafoBucato[k].nome!=-1){
    				componenteHasKing=true;
    				grafo[k].hasKing = true;
    				numeroKing+=1;
    				//cout <<"NodoKing = "<<grafo[k].nome<<endl;
    				//cout << "NumeroKing = "<<numeroKing<<endl;
    			}
    		}
    		
    	}
    }
    
}


void ccdfs(int conta,int indiceNodo, int id[],vector <nodo>& grafoBucato){

    id[indiceNodo]=conta;
    for(int i=0; i<grafoBucato[indiceNodo].vic.size();i++){
            //cout << "Guardo i vicini del nodo " <<indiceNodo<<endl;
        if(id[grafoBucato[indiceNodo].vic[i]]==0){
            //cout <<"Trovato vicino raggiungibile"<<endl;
                //temporaneo+=1;
            ccdfs(conta,grafoBucato[indiceNodo].vic[i],id,grafoBucato);
        }
    }

}

void controllaFoglie(){


	for(int i=0; i < N;i++){

		if(grafo[i].vic.size()==1 || grafo[i].vic.size()==0){

			grafo[i].hasKing=true;
			numeroKing+=1;
			//cout<<"NumeroKing  = "<<numeroKing <<endl;

		}



	}
}

vector <nodo> creaGrafoBucato(int nodoDaRimuovere){


	ifstream in1("input.txt");
   
    in1>>N>>M;

    vector<nodo> risultato;
    risultato.resize(N);

    for(int i = 0; i < M; i++)
    {


        int from,to;
        in1>>from>>to;

        if(from!= nodoDaRimuovere && to!= nodoDaRimuovere){
			risultato[from].vic.push_back(to);

        	risultato[to].vic.push_back(from);
        }

    }
    for (int i = 0; i < N; i++)
    {

    	if(i==nodoDaRimuovere){
    		risultato[i].nome = -1;
    	}else{
    		risultato[i].nome = i;
    	}
        
    }
    for(int i=0; i<N;i++){
    	if(grafo[i].hasKing){
    		risultato[i].hasKing=true;
    	}
    }

    return risultato;


    in1.close();

}


stack <nodo> creaStack(vector<nodo>& grafoBucato){


	stack <nodo> risultato;
	for(int i=0; i < N;i++){
		risultato.push(grafoBucato[i]);
	}

	return risultato;

}