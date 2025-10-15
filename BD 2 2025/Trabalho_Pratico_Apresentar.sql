-- Criação do banco de dados
DROP DATABASE IF EXISTS vs_escola_idiomas;
CREATE DATABASE vs_escola_idiomas;

-- Seleciona o banco de dados para uso
use vs_escola_idiomas;

-- Criação da tabela gerenciar Alunos
create table vs_alunos(
aluno_id integer not null auto_increment primary key,
nome varchar(50) not null,
data_nasc date not null,
cpf varchar(11) unique not null,
email varchar(50) not null unique,
telefone varchar(15) not null,
endereco varchar(100) not null
);

-- Criação da tabela gerenciar Professores
create table vs_professores(
professor_id integer not null auto_increment primary key,
nome varchar(50) not null,
data_nasc date not null,
cpf varchar(11) unique not null,
email varchar(50) not null unique,
telefone varchar(15) not null,
endereco varchar(100) not null,
especialidade varchar(50),
data_contratacao date not null default (current_date),
salario decimal(10,2) default (0.00)
);

-- Criação da tabela gerenciar Cursos
create table vs_cursos(
curso_id integer not null auto_increment primary key,
nome varchar(50) not null,
descricao varchar(150),
duracao_meses integer,
valor_mensalidade decimal(8,2)
);

-- Criação da tabela gerenciar Formas de Pagamento
create table vs_formas_pagamento(
forma_pagamento_id integer not null auto_increment primary key,
nome varchar(50) not null,
descricao varchar(100)
);

-- Criação da tabela gerenciar Turmas
create table vs_turmas(
turma_id integer not null auto_increment primary key,
nome varchar(50) not null,
dias_semana varchar(50),
horario_inicio time not null,
horario_fim time not null,
data_inicio date not null,
data_fim date not null,
curso_id integer,
professor_id integer,
-- Definição das Chaves Estrangeiras (FKs)
foreign key (curso_id) references vs_cursos (curso_id),
foreign key (professor_id) references vs_professores (professor_id)
);

-- Criação da tabela gerenciar Matrículas
create table vs_matriculas(
matricula_id integer not null auto_increment primary key,
data_matricula date not null default (current_date),
status_mat varchar(20) not null,
aluno_id integer,
turma_id integer,
-- Definição das Chaves Estrangeiras (FKs)
foreign key (aluno_id) references vs_alunos (aluno_id),
foreign key (turma_id) references vs_turmas (turma_id),
-- Restrição CHECK para o campo status_mat
check (status_mat in ('Ativa', 'Inativa', 'Concluída'))
);

-- Criação da tabela gerenciar Pagamentos
create table vs_pagamentos(
pagamento_id integer not null auto_increment primary key,
data_pag date not null,
valor decimal(8,2) default (0.00),
mes_referencia varchar(10) not null,
status_pag varchar(20) not null,
aluno_id integer,
matricula_id integer,
forma_pagamento_id integer,
-- Definição das Chaves Estrangeiras (FKs)
foreign key (aluno_id) references vs_alunos (aluno_id),
foreign key (matricula_id) references vs_matriculas (matricula_id),
foreign key (forma_pagamento_id) references vs_formas_pagamento (forma_pagamento_id),
-- Restrição CHECK para o campo status_pag
check (status_pag in ('Pago', 'Atrasado', 'Pendente'))
);

-- Criação da tabela gerenciar Avaliações
create table vs_avaliacoes(
avaliacao_id integer not null auto_increment primary key,
data_ava date not null default (current_date),
tipo varchar(50) not null,
nota decimal(4,2) not null default (0.00),
aluno_id integer,
turma_id integer,
professor_id integer,
-- Definição das Chaves Estrangeiras (FKs)
foreign key (aluno_id) references vs_alunos (aluno_id),
foreign key (turma_id) references vs_turmas (turma_id),
foreign key (professor_id) references vs_professores (professor_id)
);

-- ---------------------------------------------------------------------------------------------------------------------------------------------------------------
-- Desabilita a verificação de chaves estrangeiras temporariamente para facilitar a inserção de dados
SET FOREIGN_KEY_CHECKS = 0;
-- INSERÇÃO DE DADOS FICTÍCIOS

-- Inserindo 20 registros na tabela vs_alunos
INSERT INTO vs_alunos (nome, data_nasc, cpf, email, telefone, endereco) VALUES
('Ana Silva', '2000-01-15', '11122233344', 'ana.silva@email.com', '11987654321', 'Rua das Flores, 123, Centro, São Paulo'),
('Bruno Costa', '1999-03-22', '22233344455', 'bruno.costa@email.com', '21998765432', 'Av. Atlântica, 456, Copacabana, Rio de Janeiro'),
('Carla Dias', '2001-07-01', '33344455566', 'carla.dias@email.com', '31976543210', 'Rua da Paz, 789, Savassi, Belo Horizonte'),
('Daniel Souza', '1998-11-10', '44455566677', 'daniel.souza@email.com', '41965432109', 'Rua XV de Novembro, 101, Centro, Curitiba'),
('Eduarda Lima', '2002-05-03', '55566677788', 'eduarda.lima@email.com', '51954321098', 'Av. Borges de Medeiros, 202, Praia de Belas, Porto Alegre'),
('Felipe Santos', '1997-09-18', '66677788899', 'felipe.santos@email.com', '61943210987', 'SQS 103 Bloco A, Asa Sul, Brasília'),
('Gabriela Pereira', '2000-02-28', '77788899900', 'gabriela.p@email.com', '71932109876', 'Rua Bahia, 303, Graça, Salvador'),
('Hugo Oliveira', '1996-04-05', '88899900011', 'hugo.o@email.com', '81921098765', 'Av. Boa Viagem, 505, Boa Viagem, Recife'),
('Isabela Rocha', '2003-08-12', '99900011122', 'isabela.r@email.com', '85910987654', 'Av. Beira Mar, 606, Meireles, Fortaleza'),
('João Almeida', '1995-12-25', '00011122233', 'joao.a@email.com', '92909876543', 'Rua Amazonas, 707, Adrianópolis, Manaus'),
('Kelly Cristina', '2001-06-07', '12345678901', 'kelly.c@email.com', '11987654322', 'Rua da Consolação, 321, Consolação, São Paulo'),
('Lucas Fernandes', '1999-02-14', '23456789012', 'lucas.f@email.com', '21998765433', 'Rua Voluntários da Pátria, 876, Botafogo, Rio de Janeiro'),
('Mariana Gomes', '2000-10-30', '34567890123', 'mariana.g@email.com', '31976543211', 'Av. Afonso Pena, 234, Centro, Belo Horizonte'),
('Nuno Rodrigues', '1998-04-19', '45678901234', 'nuno.r@email.com', '41965432110', 'Rua Padre Anchieta, 543, Bigorrilho, Curitiba'),
('Olívia Martins', '2002-01-20', '56789012345', 'olivia.m@email.com', '51954321099', 'Rua Mostardeiro, 987, Moinhos de Vento, Porto Alegre'),
('Pedro Henrique', '1997-07-07', '67890123456', 'pedro.h@email.com', '61943210988', 'CLN 205 Bloco C, Asa Norte, Brasília'),
('Quiteria Barbosa', '2000-09-09', '78901234567', 'quiteria.b@email.com', '71932109877', 'Av. Oceânica, 123, Ondina, Salvador'),
('Ricardo Neves', '1996-01-01', '89012345678', 'ricardo.n@email.com', '81921098766', 'Rua do Futuro, 456, Jaqueira, Recife'),
('Sofia Costa', '2003-03-03', '90123456789', 'sofia.c@email.com', '85910987655', 'Av. Abolição, 789, Mucuripe, Fortaleza'),
('Thiago Mendes', '1995-05-05', '01234567890', 'thiago.m@email.com', '92909876544', 'Av. Djalma Batista, 101, Chapada, Manaus');

