# Sistema de Monitoramento de Idosos - Projeto de Banco de Dados

Este repositório contém o projeto final da disciplina de Banco de Dados I, focado na modelagem, criação e manipulação de um banco de dados relacional para uma aplicação de monitoramento de idosos.

**Colaboradores:**
*   Gustavo de Souza
*   José Augusto Laube

---

## 1. Objetivo do Projeto

O objetivo deste projeto é desenvolver um sistema para uma empresa fictícia que comercializa e opera pulseiras e colares inteligentes para o monitoramento de idosos. O sistema deve ser capaz de gerenciar clientes, dispositivos, equipes de suporte e registrar eventos críticos, como quedas, para garantir a segurança e o bem-estar dos usuários.

Este repositório abrange duas fases do projeto:
1.  **Fase 1:** Modelagem do banco de dados, incluindo o Esquema Entidade-Relacionamento (EER), o Esquema Lógico Relacional e o Dicionário de Dados.
2.  **Fase 2:** Desenvolvimento de uma aplicação de console em linguagem C que interage com o banco de dados PostgreSQL, implementando as operações básicas de CRUD (Create, Read, Update, Delete) e consultas complexas.

---

## 2. Modelo do Banco de Dados

O banco de dados foi modelado para ser robusto e eficiente, seguindo as boas práticas de normalização. As principais entidades do sistema são:

*   **Clientes:** Idosos que utilizam o serviço.
*   **Equipamento:** Dispositivos de monitoramento (pulseiras, colares).
*   **Funcionarios:** Operadores que monitoram os clientes e prestam suporte.
*   **Equipes:** Grupos de funcionários organizados por turnos.
*   **Anomalias:** Registros de eventos críticos detectados pelos dispositivos.

O esquema SQL completo para criar a estrutura do banco de dados pode ser encontrado no arquivo `schema.sql`.

---

## 3. Requisitos da Aplicação (Fase 2)

A aplicação de console em C (`monitor_app`) foi desenvolvida para cumprir os seguintes requisitos mínimos:

-   [x] **Inserir novas tuplas:** Adicionar novos registros em todas as tabelas selecionadas.
-   [x] **Remover tuplas:** Deletar registros existentes em todas as tabelas.
-   [x] **Listar todas as tuplas:** Exibir todos os registros de cada tabela.
-   [x] **Consulta com Junção (JOIN):** Implementar uma consulta que combina dados de pelo menos duas tabelas.
-   [x] **Consulta com Subconsulta e Agregação:** Implementar uma consulta que utiliza subconsultas e funções de agregação (ex: `COUNT`, `AVG`).

---

## 4. Tecnologias Utilizadas

*   **Linguagem de Programação:** C
*   **Sistema de Gerenciamento de Banco de Dados (SGBD):** PostgreSQL
*   **Biblioteca de Conexão:** `libpq` (biblioteca C oficial do PostgreSQL)
*   **Sistema Operacional (Desenvolvimento):** Linux (Ubuntu)
*   **Compilador:** GCC

---

## 5. Como Executar o Projeto

Siga os passos abaixo para compilar e executar a aplicação em um ambiente Linux (Ubuntu/Debian).

### Pré-requisitos

1.  **PostgreSQL Server:** Certifique-se de que o servidor PostgreSQL esteja instalado e rodando.
    ```bash
    sudo apt install postgresql postgresql-contrib
    ```
2.  **Biblioteca de Desenvolvimento do PostgreSQL:** Essencial para a compilação do código C.
    ```bash
    sudo apt install libpq-dev
    ```
3.  **Compilador GCC:** Geralmente já vem instalado na maioria das distribuições Linux.
    ```bash
    sudo apt install build-essential
    ```

### Passos para Execução

**1. Clone o Repositório:**
```bash
git clone https://github.com/Souza04Gustavo/Projeto_Final_Ban1
cd Projeto_Final_Ban1
```

**2. Configure o Banco de Dados:**
Primeiro, configure um usuário e uma senha no PostgreSQL. Em seguida, crie e popule o banco de dados usando os scripts fornecidos.

   a. **Crie a estrutura do banco de dados:**
   ```bash
   psql -U seu_usuario -d seu_banco -f schema.sql
   ```
   *Substitua `seu_usuario` e `seu_banco` pelos seus dados do PostgreSQL.*

   b. **Popule o banco de dados com dados de exemplo:**
   ```bash
   psql -U seu_usuario -d seu_banco -f populate.sql
   ```

**3. Configure a Conexão no Código:**
Abra o arquivo `database.c` e edite a string de conexão com suas credenciais do PostgreSQL na função `conectar_bd()`:
```c
// Em database.c
const char *conninfo = "dbname=seu_banco user=seu_usuario password=sua_senha host=localhost";
```

**4. Compile a Aplicação:**
Use o seguinte comando no terminal, na raiz do projeto:
```bash
gcc -o monitor_app main.c database.c cliente.c -I/usr/include/postgresql -lpq
```

**5. Execute o Programa:**
```bash
./monitor_app
```
A aplicação iniciará e exibirá um menu de opções no console.

---

