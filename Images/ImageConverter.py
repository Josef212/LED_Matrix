from PIL import Image
import numpy as np
import os

# =========================================================
#RoboFace
IMAGE_PATH = "test.png"
IMAGE_NAME = os.path.splitext(IMAGE_PATH)[0]
OUT_TXT = IMAGE_NAME + ".txt"

# =========================================================

def ClampColor(v):
	return max(0, min(v, 255))

def rgb2hex(rgb):
	return "0x{:02x}{:02x}{:02x}".format(ClampColor(rgb[0]), ClampColor(rgb[1]), ClampColor(rgb[2]))

def hex2rgb(hex):
	return tuple(map(ord, hex[1:].decode('hex')))

def ConvertImage(image, output):

	rows = image.shape[0]
	columns = image.shape[1]

	output.write(IMAGE_NAME + "==========\t")
	output.write("Width: " + str(columns) + "\tHeight: " + str(rows) + "\n")
	output.write("const long " + IMAGE_NAME + "[] PROGMEM = \n{\n")


	for row in range(0, rows):
		line = "\t"
			
		# even: parells -- odd: imparells	
		# For even rows we must invert the pixel order since we start from 0 instead of even odd must be inverted

		start = 0
		end = columns
		step = 1
		if row % 2 != 0:
			start = columns - 1
			end = -1
			step = -1

		for col in range(start, end, step):
			line += rgb2hex(image[row, col])

			line += ", "

		# Remove the comma from the last row
		if row == rows - 1:
			line = line[:-1]

		line += "\n"

		output.write(line)

	output.write("};")

# =========================================================



img = Image.open(IMAGE_PATH)
img_array = np.asarray(img)


with open(OUT_TXT, 'w') as txt:
	ConvertImage(img_array, txt)

	txt.close()