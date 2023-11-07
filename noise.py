from perlin_noise import PerlinNoise



def main():

    noise = PerlinNoise(octaves=10, seed=1)
    rows , cols= 1000, 1000
    data  = [[noise([i/rows, j/ cols]) for j in range(cols)] for i in range(rows)]

    print("complete generating data")

    output = f"{rows} {cols}\n"


    for row in range(rows):
        line =  ""
        for col in range(cols):
            line += str(data[row][col]) + " "

        output += line.strip() + "\n"

    with open("noice.txt", "w") as f:
        f.write(output)
main()
