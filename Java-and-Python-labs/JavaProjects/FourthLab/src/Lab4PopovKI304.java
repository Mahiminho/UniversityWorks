import java.util.Scanner;
import java.io.*;
import static java.lang.System.out;

/**
 * Class <code>EquationsApp</code> Implements driver for Equations class
 * 
 * @author Popov Maxim
 * @version 1.0
 */
public class Lab4PopovKI304 {
    /**
     * @param args
     */
    public static void main(String[] args) {
        try {
            out.print("Enter file name: ");
            Scanner in = new Scanner(System.in);
            String fName = in.nextLine();
            PrintWriter fout = new PrintWriter(new File(fName));
            try {
                try {
                    Equations eq = new Equations();
                    out.print("Enter X: ");
                    fout.print(eq.calculate(in.nextInt()));
                } finally {
                    // Цей блок виконається за будь-яких обставин
                    fout.flush();
                    fout.close();
                }
            } catch (CalcException ex) {
                // Блок перехоплює помилки обчислень виразу
                out.print(ex.getMessage());
            }
            in.close();
        } catch (FileNotFoundException ex) {
            // Блок перехоплює помилки роботи з файлом навіть якщо вони
            // виникли у блоці finally
            out.print("Exception reason: Perhaps wrong file path");
        }
    }
}

/**
 * Class <code>CalcException</code> more precises ArithmeticException
 * 
 * @author Popov Maxim
 * @version 1.0
 */
class CalcException extends ArithmeticException {
    public CalcException() {
    }

    public CalcException(String cause) {
        super(cause);
    }
}

/**
 * Class <code>Equations</code> implements method for 7x/tg(2x-4)
 * expression
 * calculation
 * 
 * @author Popov Maxim
 * @version 1.0
 */
class Equations {
    /**
     * Method calculates the 7x/tg(2x-4) expression
     * 
     * @param <code>x</code> Angle in degrees
     * @throws CalcException
     */
    public double calculate(int x) throws CalcException {
        double y, rad, numPI = Math.PI;
        rad = (2 * x - 4) * numPI / 180.0;
        // System.out.println(rad);
        // System.out.println(Math.tan(rad));
        try {
            y = 7.0 * x / Math.tan((2 * x - 4) * numPI / 180.0);
            // Якщо результат не є числом, то генеруємо виключення
            if (y == Double.NaN || y == Double.NEGATIVE_INFINITY ||
                    y == Double.POSITIVE_INFINITY || x == 90 || x == -90)
                throw new ArithmeticException();
        } catch (ArithmeticException ex) {
            // створимо виключення вищого рівня з поясненням причини
            // виникнення помилки
            if (rad == numPI / 2.0 || rad == 3 * numPI / 2.0)
                throw new CalcException("Exception reason: Illegal value of X for tangent calculation");
            else if (rad == numPI)
                throw new CalcException("Exception reason: the denominator equals 0");
            else
                throw new CalcException("Unknown reason of the exception during exception calculation");
        }
        return y;
    }
}

// import java.util.Scanner;
// import java.io.*;
// import static java.lang.System.out;

// public class Lab4PopovKI304 {
//     /**
//      * @param args
//      */
//     public static void main(String[] args) {
//         System.out.println("Radians");
//         System.out.println("Tan of 0: " + Math.tan(0));
//         System.out.println("Tan of 90: " + Math.tan(Math.PI/2));
//         System.out.println("Tan of 180: " + Math.tan(Math.PI));
//         System.out.println("Tan of 270: " + Math.tan(3*Math.PI/2) + "\n");

//         // System.out.println("Gradus");
//         // System.out.println("Tan of 0: " + Math.tan(0));
//         // System.out.println("Tan of 90: " + Math.tan(90));
//         // System.out.println("Tan of 180: " + Math.tan(180));
//         // System.out.println("Tan of 270: " + Math.tan(270) + "\n");

//         System.out.println("Radians with func");
//         System.out.println("Tan of 0: " + Math.tan(Math.toRadians(0)));
//         System.out.println("Tan of 90: " + Math.tan(Math.toRadians(90)));
//         System.out.println("Tan of 180: " + Math.tan(Math.toRadians(180)));
//         System.out.println("Tan of 270: " + Math.tan(Math.toRadians(270)));
//     }
// }

