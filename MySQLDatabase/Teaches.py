import mysql.connector

cnx = mysql.connector.connect(user='cmoneal', password='829812390',
                              host='127.0.0.1',
                              port='8080',
                              database='cmoneal')
cursor = cnx.cursor()

add_teach = ("INSERT INTO Teaches"
            "(class_id,section_id,semester,emp_id) "
            "VALUES (%s, %s, %s, %s)")

with open("Prof_Class.txt") as afile:
    for line in afile:
        data = line.split(",")
        print data 
        class_id = data[0].strip()
        section_id = data[1].strip()
        semester = data[2].strip()
        emp_id = data[3].strip()
        data_teach = (class_id, section_id, semester, emp_id)
        cursor.execute(add_teach, data_teach)
    cnx.commit()