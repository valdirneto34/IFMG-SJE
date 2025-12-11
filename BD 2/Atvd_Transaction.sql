use sakila_valdir;

-- ================================================================================
delimiter //
create procedure pr_novo_aluguel()
begin
declare erro_sql tinyint default false;
declare continue handler for sqlexception set erro_sql = true;
start transaction;
	insert into aluguel values (null, '2025-11-24 14:10:22', 1, 1, null, 1, '2025-11-24 14:10:22');
	update inventario set ultima_atualizacao = '2025-11-24 14:10:22' where inventario_id = 1;
if erro_sql = false then
	commit;
	select 'Transação realizada com sucesso!' as Resultado;
else 
	rollback;
	select 'Erro!' as Resultado;
end if;
end //
delimiter ;

call pr_novo_aluguel();
-- drop procedure pr_novo_aluguel;

-- ================================================================================
delimiter //
create procedure pr_atualiza_dados()
begin
declare erro_sql tinyint default false;
declare continue handler for sqlexception set erro_sql = true;
start transaction;
	update cliente set email = 'MARY.SMITH@onebitjr.com.br' where cliente_id = 1;
	update cliente set ultima_atualizacao = '2025-11-24 14:32:47' where cliente_id = 1;
	insert into pagamento values (null, 2, 1, 16050, 22, '2025-11-24 14:32:47', '2025-11-24 14:32:47');
if erro_sql = false then
	commit;
	select 'Transação realizada com sucesso!' as Resultado;
else 
	rollback;
	select 'Erro!' as Resultado;
end if;
end //
delimiter ;

call pr_atualiza_dados();
-- drop procedure pr_atualiza_dados;

-- ================================================================================
delimiter //
create procedure pr_devolver_filme()
begin
declare erro_sql tinyint default false;
declare continue handler for sqlexception set erro_sql = true;
start transaction;
	update aluguel set data_de_devolucao = '2025-11-24 21:27:31';
    update aluguel set ultima_atualizacao = '2025-11-24 21:27:31';
    update inventario set ultima_atualizacao = '2025-11-24 21:27:31' where inventario_id = 1;
if erro_sql = false then
	commit;
	select 'Transação realizada com sucesso!' as Resultado;
else 
	rollback;
	select 'Erro!' as Resultado;
end if;
end //
delimiter ;

call pr_devolver_filme();
-- drop pr_devolver_filme;

-- ================================================================================
delimiter //
create procedure pr_cancelar_aluguel()
begin
declare erro_sql tinyint default false;
declare continue handler for sqlexception set erro_sql = true;
start transaction;
	update aluguel set data_de_devolucao = '2025-11-24 21:39:27';
    update aluguel set ultima_atualizacao = '2025-11-24 21:39:27';
    update inventario set ultima_atualizacao = '2025-11-24 21:39:27' where inventario_id = 1;
if erro_sql = false then
	commit;
	select 'Transação realizada com sucesso!' as Resultado;
else 
	rollback;
	select 'Erro!' as Resultado;
end if;
end //
delimiter ;

call pr_cancelar_aluguel();
-- drop pr_cancelar_aluguel;

-- ================================================================================
delimiter //
create procedure pr_registrar_aluguel_pagamento(cliente_id int, inventario_id int, funcionario_id int, valor decimal(5,2))
begin
declare erro_sql tinyint default false;
declare continue handler for sqlexception set erro_sql = true;
start transaction;
	insert into aluguel values (null, '2025-11-24 21:44:57', inventario_id, cliente_id, null, funcionario_id, '2025-11-24 21:44:57');
    insert into pagamento values (null, cliente_id, funcionario_id, (select max(aluguel_id) from aluguel), valor, '2025-11-24 21:44:57', '2025-11-24 21:44:57');
if erro_sql = false then
	commit;
	select 'Transação realizada com sucesso!' as Resultado;
else 
	rollback;
	select 'Erro!' as Resultado;
end if;
end //
delimiter ;

call pr_registrar_aluguel_pagamento(1, 1, 1, 55);
-- drop pr_registrar_aluguel_pagamento;

-- ================================================================================