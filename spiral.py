n = int(input())
endStr = n**2 - 1

arrTwoD = []

for i in range(n):
    currArr = []
    for j in range(n):
        currArr.append(0)
    arrTwoD.append(currArr)

x = 0
for i in range (n//2):
    for j in range (n-1-i, -1+i, -1):
        arrTwoD[i][j] = endStr - x
        x+=1
    for k in range (1+i, n-i):
        arrTwoD[k][i] = endStr - x
        x+=1
    for l in range (1+i, n-i):
        arrTwoD[n-i-1][l] = endStr - x
        x+=1
    for m in range(n-2-i, i, -1):
        arrTwoD[m][n-i-1] = endStr - x
        x+=1

for i in range(n):
    print(arrTwoD[i])

# email this at: bhardwajsapna04@gmail.com
