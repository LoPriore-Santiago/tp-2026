#include <iostream>
#include <cstdio>
#include <cstring>


using namespace std;

// Estructuras
struct Producto{
    int codigo;
    char descripcion[50];
    float precio;
    int stockActual;
};

struct Mozo {
    int idMozo;
    char nombre[50];
    int password[20];
    float totalComision;
};

struct Comanda {
    int idMozo;
    int codigoProducto;
    int cantidad;
    float comision;
};

const float TASA_COMISION = 0.10f;





// Funciones auxiliares 


// Retorna el codigo del producto buscado, usamos busqueda binaria debido a que en el enunciado especifica que faltan codigos en el medio.(no podemos usar PUP)
long buscarProducto( const char* nombreArchivo, int codigoProducto, Producto& producto){

    FILE* f =  fopen(nombreArchivo, "rb");
    if (f == NULL){
        return -1;
    }

    fseek(f, 0, SEEK_END);
    long n = ftell(f) / sizeof(Producto);       // cantidad de productos que hay en ""inventarios.dat"
    long inicio = 0;                           
    long fin = n - 1;
    long pos = -1;

        while(inicio <= fin && pos == -1){
            long mitad = (inicio + fin) / 2;
            fseek(f, mitad * sizeof(Producto), SEEK_SET);   // posicionamos el puntero al medio
            fread(&producto, sizeof(Producto), 1, f);  
                if(producto.codigo == codigoProducto){
                    pos = mitad;
                }else if(producto.codigo < codigoProducto){   
                    inicio = mitad + 1;
                }else{
                    fin = mitad - 1;
                }
        }
        fclose(f);
        return pos;
};

//Pedimos el id del mozo y buscamos si existe
bool buscarMozo(const char* nombreArchivo, int idMozo, Mozo& mozo){
    FILE* f = fopen(nombreArchivo, "rb");
    if (f == NULL){
        return false;
    }

    fseek(f, 0, SEEK_END);
    long n = ftell(f) / sizeof(Mozo);  // cantidad de mozos queh hay en "mozos.dat"

    long inicio = 0;
    long fin = n - 1;
    bool encontrado = false;

        while(inicio <= fin && !encontrado){
            long mitad = (inicio + fin) / 2;

            fseek(f, mitad * sizeof(Mozo), SEEK_SET);   // posicionamos el puntero al medio
            fread(&mozo, sizeof(Mozo), 1, f);  
                if(mozo.idMozo == idMozo){
                    encontrado = true;
                }else if(mozo.idMozo < idMozo){   
                    inicio = mitad + 1;
                }else{
                    fin = mitad - 1;
                }
        }
        fclose(f);
        return encontrado;
};



float calcularComision(float precio, int cantidad)
{
    return precio * cantidad * TASA_COMISION;
};






int main()
{
// Pedir Fecha
    char fecha[20];

    cout << "Ingrese la fecha del dia (dd-mm-aaaa): ";
    cin >> fecha;

// Generar nombre de la comanda/planilla
    char nombreComanda[30];

    sprintf(nombreComanda, "comandas_%s.dat", fecha); 

    FILE* f = fopen(nombreComanda, "rb+");    // Abrir la planilla

    if (f == NULL) {
        f = fopen(nombreComanda, "wb+");       // Crear la planilla si no esta creada
    }

    if (f == NULL) {
        cout << "No se pudo abrir o crear la planilla" << endl;  //Error al crear planilla
        return 1;
    }

    int idMozo;

    cout << "Ingrese el ID del mozo: ";
    cin >> idMozo;

    Mozo mozo;
    
    if (buscarMozo("mozos.dat", idMozo, mozo)) {  // Si no encuentro al mozo
        cout << "Mozo encontrado" << endl;
            // VALIDAR TODAVIA CONTRASEÑA
    }
    else {
        cout << "Mozo no encontrado" << endl;
    }




    calcularComision(100, 3);
    return 0;
}