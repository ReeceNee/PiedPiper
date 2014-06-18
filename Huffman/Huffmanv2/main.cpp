//
//  main.cpp
//  Huffmanv2
//
//  Created by Gustavo Ferrufino on 5/3/14.
//  Copyright (c) 2014 Gustavo Ferrufino. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>
#include <bitset>
using namespace std;
#include "node.h"
#include <iterator>
//Constante de tabla de compression
const int PREFIX_BITS = 4;

string add ="/Users/Ferrufino/Documents/Code/Tec/Algoritmos/Huffmanv2/Huffmanv2/File";

int arr[100000];
int weighOfEach[68];
vector < pair<int, char> > WV;
node* tempSum; //Va tener al final de la creacion del arbol, el nodo raiz

string finito = "";

//Variable global para la descompresion
string decompressionTable[65];


//Arreglo global de caracteres
char charArray[65];

void buildArray(){
    for (int i=0; i<26; i++) {
        charArray[i] = ('A' + i);
    }
    for (int i=0; i<26; i++) {
        charArray[26+i] = ('a' + i);
    }
    charArray[52] = '.';
    charArray[53] = '-';
    for (int i=0; i<10; i++) {
        charArray[i+54]=('0'+i);
    }
    charArray[54] = '$';
    charArray[55] = '%';
 
    
    cout<<"----------------------------------------------------"<<endl;

    
}


void despBin (node *n, string word){

    if (n != NULL){
        
        word+=(to_string(n->assigned));
        

        cout <<" assigned:"<< n->assigned << " valor: "<<n->value<<endl;
        
            if (n->left ==NULL && n->right ==NULL) {
                finito+="="+(string) &n->value+word.substr(1);
               
            }
        
        despBin(n->left,word);
        despBin(n->right,word);
    }

}


void desplegar(node* n){
    
    
    
    if (n != NULL){
        cout <<" weigh:"<< n->weigh << " valor: "<<n->value<<endl;
        desplegar(n->left);
        desplegar(n->right);
    }
    
    
}

void huffman(){
    
    
    node* array = new node();
    cout<<endl;
    while (WV.size() != 1) {
        cout<<"----------------------------------------------------"<<endl;
        cout<<"DEBUG:: Huffman 1  - cada inicio del loop"<<endl;
         
         for (int i=0; i<WV.size(); i++) {
         
         cout<<"Value: "<<WV[i].second<<" Weigh: "<<WV[i].first<<endl;
         
         }
         cout<<"----------------------------------------------------"<<endl;
        
        
        //
        int tempWeigh=0;
        node *aux1=array;
        node *aux2=array;
        node* semueve=array;
        
        tempWeigh = WV[0].first + WV[1].first;
        
        node* temp1=NULL;
        node* temp2=NULL;
        tempSum = new node(tempWeigh, '*');
        
        //FIND IF ITS ALREADY A TEMPSUM
        if (WV[0].second == '*') {
            
            while ((aux1->next->pointsTo)->weigh != WV[0].first || aux1->next == NULL ) {
                aux1=aux1->next;
            }
            
            if ((aux1->next->pointsTo)->weigh != WV[0].first){
                
                cout<<"no son iguales"<<endl;
                cout<<aux1->next->pointsTo->weigh<<" "<<aux1->next->pointsTo->value<<endl;
                cout<<WV[0].first<<endl;
                
            } else {
                
                
                cout<<"despligue AUX1 antes"<<endl;
                desplegar(temp1);
                cout<<endl;
                cout<<"despligue AUX1 despues"<<endl;
                temp1 = aux1->next->pointsTo;
                aux1->next=aux1->next->next;
                desplegar(temp1);
                cout<<endl;
                
            }
            
            
        } else {
            
            temp1 = new node(WV[0].first, WV[0].second);
        }
        
        
        if (WV[1].second == '*') {
            
            while ((aux2->next->pointsTo)->weigh != WV[1].first || aux2->next == NULL ) {
                aux2=aux2->next;
            }
            
            if ((aux2->next->pointsTo)->weigh != WV[1].first){
                
                cout<<"no son iguales"<<endl;
                cout<<aux2->next->pointsTo->weigh<<" "<<aux2->next->pointsTo->value<<endl;
                cout<<WV[1].first<<endl;
                
            } else {
                
                
                cout<<"despligue AUX2 antes"<<endl;
                desplegar(temp2);
                cout<<endl;
                cout<<"despligue AUX2 despues"<<endl;
                temp2 = aux2->next->pointsTo;
                aux2->next=aux2->next->next;
                desplegar(temp2);
                cout<<endl;
            }

            
            
        } else {
            temp2 = new node(WV[1].first, WV[1].second);
        }
        
        //Asigna lado izq o der los hijos nodos
        
        if (temp1->weigh <= temp2->weigh) {
            tempSum->left = temp1;
            temp1->assigned=0;
            tempSum->right = temp2;
            temp2->assigned=1;
            
        } else if (temp1->weigh > temp2->weigh) {
            tempSum->left = temp2;
            temp1->assigned=0;
            tempSum->right = temp1;
            temp2->assigned=1;
        }
        
        WV.erase(WV.begin(), WV.begin()+2); //Borro los dos primeros del vector
        WV.push_back(make_pair(tempSum->weigh, '*'));// agrego la suma de los dos primeros
        sort(WV.begin(), WV.end());//ordeno el vector
        
        
        
        if (semueve == NULL) {
            semueve->pointsTo=tempSum;
        } else {
            node* tempArray = new node();
            tempArray->pointsTo=tempSum;
            while (semueve->next != NULL) {
                semueve = semueve->next;
            }
            
            semueve->next=tempArray;
            
        }
        
         cout<<"----------------------------------------------------"<<endl;
         cout<<"DEBUG:: Array of pointers display al que este apuntado"<<endl;
         aux1=array;
         while (aux1->next != NULL) {
         cout<<"peso: "<<aux1->next->pointsTo->weigh<<endl;
         cout<<"valor: "<<aux1->next->pointsTo->value<<endl;
         aux1=aux1->next;
         }
        
        
    } //loop while
    cout<<"----------------------------------------------------"<<endl;
     cout<<"DEBUG:: Huffman 2 - DESPUES: de tomar todos los primeros dos y ingresar suma  y ELIMINAR los dos primeros de WV"<<endl;
     
     for (int i=0; i<WV.size(); i++) {
     
     cout<<"Value: "<<WV[i].second<<" Weigh: "<<WV[i].first<<endl;
     
     }
    cout<<"----------------------------------------------------"<<endl;
    cout << "Despligue de arbol (preorden): "<<endl;
    desplegar(tempSum);
    string w="";
    despBin(tempSum,w);
    cout<<endl;
    cout<<"----------------------------------------------------"<<endl;
    //delete []array;
    
    
    
}

