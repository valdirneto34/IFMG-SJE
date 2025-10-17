drop database if exists loja_do_Valdir;
create database loja_do_Valdir;
use loja_do_Valdir;

-- Tabela de Clientes
CREATE TABLE clientes (
    id_cliente INT PRIMARY KEY,
    nome VARCHAR(255) NOT NULL,
    idade INT,
    data_cadastro DATE NOT NULL
);

-- Tabela de Produtos
CREATE TABLE produtos (
    id_produto INT PRIMARY KEY,
    nome_produto VARCHAR(255) NOT NULL,
    categoria VARCHAR(50),
    preco DECIMAL(10, 2)
);

-- Tabela de Vendas
CREATE TABLE vendas (
    id_venda INT PRIMARY KEY,
    id_cliente INT,
    id_produto INT,
    data_venda DATE,
    quantidade INT,
    FOREIGN KEY (id_cliente) REFERENCES clientes(id_cliente),
    FOREIGN KEY (id_produto) REFERENCES produtos(id_produto)
);

INSERT INTO clientes (id_cliente, nome, idade, data_cadastro) VALUES
(1, 'João da Silva', 32, '2024-01-20'),
(2, 'Maria Souza', 45, '2023-05-10'),
(3, 'Pedro Santos', 16, '2024-03-05'),
(4, 'Ana Oliveira', 28, '2022-11-12'),
(5, 'Carlos Pereira', 65, '2023-09-01'),
(6, 'Mariana Costa', 19, '2024-02-28'),
(7, 'Fernando Alves', 58, '2023-07-15'),
(8, 'Juliana Dias', 30, '2024-04-10'),
(9, 'Roberto Gomes', 22, '2023-12-25'),
(10, 'Patrícia Martins', 50, '2022-08-08'),
(11, 'Lucas Lima', 27, '2024-01-01'),
(12, 'Sandra Fernandes', 71, '2023-06-30'),
(13, 'Gustavo Ribeiro', 39, '2022-09-17'),
(14, 'Amanda Rocha', 24, '2024-05-20'),
(15, 'Daniel Pires', 60, '2023-03-22'),
(16, 'Larissa Castro', 35, '2024-02-14'),
(17, 'Ricardo Vieira', 48, '2023-10-05'),
(18, 'Beatriz Cardoso', 17, '2024-01-30'),
(19, 'Paulo Almeida', 53, '2022-12-19'),
(20, 'Carolina Ferreira', 29, '2023-04-18');

