#include <iostream>
//#include <bits/stdc++.h>
#include <iomanip>
#include <fstream>
#include <typeinfo>
#include <sstream>
using namespace std;

const MAX_REGS = 500;
const MAX_ETAPAS = 5;
const MAX_TIPOS = 4;
typedef unsigned short ushort;
typedef char str20[21];
typedef char str15[16];

struct sEtapasRally {
    string nombre_piloto,
        nombre_copiloto,
        marca_vehiculo;
    ushort tiempo,
        nro_etapa,
        tipo_vehiculo,
        nro_vehiculo;
};

struct sTiempoTotal {
    string nombre_piloto,
        nombre_copiloto,
        marca_vehiculo;
    ushort tipo_vehiculo,
        nro_vehiculo,
        tiempo_total;
};
typedef sEtapasRally tblEtapasRally[MAX_REGS];
typedef sTiempoTotal tblTiemposTotales[MAX_REGS/MAX_ETAPAS];

//Métodos auxiliares

string trim(string str, int a, int b)
{
    string ret;

    for (int i = a; i <= b; i++)
    {
        ret = ret + str[i];
    }
    return ret;
} // Funcion para recortar un string

void IntCmb(sEtapasRally &linea_1, sEtapasRally &linea_2) {
    sEtapasRally aux = linea_1;
    linea_1 = linea_2;
    linea_2 = aux;
} // IntCmb

void IntCmb(sTiempoTotal &linea_1, sTiempoTotal &linea_2) {
    sTiempoTotal aux = linea_1;
    linea_1 = linea_2;
    linea_2 = aux;
} // IntCmb

void OrdxBur1(tblEtapasRally linea_tabla,ushort card) {
    bool ordenado;
    ushort  k = 0;

    do{
        ordenado = true;
        k++;
        for (ushort i = 0; i < card - k; i++){
            if (linea_tabla[i].tipo_vehiculo > linea_tabla[i + 1].tipo_vehiculo) {
            ordenado = false;
            IntCmb(linea_tabla[i],linea_tabla[i + 1]);
            }
        }
    }
    while (!ordenado);
} // OrdxBur según tipo_vehiculo

void OrdxBur2(tblEtapasRally linea_tabla, ushort card) {
    bool ordenado;
    ushort  k = 0;

    do{
        ordenado = true;
        k++;
        for (ushort i = 0; i < card - k; i++){
            if (linea_tabla[i].nro_etapa > linea_tabla[i + 1].nro_etapa){
            ordenado = false;
            IntCmb(linea_tabla[i],linea_tabla[i + 1]);
            }
        }
    }
    while (!ordenado);
} // OrdxBur según nro_etapa
void OrdxBur3(tblEtapasRally linea_tabla, ushort card) {
    bool ordenado;
    ushort  k = 0;

    do{
        ordenado = true;
        k++;
        for (ushort i = 0; i < card - k; i++){
            if (linea_tabla[i].nro_vehiculo > linea_tabla[i + 1].nro_vehiculo){
            ordenado = false;
            IntCmb(linea_tabla[i],linea_tabla[i + 1]);
            }
        }
    }
    while (!ordenado);
} // OrdxBur la copia del array de registros según nro_vehiculo

void OrdxBur4(tblTiemposTotales tiempos_totales, ushort card) {
    bool ordenado;
    ushort  k = 0;

    do{
        ordenado = true;
        k++;
        for (ushort i = 0; i < card - k; i++){
            if (tiempos_totales[i].tiempo_total > tiempos_totales[i + 1].tiempo_total){
            ordenado = false;
            IntCmb(tiempos_totales[i],tiempos_totales[i + 1]);
            }
        }
    }
    while (!ordenado);
}// OrdxBur según tiempos totales en el vector tiempos_totales

void OrdxBur5(tblTiemposTotales tiempos_totales, ushort card) {
    bool ordenado;
    ushort  k = 0;

    do{
        ordenado = true;
        k++;
        for (ushort i = 0; i < card - k; i++){
            if (tiempos_totales[i].tipo_vehiculo > tiempos_totales[i + 1].tipo_vehiculo){
            ordenado = false;
            IntCmb(tiempos_totales[i],tiempos_totales[i + 1]);
            }
        }
    }
    while (!ordenado);
} // OrdxBur segun tipo de vehiculo en el vector de tiempos totales



