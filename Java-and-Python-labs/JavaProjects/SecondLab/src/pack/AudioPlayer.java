package pack;
import java.io.*;

/**
 * Class <code>AudioPlayer</code> implements audio player
 */
public class AudioPlayer {
    private Case caseOfAudioPlayer;
    private Dynamic dynamicOfAudioPlayer;
    private Button volumeUpButton;
    private Button volumeDownButton;
    private PrintWriter fout;
    static int volume;

    /**
     * Constructor
     * 
     * @throws FileNotFoundException
     */
    public AudioPlayer() throws FileNotFoundException {
        caseOfAudioPlayer = new Case();
        dynamicOfAudioPlayer = new Dynamic();
        volumeUpButton = new Button();
        volumeDownButton = new Button();
        fout = new PrintWriter(new File("TxtFiles\\Log.txt"));
    }

    /**
     * Constructor
     * 
     * @param <code>resource</code> Button clicks resource
     * @throws FileNotFoundException
     */
    public AudioPlayer(int resource) throws FileNotFoundException {
        caseOfAudioPlayer = new Case();
        dynamicOfAudioPlayer = new Dynamic();
        volumeUpButton = new Button(resource);
        volumeDownButton = new Button(resource);
        fout = new PrintWriter(new File("TxtFiles\\Log.txt"));
    }

    /**
     * Method change color of audio player
     */
    public void repaintAudioPLayer(String uCollor) {
        caseOfAudioPlayer.setColor(uCollor);
        System.out.println("New color of audio player is " + uCollor + ".");
        fout.println("New color of audio player is " + uCollor + ".");
        fout.flush();
    }

    /**
     * Method provides information about the appearance of the audio player
     */
    public void getInfoLook() {
        System.out.println("Size of audio player: " + caseOfAudioPlayer.getSize() + " cm^2.");
        System.out.println("Weight of audio player: " + caseOfAudioPlayer.getWeight() + " g.");
        System.out.println("Color of audio player: " + caseOfAudioPlayer.getColor() + ".");
        fout.println("Size of audio player: " + caseOfAudioPlayer.getSize() + " cm^2.");
        fout.println("Weight of audio player: " + caseOfAudioPlayer.getWeight() + " g.");
        fout.println("Color of audio player: " + caseOfAudioPlayer.getColor() + ".");
        fout.flush();
    }

    /**
     * Method provides information about the area of all dynamics
     */
    public void getFullDynamicsArea() {
        System.out.println("Dynamics occupy " + dynamicOfAudioPlayer.getArea() * 2 + " cm^2 of size.");
        fout.println("Dynamics occupy " + dynamicOfAudioPlayer.getArea() * 2 + " cm^2 of size.");
        fout.flush();
    }

    /**
     * Method provides information about the count of clicks of volume up button
     */
    public void volumeUpButtonResource() {
        System.out.println("You can tap the volume up button " + volumeUpButton.getResource() + " more times.");
        fout.println("You can tap the volume up button " + volumeUpButton.getResource() + " more times.");
        fout.flush();
    }

    /**
     * Method provides information about the count of clicks of volume down button
     */
    public void volumeDownButtonResource() {
        System.out.println("You can tap the volume up button " + volumeDownButton.getResource() + " more times.");
        fout.println("You can tap the volume up button " + volumeDownButton.getResource() + " more times.");
        fout.flush();
    }

    /**
     * Method simulate the volume up button tap
     */
    public void volumeUp() {
        volumeUpButton.clickButton(true);
        System.out.println("You tap the volume up button.");
        fout.println("You tap the volume up button.");
        fout.flush();

        if (dynamicOfAudioPlayer.getLoudness() > 100) {
            dynamicOfAudioPlayer.setLoudness(100);
        }
    }

