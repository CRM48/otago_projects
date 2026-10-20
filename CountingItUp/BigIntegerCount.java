import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.Scanner;
public class BigIntegerCount{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        long n = 0;
        long k = 0;
        while(sc.hasNextLine()){
            String nk = sc.nextLine();
            String[] numbers = nk.split(" ");
            try{
                n = Long.parseLong(numbers[0]);
                k = Long.parseLong(numbers[1]);
                System.out.println(calculation(n, k));
            }catch(NumberFormatException e){
                System.out.println("Error: incorrect format");
            }
            
        }
    }
    public static long calculation(long n, long k) {
        long nk = 1;
        double excess = 0;
        long min = 0;
    
        if (k > n - k) {
            min = k;
        } else {
            min = n - k;
        }
        BigDecimal n1 = new BigDecimal(Long.toString(1));
        BigDecimal remainder = new BigDecimal("1");
    
        for (long i = n; i > min; i--) {
            long x = i-min;
            
            //System.out.println("i%(i-min) Remainer:" + i%(i-min));
            n1 = n1.multiply(new BigDecimal(Long.toString(i)));
            n1 = n1.divide(new BigDecimal(Long.toString(x)), 100, RoundingMode.HALF_UP);
            System.out.println("NK Remainer:" + n1.remainder(remainder));
            remainder = n1.remainder(BigDecimal.ONE);
            //System.out.println(n1);
        }
    
        
    
        return nk + (long) excess;
    }
}