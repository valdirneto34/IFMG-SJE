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