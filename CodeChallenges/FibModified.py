
A,B,N = raw_input().split()
A = int(A)
B = int(B)
N = int(N)

found = [-1] * 21 # Constraints: 3<=N<=20

def fibonMod(n):
    if(n == 1):
        return A;
    elif(n == 2):
        return B;
    elif(found[n] != -1):
        return found[n];
    else:
        found[n] = (fibonMod(n-1)**2) + fibonMod(n-2)
        return found[n]
    

print fibonMod(N)
