
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;

public class Lab4B
{
	private String url, dbName, driverName, userName, password;
	private Connection con;
	private ResultSet rs;
	private static String[] buttons1 = { "Yes", "No", "Cancel" };
	private static String[] buttons2 = { "Confirm", "Cancel" };
	Statement stmt;
	private JFrame mainFrame;
	private JLabel headerLabel;
	private JLabel statusLabel;
	private JPanel controlPanel;
	
	public Lab4B()
	{
	    con = null;
		url = "jdbc:mysql://faure/";
		dbName = "cmoneal";
		driverName = "com.mysql.jdbc.Driver";
		userName = "cmoneal";
		password = "829812390";
		
		
		try {
			Class.forName(driverName).newInstance();
			con = DriverManager.getConnection(url+dbName, userName, password);
		} catch (InstantiationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
	}

	public boolean enterNewStudentId(String value) throws InstantiationException, IllegalAccessException, ClassNotFoundException
	{
		try {
			Statement st = con.createStatement();
			String getst = "SELECT * FROM Enrolled WHERE student_id = '"+value+"';";
			rs = st.executeQuery(getst);
			if(!rs.isBeforeFirst())
			{
				JOptionPane.showMessageDialog(null, "Error: Invalid Student ID");
				
				 int rc = JOptionPane.showOptionDialog(null, "Add student for enrollment?", "Confirmation",
					        JOptionPane.INFORMATION_MESSAGE, 0, null, buttons1, buttons1[2]);
				if(rc == 0)
				{
					Statement stmt = con.createStatement();
					JOptionPane.showMessageDialog(null, "Enter information");
					String student_id = JOptionPane.showInputDialog (null, "Enter Student Id");
					String first_name = JOptionPane.showInputDialog (null, "Enter First Name");
					String last_name = JOptionPane.showInputDialog (null, "Enter Last Name");
					String birth_day = JOptionPane.showInputDialog (null, "Enter Birthday");
					String major = JOptionPane.showInputDialog (null, "Enter Major");
					String phone = JOptionPane.showInputDialog (null, "Enter Phone");
					String phone_type = JOptionPane.showInputDialog (null, "Enter Phone Type");
					String sql = "INSERT INTO Student " +
			                   "VALUES ('"+student_id+"', '"+first_name+"', '"+last_name+"', '"+birth_day+"' , '"+major+"')";
					stmt.executeUpdate(sql);
					sql = "INSERT INTO Phone " +
			                   "VALUES ('"+student_id+"', '"+phone+"', '"+phone_type+"')";
					stmt.executeUpdate(sql);
					return true; 
				}
			else
			{
				return false;
			}
		}
			while(rs.next()) {
			    //System.out.println(rs.getString(5));
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			System.out.print("ERROR");
			System.out.println(e);
			try {
				con.close();
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}
		return true;
	}
	public ArrayList<String> getClasses(String value)
	{
		ArrayList<String> classes = new ArrayList<String>();
		try {
			
			Statement stmt = con.createStatement();
			ResultSet rs = stmt.executeQuery("SELECT * FROM Enrolled WHERE student_id = '"+value+"' AND grade NOT LIKE 'NULL' AND GRADE NOT LIKE 'D';");
			while(rs.next())
			{
			//System.out.println(rs.getString("class_id"));
			classes.add(rs.getString(2));
			}   
			}
		   catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return classes;
	}
	
	public String enterStudentID()
	{
		String value = JOptionPane.showInputDialog ("Enter student id:");
		return value;
		
	}
	
	public ArrayList<String> getPrereqs(String class_id)
	{
		Statement stmt;
		ArrayList<String> pre_reqs = new ArrayList<String>();
		try {
		
			stmt = con.createStatement();
			ResultSet rs = stmt.executeQuery("SELECT * FROM Pre_req WHERE class_id = '"+class_id+"' ;");
			while(rs.next())
			{
				//System.out.println(rs.getString(2));
				pre_reqs.add(rs.getString(2));
				
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return pre_reqs;
	}
	
	public boolean hasClass(String semester, String class_id)
	{
		try {
			stmt = con.createStatement();
			ResultSet rs = stmt.executeQuery("SELECT * FROM Section WHERE class_id = '"+class_id+"'AND semester = '"+semester+"';");
			return rs.next();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return false;
	}
	
	public void enterSemester(String student_id, ArrayList<String> classes)
	{
		String value = JOptionPane.showInputDialog ("Enter semester:"); 
		//System.out.print(value);
		if((value.toUpperCase().equals("FA15")) || (value.toUpperCase().equals("SP16")))
		{
			ArrayList<String> classesToAdd = new ArrayList<String>();
			int credits = 0;
			while(true)
			{
				int rc = JOptionPane.showOptionDialog(null, "Add a class to take?", "Confirmation",
				        JOptionPane.INFORMATION_MESSAGE, 0, null, buttons1, buttons1[2]);
				if(rc == 1)
				{
					break;
				}
				
				String class_id = JOptionPane.showInputDialog ("Enter class: ");
				if(classesToAdd.contains(class_id))
				{
					JOptionPane.showMessageDialog (null,
							"Error: Duplicate class entered");
					continue;
					
				}
				boolean ret = this.hasClass(value, class_id);
				if(ret == false)
				{
					JOptionPane.showMessageDialog (null,
							"Error: Class not offered in this semester");
					continue;
					
				}
				boolean met = true;
				ArrayList<String> pre_reqs = this.getPrereqs(class_id);
				for(int i = 0; i < pre_reqs.size(); i++)
				{
					if(!classes.contains(pre_reqs.get(i)))
					{
						JOptionPane.showMessageDialog (null,
								"Error: Prerequisites not met");
						met = false;
						break;
					}
				}
				if(met && credits <= 18)
				{
					try {
						stmt = con.createStatement();
						ResultSet rs = stmt.executeQuery("SELECT * FROM Class WHERE class_id = '"+class_id+"' ;");
						if(!rs.isBeforeFirst())
						{
							JOptionPane.showMessageDialog(null, "Error: Invalid Class");
							continue;
						}
						rs.next();
						String c = rs.getString(2);
						credits += Integer.parseInt(c);
						if(credits <= 18)
						{
						classesToAdd.add(class_id);
						}
						else
						{
							credits -= Integer.parseInt(c);
							JOptionPane.showMessageDialog(null, "Error: Too Many Credits Over 18");
							continue;
						}
						//System.out.println(credits);
					} catch (SQLException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
					
				}
				
			}
			//this.showList(classesToAdd);
			String s = new String();
			for(int i = 0; i < classesToAdd.size(); i++)
			{
				s += classesToAdd.get(i) + '\n';
				
			}
			int rc = JOptionPane.showOptionDialog(null, s, "Confirm Classes",
			        JOptionPane.INFORMATION_MESSAGE, 0, null, buttons2, buttons2[0]);
			
			for(int i = 0; i < classesToAdd.size(); i++)
			{
				String sql = "INSERT INTO Enrolled " +
		                   "VALUES('"+student_id+"', '"+classesToAdd.get(i)+"', '"+1+"', '"+value+"', 'NULL', '0000-00-00')"; 
				try {
					stmt.executeUpdate(sql);
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
		else
		{
			JOptionPane.showMessageDialog(null, "Error: Invalid Semester");
			
		}

	}
    public static void main (String[] args)
    {
    Lab4B lab = new Lab4B();
    String value;
    
    
	//System.out.println("Asking for value");
	while(true)
	{
	// Get the value
	
	
	int rc = JOptionPane.showOptionDialog(null, "Continue ?", "Confirmation",
	        JOptionPane.INFORMATION_MESSAGE, 0, null, buttons1, buttons1[2]);
	
	if(rc == 1)
	{
		break;
	}
	
	value = lab.enterStudentID();
	
	try {
		boolean result = lab.enterNewStudentId(value);
		if(result == false)
		{
			continue;
		}
	} catch (InstantiationException | IllegalAccessException | ClassNotFoundException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	ArrayList<String> classes = lab.getClasses(value);
	//System.out.println(classes.size());
	//System.out.println("Got value:  " + value);

	// Display results
	JOptionPane.showMessageDialog (null,
		"You entered:  " + value);
	lab.enterSemester(value, classes);
	}
	
	return;
    }

} 
