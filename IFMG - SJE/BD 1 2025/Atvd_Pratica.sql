
-- CRIAÇÃO DO BANCO DE DADOS E SUAS TABELAS
CREATE DATABASE controle_estoque;

use controle_estoque;

-- TABELA CLIENTES
create table cliente(
cliente_id integer not null auto_increment primary key,
nome varchar(40) not null,
cpf_cnpj varchar(20) unique not null,
telefone bigint not null,
email varchar(30) not null,
endereco varchar(50) not null,
cidade varchar(50) not null,
estado varchar(10) not null,
data_cadastro date default (current_date),
limite_credito decimal(10, 2) not null,
status_cliente varchar(15) not null
);

-- TABELA PRODUTO
create table produto(
produto_id integer not null auto_increment primary key,
codigo varchar(20) not null unique,
descricao varchar(50) not null,
preco_venda decimal(12, 2) not null,
preco_custo decimal(12, 2) not null,
estoque_atual integer not null,
estoque_minimo integer not null,
categoria_id integer,
unidade_medida varchar(15),
data_cadastro date default (current_date),
status_produto varchar(15) not null
);

-- TABELA FORNECEDOR
create table fornecedor(
fornecedor_id integer not null auto_increment primary key,
nome varchar(30) not null,
cpf_cnpj varchar(20) unique not null,
telefone bigint not null,
email varchar(30) not null,
endereco varchar(50) not null,
cidade varchar(50) not null,
estado varchar(10) not null,
data_cadastro date default (current_date),
status_fornecedor varchar(15) not null
);

-- TABELA CATEGORIAS
create table categorias(
categoria_id integer not null auto_increment primary key,
nome varchar(30) not null,
descricao varchar(100) not null,
status_categoria varchar(15) not null
);

-- TABELA FUNCIONÁRIIO
create table funcionario(
funcionario_id integer not null auto_increment primary key,
nome varchar(30) not null,
cpf varchar(20) unique not null,
cargo varchar(30) not null,
data_contratacao date default (current_date),
salario decimal(12,2) not null,
telefone bigint not null,
email varchar(30) not null,
status_funcionario varchar(15) not null
);

-- TABELA TRANSPORTADORA
create table transportadora(
transportadora_id integer not null auto_increment primary key,
nome varchar(30) not null,
cnpj varchar(20) unique not null,
telefone bigint not null,
email varchar(30) not null,
status_transportadora varchar(15) not null
);

-- TABELA ROTA
create table rota(
rota_id integer not null auto_increment primary key,
nome varchar(30) not null,
origem varchar(30) not null,
destino varchar(30) not null,
distancia_km decimal(10,2) not null,
tempo_estimado time not null,
transportadora_id integer,
status_rota varchar(15) not null
);

-- TABELA VENDA
create table venda(
venda_id integer not null auto_increment primary key,
data_venda date default(current_date),
cliente_id integer,
funcionario_id integer,
valor_total decimal(10,2) not null,
desconto decimal(10,2) not null,
forma_pagamento varchar(30) not null,
status_venda varchar(15) not null,
observacao varchar(50) not null
);

-- TABELA VENDA
create table item_venda(
item_venda_id integer not null auto_increment primary key,
venda_id integer,
produto_id integer,
quantidade integer not null,
preco_unitario decimal(10,2) not null,
desconto decimal(10,2) not null,
valor_total decimal(10,2) not null
);

-- TABELA COMPRA
create table compra(
compra_id integer not null auto_increment primary key,
data_compra date default(current_date),
fornecedor_id integer,
funcionario_id integer,
valor_total decimal(10,2) not null,
status_compra varchar(15) not null,
observacao varchar(50) not null
);

-- TABELA ITEM_COMPRA
create table item_compra(
item_compra_id integer not null auto_increment primary key,
compra_id integer,
produto_id integer,
quantidade integer not null,
preco_unitario decimal(10,2) not null,
valor_total decimal(10,2) not null
);

-- TABELA PRODUCAO
create table producao(
producao_id integer not null auto_increment primary key,
data_inicio date default(current_date),
data_fim date default(current_date),
funcionario_id integer,
status_producao varchar(15) not null,
observacao varchar(50) not null
);

-- TABELA ITEM_PRODUCAO
create table item_producao(
item_producao_id integer not null auto_increment primary key,
producao_id integer,
produto_id integer,
quantidade_planejada integer not null,
quantidade_produzida integer not null,
custo_unitario decimal(10,2) not null,
valor_total decimal(10,2) not null
);