    /**
     * Method simulate the volume up button tap
     */
    public void volumeDown() {
        volumeDownButton.clickButton(false);
        System.out.println("You tap the volume down button.");
        fout.println("You tap the volume down button.");
        fout.flush();

        if (dynamicOfAudioPlayer.getLoudness() < 0) {
            dynamicOfAudioPlayer.setLoudness(0);
        }
    }

    /**
     * Method simulate the volume down button press
     */
    public void volumeMin() {
        volumeDownButton.clickButton(false);
        System.out.println("You press the volume down button.");
        fout.println("You press the volume down button.");
        fout.flush();
        dynamicOfAudioPlayer.setLoudness(0);
    }

    /**
     * Method simulate the volume up button press
     */
    public void volumeMax() {
        volumeUpButton.clickButton(false);
        System.out.println("You press the volume up button.");
        fout.println("You press the volume up button.");
        fout.flush();
        dynamicOfAudioPlayer.setLoudness(100);
    }

    /**
     * Method simulate the rebooting of audio player
     */
    public void rebootAudioPlayer() {
        System.out.println("You reboot your audio player.");
        fout.println("You reboot your audio player.");
        fout.flush();
    }
}

/**
 * Class <code>Case</code> implements case of audio player
 * 
 * @author Maxim Popov
 * @version 1.0
 */
class Case {
    private String color;
    private double length, width, height;

    /**
     * Constructor
     */
    public Case() {
        color = "White";
        length = 5.5;
        width = 3.1;
        height = 1.4;
    }

    /**
     * Method sets new color of case of audio player
     * 
     * @param <code>newColor</code> The color value
     */
    public void setColor(String newColor) {
        color = newColor;
    }

    /**
     * Method gets color of case of audio player
     */
    public String getColor() {
        return color;
    }

    /**
     * Method gets size of case of audio player in cm^2
     */
    public double getSize() {
        return length * width;
    }

    /**
     * Method gets weight of case of audio player in grams
     */
    public double getWeight() {
        return length * width * height * 2.2;
    }
}

/**
 * Class <code>Dynamic</code> implements dynamic of audio player
 * 
 * @author Maxim Popov
 * @version 1.0
 */
class Dynamic {
    private double diametr, loudness;

    /**
     * Constructor
     */
    public Dynamic() {
        diametr = 0.9;
        loudness = 50;
    }

    /**
     * Constructor
     * 
     * @param <code>uLoudness</code> The loudness value
     */
    public Dynamic(int uLoudness) {
        diametr = 0.9;
        loudness = uLoudness;
    }

    /**
     * Method gets area of dynamics of audio player in cm^2
     */
    public double getArea() {
        return 3.14 * (diametr / 2) * (diametr / 2);
    }

    /**
     * Method returns resource of button
     * 
     */
    public double getLoudness() {
        return loudness;
    }

    /**
     * Method sets new loudness of dynamics of audio player
     * 
     * @param <code>newLoudness</code> The loudness value
     */
    public void setLoudness(double newLoudness) {
        if (newLoudness < 0 || newLoudness > 100) {
            System.out.println("Incorrectly specified volume!");
        } else {
            loudness = newLoudness;
        }
    }
}

/**
 * Class <code>Button</code> implements buttons of audio player
 * 
 * @author Maxim Popov
 * @version 1.0
 */
class Button {
    // Button clicks resource
    private int btnResource, count;

    /**
     * Constructor
     */
    public Button() {
        btnResource = 999999999;
        count = 0;
    }

    /**
     * Constructor
     * 
     * @param <code>res</code> Button clicks resource
     */
    public Button(int res) {
        btnResource = res;
        count = 0;
    }

    /**
     * Method simulates Button clicking
     */
    public void clickButton(boolean type) {
        if (type) {
            btnResource--;
            count++;
        } else {
            btnResource--;
            count--;
        }
    }

    /**
     * Method returns resource of button
     * 
     */
    public int getResource() {
        return btnResource;
    }

    /**
     * Method returns how many times the user clicked on the button at one time
     * 
     * @return Button clicks
     */
    public int getCountClicks() {
        return count;
    }

}
