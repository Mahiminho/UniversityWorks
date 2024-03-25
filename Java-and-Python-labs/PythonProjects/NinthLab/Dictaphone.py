from AudioPlayer import AudioPlayer

# клас диктофон
class Dictaphone(AudioPlayer):
    # конструктор
    def __init__(self):
        super().__init__()
        self.__possibillityOfRecording = True
        self.__amountOfMemory = 150

    # метод симулює програвання музики
    def musicPlay(self):
        print("Music is playing.")

    # метод додає пам'ять диктофону
    def addMemory(self, additionalMemory):
        self.__amountOfMemory += additionalMemory

    # метод симулює процес запису диктофоном
    def Recording(self):
        if self.__possibillityOfRecording:
            print("Audio is being recorded.")
        else:
            print("Audio is NOT being recorded.")
        self.__amountOfMemory -= 25

    # метод повертає розмір пам'яті диктофона
    def getMemory(self):
        print("Amount of memory of dictophone: " + str(self.__amountOfMemory) + " Mb.")



    








