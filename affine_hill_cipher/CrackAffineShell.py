import numpy as np
import time
import sys

charTable = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4,
             'F': 5, 'G': 6, 'H': 7, 'I': 8, 'J': 9,
             'K': 10, 'L': 11, 'M': 12, 'N': 13, 'O': 14,
             'P': 15, 'Q': 16, 'R': 17, 'S': 18, 'T': 19,
             'U': 20, 'V': 21, 'W': 22, 'X': 23, 'Y': 24,
             'Z': 25}

def charTOnum(text):
    num= []
    for i in range(len(text)):
        num.append(charTable[text[i]])
    return num

def cutNumList(numList, mSize):
    matrix = []
    for i in range((int)(len(numList) / mSize)):
        matrix.append(numList[(i * mSize):(i * mSize + mSize)])
    return matrix

def getInverse_Mod(value, mod):
    inverse = 0
    for i in range(mod):
        if (value * i) % mod == 1:
            inverse = i
            break
    return inverse

def getInverseMatrix_Mod(matrix, mod):
    mat = np.mat(matrix)
    InverseMat = np.linalg.inv(mat)
    MatrixDet = (int)(np.linalg.det(mat))
    companionMat = (MatrixDet * InverseMat) % mod
    temp = getInverse_Mod(MatrixDet, mod)
    return (temp * companionMat) % mod

def main():
    temp = sys.stdout
    with open("Record.log", "a+") as file:
        sys.stdout = file

        print("-------------------------------------------------------------------")
        print("Record time:", time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())), "\n")
        Plaintext = "ADISPLAYEDEQUATION"
        Ciphertext = "DSRMSIOPLXLJBZULLM"
        mSize = 3
        print("We know the plaintext is:\t", Plaintext, "\nit's ciphertext is:\t\t", Ciphertext)
        print("The size of Key matrix and vector 'b' is:", mSize)
        plaList = charTOnum(Plaintext)
        cipList = charTOnum(Ciphertext)
        cipMatrix = cutNumList(cipList, mSize)
        plaMatrix = cutNumList(plaList, mSize)
        print("Change the letters in ciphertext into number(0-26):\n", cipList)
        print("Change the letters in plaintext into number(0-26):\n", plaList, "\n")

        print("Can get 6 equations:")
        for i in range(len(cipMatrix)):
            print(cipMatrix[i], "\t= ", plaMatrix[i], "\t* E_k + b")
        pla = []
        cip = []
        for i in range((int)(len(cipMatrix) / mSize)):
            pla.append(plaMatrix[(i * mSize): (i * mSize) + mSize])
            cip.append(cipMatrix[(i * mSize): (i * mSize) + mSize])

        print("\nChoose 3 equations as a group, can build 2 linear equations(matrix):")
        for i in range(len(pla)):
            print(cip[i], "\t= ", pla[i], "\t* E_k + b")

        print("\nUse the 'line2 - line1', we can get this equation(mod 26):")
        left = []
        right = []
        for i in range(mSize):
            c = []
            p = []
            for j in range(mSize):
                c.append(cip[1][i][j] - cip[0][i][j])
                p.append(pla[1][i][j] - pla[0][i][j])
            left.append(c)
            right.append(p)
        print(left, " = ", right, " * E_k")
        left_matrix = np.mat(left)
        right_matrix = np.mat(right)
        Inverse_right = getInverseMatrix_Mod(right_matrix, 26)
        print("\nWe can get the inveerse of right matrix(mod 26):\n", Inverse_right)
        keyMatrix = (Inverse_right * left_matrix) % 26
        print("\nThen we get the matrix of key:\n", keyMatrix)
        cipMat = np.mat(cipMatrix[0])
        plaMat = np.mat(plaMatrix[0])
        b = (cipMat - (plaMat * keyMatrix)) % 26
        print("\nThen, solve one of the equations above the 6 lines, the vector 'b' is:\n", b)
        print("-------------------------------------------------------------------")
        sys.stdout = temp
        print(file.readlines())
    return


if __name__ == '__main__':
    main()
