TRUNCATE TABLE Anomalias, Clientes, Funcionarios, Equipes, Escala, Equipamento RESTART IDENTITY CASCADE;


INSERT INTO Escala (diaSemana, horario_inicio, horario_fim) VALUES
('Seg-Sex', '08:00:00', '16:00:00'), -- Turno Diurno Padrão
('Seg-Sex', '16:00:00', '00:00:00'), -- Turno Noturno Padrão
('Sab-Dom', '10:00:00', '18:00:00'); -- Turno Fim de Semana


INSERT INTO Equipes (turno) VALUES
('Diurno'),
('Noturno'),
('Fim de Semana');

INSERT INTO Equipamento (modelo, dataValidade, ultimaManutencao) VALUES
('Pulseira HealthGuard V1', '2025-12-31', '2024-01-15'),
('Colar LifeAlert S2', '2026-06-30', '2024-03-20'),
('Pulseira SafeBand X', '2025-10-20', '2024-05-10'),
('Colar Guardian Angel', '2026-08-01', NULL),
('Pulseira HealthGuard V2', '2027-01-01', '2024-06-01'),
('Pulseira de Backup', '2025-05-05', NULL);

INSERT INTO Funcionarios (nome, salario, email, idEquipe, idEscala) VALUES
('Ana Silva', 3200.00, 'ana.silva@monitora.com', 1, 1),       -- Equipe Diurno, Escala Seg-Sex 08-16
('Bruno Costa', 3200.00, 'bruno.costa@monitora.com', 1, 1),    -- Equipe Diurno, Escala Seg-Sex 08-16
('Carla Dias', 3500.00, 'carla.dias@monitora.com', 2, 2),      -- Equipe Noturno, Escala Seg-Sex 16-00
('Daniel Farias', 3500.00, 'daniel.farias@monitora.com', 2, 2), -- Equipe Noturno, Escala Seg-Sex 16-00
('Eduardo Lima', 3000.00, 'eduardo.lima@monitora.com', 3, 3);   -- Equipe Fim de Semana, Escala Sab-Dom 10-18

INSERT INTO Clientes (nome, dataNascimento, cpf, endereco, telefone, idEquipamento_ativo) VALUES
('Ana Petzold', '2005-03-12', '111.222.333-44', 'Rua das Flores, 123', '(47) 98765-4321', 1),
('Gustavo de Souza', '2004-05-11' ,'555.666.777-88',  'Rua Manuel Souza, 138', '(47) 91234-5678', 2),
('José Augusto Laube', '2004-04-12', '999.888.777-66', 'Travessa da Paz, 789', '(47) 95555-4444', 3),
('Antônia Souza', '2000-03-12', '123.456.789-00', 'Praça da Matriz, 10', '(47) 94321-8765', 5);

INSERT INTO Anomalias (gravidade, localizacao, dataHora, idEquipamento, idFuncionario_registro) VALUES
('Alta', 'Residência do cliente - Cozinha', '2024-05-15 10:30:00', 1, 1),
('Média', 'Parque da Cidade', '2024-06-10 15:00:00', 2, 2),
('Baixa', 'Residência do cliente - Quarto', '2024-06-20 23:15:00', 3, 3),
('Alta', 'Supermercado Central', '2024-06-28 11:00:00', 2, 1);