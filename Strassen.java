package codeforces;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class Strassen {
    public static List<List<Integer>> generateRandomMatrix(int rows, int cols, int min, int max) {
        List<List<Integer>> randomMatrix = new ArrayList<>(rows);
        Random rd = new Random();

        for (int i = 0; i < rows; i++) {
            List<Integer> row = new ArrayList<>(cols);
            for (int j = 0; j < cols; j++) {
                row.add(rd.nextInt(max - min + 1) + min);
            }
            randomMatrix.add(row);
        }

        return randomMatrix;
    }

    public static List<List<Integer>> subtractMatrix(List<List<Integer>> matrix1, List<List<Integer>> matrix2) {
        int n = matrix1.size();
        List<List<Integer>> result = new ArrayList<>(n);

        for (int i = 0; i < n; i++) {
            List<Integer> row = new ArrayList<>(n);
            for (int j = 0; j < n; j++) {
                int diff = matrix1.get(i).get(j) - matrix2.get(i).get(j);
                row.add(diff);
            }
            result.add(row);
        }

        return result;
    }

    public static List<List<Integer>> addMatrix(List<List<Integer>> matrix1, List<List<Integer>> matrix2) {
        int n = matrix1.size();
        List<List<Integer>> result = new ArrayList<>(n);

        for (int i = 0; i < n; i++) {
            List<Integer> row = new ArrayList<>(n);
            for (int j = 0; j < n; j++) {
                int sum = matrix1.get(i).get(j) + matrix2.get(i).get(j);
                row.add(sum);
            }
            result.add(row);
        }

        return result;
    }
    public static List<List<Integer>> strassenMatrixMultiplication(
            final List<List<Integer>> matrix1,
            final List<List<Integer>> matrix2) {

        int n = matrix1.size();

        if (n == 1) {
            List<List<Integer>> result = new ArrayList<>();
            result.add(new ArrayList<>());
            result.get(0).add(matrix1.get(0).get(0) * matrix2.get(0).get(0));
            return result;
        }

        int new_n = n / 2;

        List<List<Integer>> A11 = new ArrayList<>();
        List<List<Integer>> A12 = new ArrayList<>();
        List<List<Integer>> A21 = new ArrayList<>();
        List<List<Integer>> A22 = new ArrayList<>();

        List<List<Integer>> B11 = new ArrayList<>();
        List<List<Integer>> B12 = new ArrayList<>();
        List<List<Integer>> B21 = new ArrayList<>();
        List<List<Integer>> B22 = new ArrayList<>();

        for (int i = 0; i < new_n; i++) {
            A11.add(new ArrayList<>(matrix1.get(i).subList(0, new_n)));
            A12.add(new ArrayList<>(matrix1.get(i).subList(new_n, n)));
            A21.add(new ArrayList<>(matrix1.get(i + new_n).subList(0, new_n)));
            A22.add(new ArrayList<>(matrix1.get(i + new_n).subList(new_n, n)));

            B11.add(new ArrayList<>(matrix2.get(i).subList(0, new_n)));
            B12.add(new ArrayList<>(matrix2.get(i).subList(new_n, n)));
            B21.add(new ArrayList<>(matrix2.get(i + new_n).subList(0, new_n)));
            B22.add(new ArrayList<>(matrix2.get(i + new_n).subList(new_n, n)));
        }

        List<List<Integer>> M1 = addMatrix(A21, A22);
        List<List<Integer>> M2 = subtractMatrix(M1, A11);
        List<List<Integer>> M3 = subtractMatrix(A11, A21);
        List<List<Integer>> M4 = subtractMatrix(A12, M2);
        List<List<Integer>> M5 = subtractMatrix(B12, B11);
        List<List<Integer>> M6 = subtractMatrix(B22, M5);
        List<List<Integer>> M7 = subtractMatrix(B22, B12);
        List<List<Integer>> M8 = subtractMatrix(M6, B21);

        List<List<Integer>> P1 = strassenMatrixMultiplication(M2, M6);
        List<List<Integer>> P2 = strassenMatrixMultiplication(A11, B11);
        List<List<Integer>> P3 = strassenMatrixMultiplication(A12, B21);
        List<List<Integer>> P4 = strassenMatrixMultiplication(M3, M7);
        List<List<Integer>> P5 = strassenMatrixMultiplication(M1, M5);
        List<List<Integer>> P6 = strassenMatrixMultiplication(M4, B22);
        List<List<Integer>> P7 = strassenMatrixMultiplication(A22, M8);

        List<List<Integer>> T1 = addMatrix(P1, P2);
        List<List<Integer>> T2 = addMatrix(T1, P4);

        List<List<Integer>> C11 = addMatrix(P2, P3);
        List<List<Integer>> C12 = addMatrix(T1, (addMatrix(P5, P6)));
        List<List<Integer>> C21 = subtractMatrix(T2, P7);
        List<List<Integer>> C22 = addMatrix(T2, P5);

        List<List<Integer>> result = new ArrayList<>();
        for (int i = 0; i < 2 * new_n; i++) {
            result.add(new ArrayList<>());
            for (int j = 0; j < 2 * new_n; j++) {
                if (i < new_n && j < new_n) {
                    result.get(i).add(C11.get(i).get(j));
                } else if (i < new_n && j >= new_n) {
                    result.get(i).add(C12.get(i).get(j - new_n));
                } else if (i >= new_n && j < new_n) {
                    result.get(i).add(C21.get(i - new_n).get(j));
                } else {
                    result.get(i).add(C22.get(i - new_n).get(j - new_n));
                }
            }
        }
        return result;
    }

    public static void main(String[] args) {
//        List<List<Integer>> matrix1 = generateRandomMatrix(16, 16, 1, 9);
//        List<List<Integer>> matrix2 = generateRandomMatrix(16, 16, 1, 9);
        List<List<Integer>> matrix1 = Arrays.asList(
                Arrays.asList(1, 2, 3, 4),
                Arrays.asList(5, 6, 7, 8),
                Arrays.asList(9, 10, 11, 12),
                Arrays.asList(5, 6, 7, 8)
        );
        List<List<Integer>> matrix2 = Arrays.asList(
                Arrays.asList(10, 11, 12, 13),
                Arrays.asList(13, 14, 15, 16),
                Arrays.asList(16, 17, 18, 19),
                Arrays.asList(5, 6, 7, 8)
        );

        List<List<Integer>> result = strassenMatrixMultiplication(matrix1, matrix2);

        System.out.println("Matrix 1:");
        for (List<Integer> row : matrix1) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }

        System.out.println("Matrix 2:");
        for (List<Integer> row : matrix2) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }

        System.out.println("Result:");
        for (List<Integer> row : result) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
    }
}