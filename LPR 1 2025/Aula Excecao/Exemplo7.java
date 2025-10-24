import java.io.*;

public class Exemplo7 {
    private static void lerArquivo() throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("arquivo.txt"));
        System.out.println(br.readLine());
        br.close();
    }

    public static void main(String[] args) {
        try {
            lerArquivo();
        } catch (FileNotFoundException e) {
            System.out.println("Arquivo não encontrado!");
        }
        catch (IOException e) {
            System.out.println("Erro de entrada e saída desconhecido. " + e.getMessage());
        }
         catch (Exception e) {
            System.out.println("Erro desconhecido. " + e.getMessage());
        }
    }
}
