# Display the first_name, last_name, latest salary of the 10 higher salaried employees still actively working in the company
SELECT first_name, last_name, salary FROM salaries NATURAL JOIN employees WHERE to_date > CURRENT_DATE() ORDER BY salary DESC LIMIT 10;

