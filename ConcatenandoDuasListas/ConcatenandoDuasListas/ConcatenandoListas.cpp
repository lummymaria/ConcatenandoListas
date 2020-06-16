#include <iostream>
#include <locale.h> // setlocale
#include <stdlib.h> // system
#include <string>   // Textos em geral

using namespace std;


struct Remedio {
	int codigo;
	string nomeLab;
	string pAtivo;
	float precoCompra;
	float precoVenda;
	string nomeRemedio;
	string validade;
};


// Estrutura do Nó - ok
struct No {
	Remedio dados;		// estrutura guardada dentro da lista
	No* proxNo;			// aponta para o próximo Nó da lista
};


// Nó início da lista
struct Lista {
	int qtdNo;
	No* inicio;
};



//prototipacoes
Lista* criarLista();

// Inserir

bool inserirListaFim(Lista* ptrLista, int codigo, string nomeLab, string pAtivo, float precoCompra, float precoVenda, string nomeRemedio, string validade);

// Exibir
void exibirLista(Lista* ptrLista);
// Liberar
void liberarLista(Lista* ptrLista);
// Concatenar
void concatenarLista(Lista* pmedControlado, Lista* pmedGenerico, Lista* pmedEmEstoque);

int main() {
	setlocale(LC_ALL, "Portuguese");

	Lista *pmedControlado, *pmedGenerico, *pmedEmEstoque;
	// CRIAR lista - ok
	pmedControlado = criarLista();
	pmedGenerico = criarLista();
	pmedEmEstoque = criarLista();

	// Insira, programaticamente, 5 medicamentos em cada lista.
	//--------------------------------------------------------
	// Inserção no FINAL
	//--------------------------------------------------------
	// lista medicamentos Controlados
	inserirListaFim(pmedControlado, 4, "Biosintetica", "nimesulida", 5.55, 20.50, "Allegra", "09/09/2020");
	inserirListaFim(pmedControlado, 5, "Eurofarma", "amoxicilina tri-hidratada", 10.55, 35.50, "Amoxicilina", "08/08/2020");
	inserirListaFim(pmedControlado, 6, "Biolab", "ondansetrona", 9.55, 25.50, "Vonau Flash", "07/07/2020");
	inserirListaFim(pmedControlado, 1, "Ache", "AAS", 2.55, 9.50, "Aspirina", "12/12/2020");
	inserirListaFim(pmedControlado, 2, "Bayer", "Metamizol", 3.70, 11.50, "Dipirona", "11/11/2020");
	
	//PERFUMARIA
	cout << "--------------------------------------------- " << endl;
	cout << "--------LISTA MEDICAMENTOS CONTROLADOS------- " << endl;
	cout << "--------------------------------------------- " << endl;
	exibirLista(pmedControlado);



	// lista medicamentos Genericos
	inserirListaFim(pmedGenerico, 3, "Pfizer", "ibuprofeno", 3.55, 14.50, "Advil", "10/10/2020");
	inserirListaFim(pmedGenerico, 7, "Cimed", "maleato de clorfeniramina + paracetamol", 10.55, 50.50, "Cimegripe", "09/12/2020");
	inserirListaFim(pmedGenerico, 8, "Ache", "gestodeno e etinilestradiol", 15.55, 35.50, "Alestra 20", "11/09/2020");
	inserirListaFim(pmedGenerico, 9, "Cimed", "Loratadina", 4.05, 12.50, "Loratamed", "23/08/2020");
	inserirListaFim(pmedGenerico, 10, "Altapharma", "Biotina", 1.55, 5.30, "hairUp", "06/06/2020");
	
	//PERFUMARIA
	cout << "--------------------------------------------- " << endl;
	cout << "--------LISTA MEDICAMENTOS GENERICOS--------- " << endl;
	cout << "--------------------------------------------- " << endl;
	exibirLista(pmedGenerico);

	// Lista concatenada
	concatenarLista(pmedControlado, pmedGenerico, pmedEmEstoque);

	//PERFUMARIA
	cout << "--------------------------------------------- " << endl;
	cout << "--------LISTA MEDICAMENTOS COMPLETA---------- " << endl;
	cout << "--------------------------------------------- " << endl;
	exibirLista(pmedEmEstoque);
	
	// liberando as listas
	liberarLista(pmedControlado);
	liberarLista(pmedGenerico);
	liberarLista(pmedEmEstoque);

	system("pause");
	return 0;
}

//--------------------------------------------------------
// CRIAR LISTA - ok
//--------------------------------------------------------
Lista* criarLista() {
	Lista* ptrLista;

	ptrLista = new Lista;

	// Se a lista NÃO pode ser criada
	if (ptrLista == NULL) {
		cout << "Não foi possível criar a lista!" << endl;
		return NULL;
	}

	// Como a lista está vazia, o INÍCIO aponta para NULL	
	ptrLista->qtdNo = 0;
	ptrLista->inicio = NULL;

	return ptrLista;
}


