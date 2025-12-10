/* 
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
SCRIPT PARA SGBD MYSQL
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

-- =================================================================================================================================================
-- FUNCTION 1
/*
Evento (Entrada): O sistema ou um usuário solicita a verificação financeira de um aluno específico (passando o id_aluno).
Condição (Lógica): O sistema deve identificar na tabela mensalidades todos os registros vinculados a este aluno que satisfaçam uma das seguintes condições:
O status de pagamento é explicitamente 'Vencido'; OU
O status de pagamento é 'Pendente', mas a data_vencimento é anterior à data atual do sistema (indicando atraso não processado).
Ação (Saída): Retornar a soma (SUM) dos valores nominais dessas parcelas filtradas. 
Caso nenhuma parcela se enquadre nas condições (aluno adimplente), a função deve retornar, obrigatoriamente, o valor 0.00 em vez de NULL.
*/
drop function if exists fc_calcular_divida_ativa;
delimiter //
create function fc_calcular_divida_ativa(param_id_aluno int)
returns decimal(10,2)
deterministic
begin
declare total_divida decimal(10,2);
select coalesce(sum(men.valor_nominal), 0) into total_divida
from mensalidades men join matriculas ma on ma.matricula_id = men.matricula_id
where param_id_aluno = ma.aluno_id and(
men.status_pag = 'Vencido'or(men.status_pag = 'Pendente' and men.data_vencimento < curdate()));
return total_divida;
end //
delimiter ;
/*
Decisões de Implementação:
Tratamento de Nulos (COALESCE): A decisão mais crítica desta função foi o uso de COALESCE(SUM(...), 0). Em SQL, a soma de um conjunto vazio resulta em NULL. Para regras de negócio financeiras, retornar NULL pode causar erros de cálculo em aplicações (ex: NULL + 100 = NULL). O COALESCE garante que um aluno sem dívidas retorne 0.00.
Lógica de Vencimento Dupla: A cláusula WHERE implementa uma verificação de segurança. Não confiamos apenas no status 'Vencido' (que pode depender de uma rotina noturna de atualização). Verificamos também se é 'Pendente' com data passada (data_vencimento < CURRENT_DATE), garantindo que a dívida seja calculada em tempo real, mesmo se o status no banco estiver desatualizado.
Compatibilidade de Datas: No MySQL utilizamos CURDATE() e no PostgreSQL CURRENT_DATE, respeitando as funções nativas de cada SGBD para capturar a data do servidor.
*/

/*
Este teste valida o cenário positivo. O aluno ID 4 (Gabriela) possui parcelas explicitamente vencidas no script de população. 
O retorno esperado é a soma exata dessas parcelas, confirmando que a lógica de soma está correta.
*/
select pessoa_id, p.nome, fc_calcular_divida_ativa(pessoa_id) as divida_total from pessoas p where pessoa_id = 4;
 
/*
Este caso testa a robustez da função via COALESCE. O aluno ID 28 tem todas as mensalidades pagas. 
O sistema não deve retornar NULL nem erro, mas sim o valor numérico 0.00, 
provando que o tratamento de exceção para conjuntos vazios funciona.
*/
select p.nome, fc_calcular_divida_ativa(p.pessoa_id) as divida_total from pessoas p where p.pessoa_id = 28;

-- -------------------------------------------------------------------------------------------------------------------------------------------------
-- FUNCTION 2
/*
Evento (Entrada): Necessidade de emitir um boletim ou relatório de desempenho de um aluno em um idioma específico (passando id_aluno e id_idioma).
Condição (Lógica): O sistema deve rastrear as avaliações do aluno percorrendo o caminho: Avaliações → Matrículas → Turmas → Cursos → Idiomas. 
Devem ser consideradas apenas as notas das avaliações que pertençam a cursos do idioma solicitado.
Ação (Saída): Calcular e retornar a média aritmética (AVG) dessas notas, arredondada para duas casas decimais. 
Se o aluno nunca cursou aquele idioma (sem avaliações), retornar 0.00.
*/
drop function if exists fc_media_idioma;
delimiter //
create function fc_media_idioma(param_id_aluno int, param_id_idioma int)
returns decimal(4,2)
deterministic
begin
declare media decimal(4,2);
select coalesce(avg(av.nota), 0) into media
from avaliacoes av join matriculas ma on ma.matricula_id = av.matricula_id
join turmas tu on tu.turma_id = ma.turma_id join cursos cu on cu.curso_id = tu.curso_id
where ma.aluno_id = param_id_aluno and cu.idioma_id = param_id_idioma;
return media;
end //
delimiter ;
/*
Decisões de Implementação:
Navegação entre Tabelas (Joins): A complexidade desta função reside na distância entre a tabela avaliacoes (onde está a nota) e a tabela idiomas (o filtro desejado). Optou-se por uma cadeia de INNER JOINs (Avaliações → Matrículas → Turmas → Cursos) para garantir integridade. Isso assegura que a nota pertence, de fato, àquele aluno naquele contexto específico.
Abstração de Cursos: A função permite calcular a média de um aluno em "Inglês" (Idioma), independentemente de ele ter feito "Inglês Básico 1" ou "Inglês Avançado". O agrupamento é feito pelo idioma pai, oferecendo uma visão macro do desempenho do estudante.
Determinismo: As funções foram marcadas como DETERMINISTIC (no MySQL), informando ao otimizador do banco que, para os mesmos dados de entrada, o resultado será sempre o mesmo, o que pode otimizar a performance em consultas repetitivas.
*/

