import pandas as pd
import time

def readData():
    # create a .csv from the excel file
    df = pd.read_excel('./haastepisteet.xlsx')
    df.to_csv('./haastepisteetdata.csv', index=False, sep=';', decimal=',')

    # enter the name and location of the data file
    # the current setting is that it reads haastepisteetdata.csv named file
    # from the directory the program is in
    filename = "./haastepisteetdata.csv"

    # give the file a status that makes the rest of the program skip actions
    try:
        topten = pd.read_csv(filename, delimiter=';', decimal=',')
    except FileNotFoundError:
        print(f'The file {filename} could not be found.')
        topten = None

    # just a debug print in terminal to see if the data read is solid
    # print(topten)
    return topten

def formatData(topten):
    # if the .csv couldn't be read, skip formatting
    if topten is None:
        return ", "
    
    max_name_length = topten['Kisaajat'].apply(len).max()
    max_points_length = topten['Kokonaispisteet'].astype(str).apply(len).max()

    # create indexing from 1 to 10 instead of 0 to 9 and align the columns neatly
    topten.index = range(1, len(topten) + 1)
    header_str = f"{'':<4} {'Kisaajat':<{max_name_length}} {'Kokonaispisteet':<{max_points_length}}\n"
    formatted_str = '\n'.join([f"{i:<4} {row['Kisaajat']:<{max_name_length}} {row['Kokonaispisteet']:<{max_points_length}}" for i, row in topten.iterrows()])

    return header_str, formatted_str

def writeFile(header, data):
    # write a new text file with formatted info as strings
    newfile_path = "./topten.txt"

    # write the file only if the .csv could be read and had data
    if header and data:
        with open(newfile_path, 'w') as newfile:
            newfile.write(header)
            newfile.write(data)

    newfile.close()

def main():
    print("Ctrl+C to exit program cleanly.")

    # run the loop infinitely, until the user inputs ctrl+c or closes the program
    # run the actions every 5 minutes
    try:
        while True:
            topten = readData()
            header, data = formatData(topten)
            writeFile(header, data)
            time.sleep(300)
    except KeyboardInterrupt:
        print("Program terminated by user.")

if __name__ == "__main__":
    main()