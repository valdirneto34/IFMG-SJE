-- VIEW 1
/*
Evento (Entrada): Solicitação de relatório gerencial financeiro.
Condição (Lógica): Agrupar os dados financeiros por nome_curso. Deve-se diferenciar os valores já recebidos dos valores a receber.
Ação (Saída): Apresentar uma tabela contendo:
Nome do Curso.
Quantidade de Alunos Ativos.
Total Recebido (Soma condicional onde status = 'Pago').
Total a Receber/Inadimplência (Soma condicional onde status = 'Pendente' ou 'Vencido').
*/
CREATE OR REPLACE VIEW vw_saude_financeira AS
SELECT c.nome_curso AS nome_curso, COUNT(DISTINCT m.aluno_id) AS qtd_alunos_ativos,
COALESCE(SUM(CASE WHEN men.status_pag = 'Pago' THEN men.valor_nominal ELSE 0 END), 0.00) AS total_recebido,
COALESCE(SUM(CASE WHEN men.status_pag IN ('Pendente', 'Vencido') THEN men.valor_nominal ELSE 0 END), 0.00) AS total_a_receber
FROM cursos c LEFT JOIN turmas t ON t.curso_id = c.curso_id
LEFT JOIN matriculas m ON m.turma_id = t.turma_id AND m.status_mat = 'Ativa' 
LEFT JOIN mensalidades men ON men.matricula_id = m.matricula_id 
GROUP BY c.nome_curso ORDER BY c.nome_curso;
/*
Decisões de Implementação:
Inclusão Total (LEFT JOIN na Cadeia): A View utiliza LEFT JOIN iniciando na tabela cursos e se estendendo para turmas e matrículas. 
Esta decisão é gerencialmente crítica: garante que **todos os cursos** cadastrados (mesmo aqueles sem alunos ativos ou sem turmas) apareçam no relatório, retornando 0.00 para os totais e 0 para alunos.
Filtro de Alunos Ativos no JOIN: A condição 'm.status_mat = 'Ativa'' é aplicada diretamente no LEFT JOIN com matriculas. 
Isso permite que a View conte apenas os alunos que estão de fato gerando receita atual, mas sem descartar cursos que possam estar inativos (pois o curso é o lado esquerdo do JOIN).
Cálculo Robusto com COALESCE: O uso de COALESCE(SUM(...), 0.00) é essencial em conjunto com o LEFT JOIN. 
Ele converte os resultados NULL (que ocorrem quando um curso não tem parcelas ou alunos ativos) para o valor numérico 0.00, prevenindo erros de cálculo e garantindo relatórios financeiros precisos.
Classificação Financeira (CASE WHEN): Mantém-se o uso de CASE WHEN para categorizar e somar valores de forma separada 
('total_recebido' para status 'Pago' e 'total_a_receber' para status 'Pendente' e 'Vencido'), fornecendo uma visão clara do fluxo de caixa por curso.
*/

/*
TESTE 1: Validação de Agregação por Curso
Verifica se o relatório agrupa corretamente pelo nome do curso e se os totais estão corretos.
Vamos verificar o curso 'Inglês Básico I' (ID 1). 
Total de alunos ativos: 4 (IDs 4, 10, 12, 16)
Total Recebido: 6 parcelas * 300.00 = 1800.00
Total a Receber: 8 parcelas * 300.00 = 2400.00
*/
SELECT nome_curso, qtd_alunos_ativos, total_recebido, total_a_receber 
FROM vw_saude_financeira 
WHERE nome_curso = 'Inglês Básico I';

/*
TESTE 2: Validação de Filtro (Total a Receber para Matrículas Sem Pagamentos)
Verifica se o curso 'Espanhol Básico' (ID 6) está calculando corretamente. 
Total de alunos ativos: 2 (IDs 25, 26).
Todos os 16 pagamentos (8x2) estão 'Pendente' no DML original.
Total Recebido: 0.00
Total a Receber: 16 parcelas * 1800.00/8 = 3600.00
*/
SELECT nome_curso, qtd_alunos_ativos, total_recebido, total_a_receber 
FROM vw_saude_financeira 
WHERE nome_curso = 'Espanhol Básico I';

