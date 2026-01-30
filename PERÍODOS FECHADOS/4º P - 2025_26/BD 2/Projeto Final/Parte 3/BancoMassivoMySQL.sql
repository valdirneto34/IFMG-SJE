/* ================================================================================
DML - DADOS INICIAIS (CENÁRIO DE TESTE PARTE I e II)
================================================================================
*/
USE escola_idiomas;

-- 1. Limpeza Total e Reset (Garante que começamos do zero)
SET FOREIGN_KEY_CHECKS = 0;
TRUNCATE TABLE avaliacoes;
TRUNCATE TABLE mensalidades;
TRUNCATE TABLE matriculas;
TRUNCATE TABLE turmas;
TRUNCATE TABLE cursos;
TRUNCATE TABLE salas;
TRUNCATE TABLE alunos;
TRUNCATE TABLE professores;
TRUNCATE TABLE pessoas;
TRUNCATE TABLE idiomas;
TRUNCATE TABLE formas_pagamento;
SET FOREIGN_KEY_CHECKS = 1;

-- 2. Tabelas Básicas
INSERT INTO formas_pagamento (descricao) VALUES ('Pix'), ('Boleto Bancário'), ('Cartão de Crédito'), ('Transferência'), ('Cartão de Débito');
INSERT INTO idiomas (nome_idioma) VALUES ('Inglês'), ('Espanhol'), ('Francês'), ('Alemão'), ('Italiano');

-- 3. Salas (Incluindo as Massivas para a Parte III)
INSERT INTO salas (sala_id, nome_sala, capacidade, tipo_sala) VALUES
(1, 'Sala 101', 25, 'Comum'),
(2, 'Sala 102', 20, 'Comum'),
(3, 'Sala Lab. A', 18, 'Laboratório'),
(4, 'Sala Lab. B', 15, 'Laboratório'),
(5, 'Auditório Principal', 50, 'Auditório'),
(6, 'Auditório Massivo A', 5000, 'Auditório'), -- Para Teste de Carga
(7, 'Auditório Massivo B', 5000, 'Auditório'); -- Para Teste de Carga

-- 4. Cursos
INSERT INTO cursos (curso_id, idioma_id, nome_curso, descricao, duracao_meses) VALUES
(1, 1, 'Inglês Básico I', 'Fundamentos', 6),
(2, 1, 'Inglês Intermediário II', 'Gramática', 8),
(3, 2, 'Espanhol Básico I', 'Início', 6),
(4, 2, 'Espanhol Avançado', 'Fluência', 10),
(5, 3, 'Francês Básico', 'Estrutura', 7),
(6, 3, 'Francês Conversação', 'Fluência', 4),
(7, 4, 'Alemão Básico A1', 'Nível A1', 6),
(8, 4, 'Alemão Intermediário B1', 'Nível B1', 8),
(9, 5, 'Italiano Rápido', 'Viagens', 3),
(10, 5, 'Italiano Avançado', 'Domínio', 12);

-- 5. Professores (Pessoas ID 1-5)
INSERT INTO pessoas (pessoa_id, nome, data_nasc, cpf, email, telefone, endereco) VALUES
(1, 'Prof. Ana Clara Lima', '1985-05-15', '11111111111', 'ana.lima@escola.com', '31998765432', 'Rua A, 100'),
(2, 'Prof. Bruno Costa', '1990-11-20', '22222222222', 'bruno.costa@escola.com', '31997654321', 'Av. B, 250'),
(3, 'Prof. Carla Dantas', '1978-01-01', '33333333333', 'carla.dantas@escola.com', '31996543210', 'Praça C, 50'),
(4, 'Prof. David Rocha', '1980-10-05', '44444444445', 'david.rocha@escola.com', '31969876543', 'Rua Épsilon, 50'),
(5, 'Prof. Erika Viana', '1992-03-11', '55555555556', 'erika.viana@escola.com', '31968765432', 'Av. Zeta, 60');

INSERT INTO professores (professor_id, especialidade, data_contratacao, salario) VALUES
(1, 'Inglês e Francês', '2020-02-10', 4500.00),
(2, 'Espanhol e Italiano', '2021-08-15', 4200.00),
(3, 'Alemão e Francês', '2019-05-01', 4800.00),
(4, 'Inglês e Alemão', '2023-01-20', 4600.00),
(5, 'Espanhol e Italiano', '2023-03-01', 4300.00);

-- 6. Turmas (Incluindo as Massivas IDs 20-21)
INSERT INTO turmas (turma_id, curso_id, professor_id, sala_id, nome_turma, horario, data_inicio, data_fim) VALUES
(1, 1, 1, 1, 'ING-BAS-T01-2025', 'Seg/Qua - 19h', '2025-02-01', '2025-07-30'),
(2, 1, 1, 2, 'ING-BAS-T02-2024', 'Ter/Qui - 10h', '2024-03-01', '2024-08-30'),
(3, 2, 1, 1, 'ING-INT-T01-2025', 'Seg/Qua - 21h', '2025-05-01', '2026-01-30'),
(4, 3, 2, 3, 'ESP-BAS-T01-2025', 'Ter/Qui - 18h', '2025-03-15', '2025-09-15'),
(5, 3, 2, 4, 'ESP-BAS-T02-2024', 'Sáb - 09h', '2024-01-10', '2024-07-10'),
(6, 4, 2, 3, 'ESP-AVA-T01-2025', 'Sex - 19h', '2025-01-01', '2025-10-30'),
(7, 5, 3, 5, 'FRA-BAS-T01-2025', 'Seg - 18h', '2025-04-01', '2025-10-30'),
(8, 6, 3, 5, 'FRA-CONV-T01-2024', 'Ter - 19h', '2024-09-01', '2024-12-30'),
(9, 7, 3, 1, 'ALE-A1-T01-2025', 'Qua - 18h', '2025-01-01', '2025-06-30'),
(10, 8, 3, 2, 'ALE-B1-T01-2025', 'Qui - 20h', '2025-06-01', '2026-02-01'),
(11, 9, 2, 4, 'ITA-RAP-T01-2025', 'Sáb - 14h', '2025-04-01', '2025-06-30'),
(12, 10, 2, 3, 'ITA-AVA-T01-2024', 'Dom - 10h', '2024-02-01', '2025-02-01'),
(13, 1, 1, 2, 'ING-BAS-T03-2025', 'Sex - 16h', '2025-03-01', '2025-08-30'),
(14, 3, 2, 4, 'ESP-BAS-T03-2025', 'Seg/Qua - 16h', '2025-01-20', '2025-07-20'),
(15, 5, 3, 5, 'FRA-BAS-T02-2024', 'Qui - 17h', '2024-05-01', '2024-11-30'),
(16, 2, 4, 2, 'ING-INT-T02-2025', 'Ter/Qui - 16h', '2025-05-10', '2026-01-10'),
(17, 7, 4, 4, 'ALE-A1-T02-2025', 'Seg/Qua - 20h', '2025-06-01', '2025-11-30'),
(18, 3, 5, 1, 'ESP-BAS-T04-2025', 'Ter/Qui - 17h', '2025-04-01', '2025-09-30'),
(19, 9, 5, 3, 'ITA-RAP-T02-2025', 'Sáb - 16h', '2025-05-01', '2025-07-31'),
(20, 1, 1, 6, 'ING-MASS-01', 'EAD', '2025-01-01', '2025-12-31'), -- Massiva 1
(21, 4, 2, 7, 'ESP-MASS-01', 'EAD', '2025-01-01', '2025-12-31'); -- Massiva 2

