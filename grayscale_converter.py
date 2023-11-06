import cv2

def main():
    path = "./build/heightmap.png"
    image = cv2.imread(path, cv2.IMREAD_GRAYSCALE)
    rows, cols = image.shape

    output = f"{rows} {cols}\n"


    for row in range(rows):
        line =  ""
        for col in range(cols):
            line += str(image[row][col]) + " "

        output += line.strip() + "\n"

    with open(path.split("/")[-1] + ".txt", "w") as f:
        f.write(output)


if __name__ == "__main__":
    main()
