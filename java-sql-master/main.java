import java.sql.*;
import java.io.File;
import java.util.Scanner;

class main {

    public static void main(final String[] args) throws Exception {
        final String creds = getURLFromFile("credentials.txt");
        final Connection connect = startConnection(creds);

        if (args.length > 0 && args.length < 9) {
            if (args.length <= 5 && args.length >= 3 && args[0].equals("show")) {
                if (args[1].equals("employees")) {
                    if (args.length == 5) {
                        showDepartment(connect, args[3]+ " " +args[4]);
                    } else {
                        showDepartment(connect, args[3]);
                    }
                } else if (args[1].equals("salaries")) {
                    sum(connect);
                }
            } else if(args.length == 8 && args[0].equals("add")) {
                final String[] values = {args[2], args[3], args[4], args[5], args[6], args[7]};
                addEmp(connect, values);

            } else if (args.length == 3 && args[0].equals("delete")) {
                delEmp(connect, args[2]);
            }
        } else {
            throw new Exception("No commands entered!");
        }
        connect.close();
    }

    public static Connection startConnection(final String dbURL) {
        Connection connect = null;
        try {
            connect = DriverManager.getConnection(dbURL);
//            System.out.println("Database Connected");
        } catch (Exception e) {
            System.out.println("Connection Failed: " + e);
            e.printStackTrace();
        }
        return connect;
    }

    public static String getURLFromFile(final String fileName) {
        String url = "";
        try {
            final File file = new File(fileName);
            final Scanner readFile = new Scanner(file);
            if (readFile.hasNextLine()) {
                url = readFile.nextLine();
            }
        } catch (Exception e) {
            System.out.println("Read From File Failed: " + e);
            e.printStackTrace();
        }
        return url;
    }

    public static void showDepartment(final Connection connect, final String deptName) throws SQLException {
        System.out.println(deptName);
        try {
            final String deptEmpsQ = "SELECT emp_no, first_name, last_name from employees NATURAL JOIN departments NATURAL JOIN dept_emp where dept_name = ? ";
            final PreparedStatement deptEmps = connect.prepareStatement(deptEmpsQ);
            deptEmps.setString(1, deptName);
            final ResultSet showDeptRS = deptEmps.executeQuery();

            while (showDeptRS.next()) {
                System.out.format("%d %s %s\n", showDeptRS.getInt(1), showDeptRS.getString(2), showDeptRS.getString(3));
            }

        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static void addEmp(final Connection connect, final String[] empVals) throws SQLException {
        Statement stmt = null;
        ResultSet results = null;
        int nextEmpNo = 0;
        try {
            final String getDeptNo = "SELECT dept_no FROM departments WHERE dept_name like ?";
            final PreparedStatement departments = connect.prepareStatement(getDeptNo);
            departments.setString(1, empVals[2]);

            String deptNo;
            final ResultSet deptNoQ = departments.executeQuery();

            if (deptNoQ.next()) {
                deptNo = deptNoQ.getString(1);
            } else {
                throw new SQLException("Dept name not found");
            }

            stmt = connect.createStatement(ResultSet.TYPE_FORWARD_ONLY, ResultSet.CONCUR_READ_ONLY);
            results = stmt.executeQuery("SELECT max(emp_no) FROM employees");

            if (results.next()) {
                nextEmpNo = results.getInt(1) + 1;
            }

            final String empQ = "INSERT INTO employees (emp_no, birth_date, first_name, last_name, gender, hire_date) VALUES (?, ?, ?, ?, ?, CURRENT_DATE())";
            final PreparedStatement employees = connect.prepareStatement(empQ);
            employees.setInt(1, nextEmpNo);
            employees.setString(2, empVals[3]);
            employees.setString(3, empVals[0]);
            employees.setString(4, empVals[1]);
            employees.setString(5, empVals[4]);

            final int empRes = employees.executeUpdate();

            final String deptEmpQ = "INSERT INTO dept_emp (emp_no, dept_no, from_date, to_date) VALUES (?, ?, CURRENT_DATE(), ?)";
            final PreparedStatement deptEmp = connect.prepareStatement(deptEmpQ);
            deptEmp.setInt(1, nextEmpNo);
            deptEmp.setString(2, deptNo);
            deptEmp.setString(3, "9999-01-01");

            final int deptRes = deptEmp.executeUpdate();

            final String salaryQ = "INSERT INTO salaries (emp_no, salary, from_date, to_date) VALUES (?, ?, CURRENT_DATE(), ?)";
            final PreparedStatement salary = connect.prepareStatement(salaryQ);
            salary.setInt(1, nextEmpNo);
            salary.setInt(2, Integer.parseInt(empVals[5]));
            salary.setString(3, "9999-01-01");

            final int salRes = salary.executeUpdate();

            if (empRes > 0 && deptRes > 0 && salRes > 0) {
                System.out.format("Employee %s %s added!\n", empVals[0], empVals[1]);
            }

        } finally {
            if (stmt != null) {
                stmt.close();
            }
        }
    }

    public static void delEmp (final Connection connect, final String empID) throws SQLException {
        final Statement stmt = null;
        int empNo = 0;
        try {
            final String getEmpNameQ = "SELECT first_name, last_name FROM employees WHERE emp_no = ?";
            final PreparedStatement empName = connect.prepareStatement(getEmpNameQ);

            if (!empID.matches("[0-9]+")) {
                System.exit(1);
            }
            empNo = Integer.parseInt(empID);
            empName.setInt(1, empNo);

            String fName = "";
            String lName = "";
            final ResultSet names = empName.executeQuery();

            if (names.next()) {
                fName = names.getString(1);
                lName = names.getString(2);
            }

            final String salariesQ = "DELETE FROM salaries WHERE emp_no = ?";
            final PreparedStatement salaries = connect.prepareStatement(salariesQ);
            salaries.setInt(1, empNo);

            final int salRes = salaries.executeUpdate();

            final String deptEmpQ = "DELETE FROM dept_emp WHERE emp_no = ?";
            final PreparedStatement deptEmp = connect.prepareStatement(deptEmpQ);
            deptEmp.setInt(1, empNo);

            final int deptRes = deptEmp.executeUpdate();

            final String employeesQ = "DELETE FROM employees WHERE emp_no = ?";
            final PreparedStatement employees = connect.prepareStatement(employeesQ);
            employees.setInt(1, empNo);

            final int empRes = employees.executeUpdate();

            if (empRes > 0 && deptRes > 0 && salRes > 0) {
                System.out.format("Employee %s %s deleted!\n", fName, lName);
            } else {
                System.out.format("Employee with id %d does not exist.\n", empNo);
            }

        } finally {
            if (stmt != null) {
                stmt.close();
            }
        }
    }
    public static void sum (final Connection connect) throws SQLException {
        Statement stmt = null;
        String sum = "";
        try {
            stmt = connect.createStatement(ResultSet.TYPE_FORWARD_ONLY, ResultSet.CONCUR_READ_ONLY);
            final ResultSet results = stmt.executeQuery("SELECT sum(salary) FROM salaries WHERE to_date > CURRENT_DATE()");

            if (results.next()) {
                sum = results.getString(1);
            }
            System.out.println("$" + sum);
        } finally {
            if (stmt != null) {
                stmt.close();
            }
            }
        }
    }