//Metodos principales
void Abrir (FILE **file){
    *file = fopen("EtapasRally.txt", "r");
}

bool LeerEtapaRally (tblEtapasRally linea_tabla, FILE **file, ushort &counter){
    string data_line[MAX_REGS];
    counter = 0;
    char data[69];


    if (*file==NULL) return false;
    while (!feof(*file))
    { // Mientras el archivo no acabe
        fgets(data, 100, *file);
        data_line[counter] = data;
        counter++;
    }

    for (int i = 0; i < counter; i++)
    { // En cada linea, asigno a el array linea_tabla[] su respectiva variable

        ushort x;
        stringstream etapa(trim(data_line[i], 0, 0)); // Como tienen que ser de tipo int, los transformo y despues los asigno
        etapa >> x;
        linea_tabla[i].nro_etapa = x;

        stringstream tipo(trim(data_line[i], 2, 2));
        tipo >> x;
        linea_tabla[i].tipo_vehiculo = x;

        stringstream numero(trim(data_line[i], 4, 5));
        numero >> x;
        linea_tabla[i].nro_vehiculo = x;

        stringstream tiempo(trim(data_line[i], 65, 67));
        tiempo >> x;
        linea_tabla[i].tiempo = x;


        linea_tabla[i].nombre_piloto = trim(data_line[i], 7, 26); // Como estos tienen que ser un string, los asigno asi nomas al toque perro

        linea_tabla[i].nombre_copiloto = trim(data_line[i], 28, 47);

        linea_tabla[i].marca_vehiculo = trim(data_line[i], 49, 63);
    }

    return true;
}

void ProcEtapasRally(tblEtapasRally linea_tabla, FILE **file,ushort &counter){

    if (!LeerEtapaRally(linea_tabla, file, counter)){
        cout << "No se pudo abrir el archivo";
        exit(1);
    } //Se guardan los valores en los arrays de sEtapasRally y sTiempoTotal
}

void ObtTiemposTotales(tblTiemposTotales tiempos_totales, tblEtapasRally linea_tabla,ushort counter, ushort &counter_tiempos, ushort &abandonos){
    OrdxBur3(linea_tabla,counter);
    counter_tiempos = 0;
    ushort aux = 0;
    abandonos = 0;

    for (ushort i = 0; i < counter; i++){
        if(linea_tabla[i].tiempo == 999 & linea_tabla[i-1].tiempo != 999){
           abandonos++;
        }//Calculo los conductores que abandonaron
        aux = aux + linea_tabla[i].tiempo;
        if(linea_tabla[i].nro_vehiculo != linea_tabla[i+1].nro_vehiculo){
            tiempos_totales[counter_tiempos].nombre_piloto = linea_tabla[i].nombre_piloto;
            tiempos_totales[counter_tiempos].nombre_copiloto = linea_tabla[i].nombre_copiloto;
            tiempos_totales[counter_tiempos].marca_vehiculo = linea_tabla[i].marca_vehiculo;
            tiempos_totales[counter_tiempos].tipo_vehiculo = linea_tabla[i].tipo_vehiculo;
            tiempos_totales[counter_tiempos].nro_vehiculo = linea_tabla[i].nro_vehiculo;
            tiempos_totales[counter_tiempos].tiempo_total = aux;
            counter_tiempos++;
            aux = 0;
        }
    }
}

void ListadoCorredores(tblEtapasRally linea_tabla, ushort counter){
    freopen("ListadoRally.txt", "w", stdout);
    cout << "   Listado de Corredores de Etapas y Tipos de Vehículos"<< endl;
    cout << "   ----------------------------------------------------"<< endl;
    cout << "Etp. TpVehic. Nombre del Piloto        Nombre del CoPiloto          Marca Vehic.    Tiempo mins"<< endl;
    for (ushort i = 0 ; i<counter; i++){
        cout <<" "<< linea_tabla[i].nro_etapa <<"     "<< linea_tabla[i].tipo_vehiculo <<"      "
            << linea_tabla[i].nombre_piloto <<"     "<< linea_tabla[i].nombre_copiloto <<"         "
            << linea_tabla[i].marca_vehiculo <<"    "<<setw(3)<< linea_tabla[i].tiempo << endl;
    }
    cout << endl;
}

