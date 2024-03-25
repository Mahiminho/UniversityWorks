import java.io.*;
import java.util.*;

/**
 * Class App realize example program to lab work №1
 * @author Popov Maxim
 * @version 1.2
 * @since version 1.0
 */
public class Lab1PopovKI304 {
    /**
     * Static method main is enter point to program
     * 
     * @param args
     * @throws FileNotFoundException
     * 
     */
    public static void main(String[] args) throws FileNotFoundException {
        int nRows;
        char[][] arr;
        String filler;
        Scanner in = new Scanner(System.in);
        File dataFile = new File("FirstLab\\TxtFiles\\MyFile.txt");
        PrintWriter fout = new PrintWriter(dataFile);

        System.out.print("Введіть розмір квадратної матриці (не менше, ніж 4): ");
        nRows = in.nextInt();
        in.nextLine();
        if (nRows < 4) {
            System.out.println("Розмір мартриці менше, ніж 4!");
            System.exit(0);
        }
        arr = new char[nRows][];
        for (int i = 0; i < nRows; i++) {
            if (i > 1 && i < nRows - 2) {
                arr[i] = new char[2];
            }
            else if (i == 1 || i == nRows - 2){
                arr[i] = new char[nRows - 2];
            }
        }

        System.out.print("\nВведіть символ-заповнювач: ");
        filler = in.nextLine();
        if (filler.length() != 1) {
            System.out.println("Ви повинні були ввести лише один символ!");
            System.exit(0);
        }

        for (int i = 0; i < nRows; i++) {
            if (i > 1 && i < nRows - 2) {
                for (int j = 0; j < 2; j++) {
                    arr[i][j] = (char) filler.codePointAt(0);
                }
            } 
            else if (i == 1 || i == nRows - 2){
                for (int j = 0; j < nRows - 2; j++) {
                    arr[i][j] = (char) filler.codePointAt(0);
                }
            }
        }



        for (int i = 0; i < nRows; i++) {
            if (i > 1 && i < nRows - 2) {
                System.out.print(" " + arr[i][0] + " ");
                fout.print(" " + arr[i][0] + " ");
                for (int j = 0; j < (nRows - 4) * 2; j++) {
                    System.out.print(" ");
                    fout.print(" ");
                }
                System.out.print(arr[i][1] + "   ");
                fout.print(arr[i][1] + "   ");
            } 
            else if (i == 1 || i == nRows - 2){
                System.out.print(" ");
                fout.print(" ");
                for (int j = 0; j < nRows - 2; j++) {
                    System.out.print(arr[i][j] + " ");
                    fout.print(arr[i][j] + " ");
                }
                System.out.print("  ");
                fout.print("  ");
            }
            System.out.println();
            fout.println();
        }



        fout.flush();
        fout.close();
        in.close();
    }
}


        // System.out.println();
        // for (int i = 0; i < nRows; i++) {
        //     System.out.print("   ");
        //     if (i > 1 && i < nRows - 2) {
        //         System.out.print(arr[i][j] + " ");
        //         for (int k = 0; k > nRows - 4; k++) {
        //             System.out.print("  ");
        //         }
        //     } 
        //     else if (i == 1 || i == nRows - 2){
        //         for (int j = 0; j < nRows - 2; j++) {
        //             System.out.print(arr[i][j] + " ");
        //         }
        //     }
        //     System.out.print("   ");
        //     System.out.println();
        // }
        // System.out.println();







        // for (int i = 1; i < nRows - 1; i++) {
        //     if (i == 1) {
        //         for (int j = 1; j < nRows - 1; j++) {
        //             arr[i][j] = (char) filler.codePointAt(0);
        //         }
        //     } else if (i == nRows - 2) {
        //         for (int j = 1; j < nRows - 1; j++) {
        //             arr[i][j] = (char) filler.codePointAt(0);
        //         }
        //     } else {
        //         arr[i][1] = (char) filler.codePointAt(0);
        //         arr[i][nRows - 2] = (char) filler.codePointAt(0);
        //     }
        // }

        // for (int i = 0; i < nRows; i++) {
        //     for (int j = 0; j < nRows; j++) {
        //         if (arr[i][j] != 0) {
        //             System.out.print(arr[i][j]);
        //             fout.print(arr[i][j]);
        //         } else {
        //             System.out.print(" ");
        //             fout.print(" ");
        //         }
        //     }
        //     System.out.println();
        //     fout.print("\n");
        // }



        // for (int i = 0; i < nRows; i++) {
        //     arr[i] = new char[nRows];
        // }

        


        // for (int i = 0; i < nRows; i++) {
        //     for (int j = 0; j < nRows; j++) {
        //         if (arr[i][j] != filler.charAt(0)) {
        //             arr[i][j] = ' ';
        //         }
        //     }
        // }

        // for (int i = 0; i < nRows; i++) {
        //     for(int j = 0; j < nRows; j++) {
        //         System.out.print(arr[i][j] + " ");
        //         fout.print(arr[i][j] + " ");
        //     }
        //     System.out.print("\n");
        //     fout.print("\n");
        // }