INSERT INTO produtos (id_produto, nome_produto, categoria, preco) VALUES
(1, 'Notebook Gamer', 'Eletrônicos', 7500.00),
(2, 'Smart TV 55"', 'Eletrônicos', 3200.00),
(3, 'Fone de Ouvido Bluetooth', 'Eletrônicos', 450.00),
(4, 'Mouse sem Fio', 'Eletrônicos', 120.50),
(5, 'Teclado Mecânico', 'Eletrônicos', 300.00),
(6, 'Kindle Paperwhite', 'Eletrônicos', 500.00),
(7, 'Câmera DSLR', 'Eletrônicos', 4000.00),
(8, 'Relógio Inteligente', 'Eletrônicos', 800.00),
(9, 'Mochila para Notebook', 'Acessórios', 150.00),
(10, 'Impressora Multifuncional', 'Eletrônicos', 650.00),
(11, 'Camisa Social Masculina', 'Vestuário', 110.00),
(12, 'Calça Jeans Slim Fit', 'Vestuário', 150.00),
(13, 'Vestido de Festa', 'Vestuário', 280.00),
(14, 'Tênis Esportivo', 'Vestuário', 350.00),
(15, 'Blusa de Lã', 'Vestuário', 95.00),
(16, 'Jaqueta de Couro', 'Vestuário', 450.00),
(17, 'Bermuda Casual', 'Vestuário', 80.00),
(18, 'Saia Plissada', 'Vestuário', 130.00),
(19, 'Óculos de Sol', 'Acessórios', 200.00),
(20, 'Cinto de Couro', 'Acessórios', 60.00),
(21, 'O Hobbit', 'Livros', 45.00),
(22, '1984', 'Livros', 35.00),
(23, 'O Poder do Hábito', 'Livros', 55.00),
(24, 'A Arte da Guerra', 'Livros', 25.00),
(25, 'O Pequeno Príncipe', 'Livros', 20.00),
(26, 'Dom Quixote', 'Livros', 60.00),
(27, 'Cem Anos de Solidão', 'Livros', 70.00),
(28, 'Box Harry Potter', 'Livros', 250.00),
(29, 'O Alquimista', 'Livros', 40.00),
(30, 'Cozinha Italiana', 'Livros', 85.00),
(31, 'Kit de Panelas', 'Casa e Cozinha', 300.00),
(32, 'Liquidificador', 'Casa e Cozinha', 150.00),
(33, 'Jogo de Taças', 'Casa e Cozinha', 90.00),
(34, 'Escova de Dentes Elétrica', 'Saúde e Beleza', 120.00),
(35, 'Kit de Maquiagem', 'Saúde e Beleza', 250.00),
(36, 'Perfume Masculino', 'Saúde e Beleza', 180.00),
(37, 'Barra de Proteína', 'Alimentos e Suplementos', 8.50),
(38, 'Creatina', 'Alimentos e Suplementos', 75.00),
(39, 'Whey Protein', 'Alimentos e Suplementos', 150.00),
(40, 'Mesa de Escritório', 'Móveis', 500.00),
(41, 'Cadeira Ergonômica', 'Móveis', 700.00),
(42, 'Luminária de Mesa', 'Decoração', 80.00),
(43, 'Quadro Abstrato', 'Decoração', 150.00),
(44, 'Tapete', 'Decoração', 220.00),
(45, 'Jogo de Ferramentas', 'Ferramentas', 180.00),
(46, 'Furadeira Elétrica', 'Ferramentas', 250.00),
(47, 'Caixa de Som Portátil', 'Eletrônicos', 250.00),
(48, 'Controle de Videogame', 'Eletrônicos', 300.00),
(49, 'Copo Térmico', 'Acessórios', 65.00),
(50, 'Coleira para Cachorro', 'Pet Shop', 40.00);