-- 7. Alunos (Pessoas ID 6-40)
INSERT INTO pessoas (pessoa_id, nome, data_nasc, cpf, email, telefone, endereco) VALUES
(6, 'Aluno Daniel Silva', '2001-08-01', '44444444444', 'daniel.s@aluno.com', '31986543210', 'Rua D, 30'),
(7, 'Aluno Elisa Rodrigues', '1999-03-25', '55555555555', 'elisa.r@aluno.com', '31985432109', 'Av. E, 500'),
(8, 'Aluno Fábio Gomes', '2005-01-10', '66666666666', 'fabio.g@aluno.com', '31994321098', 'Rua F, 45'),
(9, 'Aluno Gabriela Pereira', '1995-12-05', '77777777777', 'gabriela.p@aluno.com', '31993210987', 'Av. G, 120'),
(10, 'Aluno Hugo Souza', '2003-06-18', '88888888888', 'hugo.s@aluno.com', '31992109876', 'Rua H, 210'),
(11, 'Aluno Irene Alves', '1997-04-12', '99999999999', 'irene.a@aluno.com', '31991098765', 'Praça I, 15'),
(12, 'Aluno João Felipe', '2002-09-30', '00000000001', 'joao.f@aluno.com', '31990987654', 'Rua J, 300'),
(13, 'Aluno Karen Rocha', '1996-07-22', '00000000002', 'karen.r@aluno.com', '31989876543', 'Av. K, 40'),
(14, 'Aluno Lucas Mendes', '2000-02-28', '00000000003', 'lucas.m@aluno.com', '31988765432', 'Rua L, 70'),
(15, 'Aluno Mariana Neves', '2004-10-14', '00000000004', 'mariana.n@aluno.com', '31987654321', 'Av. M, 90'),
(16, 'Aluno Natália Oliveira', '1998-05-08', '00000000005', 'natalia.o@aluno.com', '31986543210', 'Rua N, 110'),
(17, 'Aluno Otávio Pires', '2006-03-17', '00000000006', 'otavio.p@aluno.com', '31985432109', 'Av. O, 130'),
(18, 'Aluno Paula Queiroz', '2001-07-03', '00000000007', 'paula.q@aluno.com', '31984321098', 'Rua P, 150'),
(19, 'Aluno Ricardo Santos', '1995-09-19', '00000000008', 'ricardo.s@aluno.com', '31983210987', 'Av. Q, 20'),
(20, 'Aluno Sofia Torres', '1992-04-29', '00000000009', 'sofia.t@aluno.com', '31982109876', 'Rua R, 88'),
(21, 'Aluno Thiago Ulisses', '2000-11-05', '00000000010', 'thiago.u@aluno.com', '31981098765', 'Av. S, 330'),
(22, 'Aluno Úrsula Viana', '1994-01-20', '00000000011', 'ursula.v@aluno.com', '31980987654', 'Rua T, 12'),
(23, 'Aluno Victor Xavier', '1997-12-12', '00000000012', 'victor.x@aluno.com', '31979876543', 'Av. U, 222'),
(24, 'Aluno Wesley Zappa', '2003-08-27', '00000000013', 'wesley.z@aluno.com', '31978765432', 'Rua V, 77'),
(25, 'Aluno Yolanda Castro', '2005-02-14', '00000000014', 'yolanda.c@aluno.com', '31977654321', 'Av. W, 404'),
(26, 'Aluno Zélia Dias', '1996-06-03', '00000000015', 'zelia.d@aluno.com', '31976543210', 'Rua X, 99'),
(27, 'Aluno Alice Rocha', '2002-10-10', '00000000016', 'alice.r@aluno.com', '31975432109', 'Av. Y, 111'),
(28, 'Aluno Benício Freitas', '2004-03-01', '00000000017', 'benicio.f@aluno.com', '31974321098', 'Rua Z, 55'),
(29, 'Aluno Cauã Guedes', '1998-09-21', '00000000018', 'caua.g@aluno.com', '31973210987', 'Rua Alfa, 10'),
(30, 'Aluno Débora Leal', '1993-05-18', '00000000019', 'debora.l@aluno.com', '31972109876', 'Av. Beta, 20'),
(31, 'Aluno Elias Moura', '2000-07-26', '00000000020', 'elias.m@aluno.com', '31971098765', 'Rua Gama, 30'),
(32, 'Aluno Fernanda Nunes', '2001-04-04', '00000000021', 'fernanda.n@aluno.com', '31970987654', 'Av. Delta, 40'),
(33, 'Aluno Gabriel H', '2001-05-05', '12345678901', 'gabriel@aluno.com', '31900000001', 'Rua Teste'),
(34, 'Aluno Helena I', '2001-06-06', '12345678902', 'helena@aluno.com', '31900000002', 'Rua Teste'),
(35, 'Aluno Igor J', '2001-07-07', '12345678903', 'igor@aluno.com', '31900000003', 'Rua Teste'),
(36, 'Aluno Julia K', '2001-08-08', '12345678904', 'julia@aluno.com', '31900000004', 'Rua Teste'),
(37, 'Aluno Kleber L', '2001-09-09', '12345678905', 'kleber@aluno.com', '31900000005', 'Rua Teste'),
(38, 'Aluno Lilian M', '2001-10-10', '12345678906', 'lilian@aluno.com', '31900000006', 'Rua Teste'),
(39, 'Aluno Marcos N', '2001-11-11', '12345678907', 'marcos@aluno.com', '31900000007', 'Rua Teste'),
(40, 'Aluno Nair O', '2001-12-12', '12345678908', 'nair@aluno.com', '31900000008', 'Rua Teste');