-- TABELA PEDIDO
create table pedido(
pedido_id integer not null auto_increment primary key,
data_pedido date default(current_date),
cliente_id integer,
funcionario_id integer,
data_entrega_prevista date default(current_date),
rota_id integer,
valor_total decimal(10,2) not null,
status_pedido varchar(15) not null,
observacao varchar(50) not null
);

-- TABELA ITEM_PEDIDO
create table item_pedido(
item_pedido_id integer not null auto_increment primary key,
pedido_id integer,
produto_id integer,
quantidade integer not null,
preco_unitario float not null,
desconto decimal(10,2) not null,
valor_total decimal(10,2) not null
);

alter table produto add constraint produto_categoria_id foreign key (categoria_id) references categorias (categoria_id);

alter table rota add constraint rota_transportadora_id foreign key (transportadora_id) references transportadora (transportadora_id);

alter table venda add constraint venda_cliente_id foreign key (cliente_id) references cliente (cliente_id);

alter table venda add constraint venda_funcionario_id foreign key (funcionario_id) references funcionario (funcionario_id);

alter table item_venda add constraint item_venda_venda_id foreign key (venda_id) references venda (venda_id);

alter table item_venda add constraint item_venda_produto_id foreign key (produto_id) references produto (produto_id);

alter table compra add constraint compra_fornecedor_id foreign key (fornecedor_id) references fornecedor (fornecedor_id);

alter table compra add constraint compra_funcionario_id foreign key (funcionario_id) references funcionario (funcionario_id);

alter table item_compra add constraint item_compra_compra_id foreign key (compra_id) references compra (compra_id);

alter table item_compra add constraint item_compra_produto_id foreign key (produto_id) references produto (produto_id);

alter table producao add constraint producao_funcionario_id foreign key (funcionario_id) references funcionario (funcionario_id);

alter table item_producao add constraint item_producao_producao_id foreign key (producao_id) references producao (producao_id);

alter table item_producao add constraint item_producao_produto_id foreign key (produto_id) references produto (produto_id);

alter table pedido add constraint pedido_cliente_id foreign key (cliente_id) references cliente (cliente_id);

alter table pedido add constraint pedido_funcionario_id foreign key (funcionario_id) references funcionario (funcionario_id);

alter table pedido add constraint pedido_rota_id foreign key (rota_id) references rota (rota_id);

alter table item_pedido add constraint item_pedido_pedido_id foreign key (pedido_id) references pedido (pedido_id);

alter table item_pedido add constraint item_pedido_produto_id foreign key (produto_id) references produto (produto_id);

-- INSERÇÃO DE DADOS MÍNIMOS
INSERT INTO categorias (nome, descricao, status_categoria) VALUES
('Eletrônicos', 'Produtos eletrônicos diversos como TVs, celulares, etc.', 'ativo'),
('Alimentos', 'Produtos alimentícios, perecíveis e não perecíveis.', 'ativo'),
('Vestuário', 'Roupas, calçados e acessórios.', 'ativo'),
('Limpeza', 'Produtos de limpeza para casa e escritório.', 'ativo'); -- 4 categorias

-- 2. Clientes (mínimo 5) 
INSERT INTO cliente (nome, cpf_cnpj, telefone, email, endereco, cidade, estado, limite_credito, status_cliente) VALUES
('João Silva', '111.111.111-11', 11987654321, 'joao.silva@email.com', 'Rua A, 123', 'São Paulo', 'SP', 5000.00, 'ativo'),
('Maria Oliveira', '222.222.222-22', 21987654322, 'maria.o@email.com', 'Av. B, 456', 'Rio de Janeiro', 'RJ', 7500.00, 'ativo'),
('Carlos Pereira ME', '33.333.333/0001-00', 31987654323, 'carlos.p@email.com', 'Rua C, 789', 'Belo Horizonte', 'MG', 10000.00, 'ativo'),
('Ana Costa', '444.444.444-44', 41987654324, 'ana.c@email.com', 'Av. D, 101', 'Curitiba', 'PR', 3000.00, 'ativo'),
('Pedro Almeida Ltda', '55.555.555/0001-00', 51987654325, 'pedro.a@email.com', 'Rua E, 202', 'Porto Alegre', 'RS', 12000.00, 'ativo');

