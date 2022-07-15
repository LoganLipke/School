# Display the first and last name of the employee that has a first name 'Elvis' and is the oldest employee
SELECT first_name, last_name FROM employees WHERE first_name like 'Elvis' and birth_date=(
	SELECT MIN(birth_date) FROM employees WHERE first_name like 'Elvis');
