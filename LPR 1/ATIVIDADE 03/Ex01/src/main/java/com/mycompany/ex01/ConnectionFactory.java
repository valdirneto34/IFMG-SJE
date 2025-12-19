/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.ex01;

import java.sql.*;

/**
 *
 * @author Valdir de Souza Carvalho Neto
 */
public class ConnectionFactory {

    private static final String user = "root";
    private static final String pwd = "teste1";
    private static final String url = "jdbc:mysql://localhost/dbtest";
    private static final String driver = "com.mysql.cj.jdbc.Driver";

    public static Connection getConexao() {
        try {
            // Selecionare o driver JDBC para a aplicação
            Class.forName(driver);

            // Estabelecr conexão com DB
            return DriverManager.getConnection(url, user, pwd);
        } catch (ClassNotFoundException ex) {
            System.out.println("Erro: " + ex.getMessage());
            return null;

        } catch (SQLException ex) {
            System.out.println("Erro do BD: " + ex.getMessage());
            return null;
        }
    }
}
