/* 
==========================================================
SCRIPT CONSULTAS PARA SGBD POSTGRESQL
==========================================================
*/

-- Para selecionar o SCHEMA (executar comando apenas no PostgreSQL)
SET search_path TO escola_idiomas;

/*
1. ESPECIFICAÇÃO TEXTUAL (CONSULTA 1)
Levantar o nome de cada professor, sua especialidade, 
a média geral das notas que seus alunos obtiveram em suas avaliações, 
e o número total de avaliações que ele aplicou. Ordenar pela maior média.
*/

-- 1. CÓDIGO SQL (CONSULTA 1)
select pe.nome as "Nome do professor", pr.especialidade as "Especialidade", 
round(avg(av.nota), 2) as "Média geral das notas", count(av.avaliacao_id) as "Número total de avaliações"
from pessoas pe join professores pr on pr.professor_id = pe.pessoa_id
join avaliacoes av on av.professor_id = pr.professor_id group by pe.nome, pr.especialidade
order by avg(av.nota) desc;

/*
2. ESPECIFICAÇÃO TEXTUAL (CONSULTA 2)
Exibir um relatório de inadimplência, agrupado por curso. 
Mostrar o nome do curso, o valor total que já deveria ter sido pago (valor nominal de parcelas vencidas), 
e o valor total que está efetivamente 'Vencido' ou 'Pendente' (que não foi pago).
*/

-- 2. CÓDIGO SQL (CONSULTA 2)
select cu.nome_curso as "Nome do curso", sum(me.valor_nominal) as "Valor nominal de parcelas vencidas", 
sum(case when me.status_pag in ('Pendente', 'Vencido') then me.valor_nominal else 0 end) as "Inadimplência Real"
from mensalidades me join matriculas ma on ma.matricula_id = me.matricula_id 
join turmas tu on tu.turma_id = ma.turma_id join cursos cu on cu.curso_id = tu.curso_id 
where (me.data_vencimento <= now()) group by cu.nome_curso order by cu.nome_curso;

/*
3. ESPECIFICAÇÃO TEXTUAL (CONSULTA 3)
Listar todas as turmas ativas, mostrando o nome da turma, o nome da sala, 
a capacidade máxima da sala, e o número de alunos matriculados. 
Exibir apenas as turmas que estão com mais de 80% de sua capacidade ocupada.
*/

-- 3. CÓDIGO SQL (CONSULTA 3)
select t.nome_turma, s.nome_sala, s.capacidade, COUNT(m.matricula_id) as "Alunos Matriculados"
from turmas t join salas s on t.sala_id = s.sala_id join matriculas m on t.turma_id = m.turma_id
where m.status_mat = 'Ativa' group by t.nome_turma, s.nome_sala, s.capacidade
having COUNT(m.matricula_id) > (s.capacidade * 0.8);

/*
4. ESPECIFICAÇÃO TEXTUAL (CONSULTA 4)
Encontrar alunos que estão simultaneamente com desempenho acadêmico baixo 
(média de notas inferior a 7.0) e com problemas financeiros (pelo menos uma mensalidade 'Vencida'). 
Mostrar o nome do aluno, o telefone e a média de notas.
*/

-- 4. CÓDIGO SQL (CONSULTA 4)
select p.nome, p.telefone, ROUND(avg(a.nota), 2) as "Media Notas"
from pessoas p join alunos al on p.pessoa_id = al.aluno_id
join matriculas m on al.aluno_id = m.aluno_id
join avaliacoes a on m.matricula_id = a.matricula_id
group by p.pessoa_id, p.nome, p.telefone 
having avg(a.nota) < 7.0 and p.pessoa_id in (
select m_sub.aluno_id 
from matriculas m_sub
join mensalidades ms_sub on m_sub.matricula_id = ms_sub.matricula_id
where ms_sub.status_pag = 'Vencido' 
);