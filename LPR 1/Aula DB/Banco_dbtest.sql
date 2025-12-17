drop database if exists dbtest;
create database dbtest;

use dbtest;

create table clientes(
id integer auto_increment primary key,
nome varchar(50) not null
);

insert into clientes (nome) values 
('Fernando'), ('Ana'), ('Carlos'), ('Pedro');

select * from clientes;