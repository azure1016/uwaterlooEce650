import a1ece650
# try:
#    # str_read = stdin("enter your command: a add c change r remove g output graph:")
#     str_read = 'a "Weber Street" (12,20) (2,1) (3,4)'

#     cmd = re.search(r'(?P<op>[acrg])\s+"(?P<street>(\w+\s*)+)"\s+(?P<coordinates>\(.*?\)\s*)+',str_read)
#     print(cmd.groups())
#     #cor = re.findall(r'.*?\((\d+),.*?\)',str_read)
#     #cmd = re.search(r'\([0-9]*\.?[0-9]+,[0-9]*\.?[0-9]+\)\s+',str_read)  
#     #py = re.findall(r'.*?\(.*?,(\d+)\)',str_read)
#     teststr = '(0,1) (1,2)'
#     #cmd = re.search(r'\([0-9]\d*,[0-9]\d*\)',str_read) 
#     if True:
#         res = cmd.groupdict()
#         print(res['coordinates']+" is digits")
#         if cor: 
#           # px = cor['x']
#            print cor
#         if py:
#            #res['coordinates'] = cor
#            print(py)
#         if res['op'] == 'a':
#            pass
           
#     else: 
#         print("nothing found")
# #actually can be processed with one exception
# except BaseException:
#     pass
# finally:
#     pass

try: 
    ns = Street()
    print "please input the command:"
    while True:
        std_read = sys.stdin.readline()#[:-1] #discard '\n' at the end
        #I heard that stdin will get a \n
        #std_read = a "King Street" (2,1) (1.2,2.3) (4.2,2)       
        if ns.isValidCmd(std_read):
            ns.process_cmd(std_read)
except exception1:
    pass
            
#test case:
#input1: a "King Street" (2,1) (1.2,2.3) (4.2,2) #float match
#input2: a "King street" (3,4) (4,5) #add an existing street
#input3: a "weber street" (2,3) #add/change a street with one point
#input4: a "university ave" (2,3) (3,6)(9,0) #missing space between coordinates
#input5: a " King street west" (3,2) (2,5) #extra space on the cmd
#input6:   c  " university  ave " (2,3 ) (4   ,6) #extra space on the cmd
#input7: c "cedarbrae avenue" (3,4) (1,3)
#input8: c "king street" (3,4) (1,2) #smaller case
#input:  a "albert street" (2,1) (1,2,2.3) #street overlap

#please format the float as 0.2f
#denominator == 0, is it exactly 0?