-- 3. Fornecedores (mínimo 5) 
INSERT INTO fornecedor (nome, cpf_cnpj, telefone, email, endereco, cidade, estado, status_fornecedor) VALUES
('TechSuprimentos S.A.', '66.666.666/0001-00', 1130001000, 'contato@techsup.com', 'Rua F, 303', 'São Paulo', 'SP', 'ativo'),
('FoodGoods Ltda.', '77.777.777/0001-00', 2130001001, 'info@foodgoods.com', 'Av. G, 404', 'Rio de Janeiro', 'RJ', 'ativo'),
('Vestuário Moderno Eireli', '88.888.888/0001-00', 3130001002, 'vendas@modas.com', 'Rua H, 505', 'Belo Horizonte', 'MG', 'ativo'),
('Limpa Tudo Distribuidora', '99.999.999/0001-00', 4130001003, 'atendimento@limpatudo.com', 'Av. I, 606', 'Curitiba', 'PR', 'ativo'),
('Componentes Xpress', '10.000.000/0001-00', 1130001004, 'contato@compX.com', 'Rua J, 707', 'São Paulo', 'SP', 'ativo');

-- 4. Produtos (mínimo 5) 
INSERT INTO produto (codigo, descricao, preco_venda, preco_custo, estoque_atual, estoque_minimo, categoria_id, unidade_medida, status_produto) VALUES
('PROD001', 'Smartphone XYZ', 1500.00, 1000.00, 50, 10, 1, 'unidade', 'ativo'),
('PROD002', 'Arroz Integral 1kg', 8.50, 5.00, 200, 50, 2, 'kg', 'ativo'),
('PROD003', 'Camiseta Algodão M', 45.00, 25.00, 100, 20, 3, 'unidade', 'ativo'),
('PROD004', 'Detergente Concentrado 5L', 25.00, 15.00, 80, 15, 4, 'litro', 'ativo'),
('PROD005', 'Notebook Gamer ABC', 6000.00, 4500.00, 20, 5, 1, 'unidade', 'ativo');

-- 5. Funcionários (mínimo 3) 
INSERT INTO funcionario (nome, cpf, cargo, data_contratacao, salario, telefone, email, status_funcionario) VALUES
('Fernanda Lima', '123.456.789-00', 'Gerente de Vendas', '2020-01-15', 5500.00, 11991234567, 'fernanda.l@empresa.com', 'ativo'),
('Ricardo Santos', '987.654.321-00', 'Vendedor', '2021-03-01', 3200.00, 11991234568, 'ricardo.s@empresa.com', 'ativo'),
('Paula Mendes', '111.222.333-44', 'Estoquista', '2022-06-10', 2500.00, 11991234569, 'paula.m@empresa.com', 'ativo');

-- 6. Transportadoras (mínimo 2) 
INSERT INTO transportadora (nome, cnpj, telefone, email, status_transportadora) VALUES
('Logistica Rápida', '11.111.111/0001-00', 1120000000, 'contato@lograpida.com', 'ativo'),
('Entrega Certa S.A.', '22.222.222/0001-00', 2120000001, 'sac@entregacerta.com', 'ativo');

-- 7. Rotas (mínimo 3) 
INSERT INTO rota (nome, origem, destino, distancia_km, tempo_estimado, transportadora_id, status_rota) VALUES
('SP-RJ Express', 'São Paulo', 'Rio de Janeiro', 430.50, '06:00:00', 1, 'ativa'),
('SP-BH Padrão', 'São Paulo', 'Belo Horizonte', 580.00, '08:30:00', 1, 'ativa'),
('RJ-SP Noturna', 'Rio de Janeiro', 'São Paulo', 430.50, '07:00:00', 2, 'ativa');

-- INSERÇÃO DE DADOS COM DEPENDÊNCIAS
-- 8. Vendas (mínimo 5) 
INSERT INTO venda (data_venda, cliente_id, funcionario_id, valor_total, desconto, forma_pagamento, status_venda, observacao) VALUES
('2025-06-20', 1, 2, 0.00, 0.00, 'Cartão de Crédito', 'pendente', 'Primeira venda do cliente João Silva'),
('2025-06-21', 2, 1, 0.00, 0.00, 'Boleto', 'pendente', 'Venda para Maria Oliveira'),
('2025-06-22', 1, 2, 0.00, 0.00, 'Pix', 'pendente', 'Segunda venda do João Silva'),
('2025-06-23', 3, 2, 0.00, 0.00, 'Cartão de Débito', 'pendente', 'Venda para Carlos Pereira ME'),
('2025-06-24', 4, 1, 0.00, 0.00, 'Dinheiro', 'pendente', 'Venda para Ana Costa');