INSERT INTO alunos (aluno_id, nivel_proeficiencia_inicial) 
SELECT pessoa_id, 'Básico' FROM pessoas WHERE pessoa_id >= 6;

-- 8. MATRÍCULAS COM IDS FORÇADOS (1 a 39) - AQUI ESTAVA O PROBLEMA DO FK
INSERT INTO matriculas (matricula_id, aluno_id, turma_id, data_matricula, valor_total_curso, status_mat) VALUES
(1, 6, 1, '2025-01-20', 1800.00, 'Ativa'),
(2, 7, 3, '2025-04-25', 2400.00, 'Ativa'),
(3, 8, 4, '2025-03-01', 1800.00, 'Ativa'),
(4, 9, 6, '2024-12-10', 3000.00, 'Ativa'),
(5, 10, 7, '2025-03-20', 2100.00, 'Ativa'),
(6, 11, 9, '2024-12-30', 1800.00, 'Ativa'),
(7, 12, 11, '2025-03-25', 900.00, 'Ativa'),
(8, 13, 13, '2025-02-15', 1800.00, 'Ativa'),
(9, 14, 14, '2025-01-10', 1800.00, 'Ativa'),
(10, 15, 1, '2025-01-25', 1800.00, 'Ativa'),
(11, 16, 3, '2025-04-20', 2400.00, 'Ativa'),
(12, 17, 7, '2025-03-22', 2100.00, 'Ativa'),
(13, 18, 1, '2025-02-01', 1800.00, 'Ativa'),
(14, 19, 2, '2024-03-10', 1800.00, 'Ativa'),
(15, 20, 4, '2025-03-05', 1800.00, 'Ativa'),
(16, 21, 9, '2025-01-15', 1800.00, 'Ativa'),
(17, 22, 10, '2024-02-15', 3600.00, 'Ativa'),
(18, 23, 6, '2025-01-25', 3000.00, 'Ativa'),
(19, 24, 13, '2025-03-10', 1800.00, 'Ativa'),
(20, 25, 14, '2025-01-20', 1800.00, 'Ativa'),
(21, 26, 3, '2025-05-01', 2400.00, 'Ativa'),
(22, 27, 11, '2025-04-05', 900.00, 'Ativa'),
(23, 28, 9, '2025-02-10', 1800.00, 'Ativa'),
(24, 29, 6, '2025-02-20', 3000.00, 'Ativa'),
(25, 30, 4, '2025-04-01', 1800.00, 'Ativa'),
(26, 31, 13, '2025-03-05', 1800.00, 'Ativa'),
(27, 32, 7, '2025-04-20', 2100.00, 'Ativa'),
(28, 33, 1, '2024-03-01', 1800.00, 'Ativa'), -- Concluídas/Pagas (Exemplo)
(29, 34, 1, '2024-02-01', 1800.00, 'Ativa'),
(30, 35, 1, '2024-09-01', 1800.00, 'Ativa'),
(31, 36, 1, '2024-02-01', 1800.00, 'Ativa'),
(32, 37, 1, '2024-03-01', 1800.00, 'Ativa'),
(33, 38, 1, '2024-02-05', 1800.00, 'Ativa'),
(34, 39, 1, '2024-10-05', 1800.00, 'Ativa'),
(35, 40, 1, '2024-05-10', 1800.00, 'Ativa'),
(36, 7, 1, '2025-05-01', 1800.00, 'Ativa'),
(37, 10, 1, '2025-05-20', 1800.00, 'Ativa'),
(38, 8, 1, '2025-03-25', 1800.00, 'Ativa'),
(39, 12, 1, '2025-04-20', 1800.00, 'Ativa');

-- 9. Agora sim, pode rodar o seu INSERT gigante de mensalidades aqui abaixo...
-- [COLE O SEU COMANDO DE MENSALIDADES AQUI]

-- 8. Mensalidades (IMPORTANTE: Inserção Manual para Preservar Histórico Específico da Parte I/II)
-- Não usaremos a procedure aqui para garantir que existem parcelas "Vencidas" no passado e "Pagas"
-- nas datas exatas que os casos de teste da Parte II (Functions/Views) exigem.
INSERT INTO mensalidades (matricula_id, numero_parcela, forma_pagamento_id, data_vencimento, valor_nominal, status_pag, data_pag, valor_pag) VALUES
-- Daniel (Matricula 1 - ID Aluno 6)
(1, 1, 1, '2025-02-20', 300.00, 'Pago', '2025-02-18', 300.00),
(1, 2, 2, '2025-03-20', 300.00, 'Pago', '2025-03-20', 300.00),
(1, 3, 5, '2025-04-20', 300.00, 'Pago', '2025-04-29', 300.00),
(1, 4, 1, '2025-05-20', 300.00, 'Pendente', NULL, NULL),
(1, 5, 2, '2025-06-20', 300.00, 'Pendente', NULL, NULL),
(1, 6, 3, '2025-07-20', 300.00, 'Pendente', NULL, NULL),

-- ID 2 (Elisa, 8x300.00)
(2, 1, 3, '2025-05-25', 300.00, 'Pendente', NULL, NULL),
(2, 2, 4, '2025-06-25', 300.00, 'Pendente', NULL, NULL),
(2, 3, 1, '2025-07-25', 300.00, 'Pendente', NULL, NULL),
(2, 4, 2, '2025-08-25', 300.00, 'Pendente', NULL, NULL),
(2, 5, 3, '2025-09-25', 300.00, 'Pendente', NULL, NULL),
(2, 6, 4, '2025-10-25', 300.00, 'Pendente', NULL, NULL),
(2, 7, 1, '2025-11-25', 300.00, 'Pendente', NULL, NULL),
(2, 8, 2, '2025-12-25', 300.00, 'Pendente', NULL, NULL),

