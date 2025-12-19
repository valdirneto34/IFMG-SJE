/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.ex02;

import java.sql.*;

/**
 *
 * @author Valdir de Souza Carvalho Neto
 */
public class Cliente {

    private int id;
    private String nome;

    public Cliente() {
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void inserir() {
        String sql = "insert into clientes (nome) values ( ? );";
        Connection conn = ConnectionFactory.getConexao();

        try {
            // Preparar o comadndo sql
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, this.getNome());

            int linhas = stmt.executeUpdate();

            if (linhas > 0) {
                System.out.println("Cliente inserido com sucesso!");
            } else {
                System.out.println("Nenhum cliente foi inserido!");
            }

            conn.close();
        } catch (SQLException ex) {
            System.out.println("Erro do BD: " + ex.getMessage());
        }
    }

    public void alterar(Cliente novoCliente) {
        String sql = "update clientes set nome =  ? where id = ?;";
        Connection conn = ConnectionFactory.getConexao();

        try {
            // Preparar o comadndo sql
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, novoCliente.getNome());
            stmt.setInt(2, this.getId());

            int linhas = stmt.executeUpdate();

            if (linhas > 0) {
                System.out.println("Cliente alterado com sucesso!");
            } else {
                System.out.println("Nenhuma mudança executada!");
            }

            conn.close();
        } catch (SQLException ex) {
            System.out.println("Erro do BD: " + ex.getMessage());
        }
    }

    public void carregar(int id) {
        String sql = "select * from clientes where id = ?;";
        Connection conn = ConnectionFactory.getConexao();

        try {
            // Preparar o comadndo sql
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setInt(1, id);

            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                this.setId(rs.getInt("id"));
                this.setNome(rs.getString("nome"));
            } else {
                System.out.println("Cliente nao encontrado!");
            }

            conn.close();
        } catch (SQLException ex) {
            System.out.println("Erro do BD: " + ex.getMessage());
        }
    }

    public void excluir() {
        String sql = "delete from clientes where id = ?;";
        Connection conn = ConnectionFactory.getConexao();

        try {
            // Preparar o comadndo sql
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setInt(1, this.getId());

            int linhas = stmt.executeUpdate();

            if (linhas > 0) {
                System.out.println("Cliente excluido com sucesso!");
            } else {
                System.out.println("Cliente nao encontrado!");
            }

            conn.close();
        } catch (SQLException ex) {
            System.out.println("Erro do BD: " + ex.getMessage());
        }
    }

}