-- 9. Itens de Venda (mínimo 10) 
INSERT INTO item_venda (venda_id, produto_id, quantidade, preco_unitario, desconto, valor_total) VALUES
(1, 1, 1, 1500.00, 0.00, 1500.00), -- Smartphone XYZ para Venda 1
(1, 2, 5, 8.50, 0.00, 42.50),   -- Arroz Integral para Venda 1
(2, 3, 2, 45.00, 5.00, 85.00),   -- Camiseta para Venda 2
(2, 4, 1, 25.00, 0.00, 25.00),   -- Detergente para Venda 2
(3, 1, 1, 1500.00, 10.00, 1490.00), -- Smartphone XYZ para Venda 3 (com desconto)
(3, 5, 1, 6000.00, 0.00, 6000.00), -- Notebook Gamer para Venda 3
(4, 2, 10, 8.50, 0.00, 85.00),  -- Arroz para Venda 4
(4, 3, 3, 45.00, 0.00, 135.00), -- Camiseta para Venda 4
(5, 4, 2, 25.00, 0.00, 50.00),  -- Detergente para Venda 5
(5, 5, 1, 6000.00, 50.00, 5950.00); -- Notebook para Venda 5 (com desconto)

-- Atualizar valor_total em Venda após inserir itens de venda.
UPDATE venda SET valor_total = (SELECT SUM(valor_total) FROM item_venda WHERE venda_id = 1) WHERE venda_id = 1;
UPDATE venda SET valor_total = (SELECT SUM(valor_total) FROM item_venda WHERE venda_id = 2) WHERE venda_id = 2;
UPDATE venda SET valor_total = (SELECT SUM(valor_total) FROM item_venda WHERE venda_id = 3) WHERE venda_id = 3;
UPDATE venda SET valor_total = (SELECT SUM(valor_total) FROM item_venda WHERE venda_id = 4) WHERE venda_id = 4;
UPDATE venda SET valor_total = (SELECT SUM(valor_total) FROM item_venda WHERE venda_id = 5) WHERE venda_id = 5;


-- 10. Compras (mínimo 3) 
INSERT INTO compra (data_compra, fornecedor_id, funcionario_id, valor_total, status_compra, observacao) VALUES
('2025-06-15', 1, 3, 0.00, 'concluida', 'Compra de eletrônicos para estoque'),
('2025-06-16', 2, 3, 0.00, 'concluida', 'Reposição de estoque de alimentos'),
('2025-06-17', 5, 3, 0.00, 'pendente', 'Compra de componentes para novos produtos');

-- 11. Itens de Compra (mínimo 6) 
INSERT INTO item_compra (compra_id, produto_id, quantidade, preco_unitario, valor_total) VALUES
(1, 1, 10, 950.00, 9500.00),  -- Compra de Smartphone XYZ
(1, 5, 5, 4200.00, 21000.00), -- Compra de Notebook Gamer ABC
(2, 2, 100, 4.50, 450.00),   -- Compra de Arroz Integral
(2, 4, 50, 14.00, 700.00),   -- Compra de Detergente
(3, 1, 20, 980.00, 19600.00), -- Nova compra de Smartphone
(3, 3, 30, 22.00, 660.00);   -- Compra de Camiseta

-- Atualizar valor_total em Compra após inserir itens de compra.
UPDATE compra SET valor_total = (SELECT SUM(valor_total) FROM item_compra WHERE compra_id = 1) WHERE compra_id = 1;
UPDATE compra SET valor_total = (SELECT SUM(valor_total) FROM item_compra WHERE compra_id = 2) WHERE compra_id = 2;
UPDATE compra SET valor_total = (SELECT SUM(valor_total) FROM item_compra WHERE compra_id = 3) WHERE compra_id = 3;

-- 12. Produções (mínimo 3) 
INSERT INTO producao (data_inicio, data_fim, funcionario_id, status_producao, observacao) VALUES
('2025-06-01', '2025-06-10', 3, 'concluida', 'Lote 1 de montagem de eletrônicos'),
('2025-06-05', '2025-06-12', 3, 'concluida', 'Produção de camisetas para verão'),
('2025-06-10', '2025-06-20', 3, 'em andamento', 'Produção de detergente concentrado');

-- 13. Itens de Produção (mínimo 6) 
INSERT INTO item_producao (producao_id, produto_id, quantidade_planejada, quantidade_produzida, custo_unitario, valor_total) VALUES
(1, 1, 10, 10, 900.00, 9000.00),  -- Produção de 10 Smartphones
(1, 5, 5, 5, 4000.00, 20000.00), -- Produção de 5 Notebooks
(2, 3, 50, 50, 20.00, 1000.00),  -- Produção de 50 Camisetas
(2, 3, 20, 18, 20.00, 360.00),   -- Outra produção de camiseta (com perda)
(3, 4, 30, 0, 10.00, 0.00),    -- Produção de 30 Detergentes (ainda não produzidos)
(3, 2, 100, 0, 4.00, 0.00);    -- Produção de Arroz (ainda não iniciada a produção)


