# Display the number of employees whose first name is Elvis
SELECT count(first_name) FROM employees WHERE first_name like "Elvis" GROUP by first_name;
