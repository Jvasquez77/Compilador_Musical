#include "ast_node_interface.hpp"
#include "statement.hpp"

// Implementación de la función auxiliar para destruir el cuerpo del programa
void destroy_program_body(ProgramBody& body) noexcept
{
    // Recorre todos los statements y llama a su método destroy
    while (!body.empty())
    {
        Statement* stmt = body.front();
        body.pop_front();
        
        if (stmt != nullptr)
        {
            stmt->destroy();
            delete stmt;
        }
    }
} 