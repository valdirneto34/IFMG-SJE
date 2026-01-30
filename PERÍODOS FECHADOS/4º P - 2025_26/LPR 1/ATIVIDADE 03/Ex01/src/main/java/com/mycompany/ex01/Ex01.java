/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */
package com.mycompany.ex01;

import java.sql.*;
import java.util.Scanner;

/**
 *
 * @author Valdir de Souza Carvalho Neto
 */
public class Ex01 {

    public static void main(String[] args) {
        Connection conn = ConnectionFactory.getConexao();

        if (conn != null) {
            try {
                String nome;
                Scanner scan = new Scanner(System.in);
                System.out.println("Informe um nome: ");
                nome = scan.next();

                String sql = "insert into clientes (nome) values ( ? );";

                // Preparar o comadndo sql
                PreparedStatement stmt = conn.prepareStatement(sql);
                stmt.setString(1, nome);

                int linhas = stmt.executeUpdate();

                if (linhas > 0) {
                    System.out.println("Cliente inserido com sucesso!");
                } else {
                    System.out.println("Nenhum cliente foi inserido!");
                }

                sql = "select * from clientes;";

                Statement stmt2 = conn.createStatement();
                ResultSet rs = stmt2.executeQuery(sql);

                System.out.println("\n----------- CLIENTES ----------");
                while (rs.next()) {
                    System.out.println("Codigo: " + rs.getString("id"));
                    System.out.println("Nome..: " + rs.getString("nome"));
                }
                System.out.println("-------------------------------");

                conn.close();
                scan.close();
            } catch (SQLException ex) {
                System.out.println("Erro do BD: " + ex.getMessage());
            }

        } else {
            System.out.println("Erro na conexao com BD!");
        }
    }
}
