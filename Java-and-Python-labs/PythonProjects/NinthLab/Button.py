# клас кнопка
class Button:
    # конструктор
    def __init__(self):
        self.__btnResource = 999999999
        self.__count = 0

    # метод симулює натискання на кнопку
    def clickButton(self, type):
        if type:
            self.__btnResource -= 1
            self.__count += 1
        else:
            self.__btnResource -= 1
            self.__count -= 1
    
    # метод повертає ресурс кнопки
    def getResource(self):
        return self.__btnResource

    # метод повертає кількість натисків на кнопку за раз
    def getCountClicks(self):
        return self.__count