-- 14. Pedidos (mínimo 4) 
INSERT INTO pedido (data_pedido, cliente_id, funcionario_id, data_entrega_prevista, rota_id, valor_total, status_pedido, observacao) VALUES
('2025-06-20', 1, 2, '2025-06-25', 1, 0.00, 'processando', 'Pedido urgente do João Silva'),
('2025-06-21', 2, 1, '2025-06-26', 2, 0.00, 'processando', 'Pedido para Maria Oliveira via rota padrão'),
('2025-06-22', 3, 2, '2025-06-27', 1, 0.00, 'pendente', 'Pedido para Carlos Pereira ME'),
('2025-06-23', 4, 1, '2025-06-28', 3, 0.00, 'pendente', 'Pedido de Ana Costa para rota noturna');

-- 15. Itens de Pedido (mínimo 8) 
INSERT INTO item_pedido (pedido_id, produto_id, quantidade, preco_unitario, desconto, valor_total) VALUES
(1, 1, 1, 1500.00, 0.00, 1500.00), -- Pedido 1: Smartphone
(1, 2, 2, 8.50, 0.00, 17.00),    -- Pedido 1: Arroz
(2, 3, 5, 45.00, 2.00, 223.00),   -- Pedido 2: Camiseta
(2, 4, 1, 25.00, 0.00, 25.00),    -- Pedido 2: Detergente
(3, 5, 1, 6000.00, 100.00, 5900.00), -- Pedido 3: Notebook
(3, 1, 1, 1500.00, 0.00, 1500.00), -- Pedido 3: Smartphone
(4, 2, 10, 8.50, 0.00, 85.00),   -- Pedido 4: Arroz
(4, 4, 3, 25.00, 0.00, 75.00);   -- Pedido 4: Detergente

-- Atualizar valor_total em Pedido após inserir itens de pedido.
UPDATE pedido SET valor_total = (SELECT SUM(valor_total) FROM item_pedido WHERE pedido_id = 1) WHERE pedido_id = 1;
UPDATE pedido SET valor_total = (SELECT SUM(valor_total) FROM item_pedido WHERE pedido_id = 2) WHERE pedido_id = 2;
UPDATE pedido SET valor_total = (SELECT SUM(valor_total) FROM item_pedido WHERE pedido_id = 3) WHERE pedido_id = 3;
UPDATE pedido SET valor_total = (SELECT SUM(valor_total) FROM item_pedido WHERE pedido_id = 4) WHERE pedido_id = 4;

-- Adicona o campo email secundario na tabela Cliente
alter table cliente add column email_secundario varchar(30) default null;

-- Remove  a coluna observacao da tabela Compra
alter table compra drop column observacao;

-- Adiciona a coluna data_atualizacao na tabela Produto
alter table produto add column data_atualizacao date default(current_date);

-- CONSULTAS 
-- 1. Selecionar todos os clientes com status ‘ativo’.
select * from cliente where status_cliente = 'ativo';

-- 2. Listar produtos com estoque atual menor que o estoque mínimo.
select * from produto where estoque_atual < estoque_minimo;

-- 3. Exibir todas as vendas realizadas em uma data específica.
select * from venda where data_venda = '2025-06-20';

-- 4. Listar fornecedores da cidade de ‘São Paulo’.
select * from fornecedor where cidade = 'São Paulo';

-- 5. Selecionar funcionários com salário maior que R$ 3000.
select * from funcionario where (salario > 3000);

-- 6. Buscar produtos cadastrados após uma determinada data.
select * from produto where (data_cadastro > '2025-07-10');

-- 7. Exibir vendas com nome do cliente e nome do funcionário.
select v.venda_id, v.data_venda, v.valor_total, f.nome as nome_funcionario, c.nome as nome_cliente from venda v join funcionario 
f on v.funcionario_id = f.funcionario_id join cliente c on v.cliente_id = c.cliente_id;

-- 8. Listar produtos vendidos com descrição, quantidade e valor total.
select v.venda_id, p.descricao, iv.quantidade, iv.valor_total from item_venda iv join produto p on iv.produto_id = p.produto_id join venda v on iv.venda_id = v.venda_id;

-- 9. Mostrar compras com nome do fornecedor e funcionário responsável.
select c.compra_id, c.data_compra, c.status_compra, c.valor_total, fu.nome as nome_funcionario, fo.nome as nome_fornecedor from compra c 
join funcionario fu on fu.funcionario_id = c.funcionario_id join fornecedor fo on c.fornecedor_id = fo.fornecedor_id;