-- ID 3 (Fábio, 6x300.00)
(3, 1, 4, '2025-04-01', 300.00, 'Pago', '2025-03-30', 300.00),
(3, 2, 1, '2025-05-01', 300.00, 'Pendente', NULL, NULL),
(3, 3, 2, '2025-06-01', 300.00, 'Pendente', NULL, NULL),
(3, 4, 3, '2025-07-01', 300.00, 'Pendente', NULL, NULL),
(3, 5, 4, '2025-08-01', 300.00, 'Pendente', NULL, NULL),
(3, 6, 1, '2025-09-01', 300.00, 'Pendente', NULL, NULL),

-- Gabriela (Matricula 4 - ID Aluno 9 - Possui dívidas para teste de função)
(4, 1, 1, '2025-01-10', 300.00, 'Pago', '2025-01-08', 300.00),
(4, 2, 2, '2025-02-10', 300.00, 'Pago', '2025-02-10', 300.00),
(4, 3, 3, '2025-03-10', 300.00, 'Pago', '2025-03-12', 300.00),
(4, 4, 4, '2025-04-10', 300.00, 'Vencido', NULL, 300.00), -- Forçando Vencido para teste
(4, 5, 1, '2025-05-10', 300.00, 'Pendente', NULL, NULL),
(4, 6, 2, '2025-06-10', 300.00, 'Pendente', NULL, NULL),
(4, 7, 3, '2025-07-10', 300.00, 'Pendente', NULL, NULL),
(4, 8, 4, '2025-08-10', 300.00, 'Pendente', NULL, NULL),
(4, 9, 1, '2025-09-10', 300.00, 'Pendente', NULL, NULL),
(4, 10, 2, '2025-10-10', 300.00, 'Pendente', NULL, NULL),

-- ID 5 (Hugo, 7x300.00)
(5, 1, 5, '2025-04-20', 300.00, 'Pago', '2025-04-30', 300.00),
(5, 2, 4, '2025-05-20', 300.00, 'Pendente', NULL, NULL),
(5, 3, 1, '2025-06-20', 300.00, 'Pendente', NULL, NULL),
(5, 4, 2, '2025-07-20', 300.00, 'Pendente', NULL, NULL),
(5, 5, 3, '2025-08-20', 300.00, 'Pendente', NULL, NULL),
(5, 6, 4, '2025-09-20', 300.00, 'Pendente', NULL, NULL),
(5, 7, 1, '2025-10-20', 300.00, 'Pendente', NULL, NULL),

-- ID 6 (Irene, 6x300.00)
(6, 1, 2, '2025-01-30', 300.00, 'Pago', '2025-01-30', 300.00),
(6, 2, 3, '2025-02-28', 300.00, 'Pago', '2025-02-27', 300.00),
(6, 3, 4, '2025-03-30', 300.00, 'Pago', '2025-04-01', 300.00),
(6, 4, 1, '2025-04-30', 300.00, 'Vencido', NULL, 300.00),
(6, 5, 2, '2025-05-30', 300.00, 'Pendente', NULL, NULL),
(6, 6, 3, '2025-06-30', 300.00, 'Pendente', NULL, NULL),

-- ID 7 (João, 3x300.00)
(7, 1, 4, '2025-04-25', 300.00, 'Vencido', NULL, 300.00),
(7, 2, 1, '2025-05-25', 300.00, 'Pendente', NULL, NULL),
(7, 3, 2, '2025-06-25', 300.00, 'Pendente', NULL, NULL),

-- ID 8 (Karen, 6x300.00)
(8, 1, 3, '2025-03-15', 300.00, 'Pago', '2025-03-14', 300.00),
(8, 2, 4, '2025-04-15', 300.00, 'Pago', '2025-04-15', 300.00),
(8, 3, 1, '2025-05-15', 300.00, 'Pendente', NULL, NULL),
(8, 4, 2, '2025-06-15', 300.00, 'Pendente', NULL, NULL),
(8, 5, 3, '2025-07-15', 300.00, 'Pendente', NULL, NULL),
(8, 6, 4, '2025-08-15', 300.00, 'Pendente', NULL, NULL),

-- ID 9 (Lucas, 6x300.00)
(9, 1, 1, '2025-02-10', 300.00, 'Pago', '2025-02-09', 300.00),
(9, 2, 2, '2025-03-10', 300.00, 'Pago', '2025-03-11', 300.00),
(9, 3, 3, '2025-04-10', 300.00, 'Pago', '2025-04-09', 300.00),
(9, 4, 4, '2025-05-10', 300.00, 'Pendente', NULL, NULL),
(9, 5, 1, '2025-06-10', 300.00, 'Pendente', NULL, NULL),
(9, 6, 2, '2025-07-10', 300.00, 'Pendente', NULL, NULL),

-- ID 10 (Mariana, 6x300.00)
(10, 1, 2, '2025-02-25', 300.00, 'Pago', '2025-02-23', 300.00),
(10, 2, 3, '2025-03-25', 300.00, 'Pago', '2025-03-25', 300.00),
(10, 3, 4, '2025-04-25', 300.00, 'Vencido', NULL, 300.00),
(10, 4, 1, '2025-05-25', 300.00, 'Pendente', NULL, NULL),
(10, 5, 2, '2025-06-25', 300.00, 'Pendente', NULL, NULL),
(10, 6, 3, '2025-07-25', 300.00, 'Pendente', NULL, NULL),

-- ID 11 (Natália, 8x300.00)
(11, 1, 3, '2025-05-20', 300.00, 'Pendente', NULL, NULL),
(11, 2, 4, '2025-06-20', 300.00, 'Pendente', NULL, NULL),
(11, 3, 1, '2025-07-20', 300.00, 'Pendente', NULL, NULL),
(11, 4, 2, '2025-08-20', 300.00, 'Pendente', NULL, NULL),
(11, 5, 3, '2025-09-20', 300.00, 'Pendente', NULL, NULL),
(11, 6, 4, '2025-10-20', 300.00, 'Pendente', NULL, NULL),
(11, 7, 1, '2025-11-20', 300.00, 'Pendente', NULL, NULL),
(11, 8, 2, '2025-12-20', 300.00, 'Pendente', NULL, NULL),

