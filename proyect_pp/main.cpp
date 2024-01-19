#include <iostream>
#include <libpq-fe.h>

// Función para buscar clientes por nombre o teléfono
void buscarCliente(PGconn* conn, const std::string& campo, const std::string& valor) {
    std::string query = "SELECT * FROM \"Clientes\" WHERE \"" + campo + "\" = '" + valor + "'";
    PGresult* result = PQexec(conn, query.c_str());

    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        std::cerr << "Error en la consulta: " << PQerrorMessage(conn) << std::endl;
        PQclear(result);
        return;
    }

    // Imprimir resultados
    for (int i = 0; i < PQntuples(result); ++i) {
        for (int j = 0; j < PQnfields(result); ++j) {
            std::cout << PQgetvalue(result, i, j) << " ";
        }
        std::cout << std::endl;
    }

    PQclear(result);
}

// Función para agregar un nuevo cliente a la base de datos
void agregarCliente(PGconn* conn, const std::string& nombre, const std::string& telefono) {
    std::string query = "INSERT INTO \"Clientes\" (\"Nombre\", \"Telefono\") VALUES ('" + nombre + "', '" + telefono + "')";
    PGresult* result = PQexec(conn, query.c_str());

    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Error al agregar cliente: " << PQerrorMessage(conn) << std::endl;
    } else {
        std::cout << "Cliente agregado con éxito." << std::endl;
    }

    PQclear(result);
}

int main() {
    try {
        // Conexión a la base de datos
        const char* conninfo = "dbname=kenwruxs user=kenwruxs password=RjL5PaB8Ofh7YYppLbT7hh1nfIandhQn host=heffalump.db.elephantsql.com port=5432";
        PGconn* conn = PQconnectdb(conninfo);

        if (PQstatus(conn) != CONNECTION_OK) {
            std::cerr << "Error de conexión: " << PQerrorMessage(conn) << std::endl;
            PQfinish(conn);
            return 1;
        }

        // Menú de opciones
        int opcion;
        do {
            std::cout << "1. Buscar cliente por nombre\n";
            std::cout << "2. Buscar cliente por teléfono\n";
            std::cout << "3. Agregar nuevo cliente\n";
            std::cout << "4. Salir\n";
            std::cout << "Ingrese la opción: ";
            std::cin >> opcion;

            switch (opcion) {
                case 1: {
                    std::string nombre;
                    std::cout << "Ingrese el nombre a buscar: ";
                    std::cin.ignore();
                    std::getline(std::cin, nombre);
                    buscarCliente(conn, "Nombre", nombre);
                    break;
                }
                case 2: {
                    std::string telefono;
                    std::cout << "Ingrese el teléfono a buscar: ";
                    std::cin >> telefono;
                    buscarCliente(conn, "Telefono", telefono);
                    break;
                }
                case 3: {
                    std::string nuevoNombre, nuevoTelefono;
                    std::cout << "Ingrese el nombre del nuevo cliente: ";
                    std::cin.ignore();
                    std::getline(std::cin, nuevoNombre);
                    std::cout << "Ingrese el teléfono del nuevo cliente: ";
                    std::cin >> nuevoTelefono;
                    agregarCliente(conn, nuevoNombre, nuevoTelefono);
                    break;
                }
                case 4:
                    std::cout << "Saliendo del programa.\n";
                    break;
                default:
                    std::cout << "Opción no válida. Inténtelo de nuevo.\n";
            }
        } while (opcion != 4);

        // Cerrar conexión al final del programa
        PQfinish(conn);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
