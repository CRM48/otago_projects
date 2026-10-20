/*
 * Binomial Coefficient
 * 
 * Pascals trangle approach
 */

import java.util.Scanner;

public class pascalTriangle {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        long n = 0;
        long k = 0;

        while (sc.hasNextLine()) {
            // Get user input and parse to long values
            String nk = sc.nextLine();
            String[] numbers = nk.split(" ");
            try {
                n = Long.parseLong(numbers[0]);
                k = Long.parseLong(numbers[1]);
            } catch (NumberFormatException e) {
                System.out.println("Error: incorrect format");
            }

            // calculate row and col for given n/k values
            long rows = n - k + 1;
            long cols = k + 1;

            // invalid cases (instructed to just output 1)
            if (k <= 0 || n <= 0 || k > n) {
                System.out.println(1);
            }

            // If k or n-k = 1 then simply output n
            else if (k == 1 || (n - k) == 1) {
                System.out.println(n);
            }

            /*
             * If k or n-k = 2 then calculate pyramidal number of the
             * larger of rows/cols
             */
            else if (k == 2 || (n - k) == 2) {
                if (rows < cols) {
                    long temp = rows;
                    rows = cols;
                    cols = temp;
                }
                long whole = rows * ((rows + 1) / 2);
                if ((rows + 1) % 2 != 0) {
                    long extra = (long) (0.5 * rows);
                    whole += extra;
                }
                System.out.println(whole);
            }

            /*
             * All other valid cases can be converted to int and therefore
             * don't need to be manually calculates
             */
            else {
                System.out.println(drawPascalsTriangle((int) (rows), (int) (cols)));
            }
        }
    }

    /**
     * drawPascalsTriangle
     * 
     * Draws a variation of pascals triangle that minimises the number of
     * cols and rows required to calculate the binomial coefficient. It uses
     * minimum memory and has maximum efficiency for the solution type
     * 
     * @param row The row to calculate to
     * @param col The column to calculate to
     * @return The value in (row, col) of the adapted triangle which is the binomial
     *         coefficient of n k
     */
    public static long drawPascalsTriangle(int row, int col) {
        if (row > col) {
            int temp = row;
            row = col;
            col = temp;
        }

        long[][] triangle = new long[2][row];
        triangle[1][0] = 1;
        triangle[1][1] = 1;
        triangle[0][0] = 1;

        for (int i = 3; i < (col + row); i++) {
            for (int j = 1; j < i && j < row; j++) {
                triangle[0][j] = triangle[1][j - 1] + triangle[1][j];
            }
            for (int j = 0; j < i && j < row; j++) {
                triangle[1][j] = triangle[0][j];
            }
        }
        return triangle[1][row - 1];
    }
}
