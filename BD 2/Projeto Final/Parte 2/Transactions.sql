-- =================================================================================================================================================
-- TRANSACTION 1
/*
Evento (Entrada): Solicitação de transferência de um aluno de sua turma atual para uma nova turma de destino (id_matricula, id_nova_turma).
Condição (Lógica): Verifica-se a disponibilidade na turma de destino. A regra é: (Capacidade da Sala - Total de Alunos Ativos na Nova Turma) > 0.
Ação (Saída):
Se a condição for verdadeira: Executar o UPDATE do turma_id na tabela matriculas e confirmar a transação (COMMIT).
Se a condição for falsa: Desfazer qualquer alteração (ROLLBACK) e levantar uma exceção informando que não há vagas disponíveis.
*/
drop procedure if exists tr_transferir_turma;
delimiter //
create procedure tr_transferir_turma(param_matricula_id INT, param_nova_turma_id INT)
begin
declare capacidade_sala INT;
declare alunos_ativos_na_nova_turma INT;
declare turma_atual_id INT;

start transaction; 

select turma_id into turma_atual_id from matriculas WHERE matricula_id = param_matricula_id;

if turma_atual_id is null then rollback;
signal sqlstate '45000' set message_text = 'Erro: Matrícula não encontrada.';
END IF;

select S.capacidade into capacidade_sala from turmas T join salas S on T.sala_id = S.sala_id where T.turma_id = param_nova_turma_id;

select count(M.matricula_id) into alunos_ativos_na_nova_turma from matriculas M where M.turma_id = param_nova_turma_id and M.status_mat = 'Ativa';
    
if (alunos_ativos_na_nova_turma + 1) > capacidade_sala then rollback;
signal sqlstate '45000' set message_text = 'Transferência Falhou: Sala de destino lotada.';
else update matriculas set turma_id = param_nova_turma_id where matricula_id = param_matricula_id;
commit;
end if;

end //
delimiter ;

/*
Decisões de Implementação:
Atomicidade: O conceito transacional é mantido. No MySQL, usamos 'START TRANSACTION', 'COMMIT' e 'ROLLBACK' explícitos. 
No PostgreSQL, ao usar 'CREATE OR REPLACE PROCEDURE' (PL/pgSQL), o bloco BEGIN/END funciona como uma transação implícita; 
o 'COMMIT' ocorre automaticamente no final do bloco, a menos que um erro ('RAISE EXCEPTION') seja lançado, o que força um ROLLBACK automático.
Controle de Erro: A sinalização de erro foi adaptada. No MySQL, utiliza-se SIGNAL SQLSTATE '45000'. 
No PostgreSQL, o comando é RAISE EXCEPTION, que é o mecanismo nativo para abortar a execução e desfazer a transação.
Validação de Vaga: A lógica de verificação (contagem de alunos ativos na nova turma vs. capacidade) é mantida, garantindo que a integridade do negócio seja a prioridade.
*/

/*
Este teste valida o cenário positivo (Transfêrencia Permitida). 
- Aluno: Daniel Silva (Matrícula ID 1).
- Turma Atual: ING-BAS-T01-2025 (ID 1).
- Turma Destino: ESP-BAS-T04-2025 (ID 18).
- Ocupação T18: 1 aluno (Matrícula 38). Capacidade: 25. HÁ VAGA.
O retorno esperado é a Matrícula 1 ter o campo turma_id = 18.
*/
call tr_transferir_turma(1, 18); 

-- Verificação (Deve mostrar turma_id = 18)
select M.matricula_id, T.turma_id, P.nome, T.nome_turma from matriculas M join pessoas P on M.aluno_id = P.pessoa_id join turmas T on M.turma_id = T.turma_id where M.matricula_id = 1;
 
/*
Este caso testa o bloqueio por lotação (Transação desfeita). 
Usamos a Turma ID 19 (ITA-RAP-T02-2025) que está lotada.
A tentativa de mover a Matrícula ID 9 (Lucas) para lá DEVE FALHAR.
O retorno esperado é o erro 'Transferência Falhou: Sala de destino lotada.' e a Matrícula ID 9 
DEVE PERMANECER com sua turma original (ID 14) após o ROLLBACK.
*/
call tr_transferir_turma(9, 19); 

-- Verificação (Deve mostrar a turma original: turma_id = 14)
select M.matricula_id, T.turma_id, P.nome, T.nome_turma from matriculas M join pessoas P on M.aluno_id = P.pessoa_id join turmas T on M.turma_id = T.turma_id where M.matricula_id = 9;

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
drop procedure if exists tr_realizar_pagamento;
delimiter //
create procedure tr_realizar_pagamento(param_matricula_id INT, param_numero_parcela INT, param_valor_pago DECIMAL(10,2))
begin
declare linhas_afetadas int default 0;

start transaction;

update mensalidades set status_pag = 'Pago', data_pag = current_date(), valor_pag = param_valor_pago
where matricula_id = param_matricula_id and numero_parcela = param_numero_parcela;

set linhas_afetadas = row_count();

if linhas_afetadas = 1 then commit;
else rollback;
signal sqlstate '45000' set message_text = 'Pagamento Falhou: Parcela não encontrada ou erro na baixa.';
    end if;
    
end //
delimiter ;

/*
Decisões de Implementação:
Atomicidade e Consistência: O comando UPDATE altera os três campos críticos simultaneamente (status_pag, data_pag, valor_pag). 
Em caso de falha de qualquer natureza (ex: registro não encontrado, falha de integridade), o sistema executa o ROLLBACK, 
impedindo que a mensalidade fique com status 'Pago' sem o registro da data ou valor, mantendo a consistência (ACID) em ambos os SGBDs.
Controle de Linhas Afetadas: Para validar a existência da parcela, utilizamos a função de contagem de linhas afetadas (ROW_COUNT() no MySQL/MariaDB e 
GET DIAGNOSTICS... ROW_COUNT no PostgreSQL). Isso garante que o COMMIT só ocorra se exatamente UMA parcela for atualizada, prevenindo confirmação para registros inexistentes.
*/

/*
Este teste valida o cenário positivo (Baixa Bem-sucedida). 
A mensalidade Matrícula ID 1, Parcela 5, está com status 'Pendente'. 
O procedimento deve realizar o UPDATE dos três campos cruciais (status, data, valor).
O retorno esperado é status_pag = 'Pago', data_pag preenchida (data atual) e valor_pag = 300.00.
*/
call tr_realizar_pagamento(1, 5, 300.00); 

-- Verificação (Deve mostrar status 'Pago' e data_pag preenchida)
select matricula_id, numero_parcela, status_pag, data_pag, valor_pag from mensalidades where matricula_id = 1 and numero_parcela = 5;
 
/*
Este caso testa o bloqueio por registro inexistente. 
Tentamos realizar a baixa da Parcela 99, que não existe na Matrícula ID 1.
O procedimento deve retornar 0 linhas afetadas, executar o ROLLBACK 
e retornar o erro 'Pagamento Falhou: Parcela não encontrada ou erro na baixa.'.
O retorno esperado é a mensagem de erro.
*/
call tr_realizar_pagamento(1, 99, 300.00); 

-- Verificação (Deve retornar 0 linhas)
select matricula_id, numero_parcela, status_pag, data_pag, valor_pag from mensalidades where matricula_id = 1 and numero_parcela = 99;

-- =================================================================================================================================================