-- Inserindo 20 registros na tabela vs_professores
INSERT INTO vs_professores (nome, data_nasc, cpf, email, telefone, especialidade, data_contratacao, salario, endereco) VALUES
('Maria Antunes', '1980-02-10', '10120230340', 'maria.a@email.com', '11911112222', 'Inglês', '2010-08-01', 4500.00, 'Rua da Harmonia, 10, Vila Madalena, São Paulo'),
('Carlos Eduardo', '1975-06-20', '20230340450', 'carlos.e@email.com', '21922223333', 'Espanhol', '2012-03-15', 4800.00, 'Av. Rio Branco, 50, Centro, Rio de Janeiro'),
('Juliana Paes', '1988-09-05', '30340450560', 'juliana.p@email.com', '31933334444', 'Francês', '2015-01-10', 4200.00, 'Rua da Bahia, 1000, Lourdes, Belo Horizonte'),
('Roberto Silva', '1970-11-30', '40450560670', 'roberto.s@email.com', '41944445555', 'Inglês', '2008-05-20', 5000.00, 'Rua das Araucárias, 200, Batel, Curitiba'),
('Fernanda Lima', '1992-01-25', '50560670780', 'fernanda.l@email.com', '51955556666', 'Alemão', '2018-07-01', 4000.00, 'Rua dos Andradas, 300, Centro, Porto Alegre'),
('Gustavo Mendes', '1985-03-17', '60670780890', 'gustavo.m@email.com', '61966667777', 'Inglês', '2013-09-01', 4700.00, 'SHIS QL 10, Lago Sul, Brasília'),
('Patrícia Souza', '1978-07-08', '70780890900', 'patricia.s@email.com', '71977778888', 'Espanhol', '2011-02-01', 4900.00, 'Rua Chile, 50, Barra, Salvador'),
('Alexandre Costa', '1983-10-14', '80890900010', 'alexandre.c@email.com', '81988889999', 'Japonês', '2016-04-01', 5500.00, 'Av. Conselheiro Aguiar, 100, Boa Viagem, Recife'),
('Silvia Santos', '1990-04-29', '90900010120', 'silvia.s@email.com', '85999990000', 'Inglês', '2017-11-01', 4300.00, 'Av. Dom Luís, 200, Aldeota, Fortaleza'),
('Marcelo Pereira', '1972-08-03', '01010120230', 'marcelo.p@email.com', '92900001111', 'Italiano', '2009-06-01', 5200.00, 'Rua Teresina, 50, Vieiralves, Manaus'),
('Cristina Oliveira', '1981-05-19', '11223344556', 'cristina.o@email.com', '11912345678', 'Inglês', '2014-03-20', 4600.00, 'Av. Paulista, 1500, Cerqueira César, São Paulo'),
('Diego Fernandes', '1977-11-23', '22334455667', 'diego.f@email.com', '21923456789', 'Espanhol', '2011-09-10', 4750.00, 'Rua Farme de Amoedo, 80, Ipanema, Rio de Janeiro'),
('Eliana Rocha', '1989-01-08', '33445566778', 'eliana.r@email.com', '31934567890', 'Francês', '2016-01-05', 4100.00, 'Av. Getúlio Vargas, 1200, Funcionários, Belo Horizonte'),
('Fábio Gomes', '1973-06-01', '44556677889', 'fabio.g@email.com', '41945678901', 'Inglês', '2007-10-15', 5100.00, 'Rua Comendador Araújo, 400, Centro, Curitiba'),
('Helena Martins', '1991-08-15', '55667788990', 'helena.m@email.com', '51956789012', 'Alemão', '2019-02-28', 3900.00, 'Rua Padre Chagas, 600, Moinhos de Vento, Porto Alegre'),
('Igor Santos', '1986-12-02', '66778899001', 'igor.s@email.com', '61967890123', 'Inglês', '2014-07-07', 4800.00, 'EQS 308/309, Asa Sul, Brasília'),
('Laura Pereira', '1979-03-27', '77889900112', 'laura.p@email.com', '71978901234', 'Espanhol', '2012-04-04', 5000.00, 'Rua da Graça, 70, Graça, Salvador'),
('Mauro Oliveira', '1984-09-11', '88990011223', 'mauro.o@email.com', '81989012345', 'Russo', '2017-06-06', 5600.00, 'Rua do Sol, 800, Rosarinho, Recife'),
('Nathalia Pires', '1993-02-06', '99001122334', 'nathalia.p@email.com', '85990123456', 'Inglês', '2018-10-10', 4400.00, 'Av. Washington Soares, 900, Edson Queiroz, Fortaleza'),
('Otávio Rocha', '1971-04-04', '00112233445', 'otavio.r@email.com', '92901234567', 'Italiano', '2010-01-01', 5300.00, 'Av. Darcy Vargas, 100, Chapada, Manaus');