-- ID 12 (Otávio, 7x300.00)
(12, 1, 4, '2025-04-22', 300.00, 'Vencido', NULL, 300.00),
(12, 2, 1, '2025-05-22', 300.00, 'Pendente', NULL, NULL),
(12, 3, 2, '2025-06-22', 300.00, 'Pendente', NULL, NULL),
(12, 4, 3, '2025-07-22', 300.00, 'Pendente', NULL, NULL),
(12, 5, 4, '2025-08-22', 300.00, 'Pendente', NULL, NULL),
(12, 6, 1, '2025-09-22', 300.00, 'Pendente', NULL, NULL),
(12, 7, 2, '2025-10-22', 300.00, 'Pendente', NULL, NULL),

-- ID 13 (Paula, 6x300.00)
(13, 1, 3, '2025-03-01', 300.00, 'Pago', '2025-03-01', 300.00),
(13, 2, 4, '2025-04-01', 300.00, 'Pago', '2025-03-31', 300.00),
(13, 3, 1, '2025-05-01', 300.00, 'Pendente', NULL, NULL),
(13, 4, 2, '2025-06-01', 300.00, 'Pendente', NULL, NULL),
(13, 5, 3, '2025-07-01', 300.00, 'Pendente', NULL, NULL),
(13, 6, 4, '2025-08-01', 300.00, 'Pendente', NULL, NULL),

-- ID 14 (Ricardo, 15x300.00)
(14, 1, 1, '2024-04-10', 300.00, 'Pago', '2024-04-09', 300.00),
(14, 2, 2, '2024-05-10', 300.00, 'Pago', '2024-05-11', 300.00),
(14, 3, 3, '2024-06-10', 300.00, 'Pago', '2024-06-10', 300.00),
(14, 4, 4, '2024-07-10', 300.00, 'Pago', '2024-07-12', 300.00),
(14, 5, 1, '2024-08-10', 300.00, 'Pago', '2024-08-10', 300.00),
(14, 6, 2, '2024-09-10', 300.00, 'Pago', '2024-09-09', 300.00),
(14, 7, 3, '2024-10-10', 300.00, 'Pago', '2024-10-10', 300.00),
(14, 8, 4, '2024-11-10', 300.00, 'Pago', '2024-11-09', 300.00),
(14, 9, 1, '2024-12-10', 300.00, 'Pago', '2024-12-10', 300.00),
(14, 10, 2, '2025-01-10', 300.00, 'Pago', '2025-01-11', 300.00),
(14, 11, 3, '2025-02-10', 300.00, 'Pago', '2025-02-10', 300.00),
(14, 12, 4, '2025-03-10', 300.00, 'Pago', '2025-03-12', 300.00),
(14, 13, 1, '2025-04-10', 300.00, 'Pago', '2025-04-09', 300.00),
(14, 14, 2, '2025-05-10', 300.00, 'Pendente', NULL, NULL),
(14, 15, 3, '2025-06-10', 300.00, 'Pendente', NULL, NULL),

-- ID 15 (Sofia, 6x300.00)
(15, 1, 3, '2025-04-05', 300.00, 'Pago', '2025-04-05', 300.00),
(15, 2, 4, '2025-05-05', 300.00, 'Pendente', NULL, NULL),
(15, 3, 1, '2025-06-05', 300.00, 'Pendente', NULL, NULL),
(15, 4, 2, '2025-07-05', 300.00, 'Pendente', NULL, NULL),
(15, 5, 3, '2025-08-05', 300.00, 'Pendente', NULL, NULL),
(15, 6, 4, '2025-09-05', 300.00, 'Pendente', NULL, NULL),

-- ID 16 (Thiago, 6x300.00)
(16, 1, 2, '2025-02-15', 300.00, 'Pago', '2025-02-14', 300.00),
(16, 2, 3, '2025-03-15', 300.00, 'Pago', '2025-03-16', 300.00),
(16, 3, 4, '2025-04-15', 300.00, 'Pago', '2025-04-15', 300.00),
(16, 4, 1, '2025-05-15', 300.00, 'Pendente', NULL, NULL),
(16, 5, 2, '2025-06-15', 300.00, 'Pendente', NULL, NULL),
(16, 6, 3, '2025-07-15', 300.00, 'Pendente', NULL, NULL),

-- ID 17 (Úrsula, 14x300.00)
(17, 1, 1, '2024-03-15', 300.00, 'Pago', '2024-03-14', 300.00),
(17, 2, 3, '2024-04-15', 300.00, 'Pago', '2024-04-14', 300.00),
(17, 3, 4, '2024-05-15', 300.00, 'Pago', '2024-05-17', 300.00),
(17, 4, 1, '2024-06-15', 300.00, 'Pago', '2024-06-15', 300.00),
(17, 5, 2, '2024-07-15', 300.00, 'Pago', '2024-07-16', 300.00),
(17, 6, 3, '2024-08-15', 300.00, 'Pago', '2024-08-15', 300.00),
(17, 7, 4, '2024-09-15', 300.00, 'Pago', '2024-09-15', 300.00),
(17, 8, 1, '2024-10-15', 300.00, 'Pago', '2024-10-14', 300.00),
(17, 9, 2, '2024-11-15', 300.00, 'Pago', '2024-11-16', 300.00),
(17, 10, 3, '2024-12-15', 300.00, 'Pago', '2024-12-13', 300.00),
(17, 11, 4, '2025-01-15', 300.00, 'Pago', '2025-01-15', 300.00),
(17, 12, 1, '2025-02-15', 300.00, 'Pago', '2025-02-17', 300.00),
(17, 13, 2, '2025-03-15', 300.00, 'Pago', '2025-03-15', 300.00),
(17, 14, 3, '2025-04-15', 300.00, 'Pago', '2025-04-14', 300.00),

