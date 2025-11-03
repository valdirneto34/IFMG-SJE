drop database if exists PROVA_01;
create database PROVA_01;
use PROVA_01;

CREATE TABLE Clientes (
id_cliente INT PRIMARY KEY AUTO_INCREMENT,
nome_cliente VARCHAR(100) NOT NULL,
email VARCHAR(100) UNIQUE NOT NULL,
data_cadastro DATETIME DEFAULT CURRENT_TIMESTAMP()
);

CREATE TABLE Produtos (
id_produto INT PRIMARY KEY AUTO_INCREMENT,
nome_produto VARCHAR(150) NOT NULL,
preco_unitario DECIMAL(10, 2) NOT NULL CHECK (preco_unitario > 0),
estoque_atual INT NOT NULL CHECK (estoque_atual >= 0)
);

CREATE TABLE Pedidos (
id_pedido INT PRIMARY KEY AUTO_INCREMENT,
id_cliente INT NOT NULL,
data_pedido DATETIME DEFAULT CURRENT_TIMESTAMP(),
status_pedido VARCHAR(20) NOT NULL DEFAULT 'Pendente' CHECK (status_pedido IN ('Pendente', 'Pago', 'Enviado', 'Cancelado')),
FOREIGN KEY (id_cliente) REFERENCES Clientes(id_cliente)
);

CREATE TABLE ItensPedido (
id_item INT PRIMARY KEY AUTO_INCREMENT,
id_pedido INT NOT NULL,
id_produto INT NOT NULL,
quantidade INT NOT NULL CHECK (quantidade > 0),
preco_momento DECIMAL(10, 2) NOT NULL,
FOREIGN KEY (id_pedido) REFERENCES Pedidos(id_pedido),
FOREIGN KEY (id_produto) REFERENCES Produtos(id_produto)
);

-- -----------------------------------------------------------------------------------------------------------------------------------
INSERT INTO Clientes (id_cliente, nome_cliente, email, data_cadastro) VALUES
(1, 'Ana Silva', 'ana.silva@email.com', '2025-01-05'), (2, 'Bruno Souza', 'bruno.souza@email.com', '2025-01-06'),
(3, 'Carla Mendes', 'carla.mendes@email.com', '2025-01-07'), (4, 'Diego Rocha', 'diego.rocha@email.com', '2025-01-08'),
(5, 'Elaine Costa', 'elaine.costa@email.com', '2025-01-09'), (6, 'Fabio Lima', 'fabio.lima@email.com', '2025-01-10'),
(7, 'Gabriela Torres', 'gabriela.torres@email.com', '2025-01-11'), (8, 'Henrique Alves', 'henrique.alves@email.com', '2025-01-12'),
(9, 'Isabela Moura', 'isabela.moura@email.com', '2025-01-13'), (10, 'João Pedro', 'joao.pedro@email.com', '2025-01-14'),
(11, 'Karen Martins', 'karen.martins@email.com', '2025-01-15'), (12, 'Lucas Oliveira', 'lucas.oliveira@email.com', '2025-01-16'),
(13, 'Mariana Ramos', 'mariana.ramos@email.com', '2025-01-17'), (14, 'Nelson Ferreira', 'nelson.ferreira@email.com', '2025-01-18'),
(15, 'Olivia Santos', 'olivia.santos@email.com', '2025-01-19'), (16, 'Paulo Henrique', 'paulo.henrique@email.com', '2025-01-20'),
(17, 'Rafael Lopes', 'rafael.lopes@email.com', '2025-01-21'), (18, 'Sabrina Teixeira', 'sabrina.teixeira@email.com', '2025-01-22'),
(19, 'Tiago Carvalho', 'tiago.carvalho@email.com', '2025-01-23'), (20, 'Ursula Figueiredo', 'ursula.figueiredo@email.com', '2025-01-24'),
(21, 'Vinicius Costa', 'vinicius.costa@email.com', '2025-01-25'), (22, 'Wellington Dias', 'wellington.dias@email.com', '2025-01-26'),
(23, 'Xenia Barros', 'xenia.barros@email.com', '2025-01-27'), (24, 'Yara Nunes', 'yara.nunes@email.com', '2025-01-28'),
(25, 'Zeca Brito', 'zeca.brito@email.com', '2025-01-29'), (26, 'Alice Pinto', 'alice.pinto@email.com', '2025-01-30'),
(27, 'Breno Tavares', 'breno.tavares@email.com', '2025-02-01'), (28, 'Cintia Rocha', 'cintia.rocha@email.com', '2025-02-02'),
(29, 'Daniel Gomes', 'daniel.gomes@email.com', '2025-02-03'), (30, 'Eduarda Lima', 'eduarda.lima@email.com', '2025-02-04');

