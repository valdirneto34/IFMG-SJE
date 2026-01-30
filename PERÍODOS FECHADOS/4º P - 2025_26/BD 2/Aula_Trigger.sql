drop database if exists loja;
create database loja;
use loja;

create table produto(
idproduto int primary key auto_increment,
nome varchar(30),
valor float(10,2)
);
-- -------------------------------------------------------
drop database if exists backup;
create database backup;
use backup;

create table bkp_produto(
id_BKP int primary key auto_increment,
idproduto int,
nome varchar(30),
valor float(10,2)
);
-- -------------------------------------------------------
use loja;
insert into backup.bkp_produto values
(null, 100, 'Teste', 1.00);

select * from backup.bkp_produto;
-- -------------------------------------------------------
delimiter //
create trigger backup_produto
before insert on produto
for each row
begin
insert into backup.bkp_produto values
(null, new.idproduto, new.nome, new.valor);
end //
delimiter ;

insert into produto values
(null, 'LIVRO C#', 50.00),
(null, 'LIVRO BD', 100.00),
(null, 'LIVRO REDES', 120.00),
(null, 'LIVRO PHP', 80.00);

select * from produto;
select * from backup.bkp_produto;
-- -------------------------------------------------------
delimiter //
create trigger backup_produto_del
before delete on produto
for each row
begin
insert into backup.bkp_produto values
(null, old.idproduto, old.nome, old.valor);
end //
delimiter ;

delete from produto where idproduto = 2;

select * from produto;
select * from backup.bkp_produto;
-- -------------------------------------------------------
drop trigger backup_produto;

delimiter //
create trigger backup_produto
after insert on produto
for each row
begin
insert into backup.bkp_produto values
(null, new.idproduto, new.nome, new.valor);
end //
delimiter ;

insert into produto values(null, 'LIVRO REDES', 70.00);

select * from produto;
select * from backup.bkp_produto;
-- -------------------------------------------------------
delimiter //
create trigger bkp_produto
before update on produto
for each row
begin
insert into backup.bkp_produto values
(null, old.idproduto, old.nome, old.valor);
end //
delimiter ;

update produto set valor = 170 where idproduto = 3;

select * from produto;
select * from backup.bkp_produto;

drop trigger bkp_produto;