void formVectorAsc(){
    
    
    for (int i=0; i<65; i++) {
        if (weighOfEach[i]>0) {
            if (i <26) { // Caracteres en MAYUSCULA
                WV.push_back(make_pair(weighOfEach[i], i + 'A'));
                //WV2[i]->weigh = weighOfEach[i];
                //WV2[i]->value = i + 'A';
                
            } else if (i < 52) { // Caracteres en MINUSCULA
                WV.push_back(make_pair(weighOfEach[i], i + 'a' -26));
                //WV2[i]->weigh = weighOfEach[i];
                //WV2[i]->value = i + 'a' - 26;
                
                
            } else if (i == 52) { // ESPACIOS SE REPRESETAN POR UN '.'
                WV.push_back(make_pair(weighOfEach[i], '.'));
                //WV2[i]->weigh = weighOfEach[i];
                //WV2[i]->value = '.';
                
                
            } else if (i == 53) { // NEW LINES SE REPRESENTAN POR UN '-'
                WV.push_back(make_pair(weighOfEach[i], '-'));
                //WV2[i]->weigh = weighOfEach[i];
                //WV2[i]->value = '-';
            } else if (i == 54) {
                WV.push_back(make_pair(weighOfEach[i], '$'));
            
            } else if (i == 55) {
                WV.push_back(make_pair(weighOfEach[i], '%'));
            
            } else if (i<65) { //ES UN NUMERO
                WV.push_back(make_pair(weighOfEach[i], i + '0' - 54));
            }
            
        }
    }
    
    cout<<"----------------------------------------------------"<<endl;

    cout<<"DEBUG:: vector bien hecho"<<endl;
     for (int i=0; i<WV.size(); i++) {
     
     cout<<"Value: "<<WV[i].second<<" Weigh: "<<WV[i].first<<endl;
     
     }
    
    sort(WV.begin(), WV.end());

    
     cout<<endl<<"DEBUG::formVectorAsc() - Ya esta ordenado ascendentementer"<<endl;
     for (int i=0; i<WV.size(); i++) {
     
     cout<<"Value: "<<WV[i].second<<" Weigh: "<<WV[i].first<<endl;
     
     }
     
    
}


