# This program automatically sorts files in their folders.

import os

#import os imports all the OS functions required for this program such as checking if a folder exists, creating folder,
#listing directories etc.

#Step 1: Creating function which makes folder (if it does not exist)

def folder(name):
    if not os.path.exists(name):
        os.makedirs(name)

#Step 2: Identifying file extensions and placing files in folders

files = os.listdir()
# files.remove("filesSorter.py")
# --> it contains the list of all folders in the directory where the program is run.

for file in files:
    print(file)
    arrofimgsformats = [".png",".jpeg",".jpg", ".bmp", ".tiff"]
    for x in range(len(arrofimgsformats)):
        if arrofimgsformats[x] in file:
            print("This is an IMAGE file.")
            folder("IMAGE")
            os.replace(file, f"IMAGE/{file}")
            break
    arrofvidformats = [".mp4", ".mkv", ".mov", ".avi"]
    for x in range(len(arrofvidformats)):
        if arrofvidformats[x] in file:
            print("This is a VIDEO file.")
            folder("VIDEO")
            os.replace(file, f"VIDEO/{file}")
            break
    arrofsoundformats = [".mp3", ".wav", ".aac"]
    for x in range(len(arrofsoundformats)):
        if arrofsoundformats[x] in file:
            print("This is a SOUND file.")
            folder("SOUND")
            os.replace(file, f"SOUND/{file}")
            break
    if ".py" in file:
        print("This is a PYTHON program.")
        folder("PYTHON")
        os.replace(file, f"PYTHON/{file}")
    if ".zip" in file or ".7z" in file:
        print("This is a ZIP file.")
        folder("ZIP")
        os.replace(file, f"ZIP/{file}")
    arrofdocformats = [".txt", ".csv", ".doc", ".pdf", ".xls", ".docx", ".xlsx"]
    for x in range(len(arrofdocformats)):
        if arrofdocformats[x] in file:
            print("This is a DOCUMENT file.")
            folder("DOCUMENT")
            os.replace(file, f"DOCUMENT/{file}")
            break
    
    
    #this input makes the program run without code editor like .exe files
input()
