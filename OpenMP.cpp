// OpenMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*int main()
{
#pragma omp parallel
    {
        std::cout << "Hello World!\n";
    }
}
*/

/*int main()
{
    std::cout << "Regiones paralelas!\n";
    int hilos, tid;

    #pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        std::cout << "Trabajando en el thread: " << tid << std::endl;
        if (tid == 0)
        {
            hilos = omp_get_num_threads();
            std::cout << "Numero de threads es: " << hilos << std::endl;
        }
    }
}*/
/*
#define N 24
using namespace std;
int tid;

int main()
{
    cout << "Estableciendo la cantidad de hilos!\n";
    int nHilos;
    cout << "Cuantos hilos quieres trabajar: ";
    cin >> nHilos;

    #ifdef _OPENMP
        omp_set_num_threads(nHilos);
    #endif // DEBUG

    #pragma omp parallel private(tid)
    {
            tid = omp_get_thread_num();
            cout << "El thread " << tid << " esta en marcha" << endl;
            cout << "El thread " << tid << " ha terminado " << endl;
    }

}
*/

#include <iostream>
#include <random>

#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#endif

#define chunk 100

using namespace std;

//funcion para crear un array con numeros aleatorios entre el numero 1 y el numero establecido en el tamanio del array
int* createArray(int size) {
    
    int* newArray = new int[size];

    //Semilla para los numero aleatorios
    random_device rd;
    mt19937 gen(rd());

    //Distribucion uniforme incluyendo los parametros
    uniform_int_distribution<> dis(1, size);

    //Asignacion del array
    for (int i = 0; i < size; ++i) {
        newArray[i] = dis(gen);
    }
    //Retorno del array
    return newArray;
}

int main()
{
    int size;
    //Solicitando el tamanio del array
    cout << "Tamanio del array: ";
    cin >> size;

    //Punteros creados apuntando a las direcciones de los arrays creados
    int* arrayNumberOne = createArray(size);
    int* arrayNumberTwo = createArray(size);
    int* arrayResult = new int[size];
    int i;
    int pedazos = chunk;
    //Establecer 2 threads para el proceso
    #ifdef _OPENMP
        omp_set_num_threads(2);
    #endif

    //Uso de for paralelo con OpenMP
    //Compartiendo los valores de los arrays y la variable pedazos entre los hilos
    //pero cada hilo teniendo su propia copia de la variable i
    //dividiendo la cantidad de iteraciones en pedazos para cada hilo
    #pragma omp parallel for \
    shared(arrayNumberOne, arrayNumberTwo, arrayResult, pedazos) \
    private(i) schedule(static, pedazos)
    for (int i = 0; i < size; ++i)
        arrayResult[i] = arrayNumberOne[i] + arrayNumberTwo[i];

    //Imprimir los datos
    for (int x = 0; x < 10; ++x) {
        cout << arrayNumberOne[x] << " + " << arrayNumberTwo[x] << " = " << arrayResult[x] << endl;
    }
    //Liberar memoria
    delete[] arrayNumberOne;
    delete[] arrayNumberTwo;
    delete[] arrayResult;
}

/*
#include <iostream>
#include <omp.h>

#define N 1000
#define chunk 100
#define mostrar 10

using namespace std;

void imprimirArreglo(float* d) {
    for (int x = 0; x < mostrar; x++)
        cout << d[x] << " - " << endl;
}

int main()
{
    cout << "Sumando arreglos en paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++) {
        a[i] = i * 10;
        b[i] = (i + 3) * 3.7;
    }
    int pedazos = chunk;

    #pragma omp parallel for shared(a, b, c, pedazos) private(i) schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];
    
    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << endl;
    imprimirArreglo(a);
    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << endl;
    imprimirArreglo(b);
    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << endl;
    imprimirArreglo(c);

}
*/
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