void count (string content) {//Cuenta la cantidad de frecuencia de cada caracter
    
    
    for (int i=0; i<65; i++) {
        weighOfEach[i]=0;
    }
    int arrEnteros[10];
    for (int i=0; i<10; i++) {
        arrEnteros[i]=i;
    }
    for (int i=0; i<content.length(); i++) {
        if (content[i] - 'A' == -33 ) {
           // cout<<"posicion: "<<i<<endl;
            weighOfEach[52]+=1;
            //cout<<"space"<<endl;
        } else if (content[i] - 'A' == -55 ) {
            //   cout<<"posicion: "<<i<<endl;
            weighOfEach[53]+=1;
           // cout<<"new line"<<endl;
            
        } else if (islower(content[i])) {
             //  cout<<"posicion: "<<i<<endl;
            weighOfEach[content[i]-'a'+26]+=1;
             //cout<<"weigh: "<<content[i]<<endl;
             //cout<<"valor: "<<(content[i] - 'a' + 26)<<endl;
            
        } else if (isupper(content[i])) {
              // cout<<"posicion: "<<i<<endl;
            weighOfEach[content[i]- 'A']+=1;
             //cout<<"weigh: "<<content[i]<<endl;
             //cout<<"valor: "<<content[i] - 'A'<<endl;
            
        } else {
           //cout<<"posicion: "<<i<<endl;
           // weighOfEach[content[i] + 54]+=1;
            //cout<<"weigh: "<<content[i]<<endl;
            //cout<<"valor: "<<content[i] + 54<<endl;
            
            for (int l=0; l<10; l++) {
                if ((content[i] - '0') == arrEnteros[l]) {
                    weighOfEach[content[i] - '0' + 54]+=1;
                }
            }
            
        }
    }

    
    
}

//Regresa el valor del indice del arreglo weightOfEach
int getIndexofChar(char x){
    for (int i=0; i<65; i++) {
        if (charArray[i]==x) {
            return i;
        }
    }
    return -1;
}

void huffmanCompress(){
    string location; //Direccion de archivo
    ifstream archivo; //ifstream para recibir info
    string content; // contenido
    string compressionTable[65];
    string temp;
    int charCounter;
    ifstream arch;
    stringstream strm; // agarrar todo contenido
    //cout<<"Introduce el nombre del archivo: ";
    //cin>>location;
    location=add;
    arch.open(location);
    
    
    strm << arch.rdbuf();
    content = strm.str();
    
    
    //1.-Metodo count cuenta la frecuencia de cada caracter
    count(content);
    
    int cantCaracteres=0;
    int pos=0;
    
    //2.-Valida si solo es un caracter repetido muchas o una sola vez
    
    
    for (int j=0; j<65; j++) {
        if(weighOfEach[j]>0){
            cantCaracteres++;
            pos=j;
        }
    }
    
    int num=1;
    cout<<pos<<endl;
    /*
    if (cantCaracteres == 1) { //CASO EXTREMO: Solo existe un caracter
        if (pos<26) {
            
            finito+=&""[(pos+'A')] + (to_string(num));
        } else if(pos<52) {
            
            finito+=(pos-26)+'a';
            
        } else if (pos==52) {
            finito+=".1";
        } else if (pos==53) {
            
            finito+="-1";
        }
        finito+="1=";
    } else{///3.- Si es que es mas de un caracter entonces ejecuta formVectorAsc() y huffman()
     */
     
       formVectorAsc();
       huffman();
        finito+="=";
    //}
 
    
    //Finito es un string en pre-orden de todos los caracteres y su representacion en 0 y 1 con huffman
   cout<<"Finito:"<<finito<<endl;
    
    
    
    //del string con el contenido del archivo original, convierte espacios y new lines
    //en la misma sintaxis
    
    for (int i=0; i<content.length(); i++) {
        if (content[i]==' ') {
            content[i]='.';
        } else if(content[i] == '\n'){
            
            content[i]='-';
        } else if (content[i] == '0') {
            content[i]='$';
        } else if (content[i] == '1') {
            content[i]='%';
        }
        
    }
    
    
    string resultado="";
    int x=0;
    charCounter = 0; //Sirve para contar el numero de caracteres en un archivo
    
    
    //se va remplazando cada caracter con su nueva representacion en 0's y 1's
    for (int y=0; y<content.length(); y++) {
        for (int j=0; j<finito.length(); j++) {
            if (content[y] == finito[j]) {
                x=j+1;
                while (finito[x]!= '=') {
                    resultado+=finito[x];
                    temp += finito[x];
                    x++;
                }
                
            }
            if (compressionTable[getIndexofChar(content[y])] == "") { //va llenando los espacios vacios.
                compressionTable[getIndexofChar(content[y])] += temp;//Se crea la tabla de frecuencias
            }
            temp = "";
        }
    }
    ofstream salida;
    string text=add+".huf";
    salida.open(text, ios::binary);
    
    for (int i=0; i<65; i++) {
        if (compressionTable[i]!="") {
            charCounter++;
        }
    }
    
    string temp2 = bitset<7>(charCounter).to_string();
    string table;
    
    resultado = temp2 + resultado;
    
    //Insertar la tabla de frecuencias en el archivo .huf
    //Cant de caracteres, tabla, contenido ya convertido
    for (int i=0; i<65; i++) {
        if (compressionTable[i]!= "") {//1.- indice de 6 bits, para representacion en ascii 2.-longitud en bit del codigo de huffman(acortarlo) 3.-codigohuffman
            table +=  bitset<7>(i).to_string() + bitset<PREFIX_BITS>(compressionTable[i].length()).to_string() + compressionTable[i]; //
            cout << bitset<7>(i) << " " << bitset<PREFIX_BITS>(compressionTable[i].length()) << " " << compressionTable[i] << endl;

        }
    }
    
    //salida<<resultado; //lo guardo
    
    cout << "Porcentaje de compresion de Hoffman (se redujo en): " << 1 - ((double)resultado.length())/(content.length()*8) << endl;
    
    stringstream lop(resultado);
    salida.write((char*)&lop, sizeof(lop));
    
    salida.close();
    arch.close();
    
}

