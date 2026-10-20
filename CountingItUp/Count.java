
/*
 * Binomial Coefficient calculation of two integers
 * 
 * Factorial Approach
 */
import java.util.Scanner;

public class Count {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        long n = 0;
        long k = 0;
        while (sc.hasNextLine()) {
            String nk = sc.nextLine();
            String[] numbers = nk.split(" ");
            try {
                n = Long.parseLong(numbers[0]);
                k = Long.parseLong(numbers[1]);
                System.out.println(calculation(n, k));
            } catch (NumberFormatException e) {
                System.out.println("Error: incorrect format");
            }

        }
    }

    public static long calculation(long n, long k) {
        long nk = 1;
        long min = 0;
        if (k > n - k) {
            min = k;
        } else {
            min = n - k;
        }
        // Binomial coefficient formula
        for (long i = n; i > min; i--) {
            nk = i * nk;
            nk = nk / (i - min);
        }
        return nk;
    }
}