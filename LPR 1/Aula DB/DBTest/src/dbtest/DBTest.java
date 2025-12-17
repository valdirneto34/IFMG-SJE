/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dbtest;

import java.sql.*;
import java.util.*;

/**
 *
 * @author Valdir de Souza Carvalho Neto
 */
public class DBTest {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        // Parâmtros de conexão
        String user = "root";
        String pwd = "root";
        String url = "jdbc:mysql://localhost/dbtest";

        Connection conn = null;

        try {
            // Selecionare o driver JDBC para a aplicação
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Estabelecr conexão com DB
            conn = DriverManager.getConnection(url, user, pwd);

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
                System.out.println("Código: " + rs.getString("id"));
                System.out.println("Nome..: " + rs.getString("nome"));
            }
            System.out.println("-------------------------------");

            conn.close();

        } catch (ClassNotFoundException ex) {
            System.out.println("Erro: " + ex.getMessage());

        } catch (SQLException ex) {
            System.out.println("Erro do BD: " + ex.getMessage());
        }
    }

}
