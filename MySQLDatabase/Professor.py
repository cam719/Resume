import mysql.connector

cnx = mysql.connector.connect(user='cmoneal', password='829812390',
                              host='127.0.0.1',
                              port='8080',
                              database='cmoneal')
cursor = cnx.cursor()

add_prof = ("INSERT INTO Professor "
                "(emp_id,first_name,last_name, dept_code) "
                "VALUES (%s, %s, %s, %s)")

add_qual = ("INSERT INTO Qualified "
           "(emp_id , crs_id) "
           "VALUES (%s, %s)")

with open("Professors.txt") as afile:
    for line in afile:
        data = line.split(",")
        #print data
        emp_id = data[0]
        name = data[1].strip().split(" ")
        first_name = name[0]
        last_name = name[1]
        #print first_name, last_name
        dept_code = data[2].strip()
        data_prof = (emp_id, first_name, last_name, dept_code)
        cursor.execute(add_prof, data_prof)
        #print major
        for i in range(len(data[3:])):
            classk = data[3:][i].replace(" ", "").strip()
            data_qual = (emp_id, classk)
            print classk
            cursor.execute(add_qual, data_qual)
        print "\n"
    cnx.commit()
            