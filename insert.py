LINES = 100000

def main():
    f = open('assgn2_bplus_data.txt', "r")
    lines = f.readlines()
    for i in xrange(LINES):
        print '0 ' + lines[i],
        #print '0 ', i / 500.0, " lol" 
        pass
    f.close()
    pass

if __name__ == "__main__":
    main()

