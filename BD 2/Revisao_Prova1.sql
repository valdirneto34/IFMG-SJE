CREATE DATABASE LOJA_VIRTUAL;
USE LOJA_VIRTUAL;
CREATE TABLE CLIENTES (
ID_CLIENTE INT AUTO_INCREMENT PRIMARY KEY,
NOME VARCHAR(100) NOT NULL,
EMAIL VARCHAR(100) UNIQUE NOT NULL,
STATUS_CLIENTE ENUM('BRONZE', 'PRATA', 'OURO') DEFAULT 'BRONZE',
DATA_CADASTRO TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
CREATE TABLE PRODUTOS (
ID_PRODUTO INT AUTO_INCREMENT PRIMARY KEY,
NOME_PRODUTO VARCHAR(100) NOT NULL,
PRECO_UNITARIO DECIMAL(10, 2) NOT NULL,
ESTOQUE INT NOT NULL
);
CREATE TABLE PEDIDOS (
ID_PEDIDO INT AUTO_INCREMENT PRIMARY KEY,
ID_CLIENTE INT NOT NULL,
DATA_PEDIDO TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
STATUS_PEDIDO ENUM('PROCESSANDO', 'ENVIADO', 'ENTREGUE',
'CANCELADO') DEFAULT 'PROCESSANDO',
FOREIGN KEY (ID_CLIENTE) REFERENCES CLIENTES(ID_CLIENTE)
);
CREATE TABLE ITENS_PEDIDO (
ID_ITEM INT AUTO_INCREMENT PRIMARY KEY,
ID_PEDIDO INT NOT NULL,
ID_PRODUTO INT NOT NULL,
QUANTIDADE INT NOT NULL,
PRECO_COBRADO DECIMAL(10, 2) NOT NULL, -- PREÇO NO MOMENTO DA COMPRA
FOREIGN KEY (ID_PEDIDO) REFERENCES PEDIDOS(ID_PEDIDO),
FOREIGN KEY (ID_PRODUTO) REFERENCES PRODUTOS(ID_PRODUTO)
);
CREATE TABLE LOG_AUDITORIA_PRECOS (
ID_LOG INT AUTO_INCREMENT PRIMARY KEY,
ID_PRODUTO INT NOT NULL,
PRECO_ANTIGO DECIMAL(10, 2),
PRECO_NOVO DECIMAL(10, 2),
USUARIO VARCHAR(50) DEFAULT 'ADMIN',
DATA_ALTERACAO TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
-- -------------------------------------------------------------------------------------------
USE LOJA_VIRTUAL;
-- Populando a tabela CLIENTES
INSERT INTO CLIENTES (NOME, EMAIL, STATUS_CLIENTE) VALUES
('João Silva', 'joao.silva@email.com', 'OURO'),
('Maria Oliveira', 'maria.oliveira@email.com', 'PRATA'),
('Carlos Pereira', 'carlos.pereira@email.com', 'BRONZE'),
('Ana Costa', 'ana.costa@email.com', 'PRATA'),
('Pedro Martins', 'pedro.martins@email.com', 'BRONZE');

-- Populando a tabela PRODUTOS
-- Produtos com preços variados para testar a função de desconto
-- E estoques variados para testar a consulta com CASE WHEN e o trigger de estoque
INSERT INTO PRODUTOS (NOME_PRODUTO, PRECO_UNITARIO, ESTOQUE) VALUES
('Notebook Gamer', 4500.00, 15),
('Mouse Sem Fio', 120.50, 50),
('Teclado Mecânico', 350.00, 30),
('Monitor 4K', 1800.75, 10),
('Cadeira de Escritório', 850.00, 5),
('Webcam Full HD', 250.00, 0), -- Produto esgotado
('SSD 1TB', 450.99, 18);     -- Estoque baixo

-- Populando a tabela PEDIDOS
-- Criando pedidos para diferentes clientes
INSERT INTO PEDIDOS (ID_CLIENTE, STATUS_PEDIDO) VALUES
(1, 'ENTREGUE'),
(2, 'ENVIADO'),
(1, 'PROCESSANDO'),
(3, 'ENTREGUE'),
(4, 'CANCELADO'),
(2, 'PROCESSANDO');

-- Populando a tabela ITENS_PEDIDO
-- Associando produtos aos pedidos, com quantidade e preço no momento da compra
INSERT INTO ITENS_PEDIDO (ID_PEDIDO, ID_PRODUTO, QUANTIDADE, PRECO_COBRADO) VALUES
-- Itens do Pedido 1
(1, 3, 1, 350.00),
(1, 2, 1, 120.50),
-- Itens do Pedido 2
(2, 4, 1, 1800.75),
-- Itens do Pedido 3
(3, 1, 1, 4500.00),
-- Itens do Pedido 4
(4, 5, 1, 850.00),
-- Itens do Pedido 5 (Cancelado)
(5, 7, 2, 450.99),
-- Itens do Pedido 6
(6, 2, 3, 120.50);
-- -------------------------------------------------------------------------------------------
USE LOJA_VIRTUAL;

/*
1. Função calcular desconto
i. Crie uma FUNCTION chamada fn_calcular_desconto.
ii. Recebe um preco_produto DECIMAL(10,2).
iii. A função deve usar IF/ELSEIF.
a. Se o preço for > R$ 300,00, retorna um desconto de 10% (preço * 0.10).
b. Se o preço for > R$ 100,00, retorna 5% (preço * 0.05).
c. Caso contrário, retorna 0.
iv. Retorno DECIMAL(10,2).
*/

delimiter //
create function fn_calcular_desconto (preco_produto decimal(10, 2))
returns decimal(10, 2)
deterministic
begin
declare desconto decimal(10, 2);
if preco_produto > 300 then set desconto = preco_produto * 0.1;
elseif preco_produto > 100 then set desconto = preco_produto * 0.05;
else set desconto = 0;
end if;
return desconto;
end //
delimiter ;

select id_produto, nome_produto, preco_unitario, fn_calcular_desconto(preco_unitario) as desconto from produtos;

/*
2. View catálogo de clientes ativos
i. Crie uma VIEW chamada vw_clientes_ativos.
ii. A View deve listar o nome, email e status_cliente da tabela Clientes.
iii. Deve exibir apenas clientes cujo status (status_cliente) seja 'Prata' ou 'Ouro'.
*/

create or replace view vw_clientes_ativos as
select nome, email, status_cliente from clientes where status_cliente = 'PRATA' or status_cliente = 'OURO';

select * from vw_clientes_ativos;

/*
3. Procedure inserir novo cliente
i. Crie uma STORED PROCEDURE chamada sp_novo_cliente.
ii. Recebe IN nome_param VARCHAR(100) e IN email_param VARCHAR(100).
iii. A procedure deve executar um comando INSERT simples para adicionar o novo
cliente na tabela Clientes. O status_cliente deve ser 'Bronze' por padrão.
*/

delimiter //
create procedure sp_novo_cliente (IN nome_param VARCHAR(100), IN email_param VARCHAR(100))
begin
insert into clientes values
(null, nome_param, email_param, 'BRONZE', current_timestamp());
end //
delimiter ;

call sp_novo_cliente('Valdir de Souza', 'valdirneto100c@gmail.com');
select * from clientes;

/*
4. Trigger validar estoque
i. Crie um TRIGGER chamado trg_validar_estoque_negativo.
ii. Tabela produtos.
iii. BEFORE UPDATE.
iv. O gatilho deve verificar se o novo valor do estoque (NEW.estoque) é menor que
zero.
v. Se for menor que zero, a operação de UPDATE deve ser cancelada (use
SIGNAL SQLSTATE '45000').
*/

delimiter //
create trigger trg_validar_estoque_negativo
before update on produtos
for each row
begin
if new.estoque < 0 then SIGNAL SQLSTATE '45000'
SET MESSAGE_TEXT = 'Estoque informado é menor do que zero';
end if;
end //
delimiter ;

update produtos set estoque = -10 where id_produto = 1;

/*
5. Função contar pedidos do cliente
i. Crie uma FUNCTION chamada fn_total_pedidos_cliente.
ii. Recebe um id_cliente_param INT.
iii. A função deve executar um SELECT COUNT(*) na tabela Pedidos para contar
quantos pedidos o cliente informado já fez.
iv. Retorno INT.
*/

delimiter //
create function fn_total_pedidos_cliente(id_cliente_param INT)
returns int
deterministic
begin
declare qtd_pedidos int;
select count(*) into qtd_pedidos from clientes c join pedidos p
on c.id_cliente = p.id_cliente where c.id_cliente = id_cliente_param;
return qtd_pedidos;
end //
delimiter ;

select id_cliente, nome, fn_total_pedidos_cliente(id_cliente) as qtd_pedidos from clientes;

/*
6. Procedure alterar preço de produto
i. Crie uma STORED PROCEDURE chamada sp_alterar_preco.
ii. Recebe IN id_produto_param INT e IN novo_preco_param DECIMAL(10,2).
iii. A procedure deve executar um UPDATE na tabela Produtos para atualizar o
preco_unitario do produto especificado.
*/

delimiter //
create procedure sp_alterar_preco(IN id_produto_param INT, IN novo_preco_param DECIMAL(10,2))
begin
update produtos set preco_unitario = novo_preco_param where id_produto = id_produto_param;
end //
delimiter ;

call sp_alterar_preco(1, 4600);
select * from produtos;

/*
7. Trigger auditoria de preços
i. Crie um TRIGGER chamado trg_log_alteracao_preco.
ii. Tabela produtos.
iii. AFTER UPDATE.
iv. O gatilho deve verificar se o preço antigo (OLD.preco_unitario) é diferente do
novo (NEW.preco_unitario).
v. Se for diferente, deve inserir o OLD.id_produto, OLD.preco_unitario e
NEW.preco_unitario na tabela Log_Auditoria_Precos.
*/

delimiter //
create trigger trg_log_alteracao_preco
after update on produtos
for each row
begin
if old.preco_unitario != new.preco_unitario then
insert into log_auditoria_precos values
(null, old.id_produto, old.preco_unitario, new.preco_unitario, current_user(), current_timestamp());
end if;
end //
delimiter ;

call sp_alterar_preco(1, 4500);
select * from log_auditoria_precos;

/*
8. Consulta com CASE WHEN
i. Crie um SELECT (não é view ou procedure).
ii. Liste o nome_produto e estoque da tabela Produtos.
iii. Crie uma coluna virtual chamada status_estoque usando CASE:
a) WHEN estoque = 0 THEN 'Esgotado'
b) WHEN estoque < 20 THEN 'Baixo'
c) ELSE 'Normal'
*/

select nome_produto, estoque, 
case when estoque = 0 then 'Esgotado'
when estoque < 20 then 'Baixo'
else 'Normal' end as status_estoque
from produtos;




