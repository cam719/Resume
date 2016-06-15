import mysql.connector
from datetime import date, datetime, timedelta

cnx = mysql.connector.connect(user='cmoneal', password='829812390',
                              host='127.0.0.1',
                              port='8080',
                              database='cmoneal')

cursor = cnx.cursor()

add_enrolled = ("INSERT INTO Enrolled "
             "(student_id,class_id , section_id, semester, grade, drop_date) "
             "VALUES (%s, %s, %s, %s, %s, %s)")
with open("Enrolled.txt") as afile:
    i = 0
    for line in afile:
        data = line.strip().split(",")
        student_id = data[0].strip()
        class_id = data[1].strip()
        section = data[2].strip()
        semester = data[3].strip()
        grade = data[4].strip()
        drop_date = "NULL"
        if grade != 'A' and grade != 'B' and grade != 'C' and grade != 'D' and grade != 'F':
            grade = "NULL"
            drop_date = data[4].strip()
            drop_date = drop_date.split("/")
            year = drop_date[2]
            day = drop_date[1]
            month = drop_date[0]            
            data_enrolled = (student_id,class_id,section,semester,grade,date(int(year), int(month), int(day)))
        else:
            data_enrolled = (student_id,class_id,section,semester,grade,drop_date)
            
        print section
        cursor.execute(add_enrolled, data_enrolled)

cnx.commit()
cursor.close()
cnx.close()
            