-- Detalhando as Matrículas e parcelas que a View está somando para Inglês Básico I
SELECT c.nome_curso, m.matricula_id, m.aluno_id, men.status_pag, men.valor_nominal
FROM cursos c
JOIN turmas t ON t.curso_id = c.curso_id
JOIN matriculas m ON m.turma_id = t.turma_id AND m.status_mat = 'Ativa'
LEFT JOIN mensalidades men ON men.matricula_id = m.matricula_id
WHERE c.nome_curso = 'Inglês Básico I';

-- VIEW 2
/*
Evento (Entrada): Consulta operacional para alocação de novas turmas.
Condição (Lógica): Calcular a ocupação atual (COUNT de matrículas ativas por sala) e compará-la com a capacidade máxima da sala.
Ação (Saída): Apresentar:
Nome da Sala e Capacidade.
Ocupação Atual.
Coluna calculada "Status Lotação": Retornar 'LOTADA' se (Ocupação >= Capacidade), caso contrário retornar 'DISPONÍVEL'.
*/
CREATE OR REPLACE VIEW vw_ocupacao_salas AS
SELECT s.sala_id, s.nome_sala, s.capacidade, COUNT(m.matricula_id) AS ocupacao_atual,
CASE WHEN COUNT(m.matricula_id) >= s.capacidade THEN 'LOTADA'
ELSE 'DISPONÍVEL' END AS status_lotacao
FROM salas s LEFT JOIN turmas t ON t.sala_id = s.sala_id
LEFT JOIN matriculas m ON m.turma_id = t.turma_id
AND m.status_mat = 'Ativa'
GROUP BY s.sala_id, s.nome_sala, s.capacidade;
/*
Decisões de Implementação:
Uso de LEFT JOIN (Inclusão Total): A View utiliza LEFT JOIN começando pela tabela salas (s) e, em seguida, turmas (t) e matrículas (m). 
Essa decisão é fundamental para garantir que TODAS as salas sejam listadas no relatório (mesmo que estejam vazias ou sem turmas agendadas), garantindo um mapa de ocupação completo.
Filtro de Matrículas Ativas: A contagem de alunos para a ocupação é restrita a 'm.status_mat = 'Ativa''. 
Isso assegura que a métrica 'ocupacao_atual' reflita apenas alunos que estão de fato ocupando a vaga, alinhando-se com a lógica da Trigger de Lotação.
Classificação de Status (CASE WHEN): Utiliza-se a função CASE WHEN para criar a coluna 'status_lotacao'. 
A regra 'COUNT(m.matricula_id) >= s.capacidade' classifica a sala como 'LOTADA', fornecendo uma indicação visual e rápida para o planejamento de novas turmas.
*/

/*
TESTE 1: Validação de Sala Lotada
Verifica a Sala ID 3 (Lab. A), que tem Capacidade 18.
Após a preparação de DML (que adicionou 17 alunos na Turma 19, que já tinha 1 aluno), a ocupação deve ser 18.
O retorno esperado é ocupacao_atual = 18 e status_lotacao = 'LOTADA'.
*/
SELECT sala_id, nome_sala, capacidade, ocupacao_atual, status_lotacao
FROM vw_ocupacao_salas 
WHERE sala_id = 3;

/*
TESTE 2: Validação de Sala Vazia (LEFT JOIN)
Verifica se uma sala que não possui nenhuma turma (ex: Sala ID 5 - Sala de Reunião, que tem Capacidade 10) 
é listada corretamente com ocupação zero e status 'DISPONÍVEL'.
O retorno esperado é ocupacao_atual = 0 e status_lotacao = 'DISPONÍVEL'.
*/
SELECT sala_id, nome_sala, capacidade, ocupacao_atual, status_lotacao
FROM vw_ocupacao_salas 
WHERE sala_id = 5;