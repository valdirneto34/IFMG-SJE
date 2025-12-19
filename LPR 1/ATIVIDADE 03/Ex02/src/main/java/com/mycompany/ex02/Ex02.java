/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */
package com.mycompany.ex02;

/**
 *
 * @author valdi
 */
public class Ex02 {

    public static void main(String[] args) {
        System.out.println("--- Teste de Insercao ---");
        Cliente c1 = new Cliente();
        c1.setNome("Teste Valdir");
        c1.inserir();

        System.out.println("\n--- Teste de Carregamento ---");
        Cliente c2 = new Cliente();
        int idTeste = 1;
        c2.carregar(idTeste);
        System.out.println("Nome recuperado: " + c2.getNome());

        System.out.println("\n--- Teste de Alteracao ---");
        Cliente novosDados = new Cliente();
        novosDados.setNome("Valdir Alterado");
        c2.alterar(novosDados);
        c2.carregar(idTeste);
        System.out.println("Nome recuperado: " + c2.getNome());

        System.out.println("\n--- Teste de Exclusao ---");
        c2.excluir();
    }
}
