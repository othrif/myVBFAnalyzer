# Print tables

regs=["SR", "CRW", "CRZ"]
procDict={"W_EWK":"EWK W", "Z_EWK":"EWK Z", "W_strong":"Strong W", "Z_strong":"Strong Z"}
vars=["renofact","pdf","qsf","ckkw"]

for var in vars:
    print("\n{}".format(var))
    with open('listTheorySyst', 'rt') as f:
        for line in f:
            for proc in procDict:
                if var in line and proc in line:
                    line=line.rstrip().split()[1].split(",")
                    x=[round(100*(float(i)-1),1) for i in line]
                    x_out="& {} & {} \% & {} \% & {} \% & {} \% & {} \% & {} \% & {} \% & {} \% & {} \% & {} \% & {} \% \\\\".format(procDict[proc], *x)
                    print(x_out)