INSERT INTO vendas (id_venda, id_cliente, id_produto, data_venda, quantidade) VALUES
(1, 1, 1, '2024-02-15', 1),
(2, 2, 12, '2023-06-01', 2),
(3, 3, 21, '2024-03-10', 1),
(4, 4, 3, '2023-01-25', 1),
(5, 5, 2, '2023-10-05', 1),
(6, 6, 11, '2024-03-01', 3),
(7, 7, 23, '2023-08-01', 1),
(8, 8, 4, '2024-04-12', 2),
(9, 9, 22, '2024-01-01', 1),
(10, 10, 13, '2022-09-10', 1),
(11, 11, 5, '2024-01-05', 1),
(12, 12, 24, '2023-07-02', 2),
(13, 13, 14, '2022-10-20', 1),
(14, 14, 6, '2024-06-01', 1),
(15, 15, 25, '2023-04-01', 1),
(16, 16, 16, '2024-03-01', 1),
(17, 17, 7, '2023-11-15', 1),
(18, 18, 26, '2024-02-05', 1),
(19, 19, 17, '2023-01-01', 2),
(20, 20, 8, '2023-05-20', 1),
(21, 1, 9, '2024-02-16', 1),
(22, 2, 1, '2023-06-05', 1),
(23, 3, 27, '2024-03-11', 1),
(24, 4, 10, '2023-01-28', 1),
(25, 5, 11, '2023-10-10', 2),
(26, 6, 2, '2024-03-05', 1),
(27, 7, 28, '2023-08-05', 1),
(28, 8, 12, '2024-04-15', 1),
(29, 9, 13, '2024-01-02', 1),
(30, 10, 3, '2022-09-15', 1),
(31, 11, 14, '2024-01-08', 1),
(32, 12, 29, '2023-07-05', 1),
(33, 13, 15, '2022-10-25', 1),
(34, 14, 16, '2024-06-03', 1),
(35, 15, 30, '2023-04-05', 1),
(36, 16, 17, '2024-03-03', 2),
(37, 17, 4, '2023-11-20', 1),
(38, 18, 18, '2024-02-10', 1),
(39, 19, 31, '2023-01-05', 1),
(40, 20, 19, '2023-05-25', 1),
(41, 1, 20, '2024-02-18', 1),
(42, 2, 21, '2023-06-10', 1),
(43, 3, 32, '2024-03-12', 1),
(44, 4, 2, '2023-02-01', 1),
(45, 5, 33, '2023-10-15', 1),
(46, 6, 22, '2024-03-10', 1),
(47, 7, 34, '2023-08-10', 1),
(48, 8, 23, '2024-04-18', 1),
(49, 9, 35, '2024-01-05', 1),
(50, 10, 24, '2022-09-20', 1),
(51, 11, 36, '2024-01-10', 1),
(52, 12, 25, '2023-07-10', 1),
(53, 13, 37, '2022-10-30', 1),
(54, 14, 26, '2024-06-05', 1),
(55, 15, 38, '2023-04-10', 1),
(56, 16, 27, '2024-03-05', 1),
(57, 17, 39, '2023-11-25', 1),
(58, 18, 28, '2024-02-15', 1),
(59, 19, 40, '2023-01-10', 1),
(60, 20, 29, '2023-05-30', 1),
(61, 1, 30, '2024-02-20', 1),
(62, 2, 31, '2023-06-15', 1),
(63, 3, 32, '2024-03-15', 1),
(64, 4, 33, '2023-02-05', 1),
(65, 5, 34, '2023-10-20', 1),
(66, 6, 35, '2024-03-12', 1),
(67, 7, 36, '2023-08-15', 1),
(68, 8, 37, '2024-04-20', 1),
(69, 9, 38, '2024-01-08', 1),
(70, 10, 39, '2022-09-25', 1),
(71, 11, 40, '2024-01-12', 1),
(72, 12, 41, '2023-07-15', 1),
(73, 13, 42, '2022-11-05', 1),
(74, 14, 43, '2024-06-07', 1),
(75, 15, 44, '2023-04-15', 1),
(76, 16, 45, '2024-03-08', 1),
(77, 17, 46, '2023-11-30', 1),
(78, 18, 47, '2024-02-20', 1),
(79, 19, 48, '2023-01-15', 1),
(80, 20, 49, '2023-06-01', 1),
(81, 1, 50, '2024-02-22', 1),
(82, 2, 1, '2023-06-20', 1),
(83, 3, 2, '2024-03-18', 1),
(84, 4, 3, '2023-02-10', 1),
(85, 5, 4, '2023-10-25', 1),
(86, 6, 5, '2024-03-15', 1),
(87, 7, 6, '2023-08-20', 1),
(88, 8, 7, '2024-04-22', 1),
(89, 9, 8, '2024-01-10', 1),
(90, 10, 9, '2022-09-30', 1),
(91, 11, 10, '2024-01-15', 1),
(92, 12, 11, '2023-07-20', 1),
(93, 13, 12, '2022-11-10', 1),
(94, 14, 13, '2024-06-10', 1),
(95, 15, 14, '2023-04-20', 1),
(96, 16, 15, '2024-03-10', 1),
(97, 17, 16, '2023-12-05', 1),
(98, 18, 17, '2024-02-25', 1),
(99, 19, 18, '2023-01-20', 1),
(100, 20, 19, '2023-06-05', 1),
(101, 1, 20, '2024-02-25', 1),
(102, 2, 21, '2023-06-25', 1),
(103, 3, 22, '2024-03-20', 1),
(104, 4, 23, '2023-02-15', 1),
(105, 5, 24, '2023-10-30', 1),
(106, 6, 25, '2024-03-18', 1),
(107, 7, 26, '2023-08-25', 1),
(108, 8, 27, '2024-04-25', 1),
(109, 9, 28, '2024-01-12', 1),
(110, 10, 29, '2022-10-05', 1),
(111, 11, 30, '2024-01-18', 1),
(112, 12, 31, '2023-07-25', 1),
(113, 13, 32, '2022-11-15', 1),
(114, 14, 33, '2024-06-12', 1),
(115, 15, 34, '2023-04-25', 1),
(116, 16, 35, '2024-03-12', 1),
(117, 17, 36, '2023-12-10', 1),
(118, 18, 37, '2024-02-28', 1),
(119, 19, 38, '2023-01-25', 1),
(120, 20, 39, '2023-06-10', 1),
(121, 1, 40, '2024-03-01', 1),
(122, 2, 41, '2023-06-30', 1),
(123, 3, 42, '2024-03-25', 1),
(124, 4, 43, '2023-02-20', 1),
(125, 5, 44, '2023-11-05', 1),
(126, 6, 45, '2024-03-20', 1),
(127, 7, 46, '2023-08-30', 1),
(128, 8, 47, '2024-04-28', 1),
(129, 9, 48, '2024-01-15', 1),
(130, 10, 49, '2022-10-10', 1),
(131, 11, 50, '2024-01-20', 1),
(132, 12, 1, '2023-07-30', 1),
(133, 13, 2, '2022-11-20', 1),
(134, 14, 3, '2024-06-15', 1),
(135, 15, 4, '2023-04-30', 1),
(136, 16, 5, '2024-03-15', 1),
(137, 17, 6, '2023-12-15', 1),
(138, 18, 7, '2024-03-01', 1),
(139, 19, 8, '2023-01-30', 1),
(140, 20, 9, '2023-06-15', 1),
(141, 1, 10, '2024-03-05', 1),
(142, 2, 11, '2023-07-05', 1),
(143, 3, 12, '2024-03-28', 1),
(144, 4, 13, '2023-02-25', 1),
(145, 5, 14, '2023-11-10', 1),
(146, 6, 15, '2024-03-22', 1),
(147, 7, 16, '2023-09-05', 1),
(148, 8, 17, '2024-05-01', 1),
(149, 9, 18, '2024-01-18', 1),
(150, 10, 19, '2022-10-15', 1),
(151, 11, 20, '2024-01-22', 1),
(152, 12, 21, '2023-08-05', 1),
(153, 13, 22, '2022-11-25', 1),
(154, 14, 23, '2024-06-18', 1),
(155, 15, 24, '2023-05-05', 1),
(156, 16, 25, '2024-03-18', 1),
(157, 17, 26, '2023-12-20', 1),
(158, 18, 27, '2024-03-05', 1),
(159, 19, 28, '2023-02-01', 1),
(160, 20, 29, '2023-06-20', 1),
(161, 1, 30, '2024-03-08', 1),
(162, 2, 31, '2023-07-10', 1),
(163, 3, 32, '2024-03-30', 1),
(164, 4, 33, '2023-03-01', 1),
(165, 5, 34, '2023-11-15', 1),
(166, 6, 35, '2024-03-25', 1),
(167, 7, 36, '2023-09-10', 1),
(168, 8, 37, '2024-05-05', 1),
(169, 9, 38, '2024-01-20', 1),
(170, 10, 39, '2022-10-20', 1),
(171, 11, 40, '2024-01-25', 1),
(172, 12, 41, '2023-08-10', 1),
(173, 13, 42, '2022-11-30', 1),
(174, 14, 43, '2024-06-20', 1),
(175, 15, 44, '2023-05-10', 1),
(176, 16, 45, '2024-03-20', 1),
(177, 17, 46, '2023-12-25', 1),
(178, 18, 47, '2024-03-10', 1),
(179, 19, 48, '2023-02-05', 1),
(180, 20, 49, '2023-06-25', 1),
(181, 1, 50, '2024-03-10', 1),
(182, 2, 1, '2023-07-15', 1),
(183, 3, 2, '2024-04-01', 1),
(184, 4, 3, '2023-03-05', 1),
(185, 5, 4, '2023-11-20', 1),
(186, 6, 5, '2024-03-28', 1),
(187, 7, 6, '2023-09-15', 1),
(188, 8, 7, '2024-05-08', 1),
(189, 9, 8, '2024-01-22', 1),
(190, 10, 9, '2022-10-25', 1),
(191, 11, 10, '2024-01-28', 1),
(192, 12, 11, '2023-08-15', 1),
(193, 13, 12, '2022-12-05', 1),
(194, 14, 13, '2024-06-22', 1),
(195, 15, 14, '2023-05-15', 1),
(196, 16, 15, '2024-03-22', 1),
(197, 17, 16, '2023-12-30', 1),
(198, 18, 17, '2024-03-15', 1),
(199, 19, 18, '2023-02-10', 1),
(200, 20, 19, '2023-06-30', 1),
(201, 1, 20, '2024-03-12', 1),
(202, 2, 21, '2023-07-20', 1),
(203, 3, 22, '2024-04-05', 1),
(204, 4, 23, '2023-03-10', 1),
(205, 5, 24, '2023-11-25', 1),
(206, 6, 25, '2024-03-30', 1),
(207, 7, 26, '2023-09-20', 1),
(208, 8, 27, '2024-05-10', 1),
(209, 9, 28, '2024-01-25', 1),
(210, 10, 29, '2022-10-30', 1),
(211, 11, 30, '2024-01-30', 1),
(212, 12, 31, '2023-08-20', 1),
(213, 13, 32, '2022-12-10', 1),
(214, 14, 33, '2024-06-25', 1),
(215, 15, 34, '2023-05-20', 1),
(216, 16, 35, '2024-03-25', 1),
(217, 17, 36, '2024-01-05', 1),
(218, 18, 37, '2024-03-18', 1),
(219, 19, 38, '2023-02-15', 1),
(220, 20, 39, '2023-07-05', 1),
(221, 1, 40, '2024-03-15', 1),
(222, 2, 41, '2023-07-25', 1),
(223, 3, 42, '2024-04-08', 1),
(224, 4, 43, '2023-03-15', 1),
(225, 5, 44, '2023-11-30', 1),
(226, 6, 45, '2024-04-01', 1),
(227, 7, 46, '2023-09-25', 1),
(228, 8, 47, '2024-05-12', 1),
(229, 9, 48, '2024-01-28', 1),
(230, 10, 49, '2022-11-05', 1),
(231, 11, 50, '2024-02-01', 1),
(232, 12, 1, '2023-08-25', 1),
(233, 13, 2, '2022-12-15', 1),
(234, 14, 3, '2024-06-28', 1),
(235, 15, 4, '2023-05-25', 1),
(236, 16, 5, '2024-03-28', 1),
(237, 17, 6, '2024-01-10', 1),
(238, 18, 7, '2024-03-20', 1),
(239, 19, 8, '2023-02-20', 1),
(240, 20, 9, '2023-07-10', 1),
(241, 1, 10, '2024-03-18', 1),
(242, 2, 11, '2023-07-30', 1),
(243, 3, 12, '2024-04-10', 1),
(244, 4, 13, '2023-03-20', 1),
(245, 5, 14, '2023-12-05', 1),
(246, 6, 15, '2024-04-05', 1),
(247, 7, 16, '2023-09-30', 1),
(248, 8, 17, '2024-05-15', 1),
(249, 9, 18, '2024-01-30', 1),
(250, 10, 19, '2022-11-10', 1),
(251, 11, 20, '2024-02-05', 1),
(252, 12, 21, '2023-08-30', 1),
(253, 13, 22, '2022-12-20', 1),
(254, 14, 23, '2024-07-01', 1),
(255, 15, 24, '2023-05-30', 1),
(256, 16, 25, '2024-03-30', 1),
(257, 17, 26, '2024-01-15', 1),
(258, 18, 27, '2024-03-22', 1),
(259, 19, 28, '2023-02-25', 1),
(260, 20, 29, '2023-07-15', 1),
(261, 1, 30, '2024-03-20', 1),
(262, 2, 31, '2023-08-05', 1),
(263, 3, 32, '2024-04-12', 1),
(264, 4, 33, '2023-03-25', 1),
(265, 5, 34, '2023-12-10', 1),
(266, 6, 35, '2024-04-08', 1),
(267, 7, 36, '2023-10-05', 1),
(268, 8, 37, '2024-05-18', 1),
(269, 9, 38, '2024-02-01', 1),
(270, 10, 39, '2022-11-15', 1),
(271, 11, 40, '2024-02-10', 1),
(272, 12, 41, '2023-09-05', 1),
(273, 13, 42, '2022-12-25', 1),
(274, 14, 43, '2024-07-05', 1),
(275, 15, 44, '2023-06-01', 1),
(276, 16, 45, '2024-04-01', 1),
(277, 17, 46, '2024-01-20', 1),
(278, 18, 47, '2024-03-25', 1),
(279, 19, 48, '2023-03-01', 1),
(280, 20, 49, '2023-07-20', 1),
(281, 1, 50, '2024-03-22', 1),
(282, 2, 1, '2023-08-10', 1),
(283, 3, 2, '2024-04-15', 1),
(284, 4, 3, '2023-03-30', 1),
(285, 5, 4, '2023-12-15', 1),
(286, 6, 5, '2024-04-10', 1),
(287, 7, 6, '2023-10-10', 1),
(288, 8, 7, '2024-05-20', 1),
(289, 9, 8, '2024-02-05', 1),
(290, 10, 9, '2022-11-20', 1),
(291, 11, 10, '2024-02-12', 1),
(292, 12, 11, '2023-09-10', 1),
(293, 13, 12, '2022-12-30', 1),
(294, 14, 13, '2024-07-08', 1),
(295, 15, 14, '2023-06-05', 1),
(296, 16, 15, '2024-04-05', 1),
(297, 17, 16, '2024-01-25', 1),
(298, 18, 17, '2024-03-28', 1),
(299, 19, 18, '2023-03-05', 1),
(300, 20, 19, '2023-07-25', 1);

