LINES = 40

def main():
    f = open('assgn2_bplus_data.txt', "r")
    lines = f.readlines()
    for i in xrange(40):
        print '0 ' + lines[i],
        #print '0 ', i / 500.0, " lol" 
        pass
    f.close()
    pass

if __name__ == "__main__":
    main()