-- ID 18 (Victor, 10x300.00)
(18, 1, 2, '2025-02-25', 300.00, 'Pago', '2025-02-25', 300.00),
(18, 2, 3, '2025-03-25', 300.00, 'Pago', '2025-03-24', 300.00),
(18, 3, 4, '2025-04-25', 300.00, 'Vencido', NULL, 300.00),
(18, 4, 1, '2025-05-25', 300.00, 'Pendente', NULL, NULL),
(18, 5, 2, '2025-06-25', 300.00, 'Pendente', NULL, NULL),
(18, 6, 3, '2025-07-25', 300.00, 'Pendente', NULL, NULL),
(18, 7, 4, '2025-08-25', 300.00, 'Pendente', NULL, NULL),
(18, 8, 1, '2025-09-25', 300.00, 'Pendente', NULL, NULL),
(18, 9, 2, '2025-10-25', 300.00, 'Pendente', NULL, NULL),
(18, 10, 3, '2025-11-25', 300.00, 'Pendente', NULL, NULL),

-- ID 19 (Wesley, 6x300.00)
(19, 1, 4, '2025-04-10', 300.00, 'Pago', '2025-04-10', 300.00),
(19, 2, 1, '2025-05-10', 300.00, 'Pendente', NULL, NULL),
(19, 3, 2, '2025-06-10', 300.00, 'Pendente', NULL, NULL),
(19, 4, 3, '2025-07-10', 300.00, 'Pendente', NULL, NULL),
(19, 5, 4, '2025-08-10', 300.00, 'Pendente', NULL, NULL),
(19, 6, 1, '2025-09-10', 300.00, 'Pendente', NULL, NULL),

-- ID 20 (Yolanda, 6x300.00)
(20, 1, 2, '2025-02-20', 300.00, 'Pago', '2025-02-21', 300.00),
(20, 2, 3, '2025-03-20', 300.00, 'Pago', '2025-03-20', 300.00),
(20, 3, 4, '2025-04-20', 300.00, 'Vencido', NULL, 300.00),
(20, 4, 1, '2025-05-20', 300.00, 'Pendente', NULL, NULL),
(20, 5, 2, '2025-06-20', 300.00, 'Pendente', NULL, NULL),
(20, 6, 3, '2025-07-20', 300.00, 'Pendente', NULL, NULL),

-- ID 21 (Zélia, 8x300.00)
(21, 1, 1, '2025-06-01', 300.00, 'Pendente', NULL, NULL),
(21, 2, 2, '2025-07-01', 300.00, 'Pendente', NULL, NULL),
(21, 3, 3, '2025-08-01', 300.00, 'Pendente', NULL, NULL),
(21, 4, 4, '2025-09-01', 300.00, 'Pendente', NULL, NULL),
(21, 5, 1, '2025-10-01', 300.00, 'Pendente', NULL, NULL),
(21, 6, 2, '2025-11-01', 300.00, 'Pendente', NULL, NULL),
(21, 7, 3, '2025-12-01', 300.00, 'Pendente', NULL, NULL),
(21, 8, 4, '2026-01-01', 300.00, 'Pendente', NULL, NULL),

-- ID 22 (Alice, 3x300.00)
(22, 1, 2, '2025-05-05', 300.00, 'Pendente', NULL, NULL),
(22, 2, 3, '2025-06-05', 300.00, 'Pendente', NULL, NULL),
(22, 3, 4, '2025-07-05', 300.00, 'Pendente', NULL, NULL),

-- ID 23 (Benício, 6x300.00)
(23, 1, 1, '2025-03-10', 300.00, 'Pago', '2025-03-10', 300.00),
(23, 2, 2, '2025-04-10', 300.00, 'Pago', '2025-04-08', 300.00),
(23, 3, 3, '2025-05-10', 300.00, 'Pendente', NULL, NULL),
(23, 4, 4, '2025-06-10', 300.00, 'Pendente', NULL, NULL),
(23, 5, 1, '2025-07-10', 300.00, 'Pendente', NULL, NULL),
(23, 6, 2, '2025-08-10', 300.00, 'Pendente', NULL, NULL),

-- ID 24 (Cauã, 10x300.00)
(24, 1, 3, '2025-03-20', 300.00, 'Pago', '2025-03-20', 300.00),
(24, 2, 4, '2025-04-20', 300.00, 'Vencido', NULL, 300.00),
(24, 3, 1, '2025-05-20', 300.00, 'Pendente', NULL, NULL),
(24, 4, 2, '2025-06-20', 300.00, 'Pendente', NULL, NULL),
(24, 5, 3, '2025-07-20', 300.00, 'Pendente', NULL, NULL),
(24, 6, 4, '2025-08-20', 300.00, 'Pendente', NULL, NULL),
(24, 7, 1, '2025-09-20', 300.00, 'Pendente', NULL, NULL),
(24, 8, 2, '2025-10-20', 300.00, 'Pendente', NULL, NULL),
(24, 9, 3, '2025-11-20', 300.00, 'Pendente', NULL, NULL),
(24, 10, 4, '2025-12-20', 300.00, 'Pendente', NULL, NULL),

-- ID 25 (Débora, 6x300.00)
(25, 1, 1, '2025-05-01', 300.00, 'Pendente', NULL, NULL),
(25, 2, 2, '2025-06-01', 300.00, 'Pendente', NULL, NULL),
(25, 3, 3, '2025-07-01', 300.00, 'Pendente', NULL, NULL),
(25, 4, 4, '2025-08-01', 300.00, 'Pendente', NULL, NULL),
(25, 5, 1, '2025-09-01', 300.00, 'Pendente', NULL, NULL),
(25, 6, 2, '2025-10-01', 300.00, 'Pendente', NULL, NULL),

-- ID 26 (Elias, 6x300.00)
(26, 1, 3, '2025-04-05', 300.00, 'Pago', '2025-04-04', 300.00),
(26, 2, 4, '2025-05-05', 300.00, 'Pendente', NULL, NULL),
(26, 3, 1, '2025-06-05', 300.00, 'Pendente', NULL, NULL),
(26, 4, 2, '2025-07-05', 300.00, 'Pendente', NULL, NULL),
(26, 5, 3, '2025-08-05', 300.00, 'Pendente', NULL, NULL),
(26, 6, 4, '2025-09-05', 300.00, 'Pendente', NULL, NULL),

