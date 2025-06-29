DROP TABLE IF EXISTS Anomalias, Clientes, Funcionarios, Equipes, Escala, Equipamento CASCADE;

-- Tabela: Escala
-- Define os horários de trabalho.
CREATE TABLE Escala (
    idEscala SERIAL PRIMARY KEY,
    diaSemana VARCHAR(20) NOT NULL,
    horario_inicio TIME NOT NULL,
    horario_fim TIME NOT NULL
);

-- Tabela: Equipes
-- Armazena as equipes de monitoramento. O conceito de líder foi removido para simplificação.
CREATE TABLE Equipes (
    idEquipe SERIAL PRIMARY KEY,
    turno VARCHAR(50) NOT NULL
);

-- Tabela: Funcionarios
-- Armazena os dados dos funcionários, com referência à sua equipe e escala.
CREATE TABLE Funcionarios (
    idFuncionario SERIAL PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    salario NUMERIC(10, 2) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    idEquipe INTEGER NOT NULL,
    idEscala INTEGER, -- Pode ser NULL se um funcionário não tiver escala fixa.
    FOREIGN KEY (idEquipe) REFERENCES Equipes(idEquipe),
    FOREIGN KEY (idEscala) REFERENCES Escala(idEscala)
);

-- Tabela: Equipamento
-- Armazena os dispositivos de monitoramento.
CREATE TABLE Equipamento (
    idEquipamento SERIAL PRIMARY KEY,
    modelo VARCHAR(50) NOT NULL,
    dataValidade DATE NOT NULL,
    ultimaManutencao DATE
);

-- Tabela: Clientes
-- Armazena os dados dos clientes, ligando-os ao seu dispositivo ativo.
CREATE TABLE Clientes (
    idCliente SERIAL PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    dataNascimento DATE NOT NULL,
    cpf VARCHAR(14) UNIQUE NOT NULL,
    endereco VARCHAR(255),
    telefone VARCHAR(20),
    idEquipamento_ativo INTEGER UNIQUE,
    FOREIGN KEY (idEquipamento_ativo) REFERENCES Equipamento(idEquipamento) ON DELETE SET NULL
);

-- Tabela: Anomalias
-- Registra eventos críticos, com referência ao equipamento que detectou e ao funcionário que registrou.
CREATE TABLE Anomalias (
    idAnomalia SERIAL PRIMARY KEY,
    gravidade VARCHAR(50) NOT NULL,
    localizacao VARCHAR(255) NOT NULL,
    dataHora TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    idEquipamento INTEGER NOT NULL,
    idFuncionario_registro INTEGER,
    FOREIGN KEY (idEquipamento) REFERENCES Equipamento(idEquipamento),
    FOREIGN KEY (idFuncionario_registro) REFERENCES Funcionarios(idFuncionario)
);