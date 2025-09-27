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



