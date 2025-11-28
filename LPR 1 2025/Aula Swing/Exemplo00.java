import javax.swing.*;
import java.awt.*;

public class Exemplo00 {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Hello World");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Label centralizado
        JLabel label = new JLabel("Hello World", SwingConstants.CENTER);
        label.setFont(new Font("Arial", Font.BOLD, 48)); /// Fonte maior

        frame.add(label);

        // Maximiza a janela
        frame.setExtendedState(JFrame.MAXIMIZED_BOTH);

        frame.setVisible(true);
    }
}