/*1. Idade dos clientes
Crie uma consulta que retorne os seguintes dados da tabela clientes: nome, idade e uma coluna
chamada faixa_etaria, que deve categorizar os clientes da seguinte forma:
a) Menor: Para clientes com idade abaixo de 18 anos.
b) Adulto: Para clientes com idade entre 18 e 59 anos.
c) Idoso: Para clientes com idade igual ou superior a 60 anos.
Utilize a expressão CASE WHEN THEN para criar a coluna faixa_etaria.*/

select nome, idade as nome_completo,
case when idade < 18 then 'Menor'
when idade between 18 and 59 then 'Adulto'
else 'Idoso'
end as faixa_etaria from clientes;
 
 /*2. Data de cadastro e status do cliente
Crie uma consulta que retorne nome, data_cadastro e uma coluna chamada status_cliente, que
deve indicar se o cliente é “Novo” ou “Antigo”:
a) Novo: Clientes cadastrados nos últimos 6 meses.
b) Antigo: Clientes cadastrados há mais de 6 meses.
Use a função DATEDIFF e um IF para determinar o status do cliente.*/

select nome, data_cadastro, if(datediff(now(), data_cadastro) <= 180,'Novo','Antigo') as status_cliente from clientes;
 
/*3. Valor total da venda com desconto
Crie uma consulta que mostre o id_venda, id_cliente, id_produto, quantidade, preco do produto
e uma coluna chamada valor_total_com_desconto, que deve calcular o valor total da venda
aplicando um desconto baseado na categoria do produto. Aplique o desconto da seguinte forma:
a) Eletrônicos: 10% de desconto.
b) Vestuário: 15% de desconto.
c) Livros: Sem desconto.
d) Caso o produto pertença a outra categoria, aplique 5% de desconto.
Use CASE WHEN THEN para definir o valor do desconto com base na categoria do produto.*/
 
