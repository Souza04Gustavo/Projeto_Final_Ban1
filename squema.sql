-- Arquivo: schema.sql
-- Descrição: Script para criar todas as tabelas e relacionamentos do projeto.

-- Garante que começamos com um ambiente limpo (cuidado ao usar em produção!)
DROP TABLE IF EXISTS Anomalias, Clientes, Equipamento, Funcionarios, Equipes CASCADE;

-- Tabela Equipes
-- Armazena as equipes de monitoramento.
-- O líder é um funcionário, então idLider será uma FK, mas precisamos definir a tabela Funcionarios primeiro.
-- Por enquanto, criamos a tabela sem a FK e a adicionaremos depois com ALTER TABLE.
CREATE TABLE Equipes (
    idEquipe SERIAL PRIMARY KEY,
    turno VARCHAR(50) NOT NULL,
    idLider INTEGER -- Será preenchido com uma FK para Funcionarios
);

-- Tabela Funcionarios
-- Armazena os dados dos funcionários. Cada funcionário pertence a uma equipe.
CREATE TABLE Funcionarios (
    idFuncionario SERIAL PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    salario NUMERIC(10, 2) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    idEquipe INTEGER NOT NULL,
    FOREIGN KEY (idEquipe) REFERENCES Equipes(idEquipe)
);

-- Agora que Funcionarios existe, podemos adicionar a chave estrangeira para o líder em Equipes.
ALTER TABLE Equipes ADD CONSTRAINT fk_lider FOREIGN KEY (idLider) REFERENCES Funcionarios(idFuncionario);

-- Tabela Equipamento
-- Armazena os dispositivos de monitoramento.
CREATE TABLE Equipamento (
    idEquipamento SERIAL PRIMARY KEY,
    modelo VARCHAR(50) NOT NULL,
    dataValidade DATE NOT NULL,
    ultimaManutencao DATE
);

-- Tabela Clientes
-- Armazena os dados dos clientes (idosos). Cada cliente tem um equipamento ativo.
CREATE TABLE Clientes (
    idCliente SERIAL PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    dataNascimento DATE NOT NULL,
    cpf VARCHAR(14) UNIQUE NOT NULL,
    endereco VARCHAR(255),
    telefone VARCHAR(20),
    idEquipamento_ativo INTEGER UNIQUE, -- Garante que um equipamento só pode estar ativo para um cliente.
    FOREIGN KEY (idEquipamento_ativo) REFERENCES Equipamento(idEquipamento)
);

-- Tabela Anomalias
-- Registra eventos críticos detectados pelos equipamentos.
CREATE TABLE Anomalias (
    idAnomalia SERIAL PRIMARY KEY,
    gravidade VARCHAR(50) NOT NULL,
    localizacao VARCHAR(255) NOT NULL,
    dataHora TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    idEquipamento INTEGER NOT NULL,
    idFuncionario_registro INTEGER, -- Funcionário que validou/registrou a anomalia (pode ser NULL se for automático)
    FOREIGN KEY (idEquipamento) REFERENCES Equipamento(idEquipamento),
    FOREIGN KEY (idFuncionario_registro) REFERENCES Funcionarios(idFuncionario)
);