/*
Verifica se os JOINS estão recuperando corretamente as notas. O aluno ID 4 cursou turmas de Inglês. 
A função deve percorrer todo o caminho relacional e retornar a média aritmética das notas lançadas.
*/
select p.nome, i.nome_idioma, fc_media_idioma(p.pessoa_id, i.idioma_id) as media_notas
from pessoas p join idiomas i where p.pessoa_id = 4 and i.idioma_id = 1;

/*
Teste de consistência. O aluno ID 4 nunca se matriculou em Alemão (ID 4). 
A função deve filtrar, não encontrar registros e retornar 0.00 (graças ao COALESCE), 
indicando ausência de histórico naquele idioma específico sem quebrar a execução.
*/
select p.nome, 'Alemão' as idioma_testado, fc_media_idioma(p.pessoa_id, 4) as media_notas
from pessoas p where p.pessoa_id = 4;
-- =================================================================================================================================================


-- =================================================================================================================================================
-- TRANSACTION 1
/*
Evento (Entrada): Solicitação de transferência de um aluno de sua turma atual para uma nova turma de destino (id_matricula, id_nova_turma).
Condição (Lógica): Verifica-se a disponibilidade na turma de destino. A regra é: (Capacidade da Sala - Total de Alunos Ativos na Nova Turma) > 0.
Ação (Saída):
Se a condição for verdadeira: Executar o UPDATE do turma_id na tabela matriculas e confirmar a transação (COMMIT).
Se a condição for falsa: Desfazer qualquer alteração (ROLLBACK) e levantar uma exceção informando que não há vagas disponíveis.
*/

-- -------------------------------------------------------------------------------------------------------------------------------------------------
-- TRANSACTION 2
/*
Evento (Entrada): Registro de pagamento de uma mensalidade no caixa (id_mensalidade, valor_recebido, id_forma_pagamento).
Condição (Lógica): A existência da mensalidade e a consistência dos dados.
Ação (Saída): Atualizar atomicamente (tudo ou nada) três campos na tabela mensalidades:
Alterar status_pag para 'Pago'.
Registrar a data_pag com a data atual do sistema.	
Registrar o valor_pag com o montante efetivamente recebido.
Se qualquer um desses updates falhar, toda a operação é desfeita para evitar inconsistência (ex: constar como pago mas sem data).
*/

-- =================================================================================================================================================


-- =================================================================================================================================================
-- PROCEDURE 1
/*
Evento (Entrada): Ocorre a confirmação de uma nova matrícula no sistema (chamada da procedure passando id_matricula).
Condição (Lógica): O curso associado à matrícula deve possuir uma duração em meses definida (duracao_meses > 0). O sistema deve iterar (loop) de 1 até N (duração do curso).
Ação (Saída): Inserir registros na tabela mensalidades correspondentes a cada parcela. A data de vencimento de cada parcela deve ser calculada para o dia 10 dos meses subsequentes à data da matrícula, com status inicial definido como 'Pendente'.
*/

-- -------------------------------------------------------------------------------------------------------------------------------------------------
-- PROCEDURE 2
/*
Evento (Entrada): A secretaria decide conceder uma bolsa ou desconto a um aluno já matriculado (chamada da procedure passando id_matricula e percentual_desconto).
Condição (Lógica): O desconto deve ser aplicado apenas sobre as mensalidades cujo status_pag seja 'Pendente'. Parcelas 'Pagas' ou 'Vencidas' devem ser ignoradas para manter a integridade do histórico financeiro e evitar recálculos indevidos de dívidas passadas.
Ação (Saída): Atualizar (UPDATE) o campo valor_nominal das parcelas elegíveis, reduzindo o valor original conforme o percentual informado. Caso o percentual seja inválido (<=0 ou >100), a operação deve ser abortada.
*/

-- =================================================================================================================================================



-- =================================================================================================================================================
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

-- -------------------------------------------------------------------------------------------------------------------------------------------------
-- VIEW 2
/*
Evento (Entrada): Consulta operacional para alocação de novas turmas.
Condição (Lógica): Calcular a ocupação atual (COUNT de matrículas ativas por sala) e compará-la com a capacidade máxima da sala.
Ação (Saída): Apresentar:
Nome da Sala e Capacidade.
Ocupação Atual.
Coluna calculada "Status Lotação": Retornar 'LOTADA' se (Ocupação >= Capacidade), caso contrário retornar 'DISPONÍVEL'.
*/

-- =================================================================================================================================================


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
