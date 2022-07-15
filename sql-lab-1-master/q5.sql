# Display the first name, last name and rounded years worked of all employees sorted in a desceding order based on the rounded years
SELECT first_name, last_name, ROUND(TIMESTAMPDIFF(SECOND, hire_date, CURDATE()) / 31557600) AS time_worked FROM employees ORDER BY time_worked DESC;