-- ID 27 (Fernanda, 7x300.00)
(27, 1, 1, '2025-05-20', 300.00, 'Pendente', NULL, NULL),
(27, 2, 2, '2025-06-20', 300.00, 'Pendente', NULL, NULL),
(27, 3, 3, '2025-07-20', 300.00, 'Pendente', NULL, NULL),
(27, 4, 4, '2025-08-20', 300.00, 'Pendente', NULL, NULL),
(27, 5, 1, '2025-09-20', 300.00, 'Pendente', NULL, NULL),
(27, 6, 2, '2025-10-20', 300.00, 'Pendente', NULL, NULL),
(27, 7, 3, '2025-11-20', 300.00, 'Pendente', NULL, NULL),

-- ==========================================================
-- Matrículas CONCLUÍDAS (ID 28 ao 35) - Todas Pagas
-- ==========================================================
(28, 1, 4, '2024-03-01', 300.00, 'Pago', '2024-03-01', 300.00),
(28, 2, 1, '2024-04-01', 300.00, 'Pago', '2024-04-02', 300.00),
(28, 3, 2, '2024-05-01', 300.00, 'Pago', '2024-05-01', 300.00),
(28, 4, 3, '2024-06-01', 300.00, 'Pago', '2024-06-03', 300.00),
(28, 5, 4, '2024-07-01', 300.00, 'Pago', '2024-07-01', 300.00),
(28, 6, 1, '2024-08-01', 300.00, 'Pago', '2024-08-01', 300.00),
(29, 1, 2, '2024-02-10', 300.00, 'Pago', '2024-02-10', 300.00),
(29, 2, 3, '2024-03-10', 300.00, 'Pago', '2024-03-11', 300.00),
(29, 3, 4, '2024-04-10', 300.00, 'Pago', '2024-04-10', 300.00),
(29, 4, 1, '2024-05-10', 300.00, 'Pago', '2024-05-12', 300.00),
(29, 5, 2, '2024-06-10', 300.00, 'Pago', '2024-06-10', 300.00),
(29, 6, 3, '2024-07-10', 300.00, 'Pago', '2024-07-10', 300.00),
(30, 1, 4, '2024-09-01', 300.00, 'Pago', '2024-09-01', 300.00),
(30, 2, 1, '2024-10-01', 300.00, 'Pago', '2024-10-03', 300.00),
(30, 3, 2, '2024-11-01', 300.00, 'Pago', '2024-11-01', 300.00),
(30, 4, 3, '2024-12-01', 300.00, 'Pago', '2024-12-02', 300.00),
(31, 1, 1, '2024-02-01', 300.00, 'Pago', '2024-01-30', 300.00),
(31, 2, 2, '2024-03-01', 300.00, 'Pago', '2024-03-01', 300.00),
(31, 3, 3, '2024-04-01', 300.00, 'Pago', '2024-04-02', 300.00),
(31, 4, 4, '2024-05-01', 300.00, 'Pago', '2024-05-01', 300.00),
(31, 5, 1, '2024-06-01', 300.00, 'Pago', '2024-06-03', 300.00),
(31, 6, 2, '2024-07-01', 300.00, 'Pago', '2024-07-01', 300.00),
(31, 7, 3, '2024-08-01', 300.00, 'Pago', '2024-08-01', 300.00),
(31, 8, 4, '2024-09-01', 300.00, 'Pago', '2024-09-02', 300.00),
(31, 9, 1, '2024-10-01', 300.00, 'Pago', '2024-10-01', 300.00),
(31, 10, 2, '2024-11-01', 300.00, 'Pago', '2024-11-01', 300.00),
(31, 11, 3, '2024-12-01', 300.00, 'Pago', '2024-12-03', 300.00),
(31, 12, 4, '2025-01-01', 300.00, 'Pago', '2025-01-01', 300.00),
(32, 1, 3, '2024-03-01', 300.00, 'Pago', '2024-03-01', 300.00),
(32, 2, 4, '2024-04-01', 300.00, 'Pago', '2024-04-01', 300.00),
(32, 3, 1, '2024-05-01', 300.00, 'Pago', '2024-05-01', 300.00),
(32, 4, 2, '2024-06-01', 300.00, 'Pago', '2024-06-02', 300.00),
(32, 5, 3, '2024-07-01', 300.00, 'Pago', '2024-07-01', 300.00),
(32, 6, 4, '2024-08-01', 300.00, 'Pago', '2024-08-01', 300.00),
(33, 1, 1, '2024-02-05', 300.00, 'Pago', '2024-02-05', 300.00),
(33, 2, 2, '2024-03-05', 300.00, 'Pago', '2024-03-06', 300.00),
(33, 3, 3, '2024-04-05', 300.00, 'Pago', '2024-04-05', 300.00),
(33, 4, 4, '2024-05-05', 300.00, 'Pago', '2024-05-05', 300.00),
(33, 5, 1, '2024-06-05', 300.00, 'Pago', '2024-06-04', 300.00),
(33, 6, 2, '2024-07-05', 300.00, 'Pago', '2024-07-05', 300.00),
(34, 1, 2, '2024-10-05', 300.00, 'Pago', '2024-10-05', 300.00),
(34, 2, 3, '2024-11-05', 300.00, 'Pago', '2024-11-06', 300.00),
(34, 3, 4, '2024-12-05', 300.00, 'Pago', '2024-12-05', 300.00),
(34, 4, 1, '2025-01-05', 300.00, 'Pago', '2025-01-07', 300.00),
(35, 1, 3, '2024-05-10', 300.00, 'Pago', '2024-05-10', 300.00),
(35, 2, 4, '2024-06-10', 300.00, 'Pago', '2024-06-09', 300.00),
(35, 3, 1, '2024-07-10', 300.00, 'Pago', '2024-07-10', 300.00),
(35, 4, 2, '2024-08-10', 300.00, 'Pago', '2024-08-10', 300.00),
(35, 5, 3, '2024-09-10', 300.00, 'Pago', '2024-09-11', 300.00),
(35, 6, 4, '2024-10-10', 300.00, 'Pago', '2024-10-10', 300.00),
(35, 7, 1, '2024-11-10', 300.00, 'Pago', '2024-11-10', 300.00),

