-- =================================================================================================================================================
-- TRIGGER 1
/*
Evento (Entrada): Tentativa de inserir uma nova linha na tabela matriculas (Momento: BEFORE INSERT).
Condição (Lógica): O sistema verifica se a contagem atual de alunos na turma de destino (NEW.turma_id) já atingiu ou ultrapassou a capacidade da sala associada àquela turma.
Ação (Saída):
Se a sala estiver cheia: Bloquear a inserção e lançar um erro no banco de dados (ex: SIGNAL SQLSTATE no MySQL ou RAISE EXCEPTION no PostgreSQL) com a mensagem "Sala Lotada".
Se houver vaga: Permitir a inserção normalmente.
*/
drop trigger if exists tg_verificar_lotacao;
delimiter //
create trigger tg_verificar_lotacao
before insert on matriculas
for each row
begin
declare alunos_ativos int;
declare capacidade_sala int;
select s.capacidade into capacidade_sala from turmas t join salas s on s.sala_id = t.sala_id where turma_id = new.turma_id;
select count(matricula_id) into alunos_ativos from matriculas where turma_id = new.turma_id and status_mat = 'Ativa';
if(alunos_ativos + 1) > capacidade_sala then signal sqlstate '45000' set message_text = 'Sala Lotada. Matrícula bloqueada.';
end if;
end //
delimiter ;
/*
Decisões de Implementação:
Momento de Execução (BEFORE INSERT): O Trigger é executado antes que o registro seja fisicamente inserido na tabela. Isso permite o bloqueio da operação sem a necessidade de um ROLLBACK custoso (melhor performance).
Filtro de Status (status_mat = 'Ativa'): A contagem de alunos é rigorosa, considerando apenas matrículas com status 'Ativa'. Isso evita que alunos com matrículas 'Concluídas' ou 'Inativas' sejam contados indevidamente para o cálculo da lotação atual.
Verificação Preditiva: A condição 'if(alunos_ativos + 1) > capacidade_sala' prevê o estado futuro. O Trigger compara a lotação ANTES da inserção (alunos_ativos) com a capacidade, mas contando o novo aluno (+1), garantindo que a regra de lotação não seja violada.
*/

/*
Este teste valida o cenário POSITIVO (Permissão). 
Usaremos a Turma ID 17 (ALE-A1-T02-2025) que tem Capacidade 15 e 
atualmente possui 1 aluno ativo (Matrícula ID 37).
O sistema deve permitir a inserção de um novo aluno (Aluno ID 29), resultando em 2/15.
O retorno esperado é a Matrícula 118 ou superior, com status 'Ativa'.
*/
INSERT INTO matriculas (aluno_id, turma_id, data_matricula, valor_total_curso, status_mat) VALUES
(29, 17, CURDATE(), 1800.00, 'Ativa');

-- Verificação (Deve retornar o novo registro)
SELECT M.matricula_id, P.nome AS Aluno, T.nome_turma FROM matriculas M JOIN pessoas P ON 
M.aluno_id = P.pessoa_id JOIN turmas T ON M.turma_id = T.turma_id WHERE M.aluno_id = 29 AND M.turma_id = 17;
 
/*
Este caso testa o BLOQUEIO (Cenário Crítico). 
A Turma ID 19 (ITA-RAP-T02-2025) foi populada até sua capacidade máxima de 18 alunos.
Este INSERT de um novo aluno (Aluno ID 30) DEVE FALHAR, pois 
(18 alunos ativos + 1 novo aluno) > 18 (Capacidade).
O retorno esperado é o erro 'Sala Lotada. Matrícula bloqueada.' e o registro não deve existir.
*/
-- ESTE COMANDO DEVE GERAR O ERRO: "Sala Lotada. Matrícula bloqueada."
INSERT INTO matriculas (aluno_id, turma_id, data_matricula, valor_total_curso, status_mat) VALUES
(30, 19, CURDATE(), 900.00, 'Ativa');

-- Verificação (Deve retornar 0 linhas, pois o INSERT foi bloqueado)
SELECT * FROM matriculas WHERE aluno_id = 30 AND turma_id = 19;

-- -------------------------------------------------------------------------------------------------------------------------------------------------
-- TRIGGER 2
/*
Evento (Entrada): Atualização de dados na tabela mensalidades (Momento: BEFORE UPDATE).
Condição (Lógica): O sistema detecta que o campo valor_pag foi preenchido pelo usuário (era NULL e agora (NEW.valor_pag) possui valor), indicando que um pagamento foi processado.
Ação (Saída): Alterar automaticamente o campo status_pag para 'Pago' e, caso a data_pag não tenha sido informada manualmente, definir a data atual como data de pagamento. Isso garante consistência mesmo que o operador esqueça de mudar o status manualmente.
*/
drop trigger if exists tg_atualizar_status_pagamento;
delimiter //
create trigger tg_atualizar_status_pagamento
before update on mensalidades
for each row
begin
if new.valor_pag is not null and old.status_pag != 'Pago' then
	set new.status_pag = 'Pago';
	if new.data_pag is null then set new.data_pag = curdate();
	end if;
end if;
end //
delimiter ;

/*
Decisões de Implementação:
Sinalização de Pagamento (NEW.valor_pag): A decisão de disparo do Trigger foca no preenchimento do campo 'valor_pag'. Isso garante que o status financeiro seja automatizado no momento em que a informação contábil mais relevante (o valor recebido) é registrada[cite: 413].
Controle de Status (OLD.status_pag): A cláusula "AND OLD.status_pag != 'Pago'" impede que o Trigger seja executado desnecessariamente em updates posteriores (como uma correção na forma de pagamento) de uma parcela que já foi quitada. Isso garante eficiência.
Consistência de Data (CURDATE()): O uso do condicional IF NEW.data_pag IS NULL em conjunto com CURDATE() (ou CURRENT_DATE no PostgreSQL) assegura que todo registro com status 'Pago' tenha uma data de pagamento associada, garantindo consistência mesmo que o operador esqueça de mudar o status manualmente[cite: 414, 415].
*/

/*
Este teste valida o cenário positivo de automação. A mensalidade ID 1, Parcela 4 
está com status 'Pendente' (data de vencimento 2025-05-20). 
O sistema insere apenas o valor pago (300.00). O Trigger deve automaticamente 
mudar 'status_pag' para 'Pago' e preencher 'data_pag' com a data atual.
O retorno esperado é status_pag = 'Pago' e data_pag preenchida.
*/
UPDATE mensalidades 
SET valor_pag = 300.00 
WHERE matricula_id = 1 AND numero_parcela = 4;

SELECT matricula_id, numero_parcela, status_pag, data_pag, valor_pag 
FROM mensalidades WHERE matricula_id = 1 AND numero_parcela = 4;

/*
Este caso testa a robustez do Trigger contra reprocessamento. 
A mensalidade ID 1, Parcela 4, já foi paga no teste anterior. 
Tentamos um update secundário (ex: mudar a forma de pagamento). 
O sistema não deve reverter ou mudar o status 'Pago', 
provando que a condição OLD.status_pag != 'Pago' funcionou.
*/
UPDATE mensalidades 
SET forma_pagamento_id = 3 
WHERE matricula_id = 1 AND numero_parcela = 4;

SELECT matricula_id, numero_parcela, status_pag, data_pag, valor_pag 
FROM mensalidades WHERE matricula_id = 1 AND numero_parcela = 4;
-- =================================================================================================================================================