INSERT INTO Produtos (id_produto, nome_produto, preco_unitario, estoque_atual) VALUES
(1, 'Mouse USB', 49.90, 200), (2, 'Teclado Mecânico', 249.00, 120), (3, 'Monitor 24"', 899.00, 60),
(4, 'Headset Gamer', 179.90, 75), (5, 'Webcam Full HD', 149.00, 90), (6, 'Notebook Dell Inspiron', 3899.00, 25),
(7, 'Cabo HDMI 2m', 29.90, 300), (8, 'Pendrive 64GB', 59.90, 200), (9, 'HD Externo 1TB', 399.00, 70),
(10, 'SSD 480GB', 329.00, 80), (11, 'Fonte 500W', 259.00, 50), (12, 'Placa de Vídeo RTX 4060', 2999.00, 20),
(13, 'Gabinete Gamer', 489.00, 35), (14, 'Mousepad Grande', 59.90, 150), (15, 'Switch 8 portas', 229.00, 40),
(16, 'Roteador Wi-Fi 6', 379.00, 45), (17, 'Cadeira Gamer', 1199.00, 15), (18, 'Teclado Sem Fio', 199.00, 70),
(19, 'Carregador USB-C', 79.90, 100), (20, 'Smartwatch', 799.00, 40), (21, 'Fone Bluetooth', 299.00, 90),
(22, 'Caixa Bluetooth', 259.00, 100), (23, 'Cabo USB 1m', 19.90, 400), (24, 'Tablet 10"', 1299.00, 25),
(25, 'Impressora Wi-Fi', 699.00, 25), (26, 'Scanner Portátil', 499.00, 15), (27, 'Monitor Ultrawide 29"', 1499.00, 10),
(28, 'Mouse Vertical', 159.00, 80), (29, 'HD Externo 2TB', 599.00, 25), (30, 'Notebook Lenovo', 4299.00, 12);

INSERT INTO Pedidos (id_pedido, id_cliente, data_pedido, status_pedido) VALUES
(1, 1, '2025-02-01', 'Pago'), (2, 2, '2025-02-02', 'Enviado'), (3, 3, '2025-02-03', 'Pendente'),
(4, 4, '2025-02-03', 'Cancelado'), (5, 5, '2025-02-04', 'Pago'),(6, 6, '2025-02-04', 'Pendente'),
(7, 7, '2025-02-05', 'Enviado'), (8, 8, '2025-02-05', 'Pendente'), (9, 9, '2025-02-06', 'Pago'),
(10, 10, '2025-02-06', 'Pago'), (11, 11, '2025-02-07', 'Cancelado'), (12, 12, '2025-02-07', 'Pago'),
(13, 13, '2025-02-08', 'Pendente'), (14, 14, '2025-02-09', 'Pago'), (15, 15, '2025-02-09', 'Pendente'),
(16, 16, '2025-02-10', 'Pago'), (17, 17, '2025-02-10', 'Pendente'),(18, 18, '2025-02-11', 'Enviado'),
(19, 19, '2025-02-11', 'Cancelado'), (20, 20, '2025-02-12', 'Pago'), (21, 21, '2025-02-12', 'Pendente'),
(22, 22, '2025-02-13', 'Enviado'), (23, 23, '2025-02-13', 'Pendente'), (24, 24, '2025-02-14', 'Pago'),
(25, 25, '2025-02-15', 'Cancelado'), (26, 26, '2025-02-16', 'Pago'), (27, 27, '2025-02-17', 'Pago'),
(28, 28, '2025-02-18', 'Enviado'), (29, 29, '2025-02-19', 'Pago'), (30, 30, '2025-02-20', 'Pendente');

