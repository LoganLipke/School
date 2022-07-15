# You will need two queries for this one. It can be done in one but it will require too much copying.
# Using the previous query, create a view (this will help you from copy pasting it) and display the ratio of women to men for each department. Display department and ratio rounded in 2 decimals points.
# For the view use: CREATE OR REPLACE VIEW
# Otherwise scripts will fail if a view exists
CREATE OR REPLACE VIEW gender_ratio AS 
SELECT dept_name, gender, count(gender) 
AS gender_count 
FROM employees, dept_emp NATURAL JOIN departments
WHERE dept_emp.emp_no=employees.emp_no GROUP BY dept_name, gender;

SELECT m.dept_name, ROUND(f.gender_count/m.gender_count,2) AS ratio
FROM gender_ratio AS m, gender_ratio AS f
WHERE m.gender like "M" AND f.gender like "F" AND m.dept_name like f.dept_name;