select v.id_venda, c.id_cliente, v.id_produto, v.quantidade, p.preco, (v.quantidade*p.preco) as valor_sem_desconto,
case when p.categoria = 'Eletrônicos' then round((v.quantidade*p.preco*0.9), 2)
when p.categoria = 'Vestuário' then round((v.quantidade*p.preco*0.85), 2)
when p.categoria = 'Livros' then round((v.quantidade*p.preco), 2)
else round((v.quantidade*p.preco*0.95), 2)
end as valor_com_desconto
from vendas v join clientes c on c.id_cliente = v.id_cliente join produtos p on p.id_produto = v.id_produto order by v.id_venda;

/*4. Resumo das vendas por categoria Crie uma consulta para gerar um resumo das vendas por
categoria. A consulta deve mostrar a categoria do produto, o total_vendas (quantidade total de
itens vendidos para essa categoria), o valor_total_vendas (soma do valor total para todas as
vendas dessa categoria após o desconto) e uma coluna chamada classificacao_vendas, que deve
categorizar a venda conforme o valor total:
a) Alta: para valores totais acima de 10.000.
b) Média: para valores entre 5.000 e 10.000.
c) Baixa: para valores abaixo de 5.000.
Use SUM, CASE WHEN THEN e operadores de comparação para criar a coluna classificacao_vendas.*/
 
