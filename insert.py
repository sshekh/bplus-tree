def main():
    print "500"
    f = open('assgn2_bplus_data.txt', "r")
    lines = f.readlines()
    for i in xrange(500):
        print '0 ' + lines[i],
        pass
    pass

if __name__ == "__main__":
    main()

