from PIL import Image

rawData = open("frame.bin", 'rb').read()
imgSize = (1280,720)
img = Image.frombytes('RGB', imgSize, rawData)
img.save("foo.jpg")