select p.categoria, sum(v.quantidade) as total_vendas, 
sum(
case when p.categoria = 'Eletrônicos' then v.quantidade * p.preco * 0.90
when p.categoria = 'Vestuário' then v.quantidade * p.preco * 0.85
when p.categoria = 'Livros' then v.quantidade * p.preco
else v.quantidade * p.preco * 0.95
end) as valor_total_vendas,
case when sum(case when p.categoria = 'Eletrônicos' then v.quantidade * p.preco * 0.90
when p.categoria = 'Vestuário' then v.quantidade * p.preco * 0.85
when p.categoria = 'Livros' then v.quantidade * p.preco
else v.quantidade * p.preco * 0.95
end) > 10000 then 'Alta' -- Classifica como 'Alta' se o valor total for acima de 10.000
when sum(case when p.categoria = 'Eletrônicos' then v.quantidade * p.preco * 0.90
when p.categoria = 'Vestuário' then v.quantidade * p.preco * 0.85
when p.categoria = 'Livros' then v.quantidade * p.preco
else v.quantidade * p.preco * 0.95
end) between 5000 and 10000 then 'Média' -- Classifica como 'Média' se o valor for entre 5.000 e 10.000
else 'Baixa' -- Classifica como 'Baixa' se o valor for abaixo de 5.000
end as classificacao_vendas
 from produtos p join vendas v on p.id_produto = v.id_produto group by p.categoria order by p.categoria;


