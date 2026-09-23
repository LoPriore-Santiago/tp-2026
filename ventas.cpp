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
        cout << "No se pudo abrir o crear la planilla" << endl;
        return 1;
    }




    calcularComision(100, 3);
    return 0;
}