/*
 * Binomial Coefficient
 * 
 * Digested factorial with minimised excess
 */

import java.util.Scanner;

public class Count4 {
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
        double excess = 0;
        long min = 0;
        if (k > n - k) {
            min = k;
        } else {
            min = n - k;
        }

        for (long i = n; i > min; i--) {
            long temp = i * nk;
            // System.out.println(temp);

            nk = nk / (i - min);
            nk = i * nk;

            excess = (double) i * excess / (double) (i - min);

            // System.out.println((double) temp / (double) (i - min) - nk);
            excess += (double) temp / (double) (i - min) - nk;

            // System.out.println("NK1: " + nk + " EXCESS1: " + excess);

            nk += (long) excess;
            excess -= (long) excess;

            // System.out.println("NK2: " + nk + " EXCESS2: " + excess);
        }
        if (excess % 1 != 0) {
            double check = excess % 1;
            if (check > 0.5) {
                excess = excess + check;
            } else {
                excess = excess - check;
            }
        }
        return nk + (long) excess;
    }
}