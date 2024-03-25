# клас динамік
class Dynamic:
    # конструктор
    def __init__(self):
        self.__diametr = 0.9
        self.__loudness = 50

    # метод повертає площу динаміка
    def getArea(self):
        return 3.14 * (self.__diametr / 2)**2

    # метод повертає гучність динаміка
    def getLoudness(self):
        return self.__loudness

    # метод втановлює гучність динаміка
    def setLoudness(self, newLoudness):
        if newLoudness < 0 or newLoudness > 100:
            return "Incorrectly specified volume!"
        else:
            self.__loudness = newLoudness
