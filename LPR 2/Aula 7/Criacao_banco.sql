DROP DATABASE IF EXISTS inscricoes;
CREATE DATABASE IF NOT EXISTS inscricoes CHARACTER SET utf8mb4;
USE inscricoes;

CREATE TABLE IF NOT EXISTS estudante (
id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
nome VARCHAR(120) NOT NULL,
email VARCHAR(180) NOT NULL UNIQUE,
curso VARCHAR(50), 
data_ingresso DATE, 
telefone VARCHAR(11), 
cidade VARCHAR(200)
);

CREATE USER "app_inscricoes"@"localhost" IDENTIFIED BY "admin123";
GRANT SELECT, INSERT, UPDATE, DELETE ON inscricoes.* TO "app_inscricoes"@"localhost";