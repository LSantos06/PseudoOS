def process_list_file(name):
    f = open(name)
    l = []
    for line in f:
        l += [line]
    return l