-- Inserindo 20 registros na tabela vs_cursos
INSERT INTO vs_cursos (nome, descricao, duracao_meses, valor_mensalidade) VALUES
('Inglês Básico I', 'Fundamentos do inglês para iniciantes.', 6, 350.00),
('Inglês Básico II', 'Continuação do básico, com foco em conversação.', 6, 350.00),
('Inglês Intermediário I', 'Estruturas mais complexas e vocabulário expandido.', 6, 400.00),
('Inglês Intermediário II', 'Aprofundamento em gramática e fluência.', 6, 400.00),
('Inglês Avançado I', 'Preparação para certificações e uso profissional.', 6, 450.00),
('Inglês Avançado II', 'Fluência e domínio da língua em diversos contextos.', 6, 450.00),
('Espanhol Básico I', 'Primeiros passos no espanhol.', 6, 320.00),
('Espanhol Básico II', 'Construção de frases e diálogos simples.', 6, 320.00),
('Espanhol Intermediário I', 'Gramática e vocabulário para comunicação diária.', 6, 370.00),
('Espanhol Intermediário II', 'Aprofundamento e prática de conversação.', 6, 370.00),
('Francês Básico I', 'Introdução ao francês e cultura.', 6, 380.00),
('Francês Básico II', 'Diálogos e expressões comuns.', 6, 380.00),
('Alemão Básico I', 'Fundamentos do alemão.', 6, 400.00),
('Alemão Básico II', 'Estruturas básicas e vocabulário.', 6, 400.00),
('Italiano Básico I', 'Primeiros contatos com o italiano.', 6, 360.00),
('Italiano Básico II', 'Conversação e cultura italiana.', 6, 360.00),
('Japonês Básico I', 'Hiragana, Katakana e frases essenciais.', 12, 500.00),
('Japonês Básico II', 'Kanji básico e conversação.', 12, 500.00),
('Russo Básico I', 'Introdução ao alfabeto cirílico e frases essenciais.', 12, 550.00),
('Russo Básico II', 'Conversação simples e gramática básica.', 12, 550.00);

-- Inserindo 10 registros na tabela vs_formas_pagamento
INSERT INTO vs_formas_pagamento (nome, descricao) VALUES
('Cartão de Crédito', 'Pagamento via cartão de crédito (parcelado ou à vista).'),
('Boleto Bancário', 'Pagamento via boleto gerado no sistema.'),
('Pix', 'Transferência instantânea via Pix.'),
('Débito em Conta', 'Débito direto na conta corrente.'),
('Transferência Bancária', 'Transferência via TED/DOC.'),
('Dinheiro', 'Pagamento em espécie.'),
('Cartão de Débito', 'Pagamento via cartão de débito.'),
('Cheque', 'Pagamento via cheque (sujeito a compensação).'),
('Crédito Recorrente', 'Débito automático mensal no cartão de crédito.'),
('Débito Recorrente', 'Débito automático mensal na conta corrente.');