-- 10. Listar pedidos com data, cliente, rota e transportadora.
select p.pedido_id, p.data_pedido, p.data_entrega_prevista, c.nome as nome_cliente, r.nome as nome_rota, t.nome as nome_transportadora 
from pedido p join cliente c on p.cliente_id = c.cliente_id 
join rota r on p.rota_id = r.rota_id join transportadora t on t.transportadora_id = r.transportadora_id;

-- 11. Mostrar itens de pedido com nome do produto e valor total.
select ip.pedido_id, ip.item_pedido_id, p.descricao, ip.valor_total from item_pedido ip join produto p on ip.produto_id = p.produto_id order by ip.pedido_id;

-- 12. Consultar produções com o nome do funcionário e quantidade produzida.
select distinct p.producao_id, ip.item_producao_id, p.data_inicio, p.status_producao, fu.nome as nome_funcionario, ip.quantidade_produzida 
from producao p join funcionario fu on p.funcionario_id = fu.funcionario_id join item_producao ip on ip.producao_id = p.producao_id order by p.producao_id;

-- 13. Calcular o total de vendas por cliente.
select distinct c.cliente_id, c.nome, c.cpf_cnpj, count(v.venda_id) as vendas_por_cliente
 from cliente c join venda v on c.cliente_id = v.cliente_id group by c.cliente_id, c.nome, c.cpf_cnpj;

-- 14. Obter a média de salário por cargo dos funcionários.
 select fu.cargo, round(avg(fu.salario), 2) as media_salarial from funcionario fu group by fu.cargo;
 
-- 15. Mostrar a quantidade total vendida por produto.
select p.produto_id, p.descricao, sum(iv.quantidade) as quantidade_total_vendida from produto p 
join item_venda iv on iv.produto_id = p.produto_id group by p.produto_id, p.descricao;

-- 16. Calcular o total comprado por fornecedor.
select f.fornecedor_id, f.nome, sum(c.valor_total) as total_comprado from fornecedor f 
join compra c on f.fornecedor_id = c.fornecedor_id group by f.fornecedor_id, f.nome;

-- 17. Listar total de pedidos por cliente com mais de 3 pedidos.
select c.cliente_id, c.nome, c.cpf_cnpj, qtd_pedidos_cliente.total_pedidos from cliente c join 
(select p.cliente_id, count(p.pedido_id) as total_pedidos from pedido p group by p.cliente_id having count(p.pedido_id) > 3) 
as qtd_pedidos_cliente on c.cliente_id = qtd_pedidos_cliente.cliente_id;

-- 18. Exibir produtos com quantidade vendida maior que 100.
select pr.produto_id, pr.descricao, qtd_produtos_vendidas.qtd_vendida from produto pr join
(select iv.produto_id, sum(iv.quantidade) as qtd_vendida from item_venda iv group by iv.produto_id having sum(iv.quantidade) > 100) 
as qtd_produtos_vendidas on pr.produto_id = qtd_produtos_vendidas.produto_id;

-- 19. Mostrar total de vendas por mês e ano.
select year(v.data_venda) as ano, month(v.data_venda) as mes, sum(v.valor_total) as total_vendas 
from venda v group by year(v.data_venda), month(v.data_venda) order by ano, mes;

-- 20. Quantidade de produções concluídas por funcionário.
select f.funcionario_id, f.nome, count(pr.producao_id) as producoes_concluidas
from producao pr join funcionario f on pr.funcionario_id = f.funcionario_id 
where pr.status_producao = 'concluida' group by f.funcionario_id, f.nome having count(pr.producao_id);

-- 21. Número de rotas ativas por transportadora.
select t.transportadora_id, t.nome as nome_transportadora, count(r.rota_id) as rotas_ativas 
from rota r join transportadora t on t.transportadora_id = r.transportadora_id  
where r.status_rota = 'ativa' group by t.transportadora_id, t.nome having count(r.rota_id);

-- 22. Listar clientes que fizeram vendas acima da média.
select c.cliente_id, c.nome, soma_vendas.soma from cliente c join 
(select v.cliente_id, sum(v.valor_total) as soma from venda v group by v.cliente_id having sum(v.valor_total)) as soma_vendas
on c.cliente_id = soma_vendas.cliente_id where soma_vendas.soma > (select round(avg(valor_total), 2) from venda having avg(valor_total));

-- 23. Mostrar produtos cujo preço de venda é maior que a média.
select p.produto_id, p.descricao, p.preco_venda from produto p where p.preco_venda > 
(select round(avg(p.preco_venda), 2) from produto p having avg(p.preco_venda));