/*5. Clientes frequentes
Crie uma consulta que identifique os clientes mais frequentes (aqueles que fizeram mais de 5
compras) e os categorize como “Frequente” ou “Infrequente” na coluna frequência:
a) Frequente: Clientes que realizaram mais de 5 compras.
b) Infrequente: Clientes com 5 compras ou menos.
Utilize COUNT, GROUP BY e CASE WHEN THEN para essa categorização.*/

select c.id_cliente, c.nome,
case when count(v.id_cliente) > 5 then 'Frequente'
else 'Infrequente' end as frequencia
from clientes c join vendas v on c.id_cliente = v.id_cliente group by c.id_cliente, c.nome;

/*6. Calcular total compras
Crie uma função chamada calcular_total_compras que receba o id_cliente e retorne o valor total
gasto por esse cliente em todas as compras realizadas.
a) A função deve fazer a soma de (preco * quantidade) para cada venda feita pelo cliente.
b) A função deve retornar o valor total gasto pelo cliente.
JOIN entre as tabelas vendas e produtos para obter o preço do produto e a quantidade
comprada.
Retorne a soma total.*/

delimiter //
create function calcular_total_compras (id_cliente int)
returns decimal(10, 2)
deterministic
begin
declare total_compras decimal(10, 2);
select sum(p.preco * v.quantidade) into total_compras from vendas v 
join produtos p on p.id_produto = v.id_produto where v.id_cliente = id_cliente;
return total_compras;
end //
delimiter ;

select id_cliente, nome, calcular_total_compras(id_cliente) as total_gasto from clientes;

