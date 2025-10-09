use sakila_valdir;

-- Questão 1 ---------------------------------------------------------------------------
create table aluguel_auditoria(
aluguel_auditoria_id int primary key auto_increment,
aluguel_id int,
data_de_aluguel datetime,
inventario_id mediumint,
cliente_id smallint,
data_de_devolucao datetime,
funcionario_id tinyint,
ultima_atualizacao timestamp
);

delimiter //
create trigger TR_aluguel_update
after update on aluguel
for each row
begin
insert into aluguel_auditoria values
(null, old.aluguel_id, old.data_de_aluguel, old.inventario_id, old.cliente_id,
old.data_de_devolucao, old.funcionario_id, old.ultima_atualizacao);
end //
delimiter ;

select * from aluguel where aluguel_id = 1;
select * from aluguel_auditoria;

update aluguel set ultima_atualizacao = current_timestamp() where aluguel_id = 1;
-- -------------------------------------------------------------------------------------

-- Questão 2 ---------------------------------------------------------------------------
create table pagamento_auditoria(
pagamento_auditoria_id int primary key auto_increment,
pagamento_id int,
cliente_id smallint,
funcionario_id tinyint,
aluguel_id int,
valor decimal(10, 2),
data_de_pagamento datetime,
ultima_atualizacao timestamp
);

delimiter //
create trigger TR_pagamento_update
before insert on pagamento
for each row
begin
insert into pagamento_auditoria values
(null, new.pagamento_id, new.cliente_id, new.funcionario_id, new.aluguel_id,
new.valor, new.data_de_pagamento, new.ultima_atualizacao);
end //
delimiter ;

select pagamento_id from pagamento order by pagamento_id desc limit 1;
select * from pagamento_auditoria;

insert into pagamento (pagamento_id, cliente_id, funcionario_id, aluguel_id, valor, data_de_pagamento, ultima_atualizacao) 
values (16050, 599, 2, 15725, 2.99, '2024-08-23 11:25:00', '2025-02-15 22:24:13');
-- -------------------------------------------------------------------------------------









