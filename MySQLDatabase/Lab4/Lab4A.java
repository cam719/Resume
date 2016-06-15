import java.io.File;
import java.io.PrintWriter;
import java.io.Writer;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class Lab4A {
	
	private String url, dbName, driverName, userName, password;
	private Connection con;
	private ResultSet rs;

	public Lab4A()
	{
		
		con = null;
		url = "jdbc:mysql://faure/";
		dbName = "cmoneal";
		driverName = "com.mysql.jdbc.Driver";
		userName = "cmoneal";
		password = "829812390";
		
	}
	public void readXML(String fileName)
	{
		try {
			Class.forName(driverName).newInstance();
			con = DriverManager.getConnection(url+dbName, userName, password);
		}catch(SQLException s)
		{	
			s.printStackTrace();
			return;
		} catch (InstantiationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		try {
			File file = new File(fileName);
			DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
			DocumentBuilder db = dbf.newDocumentBuilder();
			Document doc = db.parse(file);
			doc.getDocumentElement().normalize();
			NodeList nodeLst = doc.getElementsByTagName("section");

			for (int s = 0; s < nodeLst.getLength(); s++) {

				Node fstNode = nodeLst.item(s);

				if (fstNode.getNodeType() == Node.ELEMENT_NODE) {

					Element sectionNode = (Element) fstNode;
					
					NodeList classidElementList = sectionNode.getElementsByTagName("ClassId");
					Element classidElmnt = (Element) classidElementList.item(0);
					NodeList classidNodeList = classidElmnt.getChildNodes();
					//System.out.println("ClassId : "  + ((Node) classidNodeList.item(0)).getNodeValue().trim());
					
					String ClassId = ((Node) classidNodeList.item(0)).getNodeValue().trim();
					//System.out.println("ClassId : " + ClassId);
					
					NodeList secnoElementList = sectionNode.getElementsByTagName("SecNo");
					Element secnoElmnt = (Element) secnoElementList.item(0);
					NodeList secno = secnoElmnt.getChildNodes();
					//System.out.println("Section number : "  + ((Node) secno.item(0)).getNodeValue().trim());
					String section_number = ((Node) secno.item(0)).getNodeValue().trim();
					//System.out.println("Section number : " + section_number);
					
					NodeList semesterElementList = sectionNode.getElementsByTagName("Semester");
					Element semElmnt = (Element) semesterElementList.item(0);
					NodeList sem = semElmnt.getChildNodes();
					//System.out.println("Semester : "  + ((Node) sem.item(0)).getNodeValue().trim());
					String Semester = ((Node) sem.item(0)).getNodeValue().trim();
					
					//System.out.println("Semester : "  + Semester);
					
					NodeList empnoElementList = sectionNode.getElementsByTagName("Emp_no");
					Element empElmnt = (Element) empnoElementList.item(0);
					NodeList emp = empElmnt.getChildNodes();
					int emp_no = Integer.parseInt(((Node) emp.item(0)).getNodeValue().trim());
					//System.out.println("Professor : "  + emp_no);
					
					NodeList classroomElementList = sectionNode.getElementsByTagName("ClassRoom");
					Element classrmElmnt = (Element) classroomElementList.item(0);
					NodeList classrm = classrmElmnt.getChildNodes();
					String classroom = (String) classrm.item(0).getNodeValue().trim();
					//System.out.println("Class Room : "  + classroom);
					
					NodeList timeElementList = sectionNode.getElementsByTagName("Time");
					Element timeElmnt = (Element) timeElementList.item(0);
					NodeList time = timeElmnt.getChildNodes();
					String times = (String) time.item(0).getNodeValue().trim();
					//System.out.println("Time : "  + times);
					String[] splited = times.split("\\s+");
					String t = "";
					String days = "";
					for(int i = 0; i < 4; i++)
					{
						if(i == 3)
						{
							days += splited[3];
						}
						else
						{
							t += splited[i];
						}
					}
					//System.out.println(t);
					//System.out.println(days);
					//System.out.println();
					
					Statement stmt = con.createStatement();
					
					String sql1 = "SELECT crs_id FROM Qualified WHERE emp_id = '"+emp_no+"' AND crs_id = '"+ClassId+"' ;";
					rs = stmt.executeQuery(sql1);
					if(!rs.isBeforeFirst())
					{
						System.out.println("ERROR: TEACHER NOT QUALIFIED");
					}
					else
					{
					
					String sql = "INSERT INTO Section " +
			                   "VALUES ('"+ClassId+"', '"+section_number+"', '"+Semester+"', '"+t+"' , '"+days+"', '"+classroom+"')";
					stmt.executeUpdate(sql);
					
					sql = "INSERT INTO Teaches " +
			                   "VALUES ('"+ClassId+"', '"+section_number+"', '"+Semester+"', '"+emp_no+"')";
					stmt.executeUpdate(sql); 
					System.out.println("Added record to database");
					PrintWriter writer = new PrintWriter("oneal-output.txt", "UTF-8");
					rs = stmt.executeQuery("SELECT class_id, credits, section_id, time, days, first_name, last_name, class_room  FROM Section NATURAL JOIN Class NATURAL JOIN Teaches NATURAL JOIN Professor WHERE semester = 'SP16' ORDER BY class_id, section_id;");
					while(rs.next())
					{
						//System.out.println(rs.getString(1) + " " + rs.getString(2) + " " + rs.getString(3) + " " + rs.getString(4) + " " + rs.getString(5) + " " + rs.getString(6) + " " + rs.getString(7) + " " + rs.getString(8));
						writer.println(rs.getString(1) + " " + rs.getString(2) + " " + rs.getString(3) + " " + rs.getString(4) + " " + rs.getString(5) + " " + rs.getString(6) + " " + rs.getString(7) + " " + rs.getString(8));
					}
					writer.close();
					}
					
				
					
				}
				
			}
			Statement stmt = con.createStatement();
			rs = stmt.executeQuery("SELECT class_id, credits, section_id, time, days, first_name, last_name, class_room  FROM Section NATURAL JOIN Class NATURAL JOIN Teaches NATURAL JOIN Professor WHERE semester = 'SP16' ORDER BY class_id, section_id;");
			while(rs.next())
			{
				System.out.println(rs.getString(1) + " " + rs.getString(2) + " " + rs.getString(3) + " " + rs.getString(4) + " " + rs.getString(5) + " " + rs.getString(6) + " " + rs.getString(7) + " " + rs.getString(8));
				//writer.println(rs.getString(1) + " " + rs.getString(2) + " " + rs.getString(3) + " " + rs.getString(4) + " " + rs.getString(5) + " " + rs.getString(6) + " " + rs.getString(7) + " " + rs.getString(8));
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	

	public static void main(String args[]){
		try {

			Lab4A showXML = new Lab4A();
			showXML.readXML("newsemester.xml");
			
		}catch( Exception e ) {
			e.printStackTrace();

		}//end catch

	}//end main

}//end class 
