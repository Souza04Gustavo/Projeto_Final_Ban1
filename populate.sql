-- Arquivo: populate.sql

-- Limpa as tabelas antes de inserir para evitar duplicatas ao rodar o script várias vezes.
-- A ordem é importante devido às chaves estrangeiras (deleta das tabelas "filhas" para as "mães").
TRUNCATE TABLE Anomalias, Clientes, Funcionarios, Equipes RESTART IDENTITY CASCADE;
TRUNCATE TABLE Equipamento RESTART IDENTITY CASCADE;

-- 1. Populando a tabela Equipes
INSERT INTO Equipes (turno) VALUES
('Diurno'),
('Noturno'),
('Fim de Semana');


-- 2. Populando a tabela Funcionarios
INSERT INTO Funcionarios (nome, salario, email, idEquipe) VALUES
('Ana Silva', 3200.00, 'ana.silva@monitora.com', 1),       -- Equipe Diurno
('Bruno Costa', 3200.00, 'bruno.costa@monitora.com', 1),    -- Equipe Diurno
('Carla Dias', 3500.00, 'carla.dias@monitora.com', 2),      -- Equipe Noturno
('Daniel Farias', 3500.00, 'daniel.farias@monitora.com', 2), -- Equipe Noturno
('Eduardo Lima', 3000.00, 'eduardo.lima@monitora.com', 3);   -- Equipe Fim de Semana


UPDATE Equipes SET idLider = 1 WHERE idEquipe = 1;
UPDATE Equipes SET idLider = 3 WHERE idEquipe = 2;


-- 3. Populando a tabela Equipamento
INSERT INTO Equipamento (modelo, dataValidade, ultimaManutencao) VALUES
('Pulseira HealthGuard V1', '2025-12-31', '2024-01-15'),
('Colar LifeAlert S2', '2026-06-30', '2024-03-20'),
('Pulseira SafeBand X', '2025-10-20', '2024-05-10'),
('Colar Guardian Angel', '2026-08-01', NULL),
('Pulseira HealthGuard V2', '2027-01-01', '2024-06-01'),
('Pulseira de Backup', '2025-05-05', NULL); -- Equipamento extra, não associado a um cliente


-- 4. Populando a tabela Clientes
INSERT INTO Clientes (nome, dataNascimento, cpf, endereco, telefone, idEquipamento_ativo) VALUES
('Ana Petzold', '2005-03-12', '111.222.333-44', 'Rua das Flores, 123', '(47) 98765-4321', 1),
('Gustavo de Souza', '2004-05-11' ,'555.666.777-88',  'Rua Manuel Francisco de Oliveira, 138', '(47) 91234-5678', 2),
('José Augusto Laube', '2004-04-12', '999.888.777-66', 'Travessa da Paz, 789', '(47) 95555-4444', 3),
('Antônia Souza', '2000-03-12', '123.456.789-00', 'Praça da Matriz, 10', '(47) 94321-8765', 5);


-- 5. Populando a tabela Anomalias
INSERT INTO Anomalias (gravidade, localizacao, dataHora, idEquipamento, idFuncionario_registro) VALUES
('Alta', 'Residência do cliente - Cozinha', '2024-05-15 10:30:00', 1, 1), -- Queda do Sr. João, registrada pela Ana
('Média', 'Parque da Cidade', '2024-06-10 15:00:00', 2, 2), -- Batimento cardíaco irregular da Dona Maria, registrado pelo Bruno
('Baixa', 'Residência do cliente - Quarto', '2024-06-20 23:15:00', 3, 3), -- Bateria fraca do dispositivo do Sr. José, registrada pela Carla
('Alta', 'Supermercado Central', '2024-06-28 11:00:00', 2, 1); -- Nova queda da Dona Maria, registrada pela Ana
