# How many women and how many men are working on each department. Display three columns: dept name, gender and number of people working
SELECT dept_name, gender, count(gender) 
AS gender_count 
FROM employees, dept_emp NATURAL JOIN departments
WHERE dept_emp.emp_no=employees.emp_no GROUP BY dept_name, gender;

