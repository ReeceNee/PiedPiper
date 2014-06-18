//Eduardo Zardain Canabal
//A00813391

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <bitset>

using namespace std;

const int PARTITION = 256; //Posicion del diccionario donde comienzan a agregarse las entradas nuevas
const int ENCODE_BITS = 12; //Numero de bits por miembro del diccionario
const int DICT_SIZE = 4096; //2^ENCODE_BITS

string dictionary[DICT_SIZE]; //Arreglo donde se guardan los caracteres y strings a utilizar

//Inicializa el diccionario con los caracteres a utilizar
void loadDict(){
    for (int i=65; i<=122; i++) {
        dictionary[i] = (char) i;
    }
    dictionary[32] = " ";
    dictionary[10] = "\n";
}

//Vacia el diccionario
void clearDict(){
    for (int i=0; i<=DICT_SIZE; i++) {
        dictionary[i] = "";
    }
}

//Verifica si un string esta en el diccionario
bool isInDict(string s){
    for (int i=0; i<DICT_SIZE; i++) {
        if (dictionary[i]==s) {
            return true;
        }
    }
    return false;
}

//Obtiene el indice del diccionario de un string
int getIndex(string s){
    for (int i=0; i<DICT_SIZE; i++) {
        if (dictionary[i]==s) {
            return i;
        }
    }
    return -1;
}

//Algoritmo de compresion LZW
void lzwCompress(){
    ifstream input; //Archivo de entrada
    ofstream output; //Archivo de salida
    string current, next, content;
    int count, offset;
    stringstream stream;
    
    //Abrir el archivo y copiar todo el contenido a un string
    input.open("File");
    stream << input.rdbuf();
    content = stream.str();
    
    output.open("File.lzw");
    
    //Inicializar el contador y el el offset que indica las entradas agregadas al diccionario
    count = 0;
    offset = 0;
    
    //El ciclo atraviesa todo el string de contenido
    while (count<content.length()) {
        
        
        current = content[count]; //Guardar un caracter
        next = content[count+1]; //Guardar el siguiente caracter
        
        //Se agrega al diccionario la concatenacion de los dos caracteres
        if (!isInDict(current+next)) {
            dictionary[PARTITION+offset] = current+next;
            offset++;
            count++;
            
        } else {
            /*Si la concatenacion ya esta en el diccionario (ya existe la entrada de dos o mas caracteres)
             se inicia un ciclo hasta que exista una entrada nueva, concatenando en current los caracteres
             y desplazando count y next
             */
            while (isInDict(current+next)) {
                current = current+next;
                next = content[count+2];
                count+=1;
            }
            dictionary[PARTITION+offset] = current + next; //Se agregega la entrada al diccionario
            offset++; //Se recorre el offset del diccionario
            count++; //Se recorre el indicador de caracter
            
        }
        cout << current << endl;
        output << bitset<ENCODE_BITS>(getIndex(current)); //Se envia la entrada del diccionario en binario
    }
    input.close();
    output.close();
}

//Algoritmo de compresion LZW
void lzwDecompress(){
    ifstream input;
    ofstream output;
    stringstream stream;
    string current, next, content, newString;
    int count, offset;
    unsigned long currentNum, nextNum;
    bitset<ENCODE_BITS> binIndex;
    
    //Copiar todo el archivo de entrada a un string
    input.open("File.lzw");
    stream << input.rdbuf();
    content = stream.str();
    
    output.open("FileDec");
    
    count = 0;
    offset = 0;
    
    while (count<content.length()) {
        
        current = content.substr(count, ENCODE_BITS);
        next = content.substr(count+ENCODE_BITS, ENCODE_BITS);
        
        binIndex = bitset<ENCODE_BITS>(current);
        currentNum = binIndex.to_ullong();
        
        binIndex = bitset<ENCODE_BITS>(next);
        nextNum = binIndex.to_ullong();
        
        if (dictionary[nextNum]=="") {
            dictionary[PARTITION+offset] = dictionary[currentNum] + dictionary[currentNum].substr(0,1);
        } else {
            dictionary[PARTITION+offset] = dictionary[currentNum] + dictionary[nextNum].substr(0,1);
        }
        
        dictionary[PARTITION+offset] = dictionary[currentNum] + dictionary[nextNum].substr(0,1);
        cout << dictionary[currentNum] << endl;
        output << dictionary[currentNum];
        
        offset++;
        count+=ENCODE_BITS;
        
    }
    
    input.close();
    output.close();
    
}


int main()
{

    loadDict();
    
    lzwCompress();
    
    clearDict();
    loadDict();
    
    cout << "Hello, World!\n";
    
    lzwDecompress();
    
    
    
    return 0;
}