-- Inserindo 30 registros na tabela vs_turmas
INSERT INTO vs_turmas (nome, dias_semana, horario_inicio, horario_fim, data_inicio, data_fim, curso_id, professor_id) VALUES
('ING_BAS_I_T1', 'Seg, Qua, Sex', '18:00:00', '19:30:00', '2024-03-01', '2024-08-30', 1, 1),   -- Inglês Básico I, 1ª Turma, Seg/Qua/Sex, 18:00-19:30, Curso ID 1, Professor ID 1
('ING_BAS_I_T2', 'Ter, Qui', '09:00:00', '10:30:00', '2024-03-01', '2024-08-30', 1, 4),   -- Inglês Básico I, 2ª Turma, Ter/Qui, 09:00-10:30, Curso ID 1, Professor ID 4
('ESP_BAS_I_T1', 'Seg, Qua', '19:00:00', '20:30:00', '2024-03-01', '2024-08-30', 7, 2),   -- Espanhol Básico I, 1ª Turma, Seg/Qua, 19:00-20:30, Curso ID 7, Professor ID 2
('FRA_BAS_I_T1', 'Ter, Qui', '18:30:00', '20:00:00', '2024-03-01', '2024-08-30', 11, 3),  -- Francês Básico I, 1ª Turma, Ter/Qui, 18:30-20:00, Curso ID 11, Professor ID 3
('ING_INT_I_T1', 'Seg, Qua, Sex', '20:00:00', '21:30:00', '2024-03-01', '2024-08-30', 3, 6),   -- Inglês Intermediário I, 1ª Turma, Seg/Qua/Sex, 20:00-21:30, Curso ID 3, Professor ID 6
('ALE_BAS_I_T1', 'Sab', '09:00:00', '12:00:00', '2024-03-01', '2024-08-30', 13, 5),  -- Alemão Básico I, 1ª Turma, Sábado, 09:00-12:00, Curso ID 13, Professor ID 5
('ING_BAS_II_T1', 'Ter, Qui', '19:00:00', '20:30:00', '2024-09-01', '2025-02-28', 2, 9),  -- Inglês Básico II, 1ª Turma, Ter/Qui, 19:00-20:30, Curso ID 2, Professor ID 9
('ESP_INT_I_T1', 'Qua, Sex', '10:00:00', '11:30:00', '2024-09-01', '2025-02-28', 9, 7),  -- Espanhol Intermediário I, 1ª Turma, Qua/Sex, 10:00-11:30, Curso ID 9, Professor ID 7
('JAP_BAS_I_T1', 'Seg, Qua', '18:00:00', '19:30:00', '2024-03-01', '2025-02-28', 17, 8), -- Japonês Básico I, 1ª Turma, Seg/Qua, 18:00-19:30, Curso ID 17, Professor ID 8
('ITA_BAS_I_T1', 'Ter, Qui', '19:00:00', '20:30:00', '2024-03-01', '2024-08-30', 15, 10), -- Italiano Básico I, 1ª Turma, Ter/Qui, 19:00-20:30, Curso ID 15, Professor ID 10
('ING_AVA_I_T1', 'Seg, Qua, Sex', '10:00:00', '11:30:00', '2024-03-01', '2024-08-30', 5, 11),  -- Inglês Avançado I, 1ª Turma, Seg/Qua/Sex, 10:00-11:30, Curso ID 5, Professor ID 11
('ESP_BAS_II_T1', 'Ter, Qui', '14:00:00', '15:30:00', '2024-09-01', '2025-02-28', 8, 12),  -- Espanhol Básico II, 1ª Turma, Ter/Qui, 14:00-15:30, Curso ID 8, Professor ID 12
('FRA_INT_I_T1', 'Seg, Qua', '17:00:00', '18:30:00', '2024-03-01', '2024-08-30', 12, 13), -- Francês Intermediário I, 1ª Turma, Seg/Qua, 17:00-18:30, Curso ID 12, Professor ID 13
('ING_BAS_I_T3', 'Sab', '14:00:00', '17:00:00', '2024-03-01', '2024-08-30', 1, 14),   -- Inglês Básico I, 3ª Turma, Sábado, 14:00-17:00, Curso ID 1, Professor ID 14
('ALE_INT_I_T1', 'Ter, Qui', '19:00:00', '20:30:00', '2024-09-01', '2025-02-28', 14, 15), -- Alemão Intermediário I, 1ª Turma, Ter/Qui, 19:00-20:30, Curso ID 14, Professor ID 15
('ING_INT_II_T1', 'Seg, Qua, Sex', '18:00:00', '19:30:00', '2024-09-01', '2025-02-28', 4, 16), -- Inglês Intermediário II, 1ª Turma, Seg/Qua/Sex, 18:00-19:30, Curso ID 4, Professor ID 16
('ESP_AVA_I_T1', 'Ter, Qui', '10:00:00', '11:30:00', '2024-03-01', '2024-08-30', 10, 17), -- Espanhol Avançado I, 1ª Turma, Ter/Qui, 10:00-11:30, Curso ID 10, Professor ID 17
('RUS_BAS_I_T1', 'Qua, Sex', '18:00:00', '19:30:00', '2024-03-01', '2025-02-28', 19, 18), -- Russo Básico I, 1ª Turma, Qua/Sex, 18:00-19:30, Curso ID 19, Professor ID 18
('ING_AVA_II_T1', 'Seg, Qua', '19:00:00', '20:30:00', '2024-09-01', '2025-02-28', 6, 19), -- Inglês Avançado II, 1ª Turma, Seg/Qua, 19:00-20:30, Curso ID 6, Professor ID 19
('ITA_INT_I_T1', 'Ter, Qui', '17:00:00', '18:30:00', '2024-09-01', '2025-02-28', 16, 20), -- Italiano Intermediário I, 1ª Turma, Ter/Qui, 17:00-18:30, Curso ID 16, Professor ID 20
('ING_BAS_I_T4', 'Seg, Qua, Sex', '08:00:00', '09:30:00', '2024-03-01', '2024-08-30', 1, 1), -- Inglês Básico I, 4ª Turma, Seg/Qua/Sex, 08:00-09:30, Curso ID 1, Professor ID 1
('ING_BAS_I_T5', 'Ter, Qui', '16:00:00', '17:30:00', '2024-03-01', '2024-08-30', 1, 4), -- Inglês Básico I, 5ª Turma, Ter/Qui, 16:00-17:30, Curso ID 1, Professor ID 4
('ESP_BAS_I_T2', 'Seg, Qua', '10:00:00', '11:30:00', '2024-03-01', '2024-08-30', 7, 2), -- Espanhol Básico I, 2ª Turma, Seg/Qua, 10:00-11:30, Curso ID 7, Professor ID 2
('FRA_BAS_I_T2', 'Ter, Qui', '10:00:00', '11:30:00', '2024-03-01', '2024-08-30', 11, 3), -- Francês Básico I, 2ª Turma, Ter/Qui, 10:00-11:30, Curso ID 11, Professor ID 3
('ING_INT_I_T2', 'Seg, Qua, Sex', '14:00:00', '15:30:00', '2024-03-01', '2024-08-30', 3, 6), -- Inglês Intermediário I, 2ª Turma, Seg/Qua/Sex, 14:00-15:30, Curso ID 3, Professor ID 6
('ALE_BAS_I_T2', 'Sab', '13:00:00', '16:00:00', '2024-03-01', '2024-08-30', 13, 5), -- Alemão Básico I, 2ª Turma, Sábado, 13:00-16:00, Curso ID 13, Professor ID 5
('ING_BAS_II_T2', 'Ter, Qui', '10:00:00', '11:30:00', '2024-09-01', '2025-02-28', 2, 9), -- Inglês Básico II, 2ª Turma, Ter/Qui, 10:00-11:30, Curso ID 2, Professor ID 9
('ESP_INT_I_T2', 'Qua, Sex', '14:00:00', '15:30:00', '2024-09-01', '2025-02-28', 9, 7), -- Espanhol Intermediário I, 2ª Turma, Qua/Sex, 14:00-15:30, Curso ID 9, Professor ID 7
('JAP_BAS_I_T2', 'Seg, Qua', '10:00:00', '11:30:00', '2024-03-01', '2025-02-28', 17, 8), -- Japonês Básico I, 2ª Turma, Seg/Qua, 10:00-11:30, Curso ID 17, Professor ID 8
('TURMA_SEM_MATRICULA', 'Seg, Qua', '15:00:00', '16:30:00', '2024-03-01', '2024-08-30', 1, 1); -- Turma que será excluída, sem matrículas associadas (ID 30)

