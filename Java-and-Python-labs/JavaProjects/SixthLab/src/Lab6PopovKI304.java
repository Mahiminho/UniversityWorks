import java.util.*;

/**
 * Class Lab6PopovKI304 realize example program to lab work 6
 * @author Popov Maxim
 * @version 1.1
 * @since version 1.0
 */
public class Lab6PopovKI304 {
    public static void main(String[] args) {
        City<? super LandPlot> city = new City<LandPlot>();
        city.AddLandPlot(new House("Four-story", 189, 850));
        city.AddLandPlot(new Shop("Flowers", 220));
        city.AddLandPlot(new Shop("Foxtrot", 510));
        city.AddLandPlot(new House("Nine-story", 533, 1150));
        LandPlot res1 = city.findMin();
        System.out.print("The smallest land plot in the city has: \n");
        res1.print();
        LandPlot res2 = city.findMax();
        System.out.print("The biggest land plot in the city has: \n");
        res2.print();
    }
}

/**
 * Interface <code>LandPlot</code> implements land plot
 */
interface LandPlot extends Comparable<LandPlot> {
    public int getSize();

    public void print();
}

/**
 * Parameterized class <code>City</code> implements city
 */
class City<T extends LandPlot> { // місто
    private ArrayList<T> arr;

    /**
     * Constructor
     */
    public City() {
        arr = new ArrayList<T>();
    }

    /**
     * Method find land plot with the smallest size
     */
    public T findMin() {
        if (!arr.isEmpty()) {
            T min = arr.get(0);
            for (int i = 1; i < arr.size(); i++) {
                if (arr.get(i).compareTo(min) < 0)
                    min = arr.get(i);
            }
            return min;
        }
        return null;
    }

    /**
     * Method find land plot with the biggest size
     */
    public T findMax() {
        if (!arr.isEmpty()) {
            T max = arr.get(0);
            for (int i = 1; i < arr.size(); i++) {
                if (arr.get(i).compareTo(max) > 0)
                    max = arr.get(i);
            }
            return max;
        }
        return null;
    }

    /**
     * Method add new land plot to city
     * 
     * @param <code>landplot</code> The class value
     */
    public void AddLandPlot(T landplot) {
        arr.add(landplot);
        System.out.print("Element added: ");
        landplot.print();
    }

    /**
     * Method delete land plot from city
     * 
     * @param <code>i</code> The index of element of array in city
     */
    public void DeleteLandPlot(int i) {
        arr.remove(i);
    }
}

class House implements LandPlot { // житловий будинок
    private String houseFloors;
    private int peopleLive;
    private int size;

    /**
     * Constructor
     * 
     * @param <code>hFlours</code> The house flours type
     * @param <code>pLive</code> The count of people who live in the house
     * @param <code>pSize</code> The size of house
     */
    public House(String hFloors, int pLive, int pSize) {
        houseFloors = hFloors;
        peopleLive = pLive;
        size = pSize;
    }

    /**
     * Method return house flours type
     * @return houseFloors
     */
    public String getHouseName() {
        return houseFloors;
    }

    /**
     * Method set house flours type for house
     * @param <code>name</code> The houseFloors type
     */
    public void setHouseName(String name) {
        houseFloors = name;
    }

    /**
     * Method return count of people who live in the house
     * @return peopleLive
     */
    public int getPeopleLive() {
        return peopleLive;
    }

    /**
     * Method set count of people who live in the house
     * @param <code>n</code> The peopleLive
     */
    public void setPeopleLive(int n) {
        peopleLive = n;
    }

    /**
     * Method return size of house
     * @return size
     */
    public int getSize() {
        return size;
    }

    /**
     * Method compare objects type LandPlot
     * @param <code>p</code> The size of object
     * @return num (0, 1, -1)
     */
    public int compareTo(LandPlot p) {
        Integer s = size;
        return s.compareTo(p.getSize());
    }

    /**
     * Method print information about house
     */
    public void print() {
        System.out.print("House: " + houseFloors + ", People live: " + peopleLive +
                ", House Size: " + size + ";\n");
    }
}

class Shop implements LandPlot { // магазин
    private String shopName;
    private int shopSize;

    /**
     * Constructor
     * 
     * @param <code>sName</code> The name of shop
     * @param <code>sSize</code> The size of shop
     */
    public Shop(String sName, int sSize) {
        shopName = sName;
        shopSize = sSize;
    }

    /**
     * Method return name of shop
     * @return shopName
     */
    public String getName() {
        return shopName;
    }

    /**
     * Method set name of shop
     * @param <code>n</code> The shopName
     */
    public void setName(String name) {
        shopName = name;
    }

    /**
     * Method set size of shop
     * @param <code>n</code> The shopSize
     */
    public void setSize(int n) {
        shopSize = n;
    }

    /**
     * Method return size of shop
     * @return size
     */
    public int getSize() {
        return shopSize;
    }

    /**
     * Method compare objects type LandPlot
     * @param <code>p</code> The size of object
     * @return num (0, 1, -1)
     */
    public int compareTo(LandPlot p) {
        Integer s = shopSize;
        return s.compareTo(p.getSize());
    }

    /**
     * Method print information about shop
     */
    public void print() {
        System.out.print("Shop Name: " + shopName + ", Shop Size: " + shopSize + ";\n");
    }
}
