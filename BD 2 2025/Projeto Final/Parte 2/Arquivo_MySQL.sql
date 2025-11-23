-- =============================================================================
-- FUNCTION 1
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
 
-- FUNCTION 2
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
-- =============================================================================



-- =============================================================================
-- TRANSACTION 1

 
-- TRANSACTION 2

-- =============================================================================



-- =============================================================================
-- PROCEDURE 1

 
-- PROCEDURE 2

-- =============================================================================



-- =============================================================================
-- VIEW 1

 
-- VIEW 2

-- =============================================================================



-- =============================================================================
-- TRIGGER 1

 
-- TRIGGER 2

-- =============================================================================
