#!/usr/bin/python
'''
for simple data from user letters input, it is status= 1 for not executed and
status = 0 for the input already printed by the plotter

for image file from the user , it is status =2 for not executed and
status = 0 for the input already printed by the plotter

'''


import MySQLdb
import serial
import time
import os

pendingRequests=[]              #pending reif not line:quests to be plotted
payload=""
pendingRequest_id=[]
class plotter():
    def __init__(self):
        
        print("Establishing Link with arduino here for communication")
        #ser = serial.Serial(port ='/dev/ttyACM0',baudrate=9600) 
      

    def openFile(self):
        gcodeFile = open("test_gcode.ngc",'r')
        state=0
        
        while(1):

	        line = gcodeFile.readline()
	        if not line:
		        break
	        #self.sendGcodeSerially(line)

            

    def sendTheGcodeToArduino(self,p):
       print("Send gcode to arduino")

    def getPendingRequests(self):
        i=0
        for i in range(len(pendingRequests)):
            del pendingRequests[i]
            del pendingRequest_id[i]
        print("Accessing Database to get all the pending requests")
        print("Connecting to the database")
        db = MySQLdb.connect("localhost","omkar","helloworld2","GcodeGenerator" )
        cursor = db.cursor()
        sql = "SELECT * FROM dbrequest2 where status =1"
        try:
        # Execute the SQL command
            cursor.execute(sql)
            # Fetch all the ro/dev/ttyACM0ws in a list of lists.
            results = cursor.fetchall()
            for row in results: 
      
                _id = row[0]
                #print("ID")
                #print(_id)
                pendingRequest_id.append(_id)
                _data = row[1]
                pendingRequests.append(_data)
                _status= row[2]
               
                i=i+1     
        except: 
            print "Error: unable to fecth data"

    def showPendingRequests(self):

            for i in range(len(pendingRequests)):
               # self.separateLetters(pendingRequests[i])
                print(pendingRequests[i])
                print(pendingRequest_id[i])
            
    def separateLetters(self,payload):
        print str(payload)
        self.sendGcodeSerially(payload)
        # return and array with separated letters

    def goToNewLine(self,requests_to_be_executed):

        for i in range(len(requests_to_be_executed)):
            #print "Executing new line"
            ser=serial.Serial(port = '/dev/ttyACM0',baudrate = 9600)
            ser.flushInput()
            #print "Line Number"
            lineNumber = "#"+str(i)+"\n"
            #print lineNumber
            ser.write(lineNumber)
            time.sleep(2)
            if '.ngc' in requests_to_be_executed[i]:
                #print "Drawing Image"
                self.printingImage(requests_to_be_executed[i])
            else:
                self.sendGcodeSerially(requests_to_be_executed[i])
                self.updateStatus(pendingRequest_id[i])
            #del pendingRequest_id[i]
            #del requests_to_be_executed[i]
            


    def sendGcodeSerially(self,nth_request):
        separated_letters=[]
        for char in nth_request:
            separated_letters.append(char)

        #print "Letter Stripped"
        #for i in range(len(separated_letters)):
            #print(separated_letters[i])

        for i in range(len(separated_letters)):
        
            #print "Sending Letters serially"
            ser=serial.Serial(port ='/dev/ttyACM0',baudrate=9600)
            print separated_letters[i]
            #print "Character Position"
            #print i
            position= "*"+str(i)+"\n"
            #print position
            ser.write(position)
            filename= separated_letters[i]+".ngc"
            gcodeFile=open(filename,'r')
            ch =ser.read()
            if ch=='1':
                while(1):
                    try:
                        time.sleep(1)
                        if ch=='1':
                            #print(ch)
                            line = gcodeFile.readline()
                            
                            
                            if not line:
                                break
                            line=line.strip()
                            line= line +"\n"
                            ser.write(str(line))
                            #print(line)
                            #ser.flushOutput()
                            ch = ser.read()
                            #s/dev/ttyACM0er.flushInput()s
                    
                            time.sleep(0.2)
                    
                        else:
                            ch = ser.read()
                            #ser.flushInput()
                            #ser.flushOutput()
                            time.sleep(0.2)
                    except:
                        print "comm error"

            

            
                
            

    def updateStatus(self,updateID):
        print("Update status")     
        print updateID
        db = MySQLdb.connect("localhost","omkar","helloworld2","GcodeGenerator" )
        cursor = db.cursor()
        sql = "UPDATE dbrequest2 set status =0 where id ='%d'"% (updateID)
        try:
            cursor.execute(sql)
            db.commit()

        except:
            db.rollback()

        db.close()
        

       


    def sendGcodeSerially2(self,gcodeLine):
        self.state=0
        ser = serial.Serial(port ='/dev/ttyACM0',baudrate=9600)
      
        ser.flushOutput
        ser.write(gcodeLine)
        time.sleep(0.1)
          
    def readDataFromArduino(self):
        while(1):

            ser = serial.Serial(port ='/dev/ttyACM0',baudrate=9600)
            ser.flushInput()
            state=str(ser.read())
            if state=='1':
                print(state)
            else:
                print "invalid data"

            plotterObject.getPendingRequests()
    ''' 
        Printing Image

    '''
    def printingImage(self,imagefile):
        ser=serial.Serial(port ='/dev/ttyACM0',baudrate=9600)
        
        
        #print "Character Position"
         
        position= "*"+"1"+"\n"
        #print position
        ser.write(position)     
        filename=imagefile
        gcodeFile= open(filename,'r')
        ch=ser.read()
        if ch=='1':
                while(1):
                    try:
                        time.sleep(1)
                        if ch=='1':
                            #print(ch)
                            line = gcodeFile.readline()
                            
                            
                            if not line:
                                break
                            line=line.strip()
                            line= line +"\n"
                            ser.write(str(line))
                            #print(line)
                            #ser.flushOutput()
                            ch = ser.read()
                            #ser.flushInput()
                    
                            time.sleep(0.2)
                    
                        else:
                            ch = ser.read()
                            #ser.flushInput()
                            #ser.flushOutput()
                            time.sleep(0.2)
                    except:
                        print "comm error"


'''

printingImage function to print image

  print gcodeLines
'''            
   

if __name__ == "__main__":
    plotterObject = plotter()
    while(1):
    
        plotterObject.getPendingRequests()
       # plotterObject.showPendingRequests()
        plotterObject.goToNewLine(pendingRequests)

        time.sleep(10)

  
    