-- ID 36 (Elisa, 8x300.00, Matr: 2025-05-01) - Parcelas: 06/2025 a 01/2026
(36, 1, 1, '2025-06-01', 300.00, 'Pendente', NULL, NULL),
(36, 2, 1, '2025-07-01', 300.00, 'Pendente', NULL, NULL),
(36, 3, 1, '2025-08-01', 300.00, 'Pendente', NULL, NULL),
(36, 4, 1, '2025-09-01', 300.00, 'Pendente', NULL, NULL),
(36, 5, 1, '2025-10-01', 300.00, 'Pendente', NULL, NULL),
(36, 6, 1, '2025-11-01', 300.00, 'Pendente', NULL, NULL),
(36, 7, 1, '2025-12-01', 300.00, 'Pendente', NULL, NULL),
(36, 8, 1, '2026-01-01', 300.00, 'Pendente', NULL, NULL),

-- ID 37 (Hugo, 6x300.00, Matr: 2025-05-20) - Parcelas: 06/2025 a 11/2025
(37, 1, 2, '2025-06-20', 300.00, 'Pendente', NULL, NULL),
(37, 2, 2, '2025-07-20', 300.00, 'Pendente', NULL, NULL),
(37, 3, 2, '2025-08-20', 300.00, 'Pendente', NULL, NULL),
(37, 4, 2, '2025-09-20', 300.00, 'Pendente', NULL, NULL),
(37, 5, 2, '2025-10-20', 300.00, 'Pendente', NULL, NULL),
(37, 6, 2, '2025-11-20', 300.00, 'Pendente', NULL, NULL),

-- ID 38 (Fábio, 6x300.00, Matr: 2025-03-25) - Parcelas: 04 a 09/2025
(38, 1, 3, '2025-04-25', 300.00, 'Vencido', NULL, 300.00),
(38, 2, 3, '2025-05-25', 300.00, 'Pendente', NULL, NULL),
(38, 3, 3, '2025-06-25', 300.00, 'Pendente', NULL, NULL),
(38, 4, 3, '2025-07-25', 300.00, 'Pendente', NULL, NULL),
(38, 5, 3, '2025-08-25', 300.00, 'Pendente', NULL, NULL),
(38, 6, 3, '2025-09-25', 300.00, 'Pendente', NULL, NULL),

-- ID 39 (João, 3x300.00, Matr: 2025-04-20) - Parcelas: 05 a 07/2025
(39, 1, 4, '2025-05-20', 300.00, 'Pendente', NULL, NULL),
(39, 2, 4, '2025-06-20', 300.00, 'Pendente', NULL, NULL),
(39, 3, 4, '2025-07-20', 300.00, 'Pendente', NULL, NULL);


-- 9. Avaliações (Manual para manter consistência com consultas de média)
INSERT INTO avaliacoes (matricula_id, professor_id, data_avaliacao, tipo_avaliacao, nota) VALUES
(1, 1, '2025-03-20', 'Quiz', 8.50),
(1, 1, '2025-05-01', 'Trabalho', 7.50),
(4, 2, '2025-02-15', 'Participação', 9.50),
(4, 2, '2025-04-20', 'Trabalho', 9.80);

/* ================================================================================
PROCEDURE DE CARGA MASSIVA (PARTE III) - OTIMIZADA
================================================================================
*/
USE escola_idiomas;

DROP PROCEDURE IF EXISTS sp_carga_massiva;
DELIMITER //
CREATE PROCEDURE sp_carga_massiva(IN p_quantidade INT)
BEGIN
    DECLARE v_i INT DEFAULT 1;
    DECLARE v_novo_aluno_id INT;
    DECLARE v_nova_matricula_id INT;
    DECLARE v_turma_massiva_id INT;
    
    WHILE v_i <= p_quantidade DO
        -- 1. Cria Aluno genérico
        INSERT INTO pessoas (nome, data_nasc, cpf, email, telefone, endereco) 
        VALUES (CONCAT('Aluno Massivo ', v_i), '2000-01-01', CONCAT('CPF', LPAD(v_i, 8, '0')), CONCAT('aluno', v_i, '@massivo.com'), '31999999999', 'Rua Massiva');
        SET v_novo_aluno_id = LAST_INSERT_ID();
        INSERT INTO alunos (aluno_id, nivel_proeficiencia_inicial) VALUES (v_novo_aluno_id, 'Básico');
        
        -- 2. Define turma (20 ou 21)
        IF (RAND() > 0.5) THEN SET v_turma_massiva_id = 20; ELSE SET v_turma_massiva_id = 21; END IF;

        -- 3. Matrícula e Financeiro (Chama sua Procedure da Parte II)
        INSERT INTO matriculas (aluno_id, turma_id, data_matricula, valor_total_curso, status_mat) VALUES (v_novo_aluno_id, v_turma_massiva_id, CURDATE(), 2000.00, 'Ativa');
        SET v_nova_matricula_id = LAST_INSERT_ID();
        CALL sp_gerar_mensalidades(v_nova_matricula_id);
        
        -- 4. Avaliação aleatória
        INSERT INTO avaliacoes (matricula_id, professor_id, data_avaliacao, tipo_avaliacao, nota) VALUES (v_nova_matricula_id, 1, CURDATE(), 'Prova', ROUND((RAND() * 10), 2));

        SET v_i = v_i + 1;
    END WHILE;
END //
DELIMITER ;

-- =============================================================================
-- EXECUTANDO A CARGA (Teste com 2.000 registros para "Volume Razoável") (gerará ~12.000 mensalidades)
-- =============================================================================
-- Isso vai demorar um pouquinho pois executa a procedure financeira linha a linha,
-- mas é exatamente o que prova que seu sistema é robusto e usa as regras.
CALL sp_carga_massiva(2000);

-- Conferência Final
SELECT COUNT(*) as Quantidade_de_Pessoas FROM pessoas;
SELECT COUNT(*) as Quantidade_de_Mensalidades FROM mensalidades; -- Deve ter aumentado muito (2000 * duração do curso)