-- Inserindo 40 registros na tabela vs_matriculas (dobro de 20)
INSERT INTO vs_matriculas (data_matricula, status_mat, aluno_id, turma_id) VALUES
('2024-02-20', 'Ativa', 1, 1),   -- Aluno 1 (Ana Silva) na Turma 1 (ING_BAS_I_T1)
('2024-02-21', 'Ativa', 2, 3),   -- Aluno 2 (Bruno Costa) na Turma 3 (ESP_BAS_I_T1)
('2024-02-22', 'Ativa', 3, 4),   -- Aluno 3 (Carla Dias) na Turma 4 (FRA_BAS_I_T1)
('2024-02-23', 'Ativa', 4, 5),   -- Aluno 4 (Daniel Souza) na Turma 5 (ING_INT_I_T1)
('2024-02-24', 'Ativa', 5, 6),   -- Aluno 5 (Eduarda Lima) na Turma 6 (ALE_BAS_I_T1)
('2024-02-25', 'Ativa', 6, 1),   -- Aluno 6 (Felipe Santos) na Turma 1 (ING_BAS_I_T1)
('2024-02-26', 'Ativa', 7, 3),   -- Aluno 7 (Gabriela Pereira) na Turma 3 (ESP_BAS_I_T1)
('2024-02-27', 'Ativa', 8, 9),   -- Aluno 8 (Hugo Oliveira) na Turma 9 (JAP_BAS_I_T1)
('2024-02-28', 'Ativa', 9, 11),  -- Aluno 9 (Isabela Rocha) na Turma 11 (ING_AVA_I_T1)
('2024-02-29', 'Ativa', 10, 10), -- Aluno 10 (João Almeida) na Turma 10 (ITA_BAS_I_T1)
('2024-08-15', 'Ativa', 11, 7),  -- Aluno 11 (Kelly Cristina) na Turma 7 (ING_BAS_II_T1)
('2024-08-16', 'Ativa', 12, 8),  -- Aluno 12 (Lucas Fernandes) na Turma 8 (ESP_INT_I_T1)
('2024-08-17', 'Ativa', 13, 12), -- Aluno 13 (Mariana Gomes) na Turma 12 (ESP_BAS_II_T1)
('2024-08-18', 'Ativa', 14, 15), -- Aluno 14 (Nuno Rodrigues) na Turma 15 (ALE_INT_I_T1)
('2024-08-19', 'Ativa', 15, 16), -- Aluno 15 (Olívia Martins) na Turma 16 (ING_INT_II_T1)
('2024-08-20', 'Ativa', 16, 7),  -- Aluno 16 (Pedro Henrique) na Turma 7 (ING_BAS_II_T1)
('2024-08-21', 'Ativa', 17, 8),  -- Aluno 17 (Quiteria Barbosa) na Turma 8 (ESP_INT_I_T1)
('2024-08-22', 'Ativa', 18, 18), -- Aluno 18 (Ricardo Neves) na Turma 18 (RUS_BAS_I_T1)
('2024-08-23', 'Ativa', 19, 19), -- Aluno 19 (Sofia Costa) na Turma 19 (ING_AVA_II_T1)
('2024-08-24', 'Ativa', 20, 20), -- Aluno 20 (Thiago Mendes) na Turma 20 (ITA_INT_I_T1)
('2024-02-20', 'Ativa', 1, 21),  -- Aluno 1 (Ana Silva) na Turma 21 (ING_BAS_I_T4)
('2024-02-21', 'Ativa', 2, 23),  -- Aluno 2 (Bruno Costa) na Turma 23 (ESP_BAS_I_T2)
('2024-02-22', 'Ativa', 3, 24),  -- Aluno 3 (Carla Dias) na Turma 24 (FRA_BAS_I_T2)
('2024-02-23', 'Ativa', 4, 25),  -- Aluno 4 (Daniel Souza) na Turma 25 (ING_INT_I_T2)
('2024-02-24', 'Ativa', 5, 26),  -- Aluno 5 (Eduarda Lima) na Turma 26 (ALE_BAS_I_T2)
('2024-02-25', 'Ativa', 6, 22),  -- Aluno 6 (Felipe Santos) na Turma 22 (ING_BAS_I_T5)
('2024-02-26', 'Ativa', 7, 27),  -- Aluno 7 (Gabriela Pereira) na Turma 27 (ING_BAS_II_T2)
('2024-02-27', 'Ativa', 8, 28),  -- Aluno 8 (Hugo Oliveira) na Turma 28 (ESP_INT_I_T2)
('2024-02-28', 'Ativa', 9, 29),  -- Aluno 9 (Isabela Rocha) na Turma 29 (JAP_BAS_I_T2)
('2024-02-29', 'Ativa', 10, 1), -- Aluno 10 (João Almeida) na Turma 1 (ING_BAS_I_T1)
('2024-08-15', 'Ativa', 11, 2), -- Aluno 11 (Kelly Cristina) na Turma 2 (ING_BAS_I_T2)
('2024-08-16', 'Ativa', 12, 4), -- Aluno 12 (Lucas Fernandes) na Turma 4 (FRA_BAS_I_T1)
('2024-08-17', 'Ativa', 13, 5), -- Aluno 13 (Mariana Gomes) na Turma 5 (ING_INT_I_T1)
('2024-08-18', 'Ativa', 14, 6), -- Aluno 14 (Nuno Rodrigues) na Turma 6 (ALE_BAS_I_T1)
('2024-08-19', 'Ativa', 15, 11), -- Aluno 15 (Olívia Martins) na Turma 11 (ING_AVA_I_T1)
('2024-08-20', 'Ativa', 16, 13), -- Aluno 16 (Pedro Henrique) na Turma 13 (FRA_INT_I_T1)
('2024-08-21', 'Ativa', 17, 14), -- Aluno 17 (Quiteria Barbosa) na Turma 14 (ING_BAS_I_T3)
('2024-08-22', 'Ativa', 18, 15), -- Aluno 18 (Ricardo Neves) na Turma 15 (ALE_INT_I_T1)
('2024-08-23', 'Ativa', 19, 16), -- Aluno 19 (Sofia Costa) na Turma 16 (ING_INT_II_T1)
('2024-08-24', 'Ativa', 20, 17); -- Aluno 20 (Thiago Mendes) na Turma 17 (ESP_AVA_I_T1)


