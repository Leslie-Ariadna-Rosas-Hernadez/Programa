#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

class usuario{
	public:
	string Responder;
	string Nombre;
	
	void datos();
	void confirmar();
};

void usuario::datos(){
	cout << "\n\n\t\t\t\tPREGUNTADOS"<< endl;
cout << "\nPresiona ENTER para iniciar" << endl;
cin.get();
// Datos del usuario
cout << "¿Cual es tu nombre?"<< endl;
cin >> Nombre;
}

void usuario::confirmar(){
cout << "¿Estas list@? "<< Nombre << " si/no" << endl;
cin >> Responder;
if (Responder == "si" or Responder=="SI" or Responder=="sI") {
cout << endl;
cout << "¡SUERTE!" << endl;
}
else {
cout << "ADIOS!" << endl;
exit(0);	
}}

struct Pregunta{
    string Enunciado;
    string RespuestaCorrecta;
    string Respuestas[4];
};

vector<Pregunta> cargarPreguntas(string Materia){
    vector<Pregunta> misPregu;
    string line;
    int Cantidad;
    ifstream myfile (Materia);
    if(myfile.is_open()){
        getline(myfile,line);
        Cantidad=stoi(line);
        while(Cantidad>0){
            Pregunta Temp;
            getline(myfile,line);
            Temp.Enunciado=line;
            //cout << Temp.Enunciado<<endl;
            for (int i = 0; i < 4; i++){
                getline(myfile,line);
                Temp.Respuestas[i]=line;
                //cout << Temp.Respuestas[i]<<endl;
            }
            getline(myfile,line);
            Temp.RespuestaCorrecta=line;
            //cout << Temp.RespuestaCorrecta<<endl;
            misPregu.push_back(Temp);
            --Cantidad;
        }
        myfile.close();
    }
    else cout << "No Existe una base de preguntas"; 
    return misPregu;
}


uint64_t seed(){
	return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

int main(){
	usuario dat, confir;
    string Materia[6]={"Historia.txt","Quimica.txt","Matematicas.txt","Geografia.txt","Spanish.txt","Fisica.txt"};
    vector<Pregunta> MisPreguntas;

	dat.datos();
	confir.confirmar();

    for (int k = 0; k < 6; k++){
        vector<Pregunta> Auxiliar=cargarPreguntas(Materia[k]);
        shuffle(Auxiliar.begin(), Auxiliar.end(),default_random_engine(seed()));
        MisPreguntas.push_back(Auxiliar[0]);
        MisPreguntas.push_back(Auxiliar[1]);
    }
    vector<Pregunta> Errores;
    //shuffle(MisPreguntas.begin(), MisPreguntas.end(),default_random_engine(seed()));
    int i=0;
    int buenas=0;
    while(i<12){
        string str=MisPreguntas[i].Enunciado;
        string letras[4]={"a","b","c","d"};
        string arr[4];
        string indiceCorrecta, respuesta;
        cout <<(i+1)<<".- "<< str<<endl;
        for(int j = 0; j < 4; j++){
                arr[j]=MisPreguntas[i].Respuestas[j];
        }  
        shuffle(arr, arr + 4,default_random_engine(seed()));
        for(int j = 0; j < 4; j++){
            cout <<letras[j]<<") "<<arr[j]<<endl;
            if(arr[j] == MisPreguntas[i].RespuestaCorrecta)
                indiceCorrecta=letras[j];
        }  
        cout<<"Indice de la Respuesta: ";
        cin >> respuesta;
        if(respuesta == indiceCorrecta)
            buenas++;
        else{
            Errores.push_back(MisPreguntas[i]);
        }
        ++i;
    }
    float calificacion=(buenas*100)/12;
    cout <<endl<<endl<<"Tuviste "<<buenas<<" repuestas correctas. Tu calificaion es de "<<calificacion<<endl;
    if(buenas==12){//Saco Todas buenas
        cout << "Fantastico sigue asi."<<endl;
    }else{
        cout <<"Estas son las preguntas que te equivocaste y su respuesta correcta: "<<endl;
        for (int k = 0; k < (12-buenas); k++){
            cout << (k+1)<<".- "<<Errores[k].Enunciado<<endl;
            cout<<"Respuesta correcta: "<<Errores[k].RespuestaCorrecta <<endl;
        }
        if(buenas >= 10){//Saco 8 y 9
            cout << "Ese fue un gran trabajo sigue mejorando."<<endl;
        }else
            if (buenas>=8){//Saco entre 6 y 7.5
                cout << "Puedes Mejorar."<<endl;
            }else
                if(buenas >=6){// Saco 5
                    cout << "No pasaste el examen pero sigue intentandolo."<<endl;
                }else
                    if(buenas >= 4){//Entre 3 y 5
                        cout << "Sigue estudiando"<<endl;
                    }else
                        if(buenas >= 2){//Entre 1.6 y 2.5
                            cout << " Necesitas clases extras"<<endl;
                        }else
                            if(buenas < 2){
                                cout << " Vuelve a estudiar todo"<<endl;
                            }
    }

return 0;
}