/*7. Calcular a idade média dos clientes por categoria de produto
Crie uma função chamada idade_media_por_categoria que receba uma categoria de produto e
retorne a idade média dos clientes que compraram produtos dessa categoria.
a) Considere apenas os clientes que possuem pelo menos uma compra na categoria
indicada.
b) A função deve retornar a média de idade desses clientes.
JOIN entre as tabelas vendas, produtos e clientes para filtrar pela categoria de produto e calcular
a média de idade dos clientes.
O valor retornado deve ser um decimal.*/

delimiter //
create function idade_media_por_categoria (categoria varchar(50))
returns decimal(10, 2)
deterministic
begin
declare idade_media decimal(10, 2);
select avg(c.idade) into idade_media from clientes c 
join vendas v on v.id_cliente = c.id_cliente
join produtos p on p.id_produto = v.id_produto
where p.categoria = categoria;
return idade_media;
end //
delimiter ;

select distinct categoria, idade_media_por_categoria(categoria) as idade_media_categoria from produtos;

/*8. Calcular quantidade de produtos vendidos por cliente
Crie uma função chamada calcular_quantidade_vendida_cliente que receba o id_cliente e
retorne o total de itens que esse cliente comprou.
a) A função deve somar a quantidade de produtos em todas as vendas feitas pelo cliente
especificado.
b) Deve retornar um valor inteiro representando o total de produtos comprados.
Utilize a tabela vendas para somar a coluna quantidade para o id_cliente fornecido.*/

delimiter //
create function calcular_quantidade_vendida_cliente (id_cliente int)
returns int
deterministic
begin
declare qtd_vendida int;
select sum(v.quantidade) into qtd_vendida from vendas v where v.id_cliente = id_cliente;
return qtd_vendida;
end //
delimiter ;

select nome, calcular_quantidade_vendida_cliente(id_cliente) as qtd_comprada from clientes order by nome;

/*9. Calcular o tempo de cadastro do cliente em anos
Crie uma função chamada tempo_cadastro_cliente que receba o id_cliente e retorne o número
de anos que o cliente está cadastrado na plataforma.
a) A função deve calcular a diferença em anos entre a data de cadastro do cliente
(data_cadastro) e a data atual.
b) Deve retornar um valor inteiro representando o tempo de cadastro em anos.
Utilize a função DATEDIFF ou TIMESTAMPDIFF para calcular a diferença entre datas.
Considere CURRENT_DATE como a data atual.*/

delimiter //
create function tempo_cadastro_cliente (id_cliente int)
returns int
deterministic
begin
declare qtd_anos int;
select datediff(current_date(), c.data_cadastro)/365 into qtd_anos from clientes c where c.id_cliente = id_cliente;
return qtd_anos;
end //
delimiter ;
drop function tempo_cadastro_cliente;

select id_cliente, nome, tempo_cadastro_cliente(id_cliente) as tempo_cadastro from clientes;

/*10. Verificar cliente VIP
Crie uma função chamada verificar_cliente_vip que receba o id_cliente e retorne uma
mensagem indicando se o cliente é VIP ou não.
Critérios para ser considerado VIP:
a) O cliente deve ter gasto mais de 5000 em compras.
b) Deve ter realizado pelo menos 5 compras.
A função deve retornar:
a) "Cliente VIP" caso atenda aos critérios.
b) "Cliente regular" caso contrário.
JOIN entre vendas e produtos para calcular o gasto total do cliente.
Estrutura IF para retornar o status com base nos critérios.*/

delimiter //
create function verificar_cliente_vip (id_cliente int)
returns varchar(30)
deterministic
begin
declare vip varchar(30);
select if(sum(v.quantidade*p.preco) > 5000 and count(v.id_venda) > 5, 'Cliente VIP', 'Cliente regular') into vip 
from clientes c join vendas v on v.id_cliente = c.id_cliente
join produtos p on p.id_produto = v.id_produto where c.id_cliente = id_cliente;
return vip;
end //
delimiter ;
drop function verificar_cliente_vip;
select id_cliente, nome, verificar_cliente_vip(id_cliente) as cliente_vip from clientes;


