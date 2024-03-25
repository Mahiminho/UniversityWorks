package pack;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

interface Sounding {
    void musicPlay();
}

/**
 * Class <code>Dictaphone</code> implements dictaphone
 */
public class Dictaphone extends AudioPlayer implements Sounding {
    /**
     * Constructor
     * 
     * @throws FileNotFoundException
     */
    private boolean possibillityOfRecording;
    private int amountOfMemory;

    public Dictaphone() throws FileNotFoundException {
        caseOfAudioPlayer = new Case();
        dynamicOfAudioPlayer = new Dynamic();
        volumeUpButton = new Button();
        volumeDownButton = new Button();

        possibillityOfRecording = true;
        amountOfMemory = 150;
        fout = new PrintWriter(new File("TxtFiles\\Log.txt"));
    }

    /** 
     * Constructor
     * 
     * @param <code>resource</code> Button clicks resource
     * @throws FileNotFoundException
     */
    public Dictaphone(int resource, int uAmountOfMemory) throws FileNotFoundException {
        caseOfAudioPlayer = new Case();
        dynamicOfAudioPlayer = new Dynamic();
        volumeUpButton = new Button(resource);
        volumeDownButton = new Button(resource);

        possibillityOfRecording = true;
        amountOfMemory = uAmountOfMemory;
        fout = new PrintWriter(new File("TxtFiles\\Log.txt"));
    }

    /**
     * Method provides information about the appearance of the audio player
     */
    public void getInfoLook() {
        System.out.println("Size of audio player: " + caseOfAudioPlayer.getSize() + " cm^2.");
        System.out.println("Weight of audio player: " + caseOfAudioPlayer.getWeight() + " g.");
        System.out.println("Color of audio player: " + caseOfAudioPlayer.getColor() + ".");
        System.out.println("Amount of memory of dictophone: " + amountOfMemory + " Mb.");
        fout.println("Size of audio player: " + caseOfAudioPlayer.getSize() + " cm^2.");
        fout.println("Weight of audio player: " + caseOfAudioPlayer.getWeight() + " g.");
        fout.println("Color of audio player: " + caseOfAudioPlayer.getColor() + ".");
        fout.println("Amount of memory of dictophone: " + amountOfMemory + " Mb.");
        fout.flush();
    }

    /**
     * Method simulate the rebooting of audio player
     */
    public void rebootAudioPlayer() {
        System.out.println("You reboot your audio player and the memory was cleared.");
        fout.println("You reboot your audio player and the memory was cleared.");
        amountOfMemory = 150;
        fout.flush();
    }

    /**
     * Method simulate music
     */
    public void musicPlay() {
        System.out.println("Music is playing.");
        fout.println("Music is playing.");
        fout.flush();
    }

    /**
     * Method change memory
     * 
     * @param <code>additionalMemory</code> The memory value
     */
    public void addMemory(int additionalMemory) {
        amountOfMemory += additionalMemory;
    }

    /**
     * Method recording audio
     */
    public void Recording() {
        if (possibillityOfRecording) {
            System.out.println("Audio is being recorded.");
            fout.println("Audio is being recorded.");
        } else {
            System.out.println("Audio is NOT being recorded.");
            fout.println("Audio is NOT being recorded.");
        }
        amountOfMemory -= 25;
        fout.flush();
    }

    /**
     * Method print amount of memory
     */
    public void getMemory() {
        System.out.println("Amount of memory of dictophone: " + amountOfMemory + " Mb.");
        fout.println("Amount of memory of dictophone: " + amountOfMemory + " Mb.");
        fout.flush();
    }

}