-- 24. Listar fornecedores que realizaram ao menos uma compra.
select f.fornecedor_id, f.nome, contagem.qtd_compras  from fornecedor f join
(select c.fornecedor_id, count(c.compra_id) as qtd_compras from compra c group by c.fornecedor_id having count(c.compra_id)) as contagem 
on f.fornecedor_id = contagem.fornecedor_id where contagem.qtd_compras >= 1;

-- 25. Selecionar clientes que não fizeram pedidos.
select cliente_id, nome, cpf_cnpj from cliente where cliente_id not in
(select cliente_id from pedido);

-- 26. Exibir produtos que nunca foram vendidos.
select * from produto where produto_id not in
(select produto_id from item_venda);

-- 27. Mostrar funcionários que realizaram pedidos, mas não vendas.
select * from funcionario where funcionario_id in
(select funcionario_id from pedido) and funcionario_id not in
(select funcionario_id from venda);

-- 28. Listar pedidos com valor acima da média dos pedidos.
select * from pedido p where p.valor_total >
(select round(avg(p.valor_total), 2) from pedido p having avg(p.valor_total));

-- 29. Mostrar clientes com limite de crédito maior que qualquer valor de pedido.
select * from cliente c where c.limite_credito >
(select max(valor_total) from pedido having max(valor_total));

-- 30. Exibir produtos com custo unitário acima da média da produção.
select * from produto where preco_custo >
(select round(avg(custo_unitario), 2) from item_producao having avg(custo_unitario));

-- 31. Clientes que possuem pedidos em mais de uma rota diferente.
select c.cliente_id, c.nome, contagem.qtd_rotas from cliente c join
(select p.cliente_id, count(p.rota_id) as qtd_rotas from pedido p group by p.cliente_id having count(p.rota_id))
as contagem on contagem.cliente_id = c.cliente_id where contagem.qtd_rotas > 1;

SET SQL_SAFE_UPDATES = 0;
-- 32. Aumentar em 10% o limite de crédito de todos os clientes ativos.
update cliente set limite_credito = limite_credito*1.1 where status_cliente = 'ativo';

-- 33. Atualizar o status de produtos com estoque zerado para 'inativo'.
update produto set status_produto = 'inativo' where estoque_atual = 0;

-- 34. Alterar o salário dos funcionários do cargo ‘vendedor’ em +5%.
update funcionario set salario = salario*1.05 where cargo = 'Vendedor';

-- 35. Atualizar o tempo estimado das rotas com distância maior que 300 km.
update rota set tempo_estimado = addtime(tempo_estimado, '00:30:00') where distancia_km > 300;

-- 36. Excluir clientes com status ‘inativo’ e cadastrados há mais de 2 anos.
delete from cliente where status_cliente = 'inativo' and data_cadastro < date_sub(current_date(), interval 2 year); 

-- 37. Remover produtos que não foram vendidos nem comprados.
delete from produto where produto_id not in
(select produto_id from item_venda) and produto_id not in
(select produto_id from item_compra);

-- 38. Apagar pedidos com status ‘cancelado’.
delete from pedido where status_pedido = 'cancelado';

-- 39. Excluir produções com status 'cancelado' e sem itens produzidos.
delete from item_producao where producao_id in
(select producao_id from
(select ip_sub.producao_id from item_producao ip_sub group by ip_sub.producao_id 
having sum(ip_sub.quantidade_produzida) = 0)
as producoes_sem_itens where producao_id in 
(select p.producao_id from producao p where p.status_producao = 'cancelado'));

delete from producao where status_producao = 'cancelado' and producao_id in
(select ip.producao_id from item_producao ip group by ip.producao_id having sum(quantidade_produzida) = 0);

-- 40. Remover transportadoras sem rotas vinculadas.
delete from transportadora where transportadora_id not in
(select transportadora_id from rota);

-- 41. Mostrar total vendido por cliente, produto e funcionário.
select c.cliente_id, c.nome AS nome_cliente, f.funcionario_id, f.nome as nome_funcionario, p.produto_id, p.descricao as nome_produto,
SUM(iv.quantidade*iv.preco_unitario) AS valor_total_vendido_combinado
from venda v join cliente c on v.cliente_id = c.cliente_id join funcionario f on v.funcionario_id = f.funcionario_id join
item_venda as iv on v.venda_id = iv.venda_id join produto p on iv.produto_id = p.produto_id
group by c.cliente_id , c.nome , f.funcionario_id , f.nome , p.produto_id , p.descricao
order by nome_cliente , nome_funcionario , nome_produto;

