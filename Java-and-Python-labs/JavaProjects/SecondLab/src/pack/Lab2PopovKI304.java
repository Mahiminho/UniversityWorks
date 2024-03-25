package pack;

import java.io.FileNotFoundException;

/**
 * Class App realize example program to lab work 2
 * @author Popov Maxim
 * @version 1.1
 * @since version 1.0
 */
public class Lab2PopovKI304 {
    /**
     * @param args
     * @throws FileNotFoundException
     */
    public static void main(String[] args) throws Exception {
        AudioPlayer audioplayer1 = new AudioPlayer(454445);
        audioplayer1.repaintAudioPLayer("Purple");
        audioplayer1.getInfoLook();
        audioplayer1.getFullDynamicsArea();
        audioplayer1.volumeUpButtonResource();
        audioplayer1.volumeDownButtonResource();
        for (int i = 0; i < 6; i++) {
            audioplayer1.volumeUp();
        }
        for (int i = 0; i < 3; i++) {
            audioplayer1.volumeDown();
        }
        audioplayer1.volumeMax();
        audioplayer1.volumeMin();
        audioplayer1.rebootAudioPlayer();
    }
}