int searchTable(string s){ //busca las presentacion de 1's y 0's en la tabla d ecompresion
    for (int i=0; i<64; i++) {
        if (decompressionTable[i]==s) {
            return i;
        }
    }
    
    
    
    return -1;
    

}



void huffmanDecompress(){
    
    ifstream input;
    ofstream output;
    stringstream stream;
    string content, identifier, outputString;
    int count, charCounter, prefix;
    unsigned long index;
    bitset<7> binIndex;
    bitset<10> bitIdentifier;
    
    
    input.open(add+".huf");
    stream << input.rdbuf();
    content = stream.str();
    
    output.open(add+"SalHuffman.txt");
    
    cout << endl << endl;
    
    count = 0;
    //saco primeros 6 bits para sacar el contador de cuantos caracteres han de haber
    charCounter = bitset<7>(content.substr(0,7)).to_ullong();
    count+=7;
    
    //Leer la tabla del archivo
    //Hay que guardar la tabla de frecuencias en un arreglo de strings ordenados igual que el arreglo de caracteres
    for (int i=0; i<charCounter; i++) { //binario a unsigned long = el indice, prefijo a unsigned long,
        binIndex = bitset<7>(content.substr(count, 7));
        index = binIndex.to_ullong();
        count+=7;
        prefix = bitset<PREFIX_BITS>(content.substr(count, PREFIX_BITS)).to_ullong();
        count+=PREFIX_BITS;
        for (int i=0; i<prefix; i++) {
            decompressionTable[index] += content[count];// traduciendo la tabla
            count++;
        }
        cout << index << " " << decompressionTable[index] << endl;
    }
    
    content.erase(0, count); // borrar la tabla, entonces string tiene el contenido
    count = 0;
    
    //Ahora que ya procesamos la tabla y solo falta el mensaje...
    while (count < content.length()) {
        
        identifier = content[count];
        
        while (searchTable(identifier) == -1) {
            count++;
            identifier += content[count];
            
        }
        count++;
        outputString += charArray[searchTable(identifier)];
        //cout << charArray[searchTable(identifier)] << endl;//
        //ArrChar es tu arreglo global donde estan los caracteres
    }
    
    for (int i=0; i<outputString.length(); i++) {
        if (outputString[i]=='.') {
            outputString[i] = ' ';
        }
        if (outputString[i]=='-') {
            outputString[i] = '\n';
        }
        if (outputString[i]=='$') {
            outputString[i] = '0';
        }
        if (outputString[i]=='%') {
            outputString[i] = '1';
        }
    }
    
    output << outputString;
    input.close();
    output.close();
}

void bitShifting () {
    //el char a a de recibir de entrada el archivo en binario
    char a;
    bool txt;
    string inside=add+".huf";
    ifstream arch;
    string content;
    stringstream stream;
    arch.open(inside, ios::binary);
    


    
    string asss;
    for(int i=0; i<content.length(); i++) {
        
        txt =(content[i]&1); //el 128 lo define hasta los primeros 7 bits que ha de leer
        //a<<=1; //bitshifting me lo va dejar vovlado pero lo leo todo desde atras

        if (txt) {
            cout<<1;
        } else {
        
        cout<<0;
        }
            }



}



int main()
{
    //Huffman
    buildArray(); //arreglo de caracteres A-Z, a-z, SPACE(.), NEW LINE(-)
    huffmanCompress();
    //huffmanDecompress();
    
    bitShifting();
    
    return 0;
}