//--------------------------------------------------------
// LIBERAR LISTA
//--------------------------------------------------------
void liberarLista(Lista* ptrLista) {
	No* ptrNoAtual;

	//Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return;
	}

	// Exclui cada Nó da lista
	while (ptrLista->inicio != NULL)
	{
		ptrNoAtual = ptrLista->inicio;

		ptrLista->inicio = ptrNoAtual->proxNo;

		delete  ptrNoAtual;
	}

	delete ptrLista;
}


//--------------------------------------------------------
// INSERIR NO FINAL DA LISTA - ok
//--------------------------------------------------------
bool inserirListaFim(Lista* ptrLista, int codigo, string nomeLab, string pAtivo, float precoCompra, float precoVenda, string nomeRemedio, string validade) {
	No* ptrNoNovo;
	No* ptrNoAtual;

	//Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return false;
	}

	//---------------------------------------------------------------
	//	Cria o novo nó
	//---------------------------------------------------------------
	ptrNoNovo = new No;

	if (ptrNoNovo == NULL) {
		cout << "Memória insulficiente!" << endl;
		return false;
	}

	ptrNoNovo->dados.codigo = codigo;
	ptrNoNovo->dados.nomeLab = nomeLab;
	ptrNoNovo->dados.pAtivo = pAtivo;
	ptrNoNovo->dados.precoCompra = precoCompra;
	ptrNoNovo->dados.precoVenda = precoVenda;
	ptrNoNovo->dados.nomeRemedio = nomeRemedio;
	ptrNoNovo->dados.validade = validade;

	ptrNoNovo->proxNo = NULL;

	ptrNoAtual = ptrLista->inicio;

	// Se não houver nenhum nó na lista
	if (ptrNoAtual == NULL) {
		ptrLista->inicio = ptrNoNovo;
	}
	else {
		// Localiza o último nó
		while (ptrNoAtual->proxNo != NULL) {
			ptrNoAtual = ptrNoAtual->proxNo;
		}
		ptrNoAtual->proxNo = ptrNoNovo;
	}

	// Incrementa o quantidade de Nós
	ptrLista->qtdNo++;

	return true;
}


//--------------------------------------------------------
// EXIBIR A LISTA - ok
//--------------------------------------------------------
void exibirLista(Lista* ptrLista) {
	No* ptrNoAtual;

	//Se a lista NÃO foi criada
	if (ptrLista == NULL) {
		cout << "A lista não está criada!" << endl;
		return;
	}

	//Se não tiver nenhum Nó na lista
	if (ptrLista->inicio == NULL) {
		cout << "A lista esta vazia!" << endl;
		return;
	}

	ptrNoAtual = ptrLista->inicio;

	while (ptrNoAtual != NULL) {

		cout << "Codigo do Medicamento: " << ptrNoAtual->dados.codigo << endl;
		cout << "Laboratorio de Fabricaçao: " << ptrNoAtual->dados.nomeLab << endl;
		cout << "Preço de Compra: " << ptrNoAtual->dados.precoCompra << endl;
		cout << "Preço de Venda: " << ptrNoAtual->dados.precoVenda << endl;
		cout << "Nome do medicamento: " << ptrNoAtual->dados.nomeRemedio << endl;
		cout << "Data de Validade: " << ptrNoAtual->dados.validade << endl << endl << endl;

		ptrNoAtual = ptrNoAtual->proxNo;

	}

	cout << endl;
}


void concatenarLista(Lista* pmedControlado, Lista* pmedGenerico, Lista* pmedEmEstoque) {
	No* ptrNoAtual;
	
	int codigo;
	string nomeLab;
	string pAtivo;
	float precoCompra;
	float precoVenda;
	string nomeRemedio;
	string validade;

	ptrNoAtual = pmedControlado->inicio;

	while (ptrNoAtual != NULL) {
		codigo = ptrNoAtual->dados.codigo;
		nomeLab = ptrNoAtual->dados.nomeLab;
		pAtivo = ptrNoAtual->dados.pAtivo;
		precoCompra = ptrNoAtual->dados.precoCompra;
		precoVenda = ptrNoAtual->dados.precoVenda;
		nomeRemedio = ptrNoAtual->dados.nomeRemedio;
		validade = ptrNoAtual->dados.validade;

		inserirListaFim(pmedEmEstoque, codigo, nomeLab, pAtivo, precoCompra, precoVenda, nomeRemedio, validade);
		ptrNoAtual = ptrNoAtual->proxNo;

	}

	ptrNoAtual = pmedGenerico->inicio;

	while (ptrNoAtual != NULL) {
		codigo = ptrNoAtual->dados.codigo;
		nomeLab = ptrNoAtual->dados.nomeLab;
		pAtivo = ptrNoAtual->dados.pAtivo;
		precoCompra = ptrNoAtual->dados.precoCompra;
		precoVenda = ptrNoAtual->dados.precoVenda;
		nomeRemedio = ptrNoAtual->dados.nomeRemedio;
		validade = ptrNoAtual->dados.validade;

		inserirListaFim(pmedEmEstoque, codigo, nomeLab, pAtivo, precoCompra, precoVenda, nomeRemedio, validade);
		ptrNoAtual = ptrNoAtual->proxNo;

	}
	
		
}