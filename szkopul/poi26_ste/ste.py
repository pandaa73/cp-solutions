S = 1000

if __name__ == "__main__":
    k = int(input())
    role = input()

    if role == "encoder":
        n = int(input())
        message = input()

        for i in range(k):
            for j in range(k):
                print('0', end='')
            print('\n')
        
    elif role == "decoder":
        for i in range(k):
            input()
        print("odszyfrowano\n")
        
    else:
        exit(1)