INSERT INTO ItensPedido (id_item, id_pedido, id_produto, quantidade, preco_momento) VALUES
(1, 1, 1, 2, 49.90), (2, 1, 3, 1, 899.00), (3, 2, 4, 1, 179.90), (4, 3, 7, 3, 29.90),
(5, 4, 5, 1, 149.00), (6, 5, 6, 1, 3899.00), (7, 6, 8, 2, 59.90), (8, 7, 9, 1, 399.00),
(9, 8, 10, 1, 329.00), (10, 9, 11, 1, 259.00), (11, 10, 12, 1, 2999.00), (12, 11, 13, 1, 489.00),
(13, 12, 14, 2, 59.90), (14, 13, 15, 1, 229.00), (15, 14, 16, 1, 379.00), (16, 15, 17, 1, 1199.00),
(17, 16, 18, 1, 199.00), (18, 17, 19, 3, 79.90), (19, 18, 20, 1, 799.00), (20, 19, 21, 2, 299.00),
(21, 20, 22, 1, 259.00), (22, 21, 23, 4, 19.90), (23, 22, 24, 1, 1299.00), (24, 23, 25, 1, 699.00),
(25, 24, 26, 1, 499.00), (26, 25, 27, 1, 1499.00), (27, 26, 28, 1, 159.00), (28, 27, 29, 1, 599.00),
(29, 28, 30, 1, 4299.00), (30, 30, 2, 1, 249.00);
-- -----------------------------------------------------------------------------------------------------------------------------------

create or replace view vw_RelatorioVendasCliente as
select c.nome_cliente, pr.nome_produto, ip.quantidade, p.status_pedido, ip.quantidade * ip.preco_momento as subtotal 
from clientes c join pedidos p on p.id_cliente = c.id_cliente join itenspedido ip on
ip.id_pedido = p.id_pedido join produtos pr on pr.id_produto = ip.id_produto;

-- select * from vw_RelatorioVendasCliente;

delimiter //
create function fn_CalcularTotalPedido(id_pedido_param int)
returns decimal(10, 2)
deterministic
begin
declare total_pedido decimal(10, 2);
select ifnull(sum(quantidade * preco_momento), 0) into total_pedido from 
itenspedido where id_pedido = id_pedido_param;
return total_pedido;
end //
delimiter ;

-- select id_pedido, fn_CalcularTotalPedido(id_pedido) as total_pedido from pedidos;

delimiter //
create procedure sp_AdicionarItemPedido(IN id_pedido_param INT, IN id_produto_param INT, IN quantidade_param INT)
begin
    DECLARE v_estoque_atual INT;
    DECLARE v_preco_atual DECIMAL(10, 2);

/*Etapa 1: Verificar se id_pedido e id_produto são válidos*/
    IF (SELECT COUNT(*) FROM pedidos WHERE id_pedido = id_pedido_param) = 0 THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Erro: O ID do pedido informado não existe.';
    END IF;

-- 1.2: Verificando se o produto existe
	IF (SELECT COUNT(*) FROM produtos WHERE id_produto = id_produto_param) = 0 THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Erro: O ID do produto informado não existe.';
    END IF;
    
/* Etapa 2: Verificar se o status_pedido é 'Pendente' */
	IF (SELECT status_pedido FROM pedidos WHERE id_pedido = id_pedido_param) <> 'Pendente' THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Erro: Não é possível adicionar itens. O pedido não está "Pendente".';
    END IF;

/* Etapa 3: Verificar se o estoque é suficiente */
    SELECT estoque_atual, preco_unitario
    INTO v_estoque_atual, v_preco_atual
    FROM produtos
    WHERE id_produto = id_produto_param;

    IF v_estoque_atual < quantidade_param THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Erro: Estoque insuficiente.';
    END IF;

/* Etapa 5: Inserir o novo registro na tabela ItensPedido */
    INSERT INTO ItensPedido (id_pedido, id_produto, quantidade, preco_momento)
    VALUES (id_pedido_param, id_produto_param, quantidade_param, v_preco_atual);
end //
delimiter ;

/*
CALL sp_AdicionarItemPedido(99, 1, 1);
CALL sp_AdicionarItemPedido(3, 99, 1);
CALL sp_AdicionarItemPedido(1, 1, 1);
CALL sp_AdicionarItemPedido(3, 1, 201);
CALL sp_AdicionarItemPedido(3, 1, 5);
*/

delimiter //
create trigger trg_AtualizarEstoqueAposInsercao
after insert on itenspedido
for each row
begin
update produtos set estoque_atual = estoque_atual - new.quantidade 
where id_produto = new.id_produto;
end //
delimiter ;

/*
CALL sp_AdicionarItemPedido(3, 1, 5);
SELECT estoque_atual FROM produtos WHERE id_produto = 1;
update produtos set estoque_atual = 200 where id_produto = 1;
DELETE FROM itenspedido  WHERE id_pedido = 3 AND id_produto = 1;
*/
-- -----------------------------------------------------------------------------------------------------------------------------------


