void ListadoLargada(tblEtapasRally linea_tabla, ushort counter){
    OrdxBur1(linea_tabla,counter);
    OrdxBur2(linea_tabla,counter);
    ushort z = 0;

    cout << "   Listado de largada"<< endl;
    cout << "   ------------------"<< endl;

    for(ushort x = 1; x <= MAX_ETAPAS; x++){
        cout << "Nro. Etapa: " << x << endl;
        for(ushort y = 1; y <= MAX_TIPOS; y++){
             cout << "   Tipo Vehiculo: " << y << endl;
             cout << "       Nro. Vehic.  Nom. Piloto          Nom. CoPiloto        Marca Vehic." << endl;
             for(z; z < counter; z++){
                if (linea_tabla[z].nro_etapa == x & linea_tabla[z].tipo_vehiculo == y){
                    cout <<"          "<<setw(2)<< linea_tabla[z].nro_vehiculo<<"        "<<linea_tabla[z].nombre_piloto
                        <<" "<< linea_tabla[z].nombre_copiloto <<" "<< linea_tabla[z].marca_vehiculo << endl;
                } else {
                break;
                }
             }
        }
    }
    cout << endl;
}

void ListadoPuestosFinal(tblTiemposTotales tiempos_totales,ushort counter_tiempos){
    OrdxBur4(tiempos_totales,counter_tiempos);
    cout << "   Listado de Puestos Finales Carrera Rally" << endl;
    cout << "   ----------------------------------------" << endl;
    cout << "Puesto T.Vehic. Nro.Vehic. Nom. Piloto          Nom. CoPiloto        Marca Vehic.    Tiempo Total" << endl;
    for (ushort i = 0; i < counter_tiempos; i++){
        ushort puesto = i+1;
        cout << setw(2) << puesto << "       " << tiempos_totales[i].tipo_vehiculo << "        " << setw(2)
            << tiempos_totales[i].nro_vehiculo << "       "<< tiempos_totales[i].nombre_piloto << " " << tiempos_totales[i].nombre_copiloto << " "
            << tiempos_totales[i].marca_vehiculo << "   " << setw(4) <<tiempos_totales[i].tiempo_total << endl;
    }
    cout << endl;
}

void ListadoGanadoresxTipoVehic(tblTiemposTotales tiempos_totales, ushort counter_tiempos, ushort abandonos){
    OrdxBur5(tiempos_totales,counter_tiempos);

    ushort x = 0;
    cout << "   Listados de Ganadores por tipos de Vehiculos" << endl;
    cout << "   --------------------------------------------" << endl;
    cout << "Tipo Vehic.    Nro. Vehic.    Nombre del Piloto  Tiempo Total" << endl;
    for (ushort i = 0; i < MAX_TIPOS; i++){
        for (x; x < counter_tiempos; x++){

            if(tiempos_totales[x].tipo_vehiculo != tiempos_totales[x-1].tipo_vehiculo){
                cout << "    "<< tiempos_totales[x].tipo_vehiculo << "              "<< setw(2)
                << tiempos_totales[x].nro_vehiculo << "         " << tiempos_totales[x].nombre_piloto << "   "
                << tiempos_totales[x].tiempo_total << endl;
            }
        }
    }
    cout << endl << "Cantidad de conductores que abandonaron: " << abandonos;
    freopen("CON","w", stdout); // Vuelvo a establecer la salida en la consola
}

void Cerrar(FILE **file){
    fclose(*file);
}




int main() {
    FILE *file;
    tblEtapasRally linea_tabla;
    tblTiemposTotales tiempos_totales;
    ushort counter;
    ushort counter_tiempos;
    ushort abandonos;

    Abrir(&file);
    ProcEtapasRally(linea_tabla, &file, counter);
    ListadoCorredores(linea_tabla,counter);
    ObtTiemposTotales(tiempos_totales, linea_tabla, counter, counter_tiempos, abandonos);
    ListadoLargada(linea_tabla, counter);
    ListadoPuestosFinal(tiempos_totales,counter_tiempos);

    ListadoGanadoresxTipoVehic(tiempos_totales, counter_tiempos, abandonos);
    /*
    Falta hacer ListadoPuestosFinal(argumentos…);  // En el módulo ListadoGanadoresxTipoVehic debe
    Falta hacer ListadoGanadoresxTipoVehic(argumentos…);  // volverse el freopen a la consola.
    */
    Cerrar(&file);
    return 0;
} //main
