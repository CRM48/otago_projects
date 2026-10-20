/*
 * Binomial Coefficient
 * 
 * Extended Factorial approach
 */

import java.util.Scanner;

public class FormulaC {
    private static final long MAX_LONG = Long.MAX_VALUE;
    private static final int MAX_K = 33;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        long n = 0;
        long k = 0;

        // input of n k parsed to long values
        while (sc.hasNextLine()) {
            String nk = sc.nextLine();
            String[] numbers = nk.split(" ");
            try {
                n = Long.parseLong(numbers[0]);
                k = Long.parseLong(numbers[1]);
            } catch (NumberFormatException e) {
                System.out.println("Error: incorrect format");
            }

            // row/col calculations
            long rows = n - k + 1;
            long cols = k + 1;

            // output result
            System.out.println(pyramidNumber(rows, cols));
        }
    }

    /**
     * pyramidNumber
     * 
     * Returns the pyramid number (or a multiplied version of it)
     * of a number where row is the number and col is the multiplied
     * amount.
     * 
     * @param row The number being multiplied
     * @param col How many times to multiply
     * @return The multiplied value which is the binomial coefficient of n k
     */
    public static long pyramidNumber(long row, long col) {
        long sum = 1;
        long excess;
        long extra = 0;
        // System.out.println(row + " " + col);

        if (row < col) {
            long temp = row;
            row = col;
            col = temp;
        }

        // calculate the result
        for (long i = 1; i < col; i++) {
            excess = (row + (i - 1)) % i;
            long temp = i;
            // System.out.println(sum);
            /*
             * if the divided sum does not result in a whole number calculate the
             * excess amount to be added later
             */
            if (excess != 0) {
                /*
                 * if(sum > MAX_LONG/MAX_K){
                 * long hcf = highestCommonFactor(excess, i);
                 * excess /= hcf;
                 * temp /= hcf;
                 * }
                 */

                extra = (long) ((sum * excess) / temp);
            }

            sum *= (row + (i - 1)) / i;
            sum += extra;
            extra = 0;
        }
        return sum;
    }

    /**
     * highestCommonFactor
     * 
     * Returns the highest common factor of two numbers
     * 
     * @param a The first number
     * @param b The second number
     * @return the highest common factor of the two
     */
    public static long highestCommonFactor(long a, long b) {
        long maxFactor = 1;
        long lowestAB = a;
        if (a > b) {
            lowestAB = b;
        }
        for (int i = 1; i < lowestAB; i++) {
            if (a % i == 0 && b % i == 0) {
                maxFactor = i;
            }
        }
        return maxFactor;
    }

}