drop database if exists telaLogin;
create database telaLogin;

use telaLogin;

create table usuario(
id_usuario int primary key auto_increment,
email varchar(60) not null,
senha varchar(30) not null
);

insert into usuario (email, senha) values 
('patricia.silv.costa@gmail.com', '12354#'),
('valdir.neto@gmail.com', 'neto2312'),
('paranhos.faculdade@gmail.com', '1234'),
('rubeulos.rubson@gmail.com', '4321');
