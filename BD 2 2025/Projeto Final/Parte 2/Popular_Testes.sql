-- ==========================================================
-- PREPARAÇÃO PARA TESTE DA TRIGGER 1: LOTAÇÃO DA TURMA 19
-- Capacidade da Turma 19: 18. Ocupação Atual: 1. Faltam 17.
-- Ocupação Final: 1 (original) + 17 (preparação) + 1 (teste) = 19 (BLOQUEIO)
-- ==========================================================

-- Inserindo 17 Pessoas/Alunos fictícios (IDs 101 a 117)
INSERT INTO pessoas (pessoa_id, nome, data_nasc, cpf, email, telefone, endereco) VALUES
(101, 'Teste Aluno A', '2000-01-01', '10110110101', 'aluno101@test.com', '31900001010', 'Rua Teste A'),
(102, 'Teste Aluno B', '2000-01-02', '10210210202', 'aluno102@test.com', '31900001020', 'Rua Teste B'),
(103, 'Teste Aluno C', '2000-01-03', '10310310303', 'aluno103@test.com', '31900001030', 'Rua Teste C'),
(104, 'Teste Aluno D', '2000-01-04', '10410410404', 'aluno104@test.com', '31900001040', 'Rua Teste D'),
(105, 'Teste Aluno E', '2000-01-05', '10510510505', 'aluno105@test.com', '31900001050', 'Rua Teste E'),
(106, 'Teste Aluno F', '2000-01-06', '10610610606', 'aluno106@test.com', '31900001060', 'Rua Teste F'),
(107, 'Teste Aluno G', '2000-01-07', '10710710707', 'aluno107@test.com', '31900001070', 'Rua Teste G'),
(108, 'Teste Aluno H', '2000-01-08', '10810810808', 'aluno108@test.com', '31900001080', 'Rua Teste H'),
(109, 'Teste Aluno I', '2000-01-09', '10910910909', 'aluno109@test.com', '31900001090', 'Rua Teste I'),
(110, 'Teste Aluno J', '2000-01-10', '11011011010', 'aluno110@test.com', '31900001100', 'Rua Teste J'),
(111, 'Teste Aluno K', '2000-01-11', '11111111100', 'aluno111@test.com', '31900001110', 'Rua Teste K'),
(112, 'Teste Aluno L', '2000-01-12', '11211211211', 'aluno112@test.com', '31900001120', 'Rua Teste L'),
(113, 'Teste Aluno M', '2000-01-13', '11311311313', 'aluno113@test.com', '31900001130', 'Rua Teste M'),
(114, 'Teste Aluno N', '2000-01-14', '11411411414', 'aluno114@test.com', '31900001140', 'Rua Teste N'),
(115, 'Teste Aluno O', '2000-01-15', '11511511515', 'aluno115@test.com', '31900001150', 'Rua Teste O'),
(116, 'Teste Aluno P', '2000-01-16', '11611611616', 'aluno116@test.com', '31900001160', 'Rua Teste P'),
(117, 'Teste Aluno Q', '2000-01-17', '11711711717', 'aluno117@test.com', '31900001170', 'Rua Teste Q');

INSERT INTO alunos (aluno_id, nivel_proeficiencia_inicial) VALUES
(101, 'Básico'), (102, 'Básico'), (103, 'Básico'), (104, 'Básico'),
(105, 'Básico'), (106, 'Básico'), (107, 'Básico'), (108, 'Básico'),
(109, 'Básico'), (110, 'Básico'), (111, 'Básico'), (112, 'Básico'),
(113, 'Básico'), (114, 'Básico'), (115, 'Básico'), (116, 'Básico'),
(117, 'Básico');

-- OBS: Se o seu DDL forçar AUTO_INCREMENT em 'pessoas', você pode ter que desabilitar
-- e reabilitar para inserir IDs específicos, mas o seu DDL para 'pessoas' usa AUTO_INCREMENT, 
-- o que significa que o DML original deve ter inserido do 1 ao 32. 
-- Para fins acadêmicos e para a execução dos testes, assumiremos que os IDs acima foram inseridos.

-- Se for necessário, use um SET para o AUTO_INCREMENT:
-- ALTER TABLE pessoas AUTO_INCREMENT = 118;

-- 2. Inserção das Matrículas para Lotar (Matrículas IDs 101 ao 117)
INSERT INTO matriculas (matricula_id, aluno_id, turma_id, data_matricula, valor_total_curso, status_mat) VALUES
(101, 101, 19, '2025-05-01', 900.00, 'Ativa'),
(102, 102, 19, '2025-05-01', 900.00, 'Ativa'),
(103, 103, 19, '2025-05-01', 900.00, 'Ativa'),
(104, 104, 19, '2025-05-01', 900.00, 'Ativa'),
(105, 105, 19, '2025-05-01', 900.00, 'Ativa'),
(106, 106, 19, '2025-05-01', 900.00, 'Ativa'),
(107, 107, 19, '2025-05-01', 900.00, 'Ativa'),
(108, 108, 19, '2025-05-01', 900.00, 'Ativa'),
(109, 109, 19, '2025-05-01', 900.00, 'Ativa'),
(110, 110, 19, '2025-05-01', 900.00, 'Ativa'),
(111, 111, 19, '2025-05-01', 900.00, 'Ativa'),
(112, 112, 19, '2025-05-01', 900.00, 'Ativa'),
(113, 113, 19, '2025-05-01', 900.00, 'Ativa'),
(114, 114, 19, '2025-05-01', 900.00, 'Ativa'),
(115, 115, 19, '2025-05-01', 900.00, 'Ativa'),
(116, 116, 19, '2025-05-01', 900.00, 'Ativa'),
(117, 117, 19, '2025-05-01', 900.00, 'Ativa');