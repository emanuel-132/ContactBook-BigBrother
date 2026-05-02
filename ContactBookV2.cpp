#include <iostream>
#include <string>
#include <cstdlib>
#include <unordered_map> //Para hash Table
#include <fstream>  // Librería para el manejo de archivos

using namespace std;

// Clase Contacto
class Contacto {
public:
    string nombre;
    string telefono;
    string email;

    Contacto() {} 

    Contacto(string n, string t, string e) {
        nombre = n;
        telefono = t;
        email = e;
    }
};

// Clase Agenda usando Hash Table con Persistencia
class Agenda {
private:
    unordered_map<string, Contacto> tablaHash;
    string nombreArchivo = "contactos.txt";

    // Función para guardar los datos en el disco duro
    void guardarEnArchivo() {
        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            for (auto const& par : tablaHash) {
                // Guardamos usando el separador '|' para no tener problemas con los espacios
                archivo << par.second.nombre << "|" 
                        << par.second.telefono << "|" 
                        << par.second.email << endl;
            }
            archivo.close();
        }
    }

    // Función para cargar los datos desde el disco duro
    void cargarDesdeArchivo() {
        ifstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            string n, t, e;
            // Leemos línea por línea usando el delimitador '|'
            while (getline(archivo, n, '|') && getline(archivo, t, '|') && getline(archivo, e)) {
                Contacto nuevo(n, t, e);
                tablaHash[n] = nuevo;
            }
            archivo.close();
        }
    }

public:
    Agenda() {
        cargarDesdeArchivo(); // Intentamos cargar datos existentes

        // Valores default
        if (tablaHash.empty()) {
            agregar("Bad Bunny", "111-111-1111", "bad.bunny@gmail.com");
            agregar("Willie Colón", "222-222-2222", "wcolon@gmail.com");
            agregar("Michael Jackson", "123-231-1234", "itsthejackson@gmail.com");
            agregar("Frank Castle", "212-121-1212", "thepunisher@gmail.com");
            agregar("Darth Maul", "787-555-1111", "shadowlord@gmail.com");
        }
    }

    void agregar(string nombre, string telefono, string email) {
        Contacto nuevo(nombre, telefono, email);
        tablaHash[nombre] = nuevo; 
        guardarEnArchivo(); // Guardamos en el archivo cada vez que agregamos
    }

    void buscar(string nombre) {
        if (tablaHash.find(nombre) != tablaHash.end()) {
            Contacto c = tablaHash[nombre];
            cout << "\n--- Contacto Encontrado ---\n";
            cout << "Nombre: " << c.nombre << "\nTel: " << c.telefono << "\nEmail: " << c.email << "\n";
            cout << "---------------------------\n";
        } else {
            cout << "Error: El contacto '" << nombre << "' no existe en la libreta.\n";
        }
    }

    void mostrarTodos() {
        if (tablaHash.empty()) {
            cout << "La agenda esta vacia.\n";
            return;
        }
        cout << "\n--- Lista de Contactos (" << tablaHash.size() << " guardados en disco) ---\n";
        for (auto par : tablaHash) {
            cout << "- " << par.second.nombre << " | " << par.second.telefono << " | " << par.second.email << endl;
        }
    }
};

int main() {
    Agenda miAgenda;
    int opcion;
    string nom, tel, email;

    do {
        cout << "\n===============================\n";
        cout << "      Big Brother DataBase     \n";
        cout << "===============================\n";
        cout << "1. Agregar Contacto\n2. Buscar Contacto\n3. Ver Todos\n4. Salir\nElige una opcion: ";
        cin >> opcion;
        cin.ignore(); 
       
        switch(opcion) {
            case 1:
                system("clear");
                cout << "--- Nuevo Registro ---\n";
                cout << "Nombre: "; getline(cin, nom);
                cout << "Telefono: "; getline(cin, tel);
                cout << "Email: "; getline(cin, email);
                miAgenda.agregar(nom, tel, email);
                cout << "\nContacto guardado en base de datos física.\n";
                break;
            case 2:
                system("clear");
                cout << "Nombre a buscar: "; getline(cin, nom);
                miAgenda.buscar(nom);
                break;
            case 3:
                system("clear");
                miAgenda.mostrarTodos();
                break;
        }
    } while(opcion != 4);

    return 0;
}