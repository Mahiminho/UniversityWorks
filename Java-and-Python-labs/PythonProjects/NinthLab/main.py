import Dictaphone

# об'єкт на основі класу диктофон
dictaphone = Dictaphone.Dictaphone()

# використання методів класу за допомогою створеного об'єкта
dictaphone.repaintAudioPlayer("Purple")
dictaphone.getInfoLook()
dictaphone.getFullDynamicArea()
dictaphone.volumeUpButtonResource()
dictaphone.volumeDownButtonResource()
for i in range(5):
    dictaphone.volumeUp()
for i in range(3):
    dictaphone.volumeDown()
dictaphone.volumeMax()
dictaphone.volumeMin()
dictaphone.rebootAudioPlayer()
dictaphone.musicPlay()
dictaphone.addMemory(110)
dictaphone.Recording()
dictaphone.getMemory()