-- Inserindo 40 registros na tabela vs_pagamentos (dobro de 20)
INSERT INTO vs_pagamentos (data_pag, valor, mes_referencia, status_pag, aluno_id, matricula_id, forma_pagamento_id) VALUES
('2024-03-05', 350.00, '2024-03', 'Pago', 1, 1, 1),   -- Pagamento de Março/2024 para Ana Silva (Matrícula 1) via Cartão de Crédito
('2024-03-06', 320.00, '2024-03', 'Pago', 2, 2, 3),   -- Pagamento de Março/2024 para Bruno Costa (Matrícula 2) via Pix
('2024-03-07', 380.00, '2024-03', 'Pago', 3, 3, 2),   -- Pagamento de Março/2024 para Carla Dias (Matrícula 3) via Boleto Bancário
('2024-03-08', 400.00, '2024-03', 'Pago', 4, 4, 1),   -- Pagamento de Março/2024 para Daniel Souza (Matrícula 4) via Cartão de Crédito
('2024-03-09', 400.00, '2024-03', 'Pago', 5, 5, 4),   -- Pagamento de Março/2024 para Eduarda Lima (Matrícula 5) via Débito em Conta
('2024-04-05', 350.00, '2024-04', 'Pago', 1, 1, 1),   -- Pagamento de Abril/2024 para Ana Silva (Matrícula 1) via Cartão de Crédito
('2024-04-06', 320.00, '2024-04', 'Pago', 2, 2, 3),   -- Pagamento de Abril/2024 para Bruno Costa (Matrícula 2) via Pix
('2024-04-07', 380.00, '2024-04', 'Pago', 3, 3, 2),   -- Pagamento de Abril/2024 para Carla Dias (Matrícula 3) via Boleto Bancário
('2024-04-08', 400.00, '2024-04', 'Pago', 4, 4, 1),   -- Pagamento de Abril/2024 para Daniel Souza (Matrícula 4) via Cartão de Crédito
('2024-04-09', 400.00, '2024-04', 'Pago', 5, 5, 4),   -- Pagamento de Abril/2024 para Eduarda Lima (Matrícula 5) via Débito em Conta
('2024-09-01', 350.00, '2024-09', 'Pago', 11, 11, 3), -- Pagamento de Setembro/2024 para Kelly Cristina (Matrícula 11) via Pix
('2024-09-02', 370.00, '2024-09', 'Pago', 12, 12, 1), -- Pagamento de Setembro/2024 para Lucas Fernandes (Matrícula 12) via Cartão de Crédito
('2024-09-03', 320.00, '2024-09', 'Pago', 13, 13, 2), -- Pagamento de Setembro/2024 para Mariana Gomes (Matrícula 13) via Boleto Bancário
('2024-09-04', 400.00, '2024-09', 'Pago', 14, 14, 4), -- Pagamento de Setembro/2024 para Nuno Rodrigues (Matrícula 14) via Débito em Conta
('2024-09-05', 400.00, '2024-09', 'Pago', 15, 15, 1), -- Pagamento de Setembro/2024 para Olívia Martins (Matrícula 15) via Cartão de Crédito
('2024-10-01', 350.00, '2024-10', 'Pago', 11, 11, 3), -- Pagamento de Outubro/2024 para Kelly Cristina (Matrícula 11) via Pix
('2024-10-02', 370.00, '2024-10', 'Pago', 12, 12, 1), -- Pagamento de Outubro/2024 para Lucas Fernandes (Matrícula 12) via Cartão de Crédito
('2024-10-03', 320.00, '2024-10', 'Pago', 13, 13, 2), -- Pagamento de Outubro/2024 para Mariana Gomes (Matrícula 13) via Boleto Bancário
('2024-10-04', 400.00, '2024-10', 'Pago', 14, 14, 4), -- Pagamento de Outubro/2024 para Nuno Rodrigues (Matrícula 14) via Débito em Conta
('2024-10-05', 400.00, '2024-10', 'Pendente', 15, 15, 1), -- Pagamento de Outubro/2024 para Olívia Martins (Matrícula 15) via Cartão de Crédito (Este pagamento será atualizado)
('2024-03-05', 350.00, '2024-03', 'Pago', 6, 6, 1),   -- Pagamento de Março/2024 para Felipe Santos (Matrícula 6) via Cartão de Crédito
('2024-03-06', 320.00, '2024-03', 'Pago', 7, 7, 3),   -- Pagamento de Março/2024 para Gabriela Pereira (Matrícula 7) via Pix
('2024-03-07', 500.00, '2024-03', 'Pago', 8, 8, 2),   -- Pagamento de Março/2024 para Hugo Oliveira (Matrícula 8) via Boleto Bancário
('2024-03-08', 450.00, '2024-03', 'Pago', 9, 9, 1),   -- Pagamento de Março/2024 para Isabela Rocha (Matrícula 9) via Cartão de Crédito
('2024-03-09', 360.00, '2024-03', 'Pago', 10, 10, 4), -- Pagamento de Março/2024 para João Almeida (Matrícula 10) via Débito em Conta
('2024-04-05', 350.00, '2024-04', 'Pago', 6, 6, 1),   -- Pagamento de Abril/2024 para Felipe Santos (Matrícula 6) via Cartão de Crédito
('2024-04-06', 320.00, '2024-04', 'Pago', 7, 7, 3),   -- Pagamento de Abril/2024 para Gabriela Pereira (Matrícula 7) via Pix
('2024-04-07', 500.00, '2024-04', 'Pago', 8, 8, 2),   -- Pagamento de Abril/2024 para Hugo Oliveira (Matrícula 8) via Boleto Bancário
('2024-04-08', 450.00, '2024-04', 'Pago', 9, 9, 1),   -- Pagamento de Abril/2024 para Isabela Rocha (Matrícula 9) via Cartão de Crédito
('2024-04-09', 360.00, '2024-04', 'Pago', 10, 10, 4), -- Pagamento de Abril/2024 para João Almeida (Matrícula 10) via Débito em Conta
('2024-09-01', 350.00, '2024-09', 'Pago', 16, 16, 3), -- Pagamento de Setembro/2024 para Pedro Henrique (Matrícula 16) via Pix
('2024-09-02', 370.00, '2024-09', 'Pago', 17, 17, 1), -- Pagamento de Setembro/2024 para Quiteria Barbosa (Matrícula 17) via Cartão de Crédito
('2024-09-03', 550.00, '2024-09', 'Pago', 18, 18, 2), -- Pagamento de Setembro/2024 para Ricardo Neves (Matrícula 18) via Boleto Bancário
('2024-09-04', 450.00, '2024-09', 'Pago', 19, 19, 4), -- Pagamento de Setembro/2024 para Sofia Costa (Matrícula 19) via Débito em Conta
('2024-09-05', 360.00, '2024-09', 'Pago', 20, 20, 1), -- Pagamento de Setembro/2024 para Thiago Mendes (Matrícula 20) via Cartão de Crédito
('2024-10-01', 350.00, '2024-10', 'Pago', 16, 16, 3), -- Pagamento de Outubro/2024 para Pedro Henrique (Matrícula 16) via Pix
('2024-10-02', 370.00, '2024-10', 'Pago', 17, 17, 1), -- Pagamento de Outubro/2024 para Quiteria Barbosa (Matrícula 17) via Cartão de Crédito
('2024-10-03', 550.00, '2024-10', 'Pago', 18, 18, 2), -- Pagamento de Outubro/2024 para Ricardo Neves (Matrícula 18) via Boleto Bancário
('2024-10-04', 450.00, '2024-10', 'Pendente', 19, 19, 4), -- Pagamento de Outubro/2024 para Sofia Costa (Matrícula 19) via Débito em Conta
('2024-10-05', 360.00, '2024-10', 'Pago', 20, 20, 1); -- Pagamento de Outubro/2024 para Thiago Mendes (Matrícula 20) via Cartão de Crédito


