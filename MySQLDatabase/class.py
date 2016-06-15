import mysql.connector
from datetime import date, datetime, timedelta

cnx = mysql.connector.connect(user='cmoneal', password='829812390',
                              host='127.0.0.1',
                              port='8080',
                              database='cmoneal')

cursor = cnx.cursor()

add_class = ("INSERT INTO Class "
             "(class_id , credits, description) "
             "VALUES (%s, %s, %s)")
add_pre = ("INSERT INTO Pre_req "
             "(class_id , pre_req) "
             "VALUES (%s, %s)")

add_section = ("INSERT INTO Section "
             "(class_id , section_id, semester, time, days, class_room) "
             "VALUES (%s, %s, %s, %s, %s, %s)")

with open("Class.txt") as afile:
    classk = ""
    section = ""
    for line in afile:
        line_lengths = (len(line) - len(line.lstrip()))
        data = line.strip().split(",")
        #print line_lengths
        if line_lengths == 0:
            classk = data[0].strip()
            credits = data[1].strip()
            title = data[2].strip()
            pre_req = "NULL"
            data_class = (classk, credits, title)
            cursor.execute(add_class, data_class)
            if len(data) >= 4:
                for i in range(len(data[3:])):
                    str1 = ' '.join(data[3:])
                    str1 = str1.strip().split(" ")
                    pre_req = data[3+i].strip()
                    data_pre = classk, pre_req
                    cursor.execute(add_pre, data_pre)
                    
        else:
            section = data[0].strip()
            semester = data[1].strip()
            s = data[2].split(" ")
            time = ' '.join(s[1:7])
            time = time.split(" ")
            time = ' '.join(time[:3])
            days = s[4]
            building = data[3].strip()
            
            data_section = (classk, section, semester, time, days, building)
            cursor.execute(add_section, data_section)
            

cnx.commit()
cursor.close()
cnx.close()