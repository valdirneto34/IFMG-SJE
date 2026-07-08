import com.mycompany.soma.SomaMaiorMenor;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class TesteSomaMaiorMenor {
    
    public TesteSomaMaiorMenor() {
    }
    
    @Test
    public void testeSoma(){
        int a = 3;
        int b = 2;
        int c = 3;
        SomaMaiorMenor s = new SomaMaiorMenor();
        int resultTest = 8;
        int resultMetodo;
        resultMetodo = s.SomaMaior(a, b, c);
        assertEquals(resultTest, resultMetodo);
    }
    
    @Test
    public void testeMenorA(){
        int a = 1;
        int b = 7;
        int c = 3;
        SomaMaiorMenor s = new SomaMaiorMenor();
        int resultTest = 1;
        int resultMetodo;
        resultMetodo = s.MenorNum(a, b, c);
        assertEquals(resultTest, resultMetodo);
    }
    
    @Test
    public void testeMenorB(){
        int a = 29;
        int b = 2;
        int c = 5;
        SomaMaiorMenor s = new SomaMaiorMenor();
        int resultTest = 2;
        int resultMetodo;
        resultMetodo = s.MenorNum(a, b, c);
        assertEquals(resultTest, resultMetodo);
    }
    
    @Test
    public void testeMenorC(){
        int a = 5;
        int b = 7;
        int c = 2;
        SomaMaiorMenor s = new SomaMaiorMenor();
        int resultTest = 2;
        int resultMetodo;
        resultMetodo = s.MenorNum(a, b, c);
        assertEquals(resultTest, resultMetodo);
    }
    
    @Test
    public void testeMaiorA(){
        int a = 8;
        int b = 2;
        int c = 3;
        SomaMaiorMenor s = new SomaMaiorMenor();
        int resultTest = 8;
        int resultMetodo;
        resultMetodo = s.MaiorNum(a, b, c);
        assertEquals(resultTest, resultMetodo);
    }
    
    @Test
    public void testeMaiorB(){
        int a = 7;
        int b = 23;
        int c = 3;
        SomaMaiorMenor s = new SomaMaiorMenor();
        int resultTest = 23;
        int resultMetodo;
        resultMetodo = s.MaiorNum(a, b, c);
        assertEquals(resultTest, resultMetodo);
    }
    
    @Test
    public void testeMaiorC(){
        int a = 45;
        int b = 2;
        int c = 76;
        SomaMaiorMenor s = new SomaMaiorMenor();
        int resultTest = 76;
        int resultMetodo;
        resultMetodo = s.MaiorNum(a, b, c);
        assertEquals(resultTest, resultMetodo);
    }
    
}
