a = -0.5
b = 0.5
c = -0.5
d = 0.5
n = 7
for x in range(n):
    for y in range(n):
        step_x = 1/(n-1)*x
        step_y = 1/(n-1)*y
        #print(str(a+step_x)+'f,',str(1.0)+'f,',str(c+step_y)+'f,')
        print(str(a) + "+" + str(1.0)+"f/"+str(n-1)+'.0f*'+str(x)+'.0f,',str(1.0)+'f,', str(a) + "+" + str(1.0)+"f/"+str(n-1)+'.0f*'+str(y)+'.0f,')
i = 0
s = 20
for x in range(n):
    for y in range(n):
        if(i%n == n-1):
            i += 1
            continue
        if(i >= n*n-n):
            break
        print("{},{},{},{},{},{},".format(s+i,s+i+1,s+i+1+n,s+i,s+i+1+n,s+i+1+n-1))
        i += 1
