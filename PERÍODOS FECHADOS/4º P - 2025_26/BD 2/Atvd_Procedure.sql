use sakila_valdir;

/*Questão 1. Crie uma stored procedure que, dado o nome de um gênero, retorne a lista
de filmes desse gênero.*/

DELIMITER $$
CREATE PROCEDURE PR_LISTAR_FILME_GENERO (IN NOME_GENERO VARCHAR(50))
BEGIN -- Listar todos os filmes de um determinado gênero
SELECT f.titulo AS Filme FROM filme f
JOIN filme_categoria fc ON f.filme_id = fc.filme_id
JOIN categoria c ON fc.categoria_id = c.categoria_id
WHERE c.nome = NOME_GENERO;
END $$
DELIMITER ;

CALL PR_LISTAR_FILME_GENERO('Action');

/*Questão 2. Crie uma stored procedure que, dado o ID de um cliente, retorne o total
gasto por cliente em aluguéis.*/

delimiter $$
create procedure pr_total_gasto_cliente (in id_cliente2 int)
begin
select c.cliente_id, concat(c.primeiro_nome, " ", c.ultimo_nome) as nome, 
sum(p.valor) as total_gasto from cliente c join pagamento p on p.cliente_id = c.cliente_id 
where c.cliente_id = id_cliente2;
end $$
delimiter ;

call pr_total_gasto_cliente(1);

/*Questão 3. Crie uma stored procedure que, dado o título de um filme, verifique se há
cópias disponíveis para aluguel.*/

delimiter $$
create procedure pr_copia_fime_disponivel (in nome_filme varchar(255))
begin
select distinct i.inventario_id, f.titulo from filme f join inventario i on i.filme_id = f.filme_id 
left join aluguel a on a.inventario_id = i.inventario_id where f.titulo = nome_filme
and a.data_de_devolucao is not null group by i.inventario_id;
end $$
delimiter ;

call pr_copia_fime_disponivel('AFRICAN EGG');

/*Questão 4. Crie uma stored procedure que retorne os 5 clientes que mais alugaram
filmes.*/

delimiter $$
create procedure pr_clientes_mais_alugam ()
begin
select cliente_id, nome, qtd_alugueis from (
select c.cliente_id, concat(c.primeiro_nome, " ", c.ultimo_nome) as nome, count(c.cliente_id) as qtd_alugueis,
rank() over (order by count(c.cliente_id) desc) as ranked
from cliente c join aluguel a on c.cliente_id = a.cliente_id group by c.cliente_id, c.primeiro_nome) as r
where r.ranked <= 5;
end $$
delimiter ;

call pr_clientes_mais_alugam();

/*Questão 5. Crie uma stored procedure que gere um relatório de receita mensal por
categoria de filme. A procedure deve aceitar um intervalo de datas como entrada e
retornar o total de receita por categoria para cada mês no período especificado.
A procedure deve aceitar dois parâmetros: data inicial e data final.

A procedure deve agrupar a receita por mês e por categoria, exibindo o nome da
categoria e o total de receita gerada em aluguéis.
Parâmetros:
datini: Data de início do período.
datfim: Data de término do período.
A query se conecta às tabelas PAGAMENTO, ALUGUEL, INVENTARIO,
FILME_CATERGORIA e CATEGORIA para calcular o total de receita por categoria.
A função DATE_FORMAT agrupa as datas de pagamento por mês (%Y-%m).
O GROUP BY garante que os dados sejam agrupados por categoria e por mês.
CALL PR_categ_mes_receita('2023-01-01', '2023-06-30');*/

delimiter $$
create procedure pr_categ_mes_receita (in datini date, in datfim date)
begin
select ca.nome, date_format(p.data_de_pagamento, '%Y-%m') as receita_mes, sum(p.valor) as total_receita 
from categoria ca join filme_categoria fc on fc.categoria_id = ca.categoria_id
join inventario i on i.filme_id = fc.filme_id join aluguel a on a.inventario_id = i.inventario_id
join pagamento p on p.aluguel_id = a.aluguel_id where p.data_de_pagamento 
between datini and datfim group by receita_mes, ca.nome order by receita_mes, ca.nome;
end $$
delimiter ;

call pr_categ_mes_receita ('2023-01-01', '2023-06-30');

call  pr_categ_mes_receita('2005-01-01', '2005-06-30');

