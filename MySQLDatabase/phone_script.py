import mysql.connector

cnx = mysql.connector.connect(user='cmoneal', password='829812390',
                              host='127.0.0.1',
                              port='8080',
                              database='cmoneal')
cursor = cnx.cursor()

add_phone = ("INSERT INTO Phone "
                           "(student_id, phone_number, phone_type) "
                           "VALUES (%s, %s, %s)")
with open("Student.txt") as afile:
    for line in afile:
        data = line.split(",")
        student_id = data[0]
        for i in range(len(data[4:])):
            phone = data[4:][i].replace(" ", "").strip()
            phone_type = 'NULL'
            if phone != 'None':
                phone_type = phone[13]
            data_phone = (student_id, phone[:12], phone_type)
            cursor.execute(add_phone, data_phone)

cnx.commit()
            
cursor.close()
cnx.close()
                        