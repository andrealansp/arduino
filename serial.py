import speech_recognition as sr
from time import ctime
import time
import os
from gtts import gTTS
import serial


def speak(audiostring):
    print(audiostring)
    tts = gTTS(text=audiostring, lang='pt')
    tts.save("audio.mp3")
    os.system("audio.mp3")

def recordAudio():
    # Record Audio
    r = sr.Recognizer()
    with sr.Microphone() as source:
        print("Say something!")
        audio = r.listen(source)

    # Speech recognition using Google Speech Recognition
    data = ""
    try:
        # Uses the default API key
        # To use another API key: `r.recognize_google(audio, key="GOOGLE_SPEECH_RECOGNITION_API_KEY")`
        data = r.recognize_google(audio)
        print("Você disse: " + data)
    except sr.UnknownValueError:
        print("Não foi possível identificar o que foi dito !")
    except sr.RequestError as e:
        print("Could not request results from Google Speech Recognition service; {0}".format(e))

    return data


def jarvis(data):
    if "how are you" in data:
        speak("Eu vou bem,Obrigado por perguntar!")

    if "What Time is it" in data:
        speak(ctime())

    if "where is" in data:
        data = data.split(" ")
        location = data[2]
        speak("Hold on Frank, I will show you where " + location + " is.")
        os.system("chromium-browser https://www.google.nl/maps/place/" + location + "/&amp;")

    if "play" in data:
        ser = serial.Serial('COM4', 9600)
        print(ser.name)
        ser.write(b'a1')
        ser.close()

    if "stop" in data:
        ser = serial.Serial('COM4', 9600)
        print(ser.name)
        ser.write(b'a0')
        ser.close()


# initialization
time.sleep(2)
speak("Olá Me chamo baby, em que posso te ajudar?")
while 1:
    data = recordAudio()
    jarvis(data)
