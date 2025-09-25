create database blog_pessoal_Valdir;

use blog_pessoal_Valdir;

create table USUARIOS(
usuario_id integer not null auto_increment primary key,
nome varchar(100) not null,
email varchar(100) not null unique,
data_cadastro datetime default current_timestamp
);

create table POSTS(
post_id integer primary key auto_increment,
titulo varchar(200) not null,
conteudo text not null,
data_publicacao datetime,
usuario_id integer
);

create table COMENTARIOS(
comentario_id integer primary key auto_increment,
texto_comentario text not null,
data_comentario datetime,
usuario_id integer,
post_id integer
);

alter table posts add constraint fk_posts foreign key (usuario_id) references usuarios (usuario_id);

alter table comentarios add constraint fk_cometarios1 foreign key (post_id) references posts (post_id);

alter table comentarios add constraint fk_cometarios2 foreign key (usuario_id) references usuarios (usuario_id);

alter table posts add column resumo varchar(255);

alter table usuarios modify column nome varchar(150);

alter table posts add constraint check (length(titulo) > 5);

alter table usuarios rename column data_cadastro to data_de_criacao;

alter table posts drop column resumo;

alter table POSTS rename to PUBLICACOES;

create table CATEGORIAS(
categoria_id integer primary key auto_increment,
nome_categoria varchar(100) not null unique,
descricao text
);

create table TAGS(
tag_id integer primary key auto_increment,
nome_tag varchar(50) not null unique
);

create table PUBLICACAO_TAG(
post_id integer,
tag_id integer,
primary key(post_id, tag_id)
);

alter table publicacao_tag add constraint fk_post_tag_1 foreign key (post_id) references PUBLICACOES (post_id);

alter table publicacao_tag add constraint fk_post_tag_2 foreign key (tag_id) references tags (tag_id);

alter table publicacoes add column categoria_id integer;

alter table publicacoes add constraint fk_posts_2 foreign key (categoria_id) references categorias (categoria_id);

create table CURTIDAS(
curtida_id integer primary key auto_increment,
usuario_id integer,
post_id integer,
data_curtida datetime default current_timestamp,
unique(usuario_id, post_id)
);

alter table curtidas add constraint fk_curtidas foreign key (usuario_id) references usuarios (usuario_id);

alter table curtidas add constraint fk_curtidas_2 foreign key (post_id) references publicacoes (post_id);

alter table usuarios add column is_admin boolean default ("false");

alter table categorias modify column descricao text null;

alter table tags rename column nome_tag to nome_da_tag;

create table TABELA_TESTE(
categoria_id integer primary key auto_increment,
nome_categoria varchar(100) not null unique,
descricao text
);

drop table tabela_teste;

#--------------------------------------------------------------------------------------------------------

insert into usuarios(nome, email, data_de_criacao, is_admin) values 
('Valdir de Souza Carvalho Neto', 'valdirneto100c@gmail.com', default, true),
('Juliana Gabriel Lopes', 'jl097467@gmail.com', default, false),
('Sebastião de Souza Carvalho', 'sebastiaodesc@gmail.com', default, false),
('Emilio Pereira de Souza', 'emiiopereirasouza@gmail.com', default, false),
('Gabriel Pereira de Carvalho', 'gabrielpereiracarvalho@gmail.com', default, false);
select * from usuarios;
# - 1 - 2 - 3 - 4 - 5

insert into categorias(nome_categoria, descricao) values
('Tecnologia', 'Artigos sobre novidades tecnológicas e tendências do mercado'),
('Programação', 'Tutoriais e dicas de programação em diversas linguagens'),
('Banco de Dados', 'Conteúdo sobre gerenciamento e modelagem de dados'),
('Notícias', 'Atualizações e notícias do mundo da tecnologia');
select * from categorias;
# 1 - 2 - 3 - 4

