from Case import Case
from Dynamic import Dynamic
from Button import Button

# клас аудіоплеєр
class AudioPlayer:
    # конструктор
    def __init__(self):
        self.__caseOfAudioPlayer = Case()
        self.__dynamicOfAudioPlayer = Dynamic()
        self.__volumeUpButton = Button()
        self.__volumeDownButton = Button()

    # метод змінює колір корпусу аудіоплеєра
    def repaintAudioPlayer(self, uColor):
        self.__caseOfAudioPlayer.setColor(uColor)
        print("New color of audio player is " + uColor + ".")

    # метод повертає повну інформацію про зовнішній вигляд аудіоплеєра
    def getInfoLook(self):
        print("Size of audio player: " + str(self.__caseOfAudioPlayer.getSize()) + " cm^2.")
        print("Weight of audio player: " + str(self.__caseOfAudioPlayer.getWeight()) + " g.")
        print("Color of audio player: " + str(self.__caseOfAudioPlayer.getColor()) + ".")

    # метод повертає площу, яку займають динаміки на аудіоплеєрі
    def getFullDynamicArea(self):
        print("Dynamics occupy " + str(self.__dynamicOfAudioPlayer.getArea() * 2) + " cm^2 of size.")

    # метод виводить ресурс кнопки збільшення гучності
    def volumeUpButtonResource(self):
        print("You can tap the volume up button " + str(self.__volumeUpButton.getResource()) + " more times.")

    # метод виводить ресурс кнопки зменшення гучності
    def volumeDownButtonResource(self):
        print("You can tap the volume down button " + str(self.__volumeDownButton.getResource()) + " more times.")

    # метод симулює натискання на кнопку збільшення гучності
    def volumeUp(self):
        self.__volumeUpButton.clickButton(True)
        print("You tap the volume up button.")
        if self.__dynamicOfAudioPlayer.getLoudness() > 100:
            self.__dynamicOfAudioPlayer.setLoudness(100)

    # метод симулює натискання на кнопку зменшення гучності
    def volumeDown(self):
        self.__volumeDownButton.clickButton(False)
        print("You tap the volume down button.")
        if self.__dynamicOfAudioPlayer.getLoudness() < 0:
            self.__dynamicOfAudioPlayer.setLoudness(0)

    # метод симулює затискання кнопки зменшення гучності
    def volumeMin(self):
        self.__volumeDownButton.clickButton(False)
        print("You press the volume down button.")
        self.__dynamicOfAudioPlayer.setLoudness(0)

    # метод симулює затискання кнопки збільшення гучності
    def volumeMax(self):
        self.__volumeUpButton.clickButton(True)
        print("You press the volume up button.")
        self.__dynamicOfAudioPlayer.setLoudness(100)

    # метод симулює перезавантаження аудіоплеєра
    def rebootAudioPlayer(self):
        print("You reboot your audio player.")











