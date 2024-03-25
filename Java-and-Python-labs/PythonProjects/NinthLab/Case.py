# клас корпус
class Case:
    #конструктор
    def __init__(self):
        self.__color = "White"
        self.__length = 5.5
        self.__width = 3.1
        self.__height = 1.4
    
    # метод встановлює колір корпусу
    def setColor(self, newColor):
        self.__color = newColor

    # метод повертає колір корпусу
    def getColor(self):
        return self.__color

    # метод повертає розмір корпусу
    def getSize(self):
        return self.__length * self.__width

    # метод повертає вагу корпусу (густина пластмасу 2.2 грам / см^3)
    def getWeight(self):
        return self.__height * self.__length * self.__width * 2.2