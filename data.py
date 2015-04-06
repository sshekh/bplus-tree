import numpy

def main():
    f = open('time.out', "r")
    file_l = [[] for i in xrange(3)]
    time_l = [[] for i in xrange(3)]
    for line in f:
        type, time, file = map(int, line.split(" "))
        file_l[type].append(file)
        time_l[type].append(time)
        pass
    names = ["Insertion", "Point Query", "Range Query"]
    for type in range(3):
        print names[type]
        print "Stats for Running time (in microseconds)"
        print "Maximum ", numpy.max(time_l[type])
        print "Minimum ", numpy.min(time_l[type])
        print "Average ", numpy.mean(time_l[type])
        print "Standard Deviation", numpy.std(time_l[type])

        print "Stats for File Access"
        print "Maximum ", numpy.max(file_l[type])
        print "Minimum ", numpy.min(file_l[type])
        print "Average ", numpy.mean(file_l[type])
        print "Standard Deviation", numpy.std(file_l[type])
        print
        pass

        

if __name__ == "__main__":
    main()