-- Inserindo 40 registros na tabela vs_avaliacoes (dobro de 20)
INSERT INTO vs_avaliacoes (data_ava, tipo, nota, aluno_id, turma_id, professor_id) VALUES
('2024-08-20', 'Prova Final', 8.5, 1, 1, 1),   -- Prova Final para Ana Silva (Aluno 1) na Turma 1 (ING_BAS_I_T1) pelo Professor Maria Antunes (Professor 1)
('2024-08-21', 'Trabalho', 9.0, 2, 3, 2),    -- Trabalho para Bruno Costa (Aluno 2) na Turma 3 (ESP_BAS_I_T1) pelo Professor Carlos Eduardo (Professor 2)
('2024-08-22', 'Participação', 7.5, 3, 4, 3), -- Participação para Carla Dias (Aluno 3) na Turma 4 (FRA_BAS_I_T1) pelo Professor Juliana Paes (Professor 3)
('2024-08-23', 'Prova Final', 7.0, 4, 5, 6),   -- Prova Final para Daniel Souza (Aluno 4) na Turma 5 (ING_INT_I_T1) pelo Professor Gustavo Mendes (Professor 6)
('2024-08-24', 'Quiz', 9.5, 5, 6, 5),        -- Quiz para Eduarda Lima (Aluno 5) na Turma 6 (ALE_BAS_I_T1) pelo Professor Fernanda Lima (Professor 5)
('2024-08-25', 'Prova Final', 8.0, 6, 1, 1),   -- Prova Final para Felipe Santos (Aluno 6) na Turma 1 (ING_BAS_I_T1) pelo Professor Maria Antunes (Professor 1)
('2024-08-26', 'Trabalho', 8.8, 7, 3, 2),    -- Trabalho para Gabriela Pereira (Aluno 7) na Turma 3 (ESP_BAS_I_T1) pelo Professor Carlos Eduardo (Professor 2)
('2024-08-27', 'Prova Final', 9.2, 8, 9, 8),   -- Prova Final para Hugo Oliveira (Aluno 8) na Turma 9 (JAP_BAS_I_T1) pelo Professor Alexandre Costa (Professor 8)
('2024-08-28', 'Participação', 7.0, 9, 11, 11), -- Participação para Isabela Rocha (Aluno 9) na Turma 11 (ING_AVA_I_T1) pelo Professor Cristina Oliveira (Professor 11)
('2024-08-29', 'Quiz', 8.0, 10, 10, 10),       -- Quiz para João Almeida (Aluno 10) na Turma 10 (ITA_BAS_I_T1) pelo Professor Marcelo Pereira (Professor 10)
('2025-02-10', 'Prova Final', 7.8, 11, 7, 9),  -- Prova Final para Kelly Cristina (Aluno 11) na Turma 7 (ING_BAS_II_T1) pelo Professor Silvia Santos (Professor 9)
('2025-02-11', 'Trabalho', 8.2, 12, 8, 7),   -- Trabalho para Lucas Fernandes (Aluno 12) na Turma 8 (ESP_INT_I_T1) pelo Professor Patrícia Souza (Professor 7)
('2025-02-12', 'Participação', 9.0, 13, 12, 12), -- Participação para Mariana Gomes (Aluno 13) na Turma 12 (ESP_BAS_II_T1) pelo Professor Diego Fernandes (Professor 12)
('2025-02-13', 'Prova Final', 6.5, 14, 15, 15),  -- Prova Final para Nuno Rodrigues (Aluno 14) na Turma 15 (ALE_INT_I_T1) pelo Professor Helena Martins (Professor 15)
('2025-02-14', 'Quiz', 8.7, 15, 16, 16),       -- Quiz para Olívia Martins (Aluno 15) na Turma 16 (ING_INT_II_T1) pelo Professor Igor Santos (Professor 16)
('2025-02-15', 'Prova Final', 7.2, 16, 7, 9),  -- Prova Final para Pedro Henrique (Aluno 16) na Turma 7 (ING_BAS_II_T1) pelo Professor Silvia Santos (Professor 9)
('2025-02-16', 'Trabalho', 8.5, 17, 8, 7),   -- Trabalho para Quiteria Barbosa (Aluno 17) na Turma 8 (ESP_INT_I_T1) pelo Professor Patrícia Souza (Professor 7)
('2025-02-17', 'Prova Final', 9.5, 18, 18, 18),  -- Prova Final para Ricardo Neves (Aluno 18) na Turma 18 (RUS_BAS_I_T1) pelo Professor Mauro Oliveira (Professor 18)
('2025-02-18', 'Participação', 6.8, 19, 19, 19), -- Participação para Sofia Costa (Aluno 19) na Turma 19 (ING_AVA_II_T1) pelo Professor Nathalia Pires (Professor 19)
('2025-02-19', 'Quiz', 7.9, 20, 20, 20),       -- Quiz para Thiago Mendes (Aluno 20) na Turma 20 (ITA_INT_I_T1) pelo Professor Otávio Rocha (Professor 20)
('2024-08-20', 'Prova Final', 8.0, 1, 21, 1),   -- Prova Final para Ana Silva (Aluno 1) na Turma 21 (ING_BAS_I_T4) pelo Professor Maria Antunes (Professor 1)
('2024-08-21', 'Trabalho', 9.1, 2, 23, 2),    -- Trabalho para Bruno Costa (Aluno 2) na Turma 23 (ESP_BAS_I_T2) pelo Professor Carlos Eduardo (Professor 2)
('2024-08-22', 'Participação', 7.0, 3, 24, 3), -- Participação para Carla Dias (Aluno 3) na Turma 24 (FRA_BAS_I_T2) pelo Professor Juliana Paes (Professor 3)
('2024-08-23', 'Prova Final', 7.5, 4, 25, 6),   -- Prova Final para Daniel Souza (Aluno 4) na Turma 25 (ING_INT_I_T2) pelo Professor Gustavo Mendes (Professor 6)
('2024-08-24', 'Quiz', 9.0, 5, 26, 5),        -- Quiz para Eduarda Lima (Aluno 5) na Turma 26 (ALE_BAS_I_T2) pelo Professor Fernanda Lima (Professor 5)
('2024-08-25', 'Prova Final', 8.2, 6, 22, 4),   -- Prova Final para Felipe Santos (Aluno 6) na Turma 22 (ING_BAS_I_T5) pelo Professor Roberto Silva (Professor 4)
('2024-08-26', 'Trabalho', 8.9, 7, 27, 9),    -- Trabalho para Gabriela Pereira (Aluno 7) na Turma 27 (ING_BAS_II_T2) pelo Professor Silvia Santos (Professor 9)
('2024-08-27', 'Prova Final', 9.0, 8, 28, 7),   -- Prova Final para Hugo Oliveira (Aluno 8) na Turma 28 (ESP_INT_I_T2) pelo Professor Patrícia Souza (Professor 7)
('2024-08-28', 'Participação', 7.2, 9, 29, 8), -- Participação para Isabela Rocha (Aluno 9) na Turma 29 (JAP_BAS_I_T2) pelo Professor Alexandre Costa (Professor 8)
('2024-08-29', 'Quiz', 8.1, 10, 1, 1),       -- Quiz para João Almeida (Aluno 10) na Turma 1 (ING_BAS_I_T1) pelo Professor Maria Antunes (Professor 1)
('2025-02-10', 'Prova Final', 7.5, 11, 2, 4),  -- Prova Final para Kelly Cristina (Aluno 11) na Turma 2 (ING_BAS_I_T2) pelo Professor Roberto Silva (Professor 4)
('2025-02-11', 'Trabalho', 8.0, 12, 4, 3),   -- Trabalho para Lucas Fernandes (Aluno 12) na Turma 4 (FRA_BAS_I_T1) pelo Professor Juliana Paes (Professor 3)
('2025-02-12', 'Participação', 9.1, 13, 5, 6), -- Participação para Mariana Gomes (Aluno 13) na Turma 5 (ING_INT_I_T1) pelo Professor Gustavo Mendes (Professor 6)
('2025-02-13', 'Prova Final', 6.8, 14, 6, 5),  -- Prova Final para Nuno Rodrigues (Aluno 14) na Turma 6 (ALE_BAS_I_T1) pelo Professor Fernanda Lima (Professor 5)
('2025-02-14', 'Quiz', 8.5, 15, 11, 11),       -- Quiz para Olívia Martins (Aluno 15) na Turma 11 (ING_AVA_I_T1) pelo Professor Cristina Oliveira (Professor 11)
('2025-02-15', 'Prova Final', 7.0, 16, 13, 13),  -- Prova Final para Pedro Henrique (Aluno 16) na Turma 13 (FRA_INT_I_T1) pelo Professor Eliana Rocha (Professor 13)
('2025-02-16', 'Trabalho', 8.3, 17, 14, 14),   -- Trabalho para Quiteria Barbosa (Aluno 17) na Turma 14 (ING_BAS_I_T3) pelo Professor Fábio Gomes (Professor 14)
('2025-02-17', 'Prova Final', 9.3, 18, 15, 15),  -- Prova Final para Ricardo Neves (Aluno 18) na Turma 15 (ALE_INT_I_T1) pelo Professor Helena Martins (Professor 15)
('2025-02-18', 'Participação', 6.5, 19, 16, 16), -- Participação para Sofia Costa (Aluno 19) na Turma 16 (ING_INT_II_T1) pelo Professor Igor Santos (Professor 16)
('2025-02-19', 'Quiz', 7.7, 20, 17, 17);       -- Quiz para Thiago Mendes (Aluno 20) na Turma 17 (ESP_AVA_I_T1) pelo Professor Laura Pereira (Professor 17)

-- Habilita a verificação de chaves estrangeiras
SET FOREIGN_KEY_CHECKS = 1;

use vs_escola_idiomas;
-- ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
-- PRIMEIRO SELECT




-- SEGUNDO SELECT




-- ALTER TABLE