-- 42. Exibir produtos com maior valor de venda por categoria.
select pr.produto_id, pr.categoria_id, pr.codigo, pr.descricao, pr.preco_venda from produto pr join
(select p.categoria_id, max(p.preco_venda) as maximo from produto p group by p.categoria_id 
having max(p.preco_venda)) as produtos_maior_valor on produtos_maior_valor.categoria_id = pr.categoria_id 
where pr.preco_venda = produtos_maior_valor.maximo;

-- 43. Listar funcionários que participaram de vendas, compras e produções.
select * from funcionario where funcionario_id in
(select distinct funcionario_id from venda) and funcionario_id =
(select distinct funcionario_id from compra) and funcionario_id =
(select distinct funcionario_id from producao);

-- 44. Exibir transportadoras com mais pedidos entregues.
select t.transportadora_id, nome, cnpj, telefone, email, qtd_pedidos_entregues.pedidos_entregues from transportadora t join
(select ro.transportadora_id, sum(qtd.qtd_pedidos) as pedidos_entregues from rota ro join
(select rota_id, count(pedido_id) as qtd_pedidos from pedido  group by rota_id having count(pedido_id)) as qtd
on qtd.rota_id = ro.rota_id group by transportadora_id having sum(qtd.qtd_pedidos)) as qtd_pedidos_entregues 
on qtd_pedidos_entregues.transportadora_id = t.transportadora_id order by t.transportadora_id;

-- 45. Total de vendas por estado, agrupado por cidade.
select c.estado, c.cidade, count(v.venda_id) as quantidade_vendas 
from venda v join cliente c on v.cliente_id = c.cliente_id 
group by c.estado, c.cidade having count(v.venda_id) order by c.estado, c.cidade;

-- 46. Clientes que compraram produtos acima do custo médio.
select distinct c.cliente_id, c.nome, c.cpf_cnpj, iv.preco_unitario from cliente c 
join venda v on c.cliente_id = v.cliente_id join item_venda iv on iv.venda_id = v.venda_id
join produto p on p.produto_id = iv.produto_id
where iv.preco_unitario > (select avg(preco_custo) from produto);

-- 47. Produtos mais vendidos por transportadora.
WITH VendasPorTransportadoraProduto AS (SELECT t.transportadora_id, t.nome AS nome_transportadora, p.produto_id, p.descricao AS nome_produto, SUM(ip.quantidade) AS total_quantidade_vendida
FROM transportadora AS t JOIN rota AS r ON t.transportadora_id = r.transportadora_id
JOIN pedido AS ped ON r.rota_id = ped.rota_id JOIN item_pedido AS ip ON ped.pedido_id = ip.pedido_id JOIN produto AS p ON ip.produto_id = p.produto_id
GROUP BY t.transportadora_id, t.nome, p.produto_id, p.descricao)
SELECT RankedSales.nome_transportadora, RankedSales.nome_produto, RankedSales.total_quantidade_vendida
FROM (SELECT *, RANK() OVER (PARTITION BY transportadora_id ORDER BY total_quantidade_vendida DESC) AS rank_venda
FROM VendasPorTransportadoraProduto) AS RankedSales
WHERE RankedSales.rank_venda = 1 ORDER BY RankedSales.nome_transportadora, RankedSales.total_quantidade_vendida DESC;

-- 48. Pedidos com itens cujo valor total excede a média do pedido.
select distinct p.pedido_id, p.data_pedido, p.valor_total from pedido p join item_pedido ip on ip.pedido_id = p.pedido_id where ip.valor_total > 
(select avg(sub_ip.valor_total) from item_pedido sub_ip where sub_ip.pedido_id = ip.pedido_id);

-- 49. Produções com custo total maior que R$ 10.000, por funcionário.
select f.funcionario_id, f.nome, f.cpf, pr.producao_id, tabela_temp.custo_total from funcionario f join producao pr on pr.funcionario_id = f.funcionario_id join
(select cp.producao_id, max(cp.custo_producao) as custo_total from
(select producao_id, sum(valor_total) custo_producao from item_producao group by producao_id) as cp
group by cp.producao_id having max(cp.custo_producao) > 10000) as tabela_temp on tabela_temp.producao_id = pr.producao_id;

-- 50. Listar clientes que fizeram pedidos com mais de 3 produtos diferentes e valor total acima da média.
select distinct c.cliente_id, c.nome, c.cpf_cnpj from cliente c join pedido p on p.cliente_id = c.cliente_id join 
(select distinct pedido_id, count( distinct produto_id) as qtd_produtos_diferentes from item_pedido group by 
pedido_id having count(distinct produto_id) > 3) as qtd_produtos_por_pedido on p.pedido_id = qtd_produtos_por_pedido.pedido_id
where p.valor_total > (select avg(valor_total) from pedido);

SET SQL_SAFE_UPDATES = 1;






