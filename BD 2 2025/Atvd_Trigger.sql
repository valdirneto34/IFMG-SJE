/*
Baseados nos conhecimentos obtidos até o momento, vocês deverão criar uma trigger em que
seja possível realizar a auditoria dos dados em uma tabela.
Para isto, siga as orientações:
1. Deverá ser possível dizer quando um produto foi alterado em determinada tabela e qual
usuário realizou a alteração. Pesquise sobre os comandos now() e current_user().

2. Exclua os bancos de dados criados anteriormente nas aulas sobre trigger OU crie novos com
nomes diferentes.

3. Crie um BD com o nome LOJA e em seguida uma tabela chamada PRODUTO, seguindo o
modelo da aula anterior.

4. Insira na tabela PRODUTO os valores já especificados na aula anterior.

5. Crie um BD com o nome BACKUP e dentro dele a tabela BKP_PRODUTO

6. Na tabela BKP_PRODUTO deverá ser possível armazenar os dados da tabela PRODUTO e
também o valor original, valor alterado, data da alteração e o nome do usuário que a realizou.

7. Neste passo, você deverá criar uma trigger com o nome AUDITORIA_PROD, que ao realizar a
atualização de qualquer produto na tabela PRODUTO, ela deverá gravar as informações na
tabela BKP_PRODUTO.

8. Realizadas as tarefas especificadas anteriormente, digite os seguintes comandos:
UPDATE PRODUTO SET VALOR = 110.00 WHERE IDPRODUTO =4;
SELECT * FROM BACKUP.BKP_PRODUTO;
*/
drop database if exists loja;
create database loja;
use loja;

create table produto(
idproduto int primary key auto_increment,
nome varchar(30),
valor float(10,2)
);

drop database if exists backup;
create database backup;
use backup;

create table bkp_produto(
id_BKP int primary key auto_increment,
idproduto int,
nome varchar(30),
valor_orig float(10,2),
valor_alt float(10, 2),
data date,
usuario varchar(30)
);

-- -------------------------------------------------------
insert into produto values
(null, 'LIVRO C#', 50.00),
(null, 'LIVRO BD', 100.00),
(null, 'LIVRO REDES', 120.00),
(null, 'LIVRO SQL', 80.00),
(null, 'LIVRO PHP', 70.00);

select * from produto;
select * from backup.bkp_produto;

-- -------------------------------------------------------
delimiter //
create trigger auditoria_prod
after update on produto
for each row
begin
insert into backup.bkp_produto values
(null, old.idproduto, old.nome, old.valor, new.valor, now(), current_user());
end //
delimiter ;

update produto set valor = 110 where idproduto = 4;
SELECT * FROM BACKUP.BKP_PRODUTO;

select * from produto;
select * from backup.bkp_produto;
-- -------------------------------------------------------


