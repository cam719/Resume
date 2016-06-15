import mysql.connector
from datetime import date, datetime, timedelta

cnx = mysql.connector.connect(user='cmoneal', password='829812390',
                              host='127.0.0.1',
                              port='8080',
                              database='cmoneal')

cursor = cnx.cursor()


with open("Student.txt") as afile:
    for line in afile:
#        line_lengths = (len(line) - len(line.lstrip()))
#        print line_lengths
        data = line.split(",")
        student_id = data[0]
        major = data[3].strip()
        
        #names
        name = data[1].split(" ")
        first_name = name[1]
        last_name = name[2]
        
        
        bday = data[2]
        bday = bday.split("/")
        year = bday[2]
        day = bday[1]
        month = bday[0]
        print bday
        
        add_student = ("INSERT INTO Student "
                        "(student_id,first_name, last_name,birth_date, major) "
                        "VALUES (%s, %s, %s, %s, %s)") 
        
        data_student = (student_id, first_name, last_name, date(int(year), int(month), int(day)), major)
        cursor.execute(add_student, data_student)
        
    cnx.commit()
    cursor.close()
    cnx.close()        