insert into publicacoes(titulo, conteudo, data_publicacao, usuario_id, categoria_id) values
('Introdução ao SQL: Primeiros passos', 'Neste artigo vamos aprender os
fundamentos da linguagem SQL...', '2025-06-25 07:45:00', 5, 3),
('Python vs JavaScript: Qual escolher?', 'Uma comparação detalhada entre duas
das linguagens mais populares...', '2025-06-25 07:45:00', 1, 2),
('Novidades do MySQL 8.0', 'Conheça as principais novidades da versão 8.0 do
MySQL...', '2025-06-25 07:40:00', 4, 1),
('Como estruturar um banco de dados eficiente', 'Dicas para modelar seu banco
de dados de forma otimizada...', '2025-06-25 07:45:00', 2, 3),
('Lançamento do novo processador XYZ', 'A empresa ABC anunciou hoje seu novo
processador que promete revolucionar...', '2025-06-25 07:45:00', 1, 4),
('Frameworks JavaScript em 2025', 'Análise dos frameworks JavaScript mais
populares neste ano...', '2025-06-25 07:45:00', 3, 1);
select u.nome, p.data_publicacao from publicacoes p, usuarios u group by u.nome;
select * from publicacoes;
# 19 - 20 - 21 - 22 - 23 - 24

insert into tags(nome_da_tag) values ('SQL'), ('MySQL'), ('Python'), ('JavaScript'),
('Banco de Dados'), ('Programação'), ('Hardware'), ('Frameworks'), ('Processador');
# 1 - 2 - 3 - 4 -5 -6 - 7 - 8 - 9
select * from tags;

insert into publicacao_tag(post_id, tag_id) values 
(19, 1), (19, 2), (19, 5),
(20, 3), (20, 4), (20, 6),
(21, 1), (21, 2), (21, 5),
(22, 5), (22, 1),
(23, 7), (23, 9),
(24, 8), (24, 4);
select * from publicacao_tag;

insert into comentarios(texto_comentario, data_comentario, usuario_id, post_id) values
('Este artigo foi muito útil para mim, só aprendi SQL graças a ele!', '2025-06-25 08:35:00', 1, 19),
('Muito importante este artigo, é de suma importância saber os fundamentos da linguagem SQL!', '2025-06-25 08:35:00', 1, 19),
('Eu prefiro python pela facilidade de aprendizado e manuseabilidade kkkk', '2025-06-25 08:35:00', 2, 20),
('Quem diria que javascript é melhor, aquele tanto de linhas para um comando kkkk', '2025-06-25 08:35:00', 2, 20),
('Que isso hein, SQL tá muito fácil de trabalhar com essas novidades!', '2025-06-25 08:35:00', 3, 21),
('Sempre gostei de aplicar essas dicas nos meus modelos.', '2025-06-25 08:35:00', 3, 22),
('Esse processador vai acabar com a concorrência, a eficiência tá desafiadora!', '2025-06-25 08:35:00', 4, 23),
('O poder de processamemto dele é quase o dobro da concorrência, eles terão muito trabalho kkkkk', '2025-06-25 08:35:00', 4, 23),
('Já vou guardar um dinheiro pra testar em breve...', '2025-06-25 08:35:00', 5, 23),
('Não sabia que usavam tanto esses frameworks 4 e 5!', '2025-06-30 08:35:00', 5, 24);
select * from comentarios;
# 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20

insert into curtidas(usuario_id, post_id, data_curtida) values
(1, 19, '2025-06-25 08:40:00'), (2, 19, '2025-06-25 08:40:00'), (5, 19, '2025-06-25 08:40:00'),
(4, 20, '2025-06-25 08:40:00'), (3, 20, '2025-06-25 08:40:00'), (1, 20, '2025-06-25 08:40:00'),
(2, 21, '2025-06-25 08:40:00'), (1, 21, '2025-06-25 08:40:00'), (5, 21, '2025-06-25 08:40:00'),
(5, 22, '2025-06-25 08:40:00'), (1, 22, '2025-06-25 08:40:00'), (3, 22, '2025-06-25 08:40:00'),
(3, 23, '2025-06-25 08:40:00'), (5, 23, '2025-06-25 08:40:00'), (1, 23, '2025-06-25 08:40:00'),
(4, 24, '2025-06-25 08:40:00'), (3, 24, '2025-06-25 08:40:00'), (1, 24, '2025-06-25 08:40:00');
select * from curtidas;

# 7
select * from usuarios order by nome;

select p.titulo, p.data_publicacao, u.nome as nome_autor from publicacoes as p join usuarios as u on p.usuario_id = u.usuario_id;

select c.texto_comentario, c.data_comentario, u.nome as nome_autor_comentario, p.titulo as titulo_publicaco from comentarios as c join usuarios as u on c.usuario_id = u.usuario_id join publicacoes as p on c.post_id = p.post_id;

select p.titulo, p.conteudo, p.data_publicacao, u.nome as nome_autor_publicacao from publicacoes as p join usuarios as u on p.usuario_id = u.usuario_id where p.usuario_id = 1;

select c.texto_comentario, c.data_comentario, p.titulo as titulo_publicacao from comentarios as c join publicacoes as p on c.post_id = p.post_id where p.post_id = 20;

select p.titulo, p.conteudo, p.data_publicacao, c.nome_categoria from publicacoes as p join categorias as c on p.categoria_id = c.categoria_id where p.categoria_id = 1;

select p.usuario_id, count(p.post_id) as total_publicacoes from publicacoes as p group by p.usuario_id;

select p.titulo, count(c.post_id) as total_comentarios from publicacoes as p join comentarios as c where p.post_id = c.post_id group by p.titulo ;

select p.titulo, count(c.post_id) as total_curtidas from publicacoes as p join curtidas as c where p.post_id = c.post_id group by p.titulo ;

select p.titulo, p.conteudo, p.data_publicacao, t.nome_da_tag from publicacoes as p join publicacao_tag as pt join tags as t where p.post_id = pt.post_id and pt.tag_id = t.tag_id;

select distinct u.usuario_id, u.nome, p.titulo from usuarios as u join comentarios as com on u.usuario_id = com.usuario_id join publicacoes as p on com.post_id = p.post_id join categorias as c on p.categoria_id = c.categoria_id where c.nome_categoria like "Tecnologia";

select p.titulo, p.conteudo from publicacoes as p join publicacao_tag as pt on pt.post_id = p.post_id join tags as t on t.tag_id = pt.tag_id where t.nome_da_tag in ("SQL", "Banco de Dados") group by p.post_id, p.titulo, p.conteudo having count(distinct t.nome_da_tag) = 2;

# UPDATE
update usuarios set nome = "Gabriel P Carvalho" where usuario_id = 5;

update publicacoes set titulo = "Lançamento do novo processador da Intel" where post_id = 23;

update categorias set descricao = "Conteúdo sobre gerenciamento, modelagem de dados em SQL" where categoria_id = 3;

update usuarios set is_admin = true where usuario_id in (select usuario_id from ( select u.usuario_id from usuarios as u join publicacoes as p on u.usuario_id = p.usuario_id group by u.usuario_id having count(p.post_id) > 3) as usuarios_com_muitas_publicacaoes);

# DELETE
delete from comentarios where data_comentario = '2025-06-30 08:35:00' and usuario_id = 5 and post_id = 24;

delete from curtidas where usuario_id = 5 and post_id = 19;

SET SQL_SAFE_UPDATES = 0;
delete from comentarios where data_comentario = '2025-06-30 08:35:00';
SET SQL_SAFE_UPDATES = 1;

delete from curtidas where usuario_id = 2;
